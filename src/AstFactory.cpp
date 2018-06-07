#include "AstFactory.h"
#include <iostream>

AstFactory& AstFactory::getinstance() {
    static AstFactory theinstance;
    return theinstance;
}

AstFactory::AstFactory(){
    //default to global scope
    context="global";
    table[context]=new SymbolTable();
    stats.clear();
    funcs.clear();
}

void AstFactory::addStatement(Statement* stat){
    stats.push_back(stat);
}

void AstFactory::addFunction(Function* func){
    funcs.push_back(func);
}

//this is the only way to switch context in the program
ReturnValue AstFactory::callFunc(const std::string& id,std::list<ReturnValue>* args){
    std::string currentcontext=context;
    for(int i=0,n=funcs.size();i!=n;++i){
        if(funcs[i]->getID()==id){
            context=id;
            //if not created or is aborted,create it
            if(table.count(id)==0||table[id]==nullptr){
                table[id]=new SymbolTable();
            }
            ReturnValue result=funcs[i]->execFunc(args);
            //switch back to original context
            context=currentcontext;
            //abort the local context
            delete table[id];
            return result;
        }
    }
    return RETURN_ERROR;
}

int AstFactory::run(){
    for(int i=0,n=stats.size();i!=n;++i){
        ReturnValue tmp=stats[i]->exec();
        if(tmp.type==RETURN_ERROR){
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
    if(table[context]->getValue(id).type!=RETURN_ERROR)
        table[context]->deleteRecord(id);
    else{
        if(table["global"]->getValue(id).type!=RETURN_ERROR)
            table["global"]->deleteRecord(id);
        else{
            std::cerr<<"Segmental fault:fatal error delete "<<id<<"in"<<context<<std::endl;
            exit(1);
        }
    }
}

void AstFactory::setValue(const std::string& id,ReturnValue newvalue){
    table[context]->setValue(id,newvalue);
}

ReturnValue AstFactory::getValue(const std::string& id){
    if(table[context]->getValue(id).type!=RETURN_ERROR)
        return table[context]->getValue(id);
    else
        return table["global"]->getValue(id);
}

AstFactory::~AstFactory(){
    for(auto target:table){
        delete target.second;
    }
    for(auto target:stats){
        delete target;
    }
    for(auto target:funcs){
        delete target;
    }
}
