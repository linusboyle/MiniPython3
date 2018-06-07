//these will be the c-like function
#ifndef FUNC_H
#define FUNC_H

#define NBS 0.00001
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
