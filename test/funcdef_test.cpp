#include "AST.h"

int main(){
    //body

    std::shared_ptr<Suite> body = CREATE(Suite,\
            CREATE(Expression_Statement,
                CREATE(FunctionCall,"print",ArgList({
                        CREATE(BinaryOperation,ADD,
                            CREATE(Name,"a"),CREATE(Name,"b")
                        )})
                )
            )
    );

    //func
    std::shared_ptr<Statement> def= CREATE(FunctionDefinition_Statement,"test",body,
            CREATE(Argument,"a"),
            CREATE(Argument,"b")
            );

    /*
     * def test(a,b):
     *  print(a+b)
     */

    factory.addStatement(def);

    //arglist 可以动态pushback
    ArgList arg={CREATE(Number,1),CREATE(Number,2)};

    std::shared_ptr<Statement> call = CREATE(Expression_Statement,
                CREATE(FunctionCall,"test",arg
                    )
            );

    factory.addStatement(call);

    DEBUG<<"-------------"<<std::endl;


    /*
     * print(a)
     */

    auto assign=CREATE(Assign_Statement,CREATE(Number,1),CREATE(Name,"a"));
    auto call2=CREATE(Expression_Statement,CREATE(FunctionCall,
                    "print",ArgList({
                            CREATE(Name,"a")
                        })
                )
            );
    factory.addStatement(assign);
    factory.addStatement(call2);

    factory.run();
    return 0;
}
