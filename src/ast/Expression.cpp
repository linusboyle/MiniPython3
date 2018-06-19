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

UnaryOperation::UnaryOperation(unaryop op,std::shared_ptr<Expression> operand):Expression(1),op(op)
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
            if(result.type==RETURN_ERROR||result.type==RETURN_BREAK||result.type==RETURN_CONTINUE||result.type==RETURN_RETURN)
                return result;
            return !result.convert2bool();
        case INVERT:
            return ~result;
    }
}

BinaryOperation::BinaryOperation(binop op,std::shared_ptr<Expression> operand1,std::shared_ptr<Expression> operand2):Expression(2),op(op)
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

//BooleanOperation::BooleanOperation(boolop op,std::shared_ptr<Expression> operand1,std::shared_ptr<Expression> operand2):op(op)
//{
   //if(operand1)
       //add(operand1);
   //else
       //return;
   //if(operand2)
       //add(operand2);
//}

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


ReturnValue CompareOperation::exec()
{
   int iter_left=0,size=getChildNumber();
    while(iter_left<size-1)
    {
        ReturnValue result;
        switch (op)
        {
            case EQ:
                result=getChild(iter_left)->exec()==getChild(iter_left+1)->exec();
                break;
            case NOTEQ:
                result=getChild(iter_left)->exec()!=getChild(iter_left+1)->exec();
                break;
            case GT:
                result=getChild(iter_left)->exec()>getChild(iter_left+1)->exec();
                break;
            case LT:
                result=getChild(iter_left)->exec()<getChild(iter_left+1)->exec();
                break;
            case GTE:
                result=getChild(iter_left)->exec()>=getChild(iter_left+1)->exec();
                break;
            case LTE:
                result=getChild(iter_left)->exec()<=getChild(iter_left+1)->exec();
                break;
        }
        if(result.type==RETURN_BOOLEAN&&!result.boolean_value)
            return false;
        else if(result.type==RETURN_ERROR){
            return result;
        }
        else
            iter_left++;
    }
    return true;
}

//ReturnValue FunctionCall::exec(){
    //auto result=factory.callFunc(name,args);
    ////如果返回的是return信号的话，返回实际的值
    //if(result.type==RETURN_RETURN){
        //return *(result.true_value);
    //}
    ////否则则是result本身
    //return result;
//}

