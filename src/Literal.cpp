#include "Literal.h"

std::map<std::string,ReturnValue> Name::symboltable;

Number::Number(int value):ASTNode(0),int_value(value),type(INT){}

Number::Number(double value):ASTNode(0),double_value(value),type(FLOATING){}

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

String::String(std::string value):ASTNode(0),literal(value){}

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
Name::Name(std::string name):ASTNode(0),id(name)
{
    int count = symboltable.count(name);
    if(count==0)
        //use an undefined name is error
        //but you can assign to it
        //which overwrite the value error,
        symboltable[name]=RETURN_ERROR;
}

ReturnValue Name::exec()
{
    return symboltable[id];
}

void Name::setValue(ReturnValue newvalue)
{
    symboltable[id]=newvalue;
}

void Name::deleteRecord(std::string target)
{
    symboltable[target]=RETURN_ERROR;
}

NameConstant::NameConstant(_name_constant type):ASTNode(0),type(type)
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
