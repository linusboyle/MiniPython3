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
        Expression_Statement(std::shared_ptr<Expression>);
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
//CHANGED
//use template to allow multiple target
//syntax:
//  EXPRESSION TARGET1 TARGET2.....TARGETINF
class Assign_Statement:public Statement
{
    //assign的顺序无所谓
    //内部实现注意一下就行了
    public:
        template<class... T>
            Assign_Statement(std::shared_ptr<Expression> expr,std::shared_ptr<Name> last,T... other):Assign_Statement(expr,other...){
                this->add(last);
            };
        Assign_Statement(std::shared_ptr<Expression> expr,std::shared_ptr<Name> last){
            this->add(expr);
            this->add(last);
        }
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
        enum binop op;
    public:
        AugAssign_Statement(binop,std::shared_ptr<Name>,std::shared_ptr<Expression>);
        AugAssign_Statement(binop,const std::string&,std::shared_ptr<Expression>);
        virtual ReturnValue exec() override;
        ~AugAssign_Statement();
};

//CHANGED!!
//only one target!Keep it simple and stupid
//CHANGED!!
//making it easier is sometimes better XD
class Delete_Statement:public Statement{
    public:
        virtual ReturnValue exec() override final;
        template<class... T>
            Delete_Statement(std::shared_ptr<Name> last,T... other):Delete_Statement(other...){
                this->add(last);
            };
        Delete_Statement(std::shared_ptr<Name> last){
            this->add(last);
        }
};

class Suite:public Statement{//语句块也是语句
    public:
        ReturnValue exec() override;

        template<class... T>
            Suite(std::shared_ptr<Statement> last,T... other):Suite(other...){
                this->add(last);
            };
        Suite(std::shared_ptr<Statement> last){
            this->add(last);
        }
};

//Control Flow
//elif is not implemented,use else if instead;
class If_Statement:public Statement{
    public:
        If_Statement(std::shared_ptr<Expression>,std::shared_ptr<Suite>,std::shared_ptr<Suite> = nullptr);
        ReturnValue exec() override final;
};

class While_Statement:public Statement{
    public:
        While_Statement(std::shared_ptr<Expression>,std::shared_ptr<Suite>,std::shared_ptr<Suite> =nullptr);
        ReturnValue exec() override final;
};

//just a signal generator
class Break_Statement:public Statement{
    public:
        Break_Statement();
        ReturnValue exec() override final;
};

class Continue_Statement:public Statement{
    public:
        Continue_Statement();
        ReturnValue exec() override final;
};

//TODO
//after implementing list and tuple...
//implement *for* loop
//


class Argument;
class Function;

//a very useless and tedious wrapper
//should think a better way to represent a function
class FunctionDefinition_Statement:public Statement{
    public:
        template<class... Args>
        FunctionDefinition_Statement(const std::string& id,const std::shared_ptr<Suite>& body,Args... arg):func(std::make_shared<Function>(id,body,arg...)){
        }
        //直接传一个定义好的function
        FunctionDefinition_Statement(const std::shared_ptr<Function>&);
        //传一个包含动态参数的vector
        FunctionDefinition_Statement(const std::string& id,const std::shared_ptr<Suite>& body,const std::vector<std::shared_ptr<Argument>>&);

        ReturnValue exec() override final;
    private:
        std::shared_ptr<Function> func;
};

class Return_Statement:public Statement{
    public:
        Return_Statement();
        Return_Statement(ReturnValue value);
        ReturnValue exec() override final;
    private:
        ReturnValue result;
};

#endif //STATEMENT_H
