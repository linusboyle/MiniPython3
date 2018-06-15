#include "Expression.h"
#include <cmath>
#include "AstFactory.h"

Expression::Expression(int limit):ASTNode(limit){}

Expression::Expression():ASTNode()
{
}

ReturnValue Expression::exec()
{
    return getChild(0)->exec();
}

UnaryOperation::UnaryOperation(unaryop op,Expression* operand):Expression(1),op(op)
{
    add(operand);
}

ReturnValue UnaryOperation::exec()
{
    auto result=getChild(0)->exec();
    switch(op)
    {
        case UADD:
            return result;
        case USUB:
            if(result.type==RETURN_FLOAT)
                return ReturnValue(0.0)-result;
            return 0-result;
        case NOT:
            if(result.type==RETURN_ERROR||result.type==RETURN_NONETYPE)
                return result;
            return !result.convert2bool();
        case INVERT:
            return ~result;
    }
}

BinaryOperation::BinaryOperation(binop op,Expression* operand1,Expression* operand2):Expression(2),op(op)
{
    if(operand1)
        add(operand1);
    else
        return;
    if(operand2)
        add(operand2);
}

ReturnValue BinaryOperation::exec()
{
    auto loperand=getChild(0),roperand=getChild(1);
    if(!(loperand&&roperand)){
        return RETURN_ERROR;
    }

    auto value1=loperand->exec();
    auto value2=roperand->exec();

    switch(op)
    {
        case ADD:
            return value1+value2;
        case SUB:
            return value1-value2;
        case MULT:
            return value1*value2;
        case DIV:
            return value1/value2;
        case FLOORDIV:
        {
            auto tmp=value1/value2;
            if(tmp.type==RETURN_FLOAT)
                return floor(tmp.double_value);
            else
                return tmp;
        }
        case MOD:
            return value1%value2;
        case POW:
            if(value1.type==RETURN_INT&&value2.type==RETURN_INT)
                return pow(value1.integer_value,value2.integer_value);
            if(value1.type==RETURN_FLOAT&&value2.type==RETURN_INT)
                return pow(value1.double_value,value2.integer_value);
            if(value1.type==RETURN_INT&&value2.type==RETURN_FLOAT)
                return pow(value1.integer_value,value2.double_value);
            if(value1.type==RETURN_FLOAT&&value2.type==RETURN_FLOAT)
                return pow(value1.double_value,value2.double_value);
            return RETURN_ERROR;
        case LSHIFT:
            return value1<<value2;
        case RSHIFT:
            return value1>>value2;
        case BITOR:
            return value1|value2;
        case BITAND:
            return value1&value2;
        case BITXOR:
            return value1^value2;
    }
}

BooleanOperation::BooleanOperation(boolop op,Expression* operand1,Expression* operand2):op(op)
{
   if(operand1)
       add(operand1);
   else
       return;
   if(operand2)
       add(operand2);
}

ReturnValue BooleanOperation::exec()
{
    switch(op)
    {
        //NOTE
        //OR return the first true expression
        //if none,return the last
        case OR:
            for(int i=0,n=getChildNumber();i!=n;++i)
            {
                auto tmp=getChild(i)->exec();
                if((tmp.convert2bool())||i==n-1)
                    return tmp;
            }
            //should not reach here...
            return RETURN_ERROR;
        case AND:
            //likewise
            //but return the first false expression
            for(int i=0,n=getChildNumber();i!=n;++i)
            {
                auto tmp=getChild(i)->exec();
                if(!tmp.convert2bool()||i==n-1)
                    return tmp;
            }
            return RETURN_ERROR;
    }
}

CompareOperation::CompareOperation(int size,Expression* first):Expression(size+1),size(size)
{
    op=new compareop[size];
    add(first);
}

//void CompareOperation::addChild(Expression* child)
//{
    //add(child);
//}

void CompareOperation::addOperator(compareop _operator)
{
    op[index]=_operator;
    index++;
}

ReturnValue CompareOperation::exec()
{
    int iter_left=0;
    int iter_right=1;
    while(iter_right<=size)
    {
        ReturnValue result;
        switch (op[iter_left])
        {
            case EQ:
                result=getChild(iter_left)->exec()==getChild(iter_right)->exec();
                if(!result.boolean_value)
                    return false;
                break;
            case NOTEQ:
                result=getChild(iter_left)->exec()!=getChild(iter_right)->exec();
                if(!result.boolean_value)
                    return false;
                break;
            case GT:
                result=getChild(iter_left)->exec()>getChild(iter_right)->exec();
                if(!result.boolean_value)
                    return false;
                break;
            case LT:
                result=getChild(iter_left)->exec()<getChild(iter_right)->exec();
                if(!result.boolean_value)
                    return false;
                break;
            case GTE:
                result=getChild(iter_left)->exec()>=getChild(iter_right)->exec();
                if(!result.boolean_value)
                    return false;
                break;
            case LTE:
                result=getChild(iter_left)->exec()<=getChild(iter_right)->exec();
                if(!result.boolean_value)
                    return false;
                break;
        }
        iter_right++;
        iter_left++;
    }
    return true;
}

FunctionCall::FunctionCall(const std::string& id,std::list<ReturnValue>* args):name(id),args(args){}

ReturnValue FunctionCall::exec(){
    auto result=factory.callFunc(name,args);
    //如果返回的是return信号的话，返回实际的值
    if(result.type==RETURN_RETURN){
        return *(result.true_value);
    }
    //否则则是result本身
    return result;
}

