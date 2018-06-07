#include "Statement.h"
#include <iostream>
#include "Debug.h"

//运行效率极低
//创建效率也极低
int main()
{
    Expression* expr=new BinaryOperation(BITAND);
    Expression left=new Number(1);
    Expression right=new Number(3);
    expr->addChild(&left);
    expr->addChild(&right);

    Statement* stat=new Assign_Statement(1);
    dynamic_cast<Assign_Statement*>(stat)->setValue(expr);
    dynamic_cast<Assign_Statement*>(stat)->addTarget("a");
    auto result=stat->exec();
    std::cout<<Name::symboltable["a"];


    Statement* stat2=new AugAssign_Statement(ADD);
    dynamic_cast<AugAssign_Statement*>(stat2)->addTarget("a");
    dynamic_cast<AugAssign_Statement*>(stat2)->setValue(expr);
    auto result2=stat2->exec();
    std::cout<<result;
    std::cout<<result2;
    std::cout<<Name::symboltable["a"];


    Statement* del=new Delete_Statement();
    dynamic_cast<Delete_Statement*>(del)->addTarget("a");
    auto result3 = del->exec();
    std::cout<<result3;
    std::cout<<Name::symboltable["a"];
    return 0;
}
