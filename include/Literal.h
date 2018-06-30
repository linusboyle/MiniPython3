#ifndef LITERAL_H
#define LITERAL_H

#include "ASTNode.h"
#include "Expression.h"

//all of those below is just wrapper around returnvalue
//they are the literals used in py3
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

//DONE
//实现格式化字符串
class String:public Expression
{
    private:
        std::string literal;
    public:
        String(const std::string&);
        std::string getString();
        virtual ReturnValue exec() override final;
};

class Formatted_String:public Expression{
    private:
        std::string base_string;
    public:
        //I will not use template anymore,just tired of it
        Formatted_String(const std::string&,std::vector<std::shared_ptr<Expression>>&);
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
    EMPTY_TUPLE,
    EMPTY_LIST,
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
