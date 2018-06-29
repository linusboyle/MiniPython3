#include "AST.h"

//测试通过宏简化后的的创建过程
int main()
{
    auto expr=CREATE(BinaryOperation,BITAND,CREATE(Number,2),CREATE(Number,3));

    auto stat=CREATE(Assign_Statement,expr,CREATE(Name,"a"));
    factory.addStatement(stat);

    auto stat2=CREATE(AugAssign_Statement,ADD,"a",expr);
    factory.addStatement(stat2);

    auto del=CREATE(Delete_Statement,CREATE(Name,"a"));
    factory.addStatement(del);
    //factory.addStatement(del);

    DEBUG<<factory.run()<<std::endl;
    return 0;
}
