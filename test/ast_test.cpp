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

//测试ast单例控制类的效果
int main()
{
    std::shared_ptr<Expression> expr=std::make_shared<BinaryOperation>(BITAND,std::make_shared<Number>(2),std::make_shared<Number>(3));


    std::shared_ptr<Statement> stat=std::make_shared<Assign_Statement>(expr,std::make_shared<Name>("a"));
    factory.addStatement(stat);

    std::shared_ptr<Statement> stat2=std::make_shared<AugAssign_Statement>(ADD,"a",expr);
    factory.addStatement(stat2);

    std::shared_ptr<Statement> del=std::make_shared<Delete_Statement>(std::make_shared<Name>("a"));
    factory.addStatement(del);
    //factory.addStatement(del);

    DEBUG<<factory.run()<<std::endl;
    return 0;
}
