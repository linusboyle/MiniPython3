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

#ifndef STATEMENT_H
#define STATEMENT_H

#include "ASTNode.h"
#include "Expression.h"
//#include <stdarg.h>

//INFO
//considering the simplicity,I ignore the input layer
//statement will provide consistent execution api.
//It's abstract
class Statement:public ASTNode
{
    public:
        using ASTNode::ASTNode;//default or specify a max number
        virtual ReturnValue exec()=0;
        virtual ~Statement()=0;
};

//pass just do nothing.
class Pass_Statement:public Statement
{
    public:
        Pass_Statement()=default;
        ReturnValue exec();
};

//if an expression is not used for assignment or else
class Expression_Statement:public Statement
{
    public:
        virtual ReturnValue exec();
        Expression_Statement(Expression*);
};


//CHANGED
//I am now building ast instead of cst
//stmt will be the only second layer
//

//XXX
//I recommand using actual statement type directly
//All these are provided,though,for grammar
//class Simple_Statement:public Statement
//{
    //public:
        //ReturnValue exec();
        //using Statement::Statement;
        //Simple_Statement(int,...);
        ////this virtual function is for later use
        ////every downstream stmt class should re-implement
        ////this function,argument unchanged
        ////and using dynamic_cast
        //virtual void addChild(Statement*);
        ////child should be small statement;
        //virtual ~Simple_Statement();
//};

//class Small_Statement:public Statement
//{
    //public:
        //Small_Statement();//max is 1
        //virtual ReturnValue exec();
        //virtual ~Small_Statement();
//};

//class Compound_Statement:public Statement
//{
    //public:
        //using Statement::Statement;
        //virtual ReturnValue exec()=0;
        //virtual ~Compound_Statement();
//};


#endif //STATEMENT_H
