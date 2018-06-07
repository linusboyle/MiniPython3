#include "Function.h"
#include "AstFactory.h"

AstFactory& instance=AstFactory::getinstance();

std::string Function::getID(){
    return id;
}

Function::Function(int number,std::string* ids):_args_count(number),args_name(ids){
}

ReturnValue Function::execFunc(std::list<ReturnValue>* args){
    int count=0;
    //set all the local variable
    //IDEA
    //is this ok?
    for(auto i=args->begin(),n=args->end();i!=n;++i){
        instance.setValue(args_name[count],*i);
        ++count;
    }

    //execute
    auto result=this->exec();
    //delete the useless arg list
    delete args;

    return result;
}

Function::~Function(){
    delete args_name;
}
