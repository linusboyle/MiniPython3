#include "AST.h"
#include "Debug.h"

int main(){
    /*
     * a=3
     * while a>0:
     *      a-=1
     */
    auto stat=CREATE(Assign_Statement,CREATE(Number,3),CREATE(Name,"a"));
    auto stat2=CREATE(While_Statement,CREATE(CompareOperation,GT,CREATE(Number,0),CREATE(Name,"a")),\
            CREATE(Suite,\
                CREATE(AugAssign_Statement,SUB,CREATE(Name,"a"),CREATE(Number,1)))
            );
    /*
     * b=5
     * while true:
     *      if b==3:
     *          break
     *      else:
     *          b-=1
     */
    auto stat3=CREATE(Assign_Statement,CREATE(Number,5),CREATE(Name,"b"));
    auto stat4=CREATE(While_Statement,CREATE(NameConstant,TRUE),\
        CREATE(Suite,\
            CREATE(If_Statement,CREATE(CompareOperation,EQ,CREATE(Number,3),CREATE(Name,"b")),\
                CREATE(Suite,\
                    CREATE(Break_Statement)
                ),\
                //else
                CREATE(Suite,\
                    CREATE(AugAssign_Statement,SUB,CREATE(Name,"b"),CREATE(Number,1))\
                )\
            )\
        )\
    );

    factory.addStatement(stat);
    factory.addStatement(stat2);
    factory.addStatement(stat3);
    factory.addStatement(stat4);

    DEBUG<<factory.run()<<std::endl;
    DEBUG<<factory.getValue("a");
    DEBUG<<factory.getValue("b");
    //success test
}
