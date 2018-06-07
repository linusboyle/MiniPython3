#include "Expression.h"
#include <cmath>

Expression::Expression(int limit):ASTNode(limit){}

Expression::Expression(Number* content):ASTNode(1)
{
    add(content);
}

Expression::Expression():ASTNode()
{
}

Expression::Expression(String* content):ASTNode(1)
{
    add(content);
}

Expression::Expression(Name* content):ASTNode(1)
{
    add(content);
}

void Expression::addChild(Expression* child)
{
    add(child);
}

ReturnValue Expression::exec()
{
    return getChild(0)->exec();
}

UnaryOperation::UnaryOperation(unaryop op,Expression* operand):Expression(1),op(op)
{
    addChild(operand);
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
        addChild(operand1);
    else
        return;
    if(operand2)
        addChild(operand2);
}

ReturnValue BinaryOperation::exec()
{
    auto value1=getChild(0)->exec();
    auto value2=getChild(1)->exec();
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
       addChild(operand1);
   else
       return;
   if(operand2)
       addChild(operand2);
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
    addChild(first);
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
//Expression::Expression(Expression* from):Input(1)
//{
    //addChild(from);
//}

//void Expression::addChild(Expression* child)
//{
    //add(child);
//}

//ReturnValue Expression::exec()
//{
    //ReturnValue result;
    //for(int i=0,n=this->getChildNumber();i!=n;i++)
    //{
        //ReturnValue value=dynamic_cast<Expression*>(getChild(i))->exec();
        //if(i==0)
            //result=result+value.integer_value;
        //else
            //result=result|value.integer_value;
    //}
    //return result;
//}

////void Xor_Expression::addChild(Expression* child)
////{
    ////add(child);
////}

//ReturnValue Xor_Expression::exec()
//{
    //ReturnValue result;
    //for(int i=0,n=getChildNumber();i!=n;i++)
    //{
        //ReturnValue value=dynamic_cast<Expression*>(getChild(i))->exec();
        //if(i==0)
            //result=result+value.integer_value;
        //else
            //result=result^value.integer_value;
    //}
    //return result;
//}

////void And_Expression::addChild(Shift_Expression* child)
////{
    ////add(child);
////}

//ReturnValue And_Expression::exec()
//{
    //ReturnValue result;
    //for(int i=0,n=getChildNumber();i!=n;i++)
    //{
        //ReturnValue value=dynamic_cast<Expression*>(getChild(i))->exec();
        //if(i==0)
            //result=result+value.integer_value;
        //else
            //result=result&value.integer_value;
    //}
    //return result;
//}

//void Shift_Expression::addChild(Operator* child)
//{
    //auto type=child->getType();
    //if(type==LEFT_SHIFT||type==RIGHT_SHIFT)
        //add(child);
    //else
    //{
        //std::cout<<"RuntimeError:cannot attach child type to Shift_Expression"<<std::endl;
        //exit(1);
    //}
//}

////void Shift_Expression::addChild(Arithmetic_Expression* child)
////{
    ////add(child);
////}

//ReturnValue Shift_Expression::exec()
//{
    //enum direction
    //{
        //LEFT,
        //RIGHT,
        //NONE,
    //}dir;
    //ReturnValue result;
    //for(int i=0,n=getChildNumber();i!=n;i++)
    //{
        //ReturnValue value=dynamic_cast<Expression*>(getChild(i))->exec();
        //switch(value.type)
        //{
            //case RETURN_OPERATOR:
            //{
                ////return ReturnValue(RETURN_ERROR);
                //if(i==0||dir!=NONE)
                    //return RETURN_ERROR;
                //switch(value.operator_value.getType())
                //{
                    //case LEFT_SHIFT:
                        //dir=LEFT;
                        //break;
                    //case RIGHT_SHIFT:
                        //dir=RIGHT;
                        //break;
                    //default:
                        //return RETURN_ERROR;
                //}
            //}
            //default:
            //{
                //if(i==0)
                    //result=result+value.integer_value;
                //else
                //{
                    //switch(dir)
                    //{
                        //case LEFT:
                            //result=result<<value.integer_value;
                            //break;
                        //case RIGHT:
                            //result=result>>value.integer_value;
                            //break;
                        //default:
                            //return RETURN_ERROR;
                    //}
                    //dir=NONE;
                //}
            //}
        //}
    //}
    //return result;
//}

//void Arithmetic_Expression::addChild(Operator* child)
//{
    //auto type=child->getType();
    //if(type==PLUS||type==SUBSTRACT)
        //add(child);
    //else
    //{
        //std::cout<<"RuntimeError:cannot attach child type to Arithmetic_Expression"<<std::endl;
        //exit(1);
    //}
//}

////void Arithmetic_Expression::addChild(Term* child)
////{
    ////add(child);
////}

//ReturnValue Arithmetic_Expression::exec()
//{
    //enum operator_type
    //{
        //PLUS,
        //SUBSTRACT,
        //NONE,
    //}type;
    //ReturnValue result(0);
    //for(int i=0,n=getChildNumber();i!=n;i++)
    //{
        //ReturnValue value=dynamic_cast<Expression*>(getChild(i))->exec();
        //switch(value.type)
        //{
            //case RETURN_OPERATOR:
            //{
                //if(i==0||type!=NONE)
                    //return RETURN_ERROR;
                //switch(value.operator_value.getType())
                //{
                    //case _py_operators_::PLUS:
                        //type=PLUS;
                        //break;
                    //case _py_operators_::SUBSTRACT:
                        //type=SUBSTRACT;
                        //break;
                    //default:
                        //return ReturnValue(RETURN_ERROR);
                        //break;
                //}
                //break;
            //}
            //default:
            //{
                //if(i==0)
                    //result=result+value;
                //else
                //{
                    //switch(type)
                    //{
                        //case PLUS:
                            //result=result+value;
                            //break;
                        //case SUBSTRACT:
                            //result=result-value;
                            //break;
                        //default:
                            //return RETURN_ERROR;
                            //break;
                    //}
                    //type=NONE;
                //}
            //}
        //}
    //}
    //return ReturnValue(result);
//}


//ReturnValue Term::exec()
//{
    //enum operator_type
    //{
        //O_MULTIPLY,
        //O_DIVIDE_INT,
        //O_DIVIDE_FLOAT,
        //O_MODULUS,
        //NONE,
    //}type;
    //ReturnValue result(0);
    //for(int i=0,n=getChildNumber();i!=n;i++)
    //{
        //ReturnValue value=dynamic_cast<Expression*>(getChild(i))->exec();
        //switch(value.type)
        //{
            //case RETURN_OPERATOR:
            //{
                //if(i==0||type!=NONE)
                    //return RETURN_ERROR;
                //switch(value.operator_value.getType())
                //{
                    //case MULTIPLY:
                        //type=O_MULTIPLY;
                        //break;
                    //case DIVIDE_INT:
                        //type=O_DIVIDE_INT;
                        //break;
                    //case DIVIDE_FLOAT:
                        //type=O_DIVIDE_FLOAT;
                        //break;
                    //case MODULUS:
                        //type=O_MODULUS;
                        //break;
                    //default:
                        //return RETURN_ERROR;
                //}
            //}
            //default:
            //{
                //if(i==0)
                    //result=result+value;
                //else
                //{
                    //switch(type)
                    //{
                        //case O_MULTIPLY:
                            //result=result*value.integer_value;
                            //break;
                        //case O_DIVIDE_INT:
                            //result=result/value.integer_value;
                            //break;
                        //case O_MODULUS:
                            //result=result%value.integer_value;
                            //break;
                        //default:
                            //return RETURN_ERROR;
                    //}
                    //type=NONE;
                //}
            //}
        //}
    //}
    //return ReturnValue(result);
//}

//Factor::Factor():Expression(2){}

//void Factor::addChild(Operator* child)
//{
    //auto type=child->getType();
    //if(type==PLUS||type==SUBSTRACT||BIT_NOT)
    //{
        //if(!init_as_power)
        //{
            //add(child);
            //init_as_factor=true;
        //}
        //else
        //{
            //std::cout<<"RuntimeError:Not compatible init for Factor"<<std::endl;
            //exit(1);
        //}
    //}
    //else
    //{
        //std::cout<<"RuntimeError:cannot attach child type to Arithmetic_Expression"<<std::endl;
        //exit(1);
    //}
//}

//void Factor::addChild(Power* child)
//{
    //if(init_as_factor)
    //{
        //std::cout<<"RuntimeError:Not compatible init for Factor"<<std::endl;
        //exit(1);
    //}
    //else
    //{
        //add(child);
        //init_as_power=true;
    //}
//}

//void Factor::addChild(Factor* child)
//{
    //if(init_as_factor)
    //{
        //add(child);
    //}
    //else
    //{
        //std::cout<<"RuntimeError:Not compatible init for Factor"<<std::endl;
        //exit(1);
    //}
//}

//ReturnValue Factor::exec()
//{
    //ReturnValue value=dynamic_cast<Expression*>(getChild(0))->exec();
    //if(value.type==RETURN_OPERATOR)
    //{
        //auto result=dynamic_cast<Expression*>(getChild(1))->exec();
        //switch(value.operator_value.getType())
        //{
            //case PLUS:
                //return result;
            //case SUBSTRACT:
                //return ReturnValue(0)-result;
            //case BIT_NOT:
                //return ~result;
            //default:
                //return RETURN_ERROR;
        //}
    //}
    //else
    //{
        //return value;
    //}
//}

//Factor::Factor(Power* target)
//{
    //this->addChild(target);
//}

//Power::Power():Expression(2)
//{
//}

//void Power::addChild(Factor* child)
//{
    //if(getChildNumber()!=1)
    //{
        //std::cout<<"RuntimeError:cannot attach child type to power"<<std::endl;
        //exit(1);
    //}
    //add(child);
//}

//void Power::addChild(Atom_Expression* child)
//{
    //if(getChildNumber()!=0)
    //{
        //std::cout<<"RuntimeError:cannot attach child type to power"<<std::endl;
        //exit(1);
    //}
    //add(child);
//}

//ReturnValue Power::exec()
//{
    ////TODO
    ////use std power func here
    //if(getChildNumber()==2)
    //{
        //auto result1=dynamic_cast<Expression*>(getChild(0))->exec();
        //auto result2=dynamic_cast<Expression*>(getChild(1))->exec();
        //if(result1.type==RETURN_INT&&result2.type==RETURN_INT)
            //return pow(result1.integer_value,result2.integer_value);
        //if(result1.type==RETURN_INT&&result2.type==RETURN_FLOAT)
            //return pow(result1.integer_value,result2.double_value);
        //if(result1.type==RETURN_FLOAT&&result2.type==RETURN_INT)
            //return pow(result1.double_value,result2.integer_value);
        //if(result1.type==RETURN_FLOAT&&result2.type==RETURN_FLOAT)
            //return pow(result1.double_value,result2.double_value);
        //return RETURN_ERROR;
    //}
    //else
        //return dynamic_cast<Expression*>(getChild(0))->exec();
//}
