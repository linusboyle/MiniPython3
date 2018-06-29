#include "AST.h"

//算数表达式运算测试
int main(){
    //auto并不是万能的
    std::shared_ptr<Expression> expr=CREATE(UnaryOperation,UADD,CREATE(String,"hello~"));
    DEBUG<<expr->exec();

    expr=CREATE(UnaryOperation,USUB,CREATE(String,"this should be an error"));
    DEBUG<<expr->exec();

    expr=CREATE(UnaryOperation,NOT,CREATE(NameConstant,FALSE));
    DEBUG<<expr->exec();

    expr=CREATE(UnaryOperation,INVERT,CREATE(Number,-1));
    DEBUG<<expr->exec();

    expr=CREATE(BinaryOperation,ADD,CREATE(Number,19),CREATE(Number,20));
    DEBUG<<expr->exec();

    expr=CREATE(BinaryOperation,ADD,CREATE(String,"hello "),CREATE(String,"world~"));
    DEBUG<<expr->exec();

    expr=CREATE(BinaryOperation,POW,CREATE(Number,20),CREATE(Number,2));
    DEBUG<<expr->exec();

    expr=CREATE(BinaryOperation,MULT,CREATE(Number,20),CREATE(Number,2));
    DEBUG<<expr->exec();

    expr=CREATE(BinaryOperation,DIV,CREATE(Number,7),CREATE(Number,2.5));
    DEBUG<<expr->exec();

    expr=CREATE(BinaryOperation,MOD,CREATE(Number,7),CREATE(Number,2.5));//2
    DEBUG<<expr->exec();

    //c++的fmod函数和python的不太一样
    //如果是负数的取模运算，结果不一样
    //不过应该很少出现负数的模……
    expr=CREATE(BinaryOperation,MOD,CREATE(Number,-7.2),CREATE(Number,2.5));//-2.2 python是0.3
    DEBUG<<expr->exec();

    expr=CREATE(BinaryOperation,LSHIFT,CREATE(Number,2),CREATE(Number,1));//4
    DEBUG<<expr->exec();

    expr=CREATE(BinaryOperation,RSHIFT,CREATE(Number,2),CREATE(Number,1));//1
    DEBUG<<expr->exec();

    expr=CREATE(BinaryOperation,BITOR,CREATE(Number,2),CREATE(Number,1));//3
    DEBUG<<expr->exec();

    expr=CREATE(BinaryOperation,BITAND,CREATE(Number,2),CREATE(Number,1));//0
    DEBUG<<expr->exec();

    expr=CREATE(BinaryOperation,BITXOR,CREATE(Number,3),CREATE(Number,2));//1
    DEBUG<<expr->exec();

    //能自动检测除0并停止运行
    expr=CREATE(BinaryOperation,FLOORDIV,CREATE(Number,12.5),CREATE(Number,0.0f));
    DEBUG<<expr->exec();
}
