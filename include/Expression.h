#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "ASTNode.h"
#include "Literal.h"
#include "Operator.h"
#include <list>

//expression can be some operations,or name,number,string
class Expression:public ASTNode
{
    public:
        Expression();
        explicit Expression(int);//with limit for child
        Expression(Number*);
        Expression(String*);
        Expression(Name*);
        virtual void addChild(Expression*);
        virtual ReturnValue exec()=0;
};

class UnaryOperation:public Expression
{
    private:
        unaryop op;
    public:
        UnaryOperation(unaryop,Expression* =nullptr);
        virtual ReturnValue exec();
};

class BinaryOperation:public Expression
{
    private:
        binop op;
    public:
        BinaryOperation(binop,Expression* =nullptr,Expression* =nullptr);
        virtual ReturnValue exec();
};

class BooleanOperation:public Expression
{
    private:
        boolop op;
    public:
        BooleanOperation(boolop,Expression* =nullptr,Expression* =nullptr);
        virtual ReturnValue exec();
};

class CompareOperation:public Expression
{
    private:
        compareop* op;
        int size;
        int index=0;
    public:
        //at least one
        CompareOperation(int,Expression*);
        void addOperator(enum compareop);
        virtual ReturnValue exec() override;
};

//just a wrapper around callfunc in astfactory
//do not handle return signal
class FunctionCall:public Expression{
    private:
        std::string name;
        std::list<ReturnValue>* args;
    public:
        FunctionCall(const std::string&,std::list<ReturnValue>*);
        ReturnValue exec() override final;
};
#endif
