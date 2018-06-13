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
#include "Func.h"
#include <iostream>

ReturnValue::ReturnValue(_return_type_ T,ReturnValue* value):type(T)
{
    if(T==RETURN_RETURN)
    {
        if(value==nullptr){
            static ReturnValue holder=RETURN_NONETYPE;
            true_value=&holder;
        }
        else
            true_value=value;
    }
}

//IDEA
//maybe use init table?
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

//may seem tedious...
inline bool _same_type(const ReturnValue& operand1,const ReturnValue& operand2)
{
    return operand1.type==operand2.type;
}

//NOTE
//dangerous if it is not boolean value
//It will be used when carrying out operation to boolean
//such as True+False
inline int ReturnValue::convert2int() const
{
    return boolean_value?1:0;
    //if(boolean_value)
        //return 1;
    //else
        //return 0;
}

bool ReturnValue::convert2bool() const
{
    switch(type){
        case RETURN_BOOLEAN:
            return boolean_value;
        case RETURN_INT:
            return integer_value==0? false :true;
        case RETURN_STRING:
            //empty is false
            return !string_value.empty();
        case RETURN_FLOAT:
            return _equal_float(double_value,0.0)?false:true;
        default:
            std::cerr<<"RuntimeError:Expected test,but provided non-comparable value;aborting"<<std::endl;
            exit(1);
    }
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

//FIXME
//I forbid floating point modulus here

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
            case RETURN_BOOLEAN:
                return operand1.convert2int()<operand2.convert2int();
            default:
                return RETURN_ERROR;
        }
    }
    else
        return RETURN_ERROR;
}

ReturnValue operator>(const ReturnValue& operand1,const ReturnValue& operand2)
{
    //NOTE
    //no comparison between int and float,and etc
    if(_same_type(operand1,operand2))
    {
        switch(operand1.type)
        {
            case RETURN_INT:
                return operand1.integer_value>operand2.integer_value;
            case RETURN_STRING:
                return operand1.string_value>operand2.string_value;
            case RETURN_FLOAT:
                return operand1.double_value>operand2.double_value;
            case RETURN_BOOLEAN:
                return operand1.convert2int()>operand2.convert2int();
            default:
                return RETURN_ERROR;
        }
    }
    else
        return RETURN_ERROR;
}

ReturnValue operator==(const ReturnValue& operand1,const ReturnValue& operand2)
{
    //NOTE
    //no comparison between int and float,and etc
    if(_same_type(operand1,operand2))
    {
        switch(operand1.type)
        {
            case RETURN_INT:
                return operand1.integer_value==operand2.integer_value;
            case RETURN_STRING:
                return operand1.string_value==operand2.string_value;
            case RETURN_FLOAT:
                return _equal_float(operand1.double_value,operand2.double_value);
            case RETURN_BOOLEAN:
                return operand1.convert2int()==operand2.convert2int();
            default:
                return RETURN_ERROR;
        }
    }
    else
        return RETURN_ERROR;
}


ReturnValue operator<=(const ReturnValue& operand1,const ReturnValue& operand2)
{
    auto tmp1=operand1<operand2;
    auto tmp2=operand1==operand2;
    return tmp1.boolean_value||tmp2.boolean_value;
}

ReturnValue operator>=(const ReturnValue& operand1,const ReturnValue& operand2)
{
    auto tmp1=operand1>operand2;
    auto tmp2=operand1==operand2;
    return tmp1.boolean_value||tmp2.boolean_value;
}

ReturnValue operator!=(const ReturnValue& operand1,const ReturnValue& operand2)
{
    auto tmp=operand1==operand2;
    return !(tmp.boolean_value);
}
