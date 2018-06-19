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
#include "AST.h"
#include "Debug.h"

//运行效率极低
//创建效率也极低
//
//测试基础的赋值
//因为不能使用函数，所以不能使用print
//用cout手动执行和输出
int main()
{
    //2018-6-16
    //第一次重构说明：
    //ast内部使用的所有指针已经变为智能指针
    //这样做降低了性能
    //在创建的时候不应该使用任何原生指针
    //目前创建的过程非常繁琐，考虑再次重构为工厂模式


    //a simple expression
    std::shared_ptr<Expression> expr=std::make_shared<BinaryOperation>(BITAND,std::make_shared<Number>(2),std::make_shared<Number>(3));

    //simple declare and assign
    std::shared_ptr<Statement> stat=std::make_shared<Assign_Statement>(expr,std::make_shared<Name>("a"));
    auto result=stat->exec();
    DEBUG<<result;
    DEBUG<<factory.getValue("a");

    //assign with operator
    std::shared_ptr<Statement> stat2=std::make_shared<AugAssign_Statement>(ADD,"a",expr);
    auto result2=stat2->exec();
    DEBUG<<result2;
    DEBUG<<factory.getValue("a");

    //delete
    std::shared_ptr<Statement> del=std::make_shared<Delete_Statement>(std::make_shared<Name>("a"));
    auto result3 = del->exec();
    DEBUG<<result3;
    DEBUG<<factory.getValue("a");

    //NOTE
    //不要手动释放
    //目前很有可能出现内存泄漏或者段错误
    //考虑引入智能指针
    //
    //delete stat;
    //delete stat2;
    //delete del;
    return 0;
}
