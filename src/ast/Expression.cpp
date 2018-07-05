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
#include "Expression.h"
#include <cmath>
#include "AstFactory.h"

Expression::Expression(int limit):ASTNode(limit){}

Expression::Expression():ASTNode()
{
}

ReturnValue Expression::exec()
{
    return getChild(0)->exec();
}

UnaryOperation::UnaryOperation(unaryop op,std::shared_ptr<Expression> operand):Expression(1),op(op)
{
    add(operand);
}

ReturnValue UnaryOperation::exec()
{
    auto result=getChild(0)->exec();
    switch(op)
    {
        case UADD:
            return result;
        case USUB:
            if(result.type==RETURN_FLOAT)
                return ReturnValue(0.0)-result;
            return 0-result;
        case NOT:
            if(result.type==RETURN_ERROR||result.type==RETURN_BREAK||result.type==RETURN_CONTINUE||result.type==RETURN_RETURN)
                return result;
            return !result.convert2bool();
        case INVERT:
            return ~result;
    }
}

BinaryOperation::BinaryOperation(binop op,std::shared_ptr<Expression> operand1,std::shared_ptr<Expression> operand2):Expression(2),op(op)
{
    if(operand1)
        add(operand1);
    else
        return;
    if(operand2)
        add(operand2);
}

ReturnValue BinaryOperation::exec()
{
    auto loperand=getChild(0),roperand=getChild(1);
    if(!(loperand&&roperand)){
        return RETURN_ERROR;
    }

    auto value1=loperand->exec();
    auto value2=roperand->exec();

    switch(op)
    {
        case ADD:
            return value1+value2;
        case SUB:
            return value1-value2;
        case MULT:
            return value1*value2;
        case DIV:
            return value1/value2;
        case FLOORDIV:
        {
            auto tmp=value1/value2;
            if(tmp.type==RETURN_FLOAT)
                return int(std::floor(tmp.double_value));
            else
                return tmp;
        }
        case MOD:
            return value1%value2;
        case POW:
            if(value1.type==RETURN_INT&&value2.type==RETURN_INT)
                return pow(value1.integer_value,value2.integer_value);
            if(value1.type==RETURN_FLOAT&&value2.type==RETURN_INT)
                return pow(value1.double_value,value2.integer_value);
            if(value1.type==RETURN_INT&&value2.type==RETURN_FLOAT)
                return pow(value1.integer_value,value2.double_value);
            if(value1.type==RETURN_FLOAT&&value2.type==RETURN_FLOAT)
                return pow(value1.double_value,value2.double_value);
            return RETURN_ERROR;
        case LSHIFT:
            return value1<<value2;
        case RSHIFT:
            return value1>>value2;
        case BITOR:
            return value1|value2;
        case BITAND:
            return value1&value2;
        case BITXOR:
            return value1^value2;
    }
}

//BooleanOperation::BooleanOperation(boolop op,std::shared_ptr<Expression> operand1,std::shared_ptr<Expression> operand2):op(op)
//{
   //if(operand1)
       //add(operand1);
   //else
       //return;
   //if(operand2)
       //add(operand2);
//}

ReturnValue BooleanOperation::exec()
{
    switch(op)
    {
        //NOTE
        //OR return the first true expression
        //if none,return the last
        case OR:
            for(int i=0,n=getChildNumber();i!=n;++i)
            {
                auto tmp=getChild(i)->exec();
                if((tmp.convert2bool())||i==n-1)
                    return tmp;
            }
            //should not reach here...
            return RETURN_ERROR;
        case AND:
            //likewise
            //but return the first false expression
            for(int i=0,n=getChildNumber();i!=n;++i)
            {
                auto tmp=getChild(i)->exec();
                if(!tmp.convert2bool()||i==n-1)
                    return tmp;
            }
            return RETURN_ERROR;
    }
}


ReturnValue CompareOperation::exec()
{
   int iter_left=0,size=getChildNumber();
    while(iter_left<size-1)
    {
        ReturnValue result=RETURN_NONETYPE;
        switch (op)
        {
            case EQ:
                result=getChild(iter_left)->exec()==getChild(iter_left+1)->exec();
                break;
            case NOTEQ:
                result=getChild(iter_left)->exec()!=getChild(iter_left+1)->exec();
                break;
            case GT:
                result=getChild(iter_left)->exec()>getChild(iter_left+1)->exec();
                break;
            case LT:
                result=getChild(iter_left)->exec()<getChild(iter_left+1)->exec();
                break;
            case GTE:
                result=getChild(iter_left)->exec()>=getChild(iter_left+1)->exec();
                break;
            case LTE:
                result=getChild(iter_left)->exec()<=getChild(iter_left+1)->exec();
                break;
        }
        if(result.type==RETURN_BOOLEAN&&!result.boolean_value)
            return false;
        else if(result.type==RETURN_ERROR){
            return result;
        }
        else
            iter_left++;
    }
    return true;
}

