#ifndef LITERAL_H
#define LITERAL_H

#include "ASTNode.h"
#include <map>

enum number_type
{
    INT,
    FLOATING,
};

class Number:public ASTNode
{
    private:
        int int_value;
        double double_value;
        number_type type;
    public:
        Number(int);
        Number(double);
        number_type getType();
        int getInt();
        double getFloat();
        virtual ReturnValue exec();
};

class String:public ASTNode
{
    private:
        std::string literal;
    public:
        String(std::string);
        std::string getString();
        virtual ReturnValue exec();
};


//IDEA
//formatted?


//NOTE
//WE NEED BUILT-IN NAME:(It's actually in Python2)
//TRUE==1
//FALSE==0
//more...
//but not None
class Name:public ASTNode
{
    private:
        static std::map<std::string,ReturnValue> symboltable;
        std::string id;
    public:
        Name(std::string);
        static void deleteRecord(std::string);
        void setValue(ReturnValue newvalue);
        virtual ReturnValue exec();
};

enum _name_constant
{
    TRUE,
    FALSE,
    NONE,
};


class NameConstant:public ASTNode
{
    private:
        _name_constant type;
    public:
        NameConstant(_name_constant);
        _name_constant getType();
        virtual ReturnValue exec();
};
#endif
