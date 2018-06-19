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
#include "AstFactory.h"
#include <iostream>

AstFactory& AstFactory::getinstance() {
    static AstFactory theinstance;
    return theinstance;
}

AstFactory::AstFactory(){
    //default to global scope
    context.push("global");
    table[context.top()]=new SymbolTable();
    stats.clear();
    funcs.clear();
}

void AstFactory::addStatement(std::shared_ptr<Statement> stat){
    stats.push_back(stat);
}

void AstFactory::addFunction(std::shared_ptr<Function> func){
    funcs.push_back(func);
}

//this is the only way to switch context in the program
//ReturnValue AstFactory::callFunc(const std::string& id,std::list<ReturnValue>* args){
    ////std::string currentcontext=context.top();
    //for(int i=0,n=funcs.size();i!=n;++i){
        //if(funcs[i]->getID()==id){
            //context.push(id);
            ////if not created or is aborted,create it
            //if(table.count(id)==0||table[id]==nullptr){
                //table[id]=new SymbolTable();
            //}
            //ReturnValue result=funcs[i]->execFunc(args);
            ////switch back to original context
            //context.pop();
            ////abort the local context
            //delete table[id];
            //return result;
        //}
    //}
    //return RETURN_ERROR;
//}

int AstFactory::run(){
    for(int i=0,n=stats.size();i!=n;++i){
        ReturnValue tmp=stats[i]->exec();
        //作为顶层的单例
        //这里要处理下层传递的break和continue没有循环体处理的情况
        if(tmp.type==RETURN_ERROR||tmp.type==RETURN_BREAK||tmp.type==RETURN_CONTINUE){
            //line number ,indicating error in current line
            return i;
        }
    }
    //indicate no error
    return -1;
}

void SymbolTable::deleteRecord(const std::string& id){
    table[id]=RETURN_ERROR;
}

ReturnValue SymbolTable::getValue(const std::string& id){
    if(table.count(id)==1)
        return table[id];
    else
        return RETURN_ERROR;
}

void SymbolTable::setValue(const std::string& id,ReturnValue newvalue){
    table[id]=newvalue;
}

void AstFactory::deleteRecord(const std::string& id){
    if(table[context.top()]->getValue(id).type!=RETURN_ERROR)
        table[context.top()]->deleteRecord(id);
    else{
        if(table["global"]->getValue(id).type!=RETURN_ERROR)
            table["global"]->deleteRecord(id);
        else{
            std::cerr<<"Segmental fault:fatal error delete "<<id<<" in context "<<context.top()<<std::endl;
            exit(1);
        }
    }
}

void AstFactory::setValue(const std::string& id,ReturnValue newvalue){
    table[context.top()]->setValue(id,newvalue);
}

ReturnValue AstFactory::getValue(const std::string& id){
    ReturnValue tmp=table[context.top()]->getValue(id);
    if(tmp.type!=RETURN_ERROR)
        return tmp;
    else
        return table["global"]->getValue(id);
}

AstFactory::~AstFactory(){
    for(auto target:table){
        if(target.second)
            delete target.second;
    }
}

const std::shared_ptr<Function>& AstFactory::getFunc(const std::string& id){
    for(int i=0,n=funcs.size();i!=n;++i){
        if(funcs[i]->getID()==id){
            return funcs[i];
        }
    }
    std::cerr<<"RuntimeError:call to function that does not exist"<<std::endl;
    exit(1);
}

void AstFactory::createScope(const std::string& id){
    context.push(id);

    //if not created or is aborted,create it
    if(table.count(id)==0||table[id]==nullptr){
        table[id]=new SymbolTable();
    }
}

void AstFactory::deleteScope(const std::string& id){
    //switch back to original context
    context.pop();

    //abort the local context
    delete table[id];
    table[id]=nullptr;
}
