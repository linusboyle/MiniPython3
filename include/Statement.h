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
        ReturnValue exec() override;
};

//if an expression is not used for assignment or else
//then it will be a seperated statement
//NOTE if in interactive mode we may print it
//automatically
class Expression_Statement:public Statement
{
    public:
        virtual ReturnValue exec() override;
        //just use expression to initialize
        Expression_Statement(Expression*);
        ~Expression_Statement();
};

//NOTE
//multiple targets are ok
class Assign_Statement:public Statement
{
    private:
        Name** targetlist;
        int targetsize;
        int index=0;
    public:
        Assign_Statement(int);//number of targets
        //Assign_Statement(Expression*);
        void setValue(Expression*);
        void addTarget(std::string);
        virtual ReturnValue exec() override;
        ~Assign_Statement();
        //TODO
        //add support for unpacking
};

//ONLY one TARGET!
class AugAssign_Statement:public Statement
{
    private:
        Name* target=nullptr;
        enum binop op;
    public:
        AugAssign_Statement(binop);
        void setValue(Expression*);
        void addTarget(std::string);
        virtual ReturnValue exec();
        ~AugAssign_Statement();
};

class Delete_Statement:public Statement{
    private:
        std::vector<Name> target;
    public:
        virtual ReturnValue exec() override;
        void addTarget(std::string);
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
        ReturnValue exec();
};

#endif //STATEMENT_H
