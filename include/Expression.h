#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "ASTNode.h"
#include "Operator.h"
#include <list>

//expression can be some operations,or name,number,string
class Expression:public ASTNode
{
    public:
        Expression();
        explicit Expression(int);//with limit for child
        virtual ReturnValue exec()=0;
        ~Expression()=default;
};

class UnaryOperation:public Expression
{
    private:
        unaryop op;
    public:
        UnaryOperation(unaryop,Expression*);
        virtual ReturnValue exec() override final;
};

class BinaryOperation:public Expression
{
    private:
        binop op;
    public:
        BinaryOperation(binop,Expression*,Expression*);
        virtual ReturnValue exec() override final;
};

class BooleanOperation:public Expression
{
    private:
        boolop op;
    public:
        BooleanOperation(boolop,Expression*,Expression*);
        virtual ReturnValue exec() override final;
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
