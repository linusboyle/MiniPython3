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
    //a simple expression
    Expression* expr=new BinaryOperation(BITAND,new Number(2),new Number(3));

    //simple declare and assign
    Statement* stat=new Assign_Statement("a",expr);
    auto result=stat->exec();
    DEBUG<<result;
    DEBUG<<factory.getValue("a");

    //assign with operator
    Statement* stat2=new AugAssign_Statement(ADD,"a",expr);
    auto result2=stat2->exec();
    DEBUG<<result2;
    DEBUG<<factory.getValue("a");

    //delete
    Statement* del=new Delete_Statement("a");
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
