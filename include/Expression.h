/*
Simple Python Interpreter implementation by cpp
Copyright (C) 2018 LCC,ZZH,HZL,CYH

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses.
*/
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "ASTNode.h"
#include "Operator.h"

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
        UnaryOperation(unaryop,std::shared_ptr<Expression>);
        virtual ReturnValue exec() override final;
};

class BinaryOperation:public Expression
{
    private:
        binop op;
    public:
        BinaryOperation(binop,std::shared_ptr<Expression>,std::shared_ptr<Expression>);
        virtual ReturnValue exec() override final;
};

class BooleanOperation:public Expression
{
    private:
        boolop op;
    public:
        //这里的模板可变参在编译时就能检查
        //问题不大
        //需要注意顺序是反的,这个创建的时候烦恼烦恼
        template<class P,class... T>
            BooleanOperation(boolop op,P last,T... other):BooleanOperation(op,other...){
                //NOTE
                //should we take RTTI here?
                this->add(last);
            };
        template<class T>
            BooleanOperation(boolop op,T last):op(op){
                this->add(last);
            }
        virtual ReturnValue exec() override final;
};

class CompareOperation:public Expression
{
    private:
        compareop op;
    public:
        //just like the boolean operation
        //expr like 3>2>1
        //should be created as (pseudo) GT,1,2,3
        template<class P,class... T>
            CompareOperation(compareop op,P last,T... other):CompareOperation(op,other...){
                this->add(last);
            };
        template<class T>
            CompareOperation(compareop op,T last):op(op){
                this->add(last);
            }
        virtual ReturnValue exec() override final;
};

class Slice:public Expression
{
    private:
        int _beg;
        int _end;
        int _step;
    public:
        Slice(std::shared_ptr<Expression>&,int,int,int);
        virtual ReturnValue exec() override;
};

//just a wrapper around callfunc in astfactory
//do not handle return signal
//CHANGED
//no longer depend on astfactory's call utilities
//it's now functional class
class FunctionCall:public Expression{
    private:
        std::string id;
        std::vector<std::shared_ptr<Expression>> arg;
        //FIXED
        //should be able to take any expression as argument
        //DONE
        //use astnode's vector directly
    public:
        FunctionCall(const std::string&,std::vector<std::shared_ptr<Expression>>);
        ReturnValue exec() override final;
};
#endif
