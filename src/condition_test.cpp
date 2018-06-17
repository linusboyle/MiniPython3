#include "AST.h"
#include "Debug.h"

//test of condition or comparison
int main(){
    std::shared_ptr<Expression> expr=CREATE(CompareOperation,GT,CREATE(Number,1),CREATE(Number,2),CREATE(Number,3));
    DEBUG<<expr->exec();

    expr=CREATE(CompareOperation,GT,CREATE(Number,2),CREATE(Number,1),CREATE(Number,3));
    DEBUG<<expr->exec();

    expr=CREATE(CompareOperation,GT,CREATE(String,"c"),CREATE(String,"b"),CREATE(String,"a"));
    DEBUG<<expr->exec();

    expr=CREATE(CompareOperation,GT,CREATE(String,"a"),CREATE(String,"b"),CREATE(String,"c"));
    DEBUG<<expr->exec();

    expr=CREATE(CompareOperation,EQ,CREATE(Number,1),CREATE(Number,1),CREATE(Number,1));
    DEBUG<<expr->exec();

    expr=CREATE(CompareOperation,NOTEQ,CREATE(Number,2),CREATE(Number,1),CREATE(Number,1));
    DEBUG<<expr->exec();

    expr=CREATE(CompareOperation,NOTEQ,CREATE(Number,2),CREATE(Number,1),CREATE(String,"error"));
    DEBUG<<expr->exec();

    expr=CREATE(CompareOperation,GTE,CREATE(Number,2),CREATE(Number,2),CREATE(Number,3));
    DEBUG<<expr->exec();

    return 0;
}
