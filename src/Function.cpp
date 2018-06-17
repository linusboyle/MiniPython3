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
#include "Function.h"
#include "AstFactory.h"

std::string Function::getID(){
    return id;
}

Function::Function(std::string name,int number,std::string* ids,std::shared_ptr<Suite> body):id(name),_args_count(number),args_name(ids),body(body){
}

ReturnValue Function::execFunc(std::list<ReturnValue>* args){
    int count=0;
    //set all the local variable
    //IDEA
    //is this ok?
    for(auto i=args->begin(),n=args->end();i!=n;++i){
        factory.setValue(args_name[count],*i);
        ++count;
    }

    //execute
    auto result=body->exec();
    //delete the useless arg list
    delete args;

    return result;
}

Function::~Function(){
    delete args_name;
}
