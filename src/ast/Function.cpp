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

const std::string& Function::getID() const{
    return id;
}

//参数全是按值传递 这是py的机制
//至于是否实现传引用，就得思考一下了
//void Function::pushArg(const std::shared_ptr<Argument>& arg){
    //if(factory.getValue(arg->id).type==RETURN_ERROR)//none has been initialized
    //{
        //factory.setValue(arg->id,arg->defaultValue);
        //_has_explicit=true;//indicate it cannit be followed by a positonal argument
        //index++;//in fact when a none-positional argument occurs the index is useless now
    //}//not really,considering the default value provided.
    //else{
        //std::cerr<<"RuntimeError:repeatedly initialize argument of function "<<this->id<<", aborting..."<<std::endl;
        //exit(1);
    //}
//}

void Function::pushDefault(){
    for(unsigned int i=index,n=arguments.size();i!=n;++i){
        auto tmp=arguments[i];
        if(tmp->defaultValue.type!=RETURN_NONETYPE/*默认值应该是具体的可计算类型*/){
            factory.setValue(tmp->id,tmp->defaultValue);
        }
        else{//只要有一个没有默认值，就无法进行函数
            std::cerr<<"RuntimeError:argument too few for function "<<this->id<<std::endl;
            exit(1);
        }
    }
}

void Function::pushArg(ReturnValue arg){
    //if(_has_explicit){
        //std::cerr<<"RuntimeError:cannnot put a positional argument after a none-positional argument,aborting..."<<std::endl;
        //exit(1);
    //}
    //else{
    factory.setValue(this->arguments[index]->id,arg);
    if(++index>arguments.size()){
        std::cerr<<"RuntimeError:too many arguments for function "<<this->id<<std::endl;
        exit(1);
    }
    //}
}

Function::~Function(){
}

//ReturnValue Function::execFunc(const std::shared_ptr<Argument>& last){
    //this->pushArg(last);
    //return this->execFunc();
//}

ReturnValue Function::operator()(ReturnValue last){
    this->pushArg(last);
    return this->operator()();
}

ReturnValue Function::operator()(){
    this->pushDefault();//尝试加入设置了默认值的参数，但这不一定会成功,如若失败则直接退出
    //没有重载，那么默认值不会造成歧义（？）
    //the process of checking args is in pushdefault

    //execute
    auto result=body->exec();

    index=0;

    if(result.type==RETURN_RETURN)
        return *(result.true_value);
    else
        return result;
}

Argument::Argument(const std::string& id,const ReturnValue& value):id(id),defaultValue(value){
}

void Function::addArg(const std::shared_ptr<Argument>& arg){
    arguments.push_back(arg);
}
