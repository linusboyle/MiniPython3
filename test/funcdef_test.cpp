#include "AST.h"
#include "Debug.h"

int main(){
    //body

    std::shared_ptr<Suite> body = CREATE(Suite,\
            CREATE(Expression_Statement,CREATE(BinaryOperation,ADD,\
                    CREATE(Name,"a"),CREATE(Name,"b")\
                    )\
                )\
            );

    //func
    std::shared_ptr<Statement> def= CREATE(FunctionDefinition_Statement,"test",body,
            CREATE(Argument,"a"),
            CREATE(Argument,"b")
            );

    /*
     * def test(a,b):
     *  a+b
     */

    factory.addStatement(def);


    //arglist 可以动态pushback
    ArgList arg={1,2};
    std::shared_ptr<Statement> call = CREATE(Expression_Statement,
                CREATE(FunctionCall,"test",arg
                    )
            );

    factory.addStatement(call);

    DEBUG<<factory.run()<<std::endl;
    DEBUG<<call->exec();
    return 0;
}
