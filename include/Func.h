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
//these will be the c-like function
#ifndef FUNC_H
#define FUNC_H

#define NBS 0.000001
#include <iostream>

//used to compare a double with 0.000...
bool _equal_float(const double& operand1,const double& operand2)
{
    auto tmp=operand1-operand2;
    return tmp<NBS && tmp>-NBS;
}

void test_number(int number)
{
    if(number==0)
        throw "zero division error!";
}

void test_number(double number)
{
    if(_equal_float(number,0.0))
        throw "zero division error!";
}

void test_zero(int number)
{
    try
    {
        test_number(number);
    }
    catch(const char* msg)
    {
        std::cerr<<msg<<std::endl;
        exit(1);
    }
}

void test_zero(double number)
{
    try
    {
        test_number(number);
    }
    catch(const char* msg)
    {
        std::cerr<<msg<<std::endl;
        exit(1);
    }
}
#endif //FUNC_H
