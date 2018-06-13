#include "Statement.h"
#include <cmath>
#include "Function.h"
#include "AstFactory.h"

AstFactory& instance=AstFactory::getinstance();

Statement::~Statement()
{
}

ReturnValue Pass_Statement::exec()
{
    //do nothing special
    return RETURN_NONETYPE;
}

ReturnValue Expression_Statement::exec()
{
    return getChild(0)->exec();
}

Expression_Statement::Expression_Statement(Expression* content):Statement(1)
{
    add(content);
}

Expression_Statement::~Expression_Statement()
{

}

Assign_Statement::Assign_Statement(int size):Statement(1)
{
    targetsize=size;
    targetlist=new Name*[size];
}

void Assign_Statement::setValue(Expression* value)
{
    add(value);
}

void Assign_Statement::addTarget(std::string target)
{
    targetlist[index]=new Name(target);
    index++;
}

ReturnValue Assign_Statement::exec()
{
    ReturnValue value=getChild(0)->exec();
    if(value.type==RETURN_ERROR)
        return RETURN_ERROR;
    for(int i=0;i!=targetsize;++i)
        targetlist[i]->setValue(value);
    return RETURN_NONETYPE;
}

Assign_Statement::~Assign_Statement()
{
    for(int i=0;i!=targetsize;++i)
        delete targetlist[i];
    delete [] targetlist;
}

AugAssign_Statement::AugAssign_Statement(binop op):Statement(1),op(op)
{
}

void AugAssign_Statement::setValue(Expression* child)
{
    add(child);
}

void AugAssign_Statement::addTarget(std::string id)
{
    target=new Name(id);
}

ReturnValue AugAssign_Statement::exec()
{
    auto right=getChild(0)->exec();
    auto left=target->exec();

    ReturnValue tmp;

    //NOTE
    //if error occurs,the assignment operation will not be carried out~
    switch(op)
    {
        case ADD:
            tmp=left+right;
            if(tmp.type==RETURN_ERROR)
                return RETURN_ERROR;
            target->setValue(tmp);
            break;
        case SUB:
            tmp=left-right;
            if(tmp.type==RETURN_ERROR)
                return RETURN_ERROR;
            target->setValue(tmp);
            break;
        case MULT:
            tmp=left*right;
            if(tmp.type==RETURN_ERROR)
                return RETURN_ERROR;
            target->setValue(tmp);
            break;
        case DIV:
            tmp=left/right;
            if(tmp.type==RETURN_ERROR)
                return RETURN_ERROR;
            target->setValue(tmp);
            break;
        case FLOORDIV:
            tmp=left/right;
            if(tmp.type==RETURN_FLOAT)
                target->setValue(std::floor(tmp.double_value));
            else
                if(tmp.type==RETURN_ERROR)
                     return RETURN_ERROR;
                else
                     target->setValue(tmp);
            break;
        case MOD:
            tmp=left%right;
            if(tmp.type==RETURN_ERROR)
                return RETURN_ERROR;
            target->setValue(tmp);
            break;
        case POW:
            if(left.type==RETURN_INT&&right.type==RETURN_INT)
                target->setValue(pow(left.integer_value,right.integer_value));
            else if(left.type==RETURN_FLOAT&&right.type==RETURN_INT)
                target->setValue(pow(left.double_value,right.integer_value));
            else if(left.type==RETURN_INT&&right.type==RETURN_FLOAT)
                target->setValue(pow(left.integer_value,right.double_value));
            else if(left.type==RETURN_FLOAT&&right.type==RETURN_FLOAT)
                target->setValue(pow(left.double_value,right.double_value));
            if(target==nullptr||target->exec().type==RETURN_ERROR)
                return RETURN_ERROR;
            break;
        case LSHIFT:
            tmp=left<<right;
            if(tmp.type==RETURN_ERROR)
                return RETURN_ERROR;
            target->setValue(tmp);
            break;
        case RSHIFT:
            tmp=left>>right;
            if(tmp.type==RETURN_ERROR)
                return RETURN_ERROR;
            target->setValue(tmp);
            break;
        case BITOR:
            tmp=left|right;
            if(tmp.type==RETURN_ERROR)
                return RETURN_ERROR;
            target->setValue(tmp);
            break;
        case BITAND:
            tmp=left&right;
            if(tmp.type==RETURN_ERROR)
                return RETURN_ERROR;
            target->setValue(tmp);
            break;
        case BITXOR:
            tmp=left^right;
            if(tmp.type==RETURN_ERROR)
                return RETURN_ERROR;
            target->setValue(tmp);
            break;
    }
    return RETURN_NONETYPE;
}

