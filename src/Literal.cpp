#include "Literal.h"
#include "AstFactory.h"

Number::Number(int value):Expression(0),int_value(value),type(INT){}

Number::Number(double value):Expression(0),double_value(value),type(FLOATING){}

number_type Number::getType()
{
    return type;
}

int Number::getInt()
{
    return int_value;
}

double Number::getFloat()
{
    return double_value;
}

ReturnValue Number::exec()
{
    if(type==INT)
        return getInt();
    return getFloat();
}

String::String(std::string value):Expression(0),literal(value){}

std::string String::getString()
{
    return literal;
}

ReturnValue String::exec()
{
    return getString();
}

//IDEA
//It may not be good to do so
Name::Name(std::string id):id(id){}

//Name is a wrapper around the symboltable
//It return the value in local context
//if not,the global scope
ReturnValue Name::exec()
{
    return factory.getValue(id);
}

void Name::setValue(ReturnValue newvalue)
{
    factory.setValue(id,newvalue);
}

//if error occurs just exit the program
//specified in astfactory
void Name::deleteRecord(){
    factory.deleteRecord(id);
}

NameConstant::NameConstant(_name_constant type):Expression(0),type(type)
{
}

_name_constant NameConstant::getType()
{
    return type;
}

ReturnValue NameConstant::exec()
{
    switch(type)
    {
        case TRUE:
            return true;
        case FALSE:
            return false;
        case NONE:
            return RETURN_NONETYPE;
    }
}
