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

#include "ReturnValue.h"
#include <iostream>
#include "Func.h"

ReturnValue::ReturnValue(_return_type_ T)
{
    //default to nonetype
    type=T;
}

ReturnValue::ReturnValue(int integer_value):integer_value(integer_value)
{
    type=RETURN_INT;
}

ReturnValue::ReturnValue(std::string string_value):string_value(string_value)
{
    type=RETURN_STRING;
}

ReturnValue::ReturnValue(double value):double_value(value)
{
    type=RETURN_FLOAT;
}

ReturnValue::ReturnValue(bool value):boolean_value(value)
{
    type=RETURN_BOOLEAN;
}

//ReturnValue::ReturnValue(Keyword& key):keyword_value(key)
//{
    //type=RETURN_KEYWORD;
//}

//ReturnValue::ReturnValue(Operator& _operator):operator_value(_operator)
//{
    //type=RETURN_OPERATOR;
//}

//may seem tedious...
inline bool _same_type(const ReturnValue& operand1,const ReturnValue& operand2)
{
    return operand1.type==operand2.type;
}

int ReturnValue::convert2int() const
{
    if(boolean_value)
        return 1;
    else
        return 0;
}

ReturnValue operator+ (const ReturnValue& operand1,const ReturnValue& operand2)
{
    if(_same_type(operand1,operand2))
    {
        switch(operand1.type)
        {
            case RETURN_INT:
                return ReturnValue(operand1.integer_value+operand2.integer_value);
            case RETURN_FLOAT:
                return ReturnValue(operand1.double_value+operand2.double_value);
            case RETURN_STRING:
                return ReturnValue(operand1.string_value+operand2.string_value);
            case RETURN_BOOLEAN:
                return operand1.convert2int()+operand2.convert2int();
            default:
                return RETURN_ERROR;
        }
    }
    else
        return RETURN_ERROR;
}

ReturnValue::~ReturnValue(){}

ReturnValue operator- (const ReturnValue& operand1,const ReturnValue& operand2)
{
    if(_same_type(operand1,operand2))
    {
        switch(operand1.type)
        {
            case RETURN_INT:
                return ReturnValue(operand1.integer_value-operand2.integer_value);
            case RETURN_FLOAT:
                return ReturnValue(operand1.double_value-operand2.double_value);
            case RETURN_BOOLEAN:
                return operand1.convert2int()-operand2.convert2int();
            default:
                return RETURN_ERROR;
        }
    }
    else
        return RETURN_ERROR;
}

ReturnValue operator* (const ReturnValue& operand1,const ReturnValue& operand2)
{
    if(_same_type(operand1,operand2))
    {
        switch(operand1.type)
        {
            case RETURN_INT:
                return ReturnValue(operand1.integer_value*operand2.integer_value);
            case RETURN_FLOAT:
                return ReturnValue(operand1.double_value*operand2.double_value);
            case RETURN_BOOLEAN:
                return operand1.convert2int()*operand2.convert2int();
            default:
                return RETURN_ERROR;
        }
    }
    else
        return RETURN_ERROR;
}

//FIXME
//I dont permit double/int here
//think about it
ReturnValue operator/ (const ReturnValue& operand1,const ReturnValue& operand2)
{
    if(_same_type(operand1,operand2))
    {
        switch(operand1.type)
        {
            case RETURN_INT:
                test_zero(operand2.integer_value);
                return ReturnValue(operand1.integer_value/operand2.integer_value);
            case RETURN_FLOAT:
                test_zero(operand2.double_value);
                return ReturnValue(operand1.double_value/operand2.double_value);
            case RETURN_BOOLEAN:
                test_zero(operand2.convert2int());
                return operand1.convert2int()/operand2.convert2int();
            default:
                return RETURN_ERROR;
        }
    }
    else
        return RETURN_ERROR;
}

ReturnValue operator| (const ReturnValue& operand1,const ReturnValue& operand2)
{
    if(_same_type(operand1,operand2))
    {
        switch(operand1.type)
        {
            case RETURN_INT:
                return ReturnValue(operand1.integer_value|operand2.integer_value);
            case RETURN_BOOLEAN:
                return operand1.convert2int()|operand2.convert2int();
            default:
                return RETURN_ERROR;
        }
    }
    else
        return RETURN_ERROR;
}

