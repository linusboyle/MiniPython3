#include "AST.h"

int main(){
    //test the if control flow

    /*
     * the program is like：
     *      a=1
     *      if a==1:
     *          a=2
     *      else:
     *          a=3
     */

    //a=1
    std::shared_ptr<Statement> stat=CREATE(Assign_Statement,CREATE(Number,1),CREATE(Name,"a"));

    auto ifstat=CREATE(If_Statement,CREATE(CompareOperation,EQ,CREATE(Name,"a"),CREATE(Number,1)),\
            CREATE(Suite,CREATE(Assign_Statement,CREATE(Number,2),CREATE(Name,"a"))),\
            CREATE(Suite,CREATE(Assign_Statement,CREATE(Number,3),CREATE(Name,"a")))//else
            );

    factory.addStatement(stat);
    factory.addStatement(ifstat);

    DEBUG<<factory.run()<<std::endl;
    DEBUG<<factory.getValue("a");

    //debug success
}
