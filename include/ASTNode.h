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

#ifndef ASTNODE_H
#define ASTNODE_H

#include <climits>
#include <vector>
#include <memory>
#include "ReturnValue.h"

//INFO
//ASTnode is the very base of AST abstractions
//
//CHANGED
//It's now mono-linked list
//because the parent pointer is of little use.
class ASTNode//:public std::enable_shared_from_this<ASTNode>
{
    private:
        //TODO
        //should we change it to binary tree?
        //vector is too wasteful
        //
        //no,just so
        std::vector<std::shared_ptr<ASTNode>> childlist;
        //this might be optional,It will be used sometimes to restrict
        int max_child_number=INT_MAX;

        ASTNode(const ASTNode&)=delete;
    public:

        ASTNode()=default;
        ASTNode(int child_number);

        //add a child,which should be derivation from the astnode class
        //IDEA
        //thinking about not using pointer here,maybe shared_ptr?
        void add(std::shared_ptr<ASTNode>);

        //set max children number
        //CHANGED
        //It's deprecated,because I ensure the constructor to do so and it should not appear as public function
        //void setMaxChild(int number);

        //the size of the vector
        int getChildNumber();

        //return the pointer to child
        //too slow here...
        std::shared_ptr<ASTNode> getChild(int);

        //const std::shared_ptr<ASTNode>& clone();

        //consistent interface to execute
        virtual ReturnValue exec()=0;

        //delete all of the vector
        //which is recursive
        virtual ~ASTNode();
};

#endif
