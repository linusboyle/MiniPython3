/*
Simple Python Interpreter implementation by cpp
Copyright (C) 2018 LCC,ZZH,HZL,CYH

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses.
*/
#include "Statement.h"
#include "Function.h"
#include "AstFactory.h"
#include <cmath>

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

Expression_Statement::Expression_Statement(std::shared_ptr<Expression> content):Statement(1)
{
    add(content);
}

Expression_Statement::~Expression_Statement()
{
}

//Assign_Statement::Assign_Statement(const std::string& id,std::shared_ptr<Expression> value):Statement(1)
//{
    //target=new Name(id);
    //if(value){
        //add(value);
    //}
    //else{
        ////actually an error
        //add(std::make_shared<NameConstant>(NONE));
    //}
//}

//void Assign_Statement::setValue(std::shared_ptr<Expression> value)
//{
    //add(value);
//}

//void Assign_Statement::addTarget(std::string target)
//{
    //targetlist[index]=new Name(target);
    //index++;
//}

ReturnValue Assign_Statement::exec()
{
    ReturnValue value=getChild(0)->exec();//expr
    if(value.type==RETURN_ERROR)
        return RETURN_ERROR;
    else{
        for(int i=1,n=getChildNumber();i!=n;++i){
            //no check for the cast?
            std::dynamic_pointer_cast<Name>(getChild(i))->setValue(value);
        }
        return RETURN_NONETYPE;
    }
}

Assign_Statement::~Assign_Statement()
{
}

AugAssign_Statement::AugAssign_Statement(binop op,const std::string& id,std::shared_ptr<Expression> value):AugAssign_Statement(op,std::make_shared<Name>(id),value){}

AugAssign_Statement::AugAssign_Statement(binop op,std::shared_ptr<Name> target,std::shared_ptr<Expression> value):Statement(),op(op)
{
    add(target);
    if(value){
        add(value);
    }
    else{
        add(std::make_shared<NameConstant>(NONE));
    }
}

//void AugAssign_Statement::setValue(std::shared_ptr<Expression> child)
//{
    //add(child);
//}

//void AugAssign_Statement::addTarget(std::string id)
//{
    //target=new Name(id);
//}

ReturnValue AugAssign_Statement::exec()
{
    auto target=std::dynamic_pointer_cast<Name>(getChild(0));
    auto right=getChild(1)->exec();
    auto left=target->exec();

    ReturnValue tmp=RETURN_NONETYPE;

    //NOTE
    //if any error occurs,the assignment operation will not be carried out~
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
            //to tedious here
            if(left.type==RETURN_INT&&right.type==RETURN_INT)
                target->setValue(pow(left.integer_value,right.integer_value));
            else if(left.type==RETURN_FLOAT&&right.type==RETURN_INT)
                target->setValue(pow(left.double_value,right.integer_value));
            else if(left.type==RETURN_INT&&right.type==RETURN_FLOAT)
                target->setValue(pow(left.integer_value,right.double_value));
            else if(left.type==RETURN_FLOAT&&right.type==RETURN_FLOAT)
                target->setValue(pow(left.double_value,right.double_value));
            if(target==nullptr||target->exec().type==RETURN_ERROR){
                target->setValue(left);
                return RETURN_ERROR;
            }
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
}

//void Delete_Statement::addTarget(std::string target) {
    //this->target.push_back(target);
//}


ReturnValue Delete_Statement::exec() {
    for(int i=0,n=getChildNumber();i!=n;++i){
        std::dynamic_pointer_cast<Name>(getChild(i))->deleteRecord();
    }
    return RETURN_NONETYPE;
}

If_Statement::If_Statement(std::shared_ptr<Expression> test,std::shared_ptr<Suite> body,std::shared_ptr<Suite> orelse):Statement(3){
    add(test);
    add(body);
    if(orelse)
        add(orelse);
}

ReturnValue If_Statement::exec(){
    auto test_result=getChild(0)->exec();
    switch(test_result.type){
        case RETURN_ERROR:
        case RETURN_BREAK:
        case RETURN_CONTINUE:
        case RETURN_RETURN:
            return test_result;
        default:
            break;
    }
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

//中文注释here：
//在多层嵌套的分支循环语句之中需要保证
//在第一次出现break或者continue时停止
//并且将此信号向上传递
//如果没有while或者for接受并处理这语句
//应该让顶层的astfactory抛出错误
//IDEA
//当一个语句块在执行的时候，应该创建一个local scope吗？
ReturnValue Suite::exec() {
    for(int i=0,n=getChildNumber();i!=n;++i) {
        ReturnValue tmp1=getChild(i)->exec();
        switch(tmp1.type){
            case RETURN_ERROR:
            case RETURN_BREAK:
            case RETURN_RETURN:
            case RETURN_CONTINUE:
                return tmp1;
            default:
                break;
        }
    }
    //其余情况均被忽略而同一化
    return RETURN_NONETYPE;
}

While_Statement::While_Statement(std::shared_ptr<Expression> test,std::shared_ptr<Suite> body,std::shared_ptr<Suite> orelse):Statement(3){
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


ReturnValue FunctionDefinition_Statement::exec(){
    factory.addFunction(func);

    //no check of executing result
    return RETURN_NONETYPE;
}

FunctionDefinition_Statement::FunctionDefinition_Statement(const std::shared_ptr<Function>& func):func(func){
}

FunctionDefinition_Statement::FunctionDefinition_Statement(const std::string& id,const std::shared_ptr<Suite>& body,const std::vector<std::shared_ptr<Argument>>& args){
    func=std::make_shared<Function>(id,body);
    for(int i=0,n=args.size();i!=n;++i){
        func->addArg(args[i]);
    }
}

Return_Statement::Return_Statement(const std::shared_ptr<Expression>& value){
    add(value);
}

//return nothing,just stop the function
Return_Statement::Return_Statement(){
    add(std::make_shared<NameConstant>(NONE));
}

ReturnValue Return_Statement::exec(){
    ReturnValue tmp=getChild(0)->exec();
    return ReturnValue(RETURN_RETURN,tmp);
}

Print_Statement::Print_Statement(std::shared_ptr<Expression> target){
        this->add(target);
}

ReturnValue Print_Statement::exec() {
    std::cout<<getChild(0)->exec();
    std::cout<<std::endl;//更改休止符比较困难，就让它是换行吧
    return RETURN_NONETYPE;
}

For_Statement::For_Statement(std::shared_ptr<Name> target,std::shared_ptr<Expression> range,std::shared_ptr<Suite> body,std::shared_ptr<Suite> orelse){
    add(target);
    add(range);
    add(body);
    if(orelse){
        add(orelse);
    }
}

ReturnValue For_Statement::exec(){
    auto target=getChild(0);
    auto range=getChild(1)->exec();
    auto body=getChild(2);
    switch(range.type){
        case RETURN_TUPLE:
        case RETURN_LIST:
            {
                int n=range.container->size();
                for(int i=0;i!=n;++i){
                    std::dynamic_pointer_cast<Name>(target)->setValue(range.container->at(i));
                    auto result=body->exec();
                    if(result.type==RETURN_BREAK)
                        break;
                    else if(result.type==RETURN_ERROR||result.type==RETURN_RETURN)
                        return result;

                    std::dynamic_pointer_cast<Name>(target)->deleteRecord();
                }
            }
            break;
        default:
            std::cerr<<"RuntimeError:the target cannot be iterated"<<std::endl;
            exit(1);
    }
    //if defined else block
    if(getChildNumber()==4)
        return getChild(3)->exec();
    else
        return RETURN_NONETYPE;
}
