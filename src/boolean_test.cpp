#include "AST.h"
#include "Debug.h"

int main(){

    /*      逻辑运算测试
     *      python语句：0 or 1 or 2
     *      抽象语法树使用了cpp11的可变模板参数，所以只能倒过来写（可以包装个函数,不过这就让parser来干吧）
     */

    auto expr=CREATE(BooleanOperation,OR,CREATE(Number,2),CREATE(Number,1),CREATE(Number,0));
    DEBUG<<expr->exec();

    auto stat=CREATE(Expression_Statement,expr);
    factory.addStatement(stat);

    //接下来一些测试，不创建语句了

    expr=CREATE(BooleanOperation,OR,CREATE(Number,2123),CREATE(String,"1234"),CREATE(NameConstant,FALSE));
    DEBUG<<expr->exec();

    expr=CREATE(BooleanOperation,AND,CREATE(Number,0),CREATE(String,"hihi"),CREATE(Number,11));
    DEBUG<<expr->exec();

    DEBUG<<factory.run()<<std::endl;
}