Slice::Slice(const std::shared_ptr<Expression>& target,const std::shared_ptr<Expression>& beg,const std::shared_ptr<Expression>& end,const std::shared_ptr<Expression>& step){
    add(target);
    add(beg);
    add(end);
    add(step);
}

ReturnValue Slice::exec(){
    ReturnValue tmp=getChild(0)->exec();
    ReturnValue beg=getChild(1)->exec();
    ReturnValue end=getChild(2)->exec();
    ReturnValue step=getChild(3)->exec();

    if(beg.type!=RETURN_INT||end.type!=RETURN_INT||step.type!=RETURN_INT){
        std::cerr<<"RuntimeError:index not integer"<<std::endl;
        std::exit(1);
    }
    int _beg=beg.integer_value;
    int _end=end.integer_value;
    int _step=step.integer_value;
    switch(tmp.type){
        //这两种情况实际上应该是不可能发生(funccall已经handle了这两种情况，而其他表达式不可能产生这两种信号)
        case RETURN_BREAK:
            return tmp;
        case RETURN_CONTINUE:
            return tmp;

        case RETURN_STRING:
            {
                int i=_beg;
                std::string& _target=tmp.string_value;
                std::string result;

                //这里的实现并没有考虑越界，一方面是at有检查
                //另一方面在下界超过长度的情况下会直接返回所有
                //这是feature
                while(i<_end){
                    result+=_target.at(i);
                    i+=_step;
                }
                return result;
            }
        //TODO
        //实际上切片对容器是有效的
        //所以如果要增加容器支持，则需要在这里进行拓展
        default:
            return RETURN_ERROR;
    }
}
//ReturnValue FunctionCall::exec(){
    //auto result=factory.callFunc(name,args);
    ////如果返回的是return信号的话，返回实际的值
    //if(result.type==RETURN_RETURN){
        //return *(result.true_value);
    //}
    ////否则则是result本身
    //return result;
//}

FunctionCall::FunctionCall(const std::string& id,std::vector<std::shared_ptr<Expression>> args):id(id){
    for(int i=0,n=args.size();i!=n;++i){
        this->add(args[i]);
    }
}

ReturnValue FunctionCall::exec()
{
    auto target=factory.getFunc(id);

    //FIXED
    //fix the bug of argument not calculated before pushed to heap
    //
    //IDEA!!
    //it works!
    std::vector<ReturnValue> tmp;

    for(int i=0,n=getChildNumber();i!=n;++i){
        tmp.push_back(getChild(i)->exec());
    }

    factory.createScope(id);

    //terminate if arguments too many
    for(int i=0,n=tmp.size();i!=n;++i){
        target->pushArg(tmp[i]);
    }
    //will detect default value when invoked
    //terminate program if argument too few
    ReturnValue result=std::__invoke(*target);

    factory.deleteScope(id);

    if(result.type==RETURN_BREAK||result.type==RETURN_CONTINUE){
        //结束函数调用之后如果有break或者continue，不应该再继续传递上去了
        //因为函数内部的东西不应该传递到外部作用域
        return RETURN_ERROR;
    }
    //return已经被函数本身截获并且转换过了
    //这一步多此一举
    //else if(result.type==RETURN_RETURN){
        //return result.true_value;
    //}
    else
        return result;
};

Range::Range(const std::shared_ptr<Expression>& beg,const std::shared_ptr<Expression>& end,const std::shared_ptr<Expression>& step)
{
    add(beg);
    add(end);
    add(step);
}

ReturnValue Range::exec() {
    auto beg=getChild(0)->exec();
    auto end=getChild(1)->exec();
    auto step=getChild(2)->exec();
    if(beg.type!=RETURN_INT||end.type!=RETURN_INT||step.type!=RETURN_INT){
        std::cerr<<"RuntimeError:index is not integer"<<std::endl;
        std::exit(1);
    }
    else{
        std::vector<ReturnValue> result;
        for(int i=beg.integer_value;i<end.integer_value;i+=step.integer_value){
            result.push_back(i);
        }
        return ReturnValue(RETURN_TUPLE,result);
    }
}
