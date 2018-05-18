#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "ASTNode.h"
#include "Literal.h"
#include "Operator.h"

//expression can be some operations,and also name,number,string
//
class Expression:public ASTNode
{
    public:
        using ASTNode::ASTNode;
        Expression(Number*);
        Expression(String*);
        Expression(Name*);
        virtual ReturnValue exec();
};

class UnaryOperation:public Expression
{
    private:
        unaryop op;
    public:
        UnaryOperation(unaryop,Expression*);
        virtual ReturnValue exec();
};

class BinaryOperation:public Expression
{
    private:
        binop op;
    public:
        BinaryOperation(binop,Expression* =nullptr,Expression* =nullptr);
        void addChild(Expression*);
        virtual ReturnValue exec();
};

class BooleanOperation:public Expression
{
    private:
        boolop op;
    public:
        BooleanOperation(boolop,Expression* =nullptr,Expression* =nullptr);
        void addChild(Expression*);
        virtual ReturnValue exec();
};
#endif


//class Xor_Expression;
//class And_Expression;
//class Shift_Expression;
//class Arithmetic_Expression;
//class Term;
//class Factor;
//class Power;
//class Atom_Expression;

//class Expression:public Input
//{
    //public:
        //using Input::Input;
        //Expression(Expression*);
        //void addChild(Expression*);
        //virtual ReturnValue exec();
//};

//class Xor_Expression:public Expression
//{
    //public:
        //using Expression::Expression;
        //virtual ReturnValue exec();
//};

//class And_Expression:public Expression
//{
    //public:
        //using Expression::Expression;
        //virtual ReturnValue exec();
//};

//class Shift_Expression:public Expression
//{
    //public:
        //using Expression::Expression;
        //void addChild(Operator*);
        //virtual ReturnValue exec();
//};

//class Arithmetic_Expression:public Expression
//{
    //public:
        //using Expression::Expression;
        //void addChild(Operator*);
        //virtual ReturnValue exec();
//};

//class Term:public Expression
//{
    //public:
        //using Expression::Expression;
        //void addChild(Factor*);
        //virtual ReturnValue exec();
//};

//class Factor:public Expression
//{
    //private:
        //bool init_as_factor=false;
        //bool init_as_power=false;
    //public:
        //using Expression::Expression;
        //Factor();
        //Factor(Power*);
        //void addChild(Operator*);
        //void addChild(Factor*);
        //void addChild(Power*);
        //virtual ReturnValue exec();
//};

//class Power:public Expression
//{
    //public:
        //using Expression::Expression;
        //Power();
        //void addChild(Factor*);
        //void addChild(Atom_Expression*);
        //virtual ReturnValue exec();
//};