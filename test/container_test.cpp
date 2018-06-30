#include "AST.h"

int main(){
    /*
     * for i in range(1,10):  //actually 1~9
     *      print(i)
     */

    auto print_call=CREATE(Expression_Statement,CREATE(FunctionCall,
                        "print",ArgList({
                            CREATE(Name,"i")
                        })
                )
            );//call

    auto range_call=CREATE(FunctionCall,
                        "range",ArgList({
                            CREATE(Number,1),CREATE(Number,10)
                        })
                );//call

    auto loop=CREATE(For_Statement,
                CREATE(Name,"i"),
                range_call,
                CREATE(Suite,
                    print_call)
            );

    factory.addStatement(loop);
    factory.run();
}//main
