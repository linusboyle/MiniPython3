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

#include <vector>
#include <climits>
#include "ReturnValue.h"

//INFO
//ASTnode is the very basic of AST abstractions
//
//CHANGED
//It's now mono-linked list
//because the parent pointer is of little use.
class ASTNode
{
    private:
        std::vector<ASTNode*> childlist;
        //this might be optional,It will be used sometimes to restrict
        int max_child_number=INT_MAX;
    public:

        ASTNode()=default;
        ASTNode(int child_number);

        //std::vector<ASTNode*>::iterator add(ASTNode*);
        //the iterator is of no use here

        //add a child,which should be derivation from the astnode class
        //IDEA
        //thinking about not using pointer here
        void add(ASTNode*);

        //set max children number
        //CHANGED
        //It's deprecated,because I ensure the constructor to do so and it should not appear as public function
        //void setMaxChild(int number);

        //the size of the vector
        int getChildNumber();

        //ASTNode* getParent();

        //return the pointer to child
        ASTNode* getChild(int);

        virtual ReturnValue exec()=0;
        //NOTE
        //exec api will be provided by STATEMENT
        //CHANGED
        //back originally

        //delete all of the vector
        virtual ~ASTNode();
};

#endif
