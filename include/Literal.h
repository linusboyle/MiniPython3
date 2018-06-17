#ifndef LITERAL_H
#define LITERAL_H

#include "ASTNode.h"
#include "Expression.h"
#include <map>

enum number_type
{
    INT,
    FLOATING,
};

class Number:public Expression
{
    private:
        int int_value;
        double double_value;
        number_type type;
        int getInt();
        double getFloat();
    public:
        Number(int);
        Number(char)=delete;
        Number(double);
        virtual ReturnValue exec() override final;
};


class String:public Expression
{
    private:
        std::string literal;
    public:
        String(std::string);
        std::string getString();
        virtual ReturnValue exec() override final;
};

//Name is visible in current context and global context
class Name:public Expression
{
    private:
        std::string id;
    public:
        Name(std::string);
        void setValue(ReturnValue newvalue);
        void deleteRecord();
        virtual ReturnValue exec() override final;
};

enum _name_constant
{
    TRUE,
    FALSE,
    NONE,
};


class NameConstant:public Expression
{
    private:
        _name_constant type;
    public:
        NameConstant(_name_constant);
        _name_constant getType();
        virtual ReturnValue exec();
};
#endif