ReturnValue operator& (const ReturnValue& operand1,const ReturnValue& operand2)
{
    if(_same_type(operand1,operand2))
    {
        switch(operand1.type)
        {
            case RETURN_INT:
                return ReturnValue(operand1.integer_value&operand2.integer_value);
            case RETURN_BOOLEAN:
                return operand1.convert2int()&operand2.convert2int();
            default:
                return RETURN_ERROR;
        }
    }
    else
        return RETURN_ERROR;
}

ReturnValue operator^ (const ReturnValue& operand1,const ReturnValue& operand2)
{
    if(_same_type(operand1,operand2))
    {
        switch(operand1.type)
        {
            case RETURN_INT:
                return ReturnValue(operand1.integer_value^operand2.integer_value);
            case RETURN_BOOLEAN:
                return operand1.convert2int()^operand2.convert2int();
            default:
                return RETURN_ERROR;
        }
    }
    else
        return RETURN_ERROR;
}

//NOTE
//I forbid floating point modulus here
//FIXME
ReturnValue operator% (const ReturnValue& operand1,const ReturnValue& operand2)
{
    if(_same_type(operand1,operand2))
    {
        switch(operand1.type)
        {
            case RETURN_INT:
                test_zero(operand2.integer_value);
                return ReturnValue(operand1.integer_value%operand2.integer_value);
            case RETURN_BOOLEAN:
                test_zero(operand2.convert2int());
                return operand1.convert2int()%operand2.convert2int();
            default:
                return RETURN_ERROR;
        }
    }
    else
        return RETURN_ERROR;
}

ReturnValue operator~(const ReturnValue& operand)
{
    switch(operand.type)
    {
        case RETURN_INT:
            return ~operand.integer_value;
        case RETURN_BOOLEAN:
            return ~operand.convert2int();
        default:
            return RETURN_ERROR;
    }
}

ReturnValue operator<<(const ReturnValue& operand1,const ReturnValue& operand2)
{
    if(operand1.type==RETURN_INT&&operand2.type==RETURN_INT)
        return operand1.integer_value<<operand2.integer_value;
    return RETURN_ERROR;
}

ReturnValue operator>>(const ReturnValue& operand1,const ReturnValue& operand2)
{
    if(operand1.type==RETURN_INT&&operand2.type==RETURN_INT)
        return operand1.integer_value>>operand2.integer_value;
    return RETURN_ERROR;
}

ReturnValue operator<(const ReturnValue& operand1,const ReturnValue& operand2)
{
    //NOTE
    //no comparison between int and float,and etc
    if(_same_type(operand1,operand2))
    {
        switch(operand1.type)
        {
            case RETURN_INT:
                return operand1.integer_value<operand2.integer_value;
            case RETURN_STRING:
                return operand1.string_value<operand2.string_value;
            case RETURN_FLOAT:
                return operand1.double_value<operand2.double_value;
        }
    }
    else
        return RETURN_ERROR;
}

bool ReturnValue::checkfalse() const
{
    if(type==RETURN_NONETYPE)
        return true;
    if(type==RETURN_INT&&integer_value==0)
        return true;
    if(type==RETURN_STRING&&string_value.empty())
        return true;
    return false;
}
//bool ReturnValue::convertBool()
//{
    //if(type==RETURN_INT)
    //{
        //if(integer_value!=0)
            //return true;
        //return false;
    //}
    //else
    //{
        //std::cout<<"Fatal RuntimeError:Wrong notation for boolean value"<<std::endl;
        //exit(1);
    //}
//}


//Keyword::Keyword(enum _py_keywords_ type):type(type){}

//_py_keywords_ Keyword::getType()
//{
    //return type;
//}

//ReturnValue Keyword::exec()
//{
    //return ReturnValue(*this);
//}

//Operator::Operator(enum _py_operators_ type):type(type){}

////ReturnValue Operator::exec()
////{
    ////return ReturnValue(*this);
////}

//_py_operators_ Operator::getType()
//{
    //return type;
//}
