#include "AstFactory.h"

//just a wrapper around callfunc in astfactory
//do not handle return signal
template<size_t N>
class FunctionCall:public Expression{
    private:
        std::array<ReturnValue,N> arg;
        std::string id;
    public:
        FunctionCall(const std::string& id,std::array<ReturnValue,N> arg):id(id),arg(arg){};
        ReturnValue exec() override final{
            auto target=factory.getFunc(id);
            factory.createScope(id);
            ReturnValue result=std::apply(*target,arg);
            factory.deleteScope(id);
            if(result.type==RETURN_RETURN)
            {
                return *result.true_value;
            }
            else{
                return result;
            }
        };
};
