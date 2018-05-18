//these will be the c-like function

//used to compare a double with 0.000
#define NBS 0.00001
#include <iostream>

void test_number(int number)
{
    if(number==0)
        throw "zero division error!";
}

void test_number(double number)
{
    if(number-0.0<NBS||number-0.0>-NBS)
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