AugAssign_Statement::~AugAssign_Statement()
{
    delete target;
}

void Delete_Statement::addTarget(std::string target) {
    this->target.push_back(target);
}

ReturnValue Delete_Statement::exec() {
    for(int i=0,n=target.size();i!=n;++i) {
        target[i].deleteRecord();
    }
    return RETURN_NONETYPE;
}

If_Statement::If_Statement(Expression* test,Suite* body,Suite* orelse):Statement(3){
    add(test);
    add(body);
    if(orelse)
        add(orelse);
}

ReturnValue If_Statement::exec(){
    auto test_result=getChild(0)->exec();
    if(test_result.convert2bool()){
        return getChild(1)->exec();
    }
    else{
        if(getChildNumber()==3)
            return getChild(2)->exec();
        else
            return RETURN_NONETYPE;
    }
}

Suite::Suite(){};

void Suite::addChild(Statement* component) {
    add(component);
}

//中文注释here：
//在多层嵌套的分支循环语句之中需要保证
//在第一次出现break或者continue时停止
//并且将此信号向上传递
//如果没有while或者for接受并处理这语句
//应该让顶层的astfactory抛出错误
ReturnValue Suite::exec() {
    for(int i=0,n=getChildNumber();i!=n;++i) {
        auto tmp=getChild(i)->exec();
        if(tmp.type==RETURN_ERROR||tmp.type==RETURN_BREAK||tmp.type==RETURN_CONTINUE||RETURN_RETURN){
            return tmp;
        }
    }
    //其余情况均被忽略而同一化
    return RETURN_NONETYPE;
}

While_Statement::While_Statement(Expression* test,Suite* body,Suite* orelse):Statement(3){
    add(test);
    add(body);
    if(orelse){
        add(orelse);
    }
}

//NOTE
//I think the control flow here need debug
ReturnValue While_Statement::exec(){
    auto test=getChild(0);
    auto body=getChild(1);
    while(test->exec().convert2bool())
    {
        auto indicator=body->exec();
        switch(indicator.type){
            case RETURN_BREAK:
                //just return whole loop
                return RETURN_NONETYPE;
            case RETURN_CONTINUE:
                //as it says so
                continue;
            case RETURN_ERROR:
                return RETURN_ERROR;
            case RETURN_RETURN:
                return RETURN_RETURN;
            default:
                continue;
        }
    }
    if(getChildNumber()==3)
        return getChild(2)->exec();
    else
        return RETURN_NONETYPE;
}

Break_Statement::Break_Statement():Statement(0){};

Continue_Statement::Continue_Statement():Statement(0){};

ReturnValue Break_Statement::exec(){
    return RETURN_BREAK;
}

ReturnValue Continue_Statement::exec(){
    return RETURN_CONTINUE;
}

FunctionDefinition_Statement::FunctionDefinition_Statement(std::string& _name,int count,std::string* args_name,Suite* _body):name(_name),argnames(args_name),body(_body),arg_count(count){}

ReturnValue FunctionDefinition_Statement::exec(){
    Function* newfunc=new Function(name,arg_count,argnames,body);
    instance.addFunction(newfunc);

    //no check of executing result
    return RETURN_NONETYPE;
}

Return_Statement::Return_Statement(ReturnValue& value):result(&value){}

//return nothing,just stop the function
Return_Statement::Return_Statement(){
    result=nullptr;
}

ReturnValue Return_Statement::exec(){
    return ReturnValue(RETURN_RETURN,result);
}
