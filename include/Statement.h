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

#include "Literal.h"

//INFO
//considering the simplicity,I ignore the input layer
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
        ReturnValue exec() override final;
};

//if an expression is not used for assignment or else
//then it will be a seperated statement
//NOTE if in interactive mode we may print it
//automatically
class Expression_Statement:public Statement
{
    public:
        virtual ReturnValue exec() override final;
        //just use expression to initialize
        Expression_Statement(Expression*);
        ~Expression_Statement();
};

//NOTE
//multiple targets are ok
//CHANGED
//the current way to create a statement is too diverse
//so to make it more clear,this one will only accept one target
//statement like this:
//      a=b=1+2/2
//should be converted to 2 statements by the parser
class Assign_Statement:public Statement
{
    private:
        Name* target;
    public:
        Assign_Statement(const std::string&,Expression*);
        virtual ReturnValue exec() override;
        ~Assign_Statement();
        //TODO
        //add support for unpacking
};

//ONLY one TARGET!
//
//this version simplify the create process
class AugAssign_Statement:public Statement
{
    private:
        Name* target=nullptr;
        enum binop op;
    public:
        AugAssign_Statement(binop,const std::string&,Expression*);
        virtual ReturnValue exec();
        ~AugAssign_Statement();
};

//CHANGED!!
//only one target!Keep it simple and stupid
class Delete_Statement:public Statement{
    private:
        Name* target;
    public:
        virtual ReturnValue exec() override final;
        Delete_Statement(const std::string&);
};

class Suite :public ASTNode{
    public:
        Suite();
        void addChild(Statement*);
        ReturnValue exec() override;
};

//Control Flow
//elif is not implemented,use else if instead;
class If_Statement:public Statement{
    public:
        If_Statement(Expression*,Suite*,Suite* = nullptr);
        ReturnValue exec() override final;
};

class While_Statement:public Statement{
    public:
        While_Statement(Expression*,Suite*,Suite* =nullptr);
        ReturnValue exec() override final;
};

class Break_Statement:public Statement{
    public:
        inline Break_Statement();
        ReturnValue exec() override final;
};

class Continue_Statement:public Statement{
    public:
        inline Continue_Statement();
        ReturnValue exec() override final;
};

//TODO
//after implementing list and tuple...
//implement *for* loop


//a very useless and tedious wrapper
//should think a better way to represent a function
class FunctionDefinition_Statement:public Statement{
    public:
        FunctionDefinition_Statement(std::string&,int,std::string*,Suite*);
    private:
        std::string name;
        std::string* argnames;
        Suite* body;
        int arg_count;

        ReturnValue exec() override final;
};

class Return_Statement:public Statement{
    public:
        Return_Statement();
        Return_Statement(ReturnValue& value);
        ReturnValue exec() override final;
    private:
        ReturnValue* result;
};

#endif //STATEMENT_H
