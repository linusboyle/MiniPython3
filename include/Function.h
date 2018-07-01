#ifndef FUNCTION_h
#define FUNCTION_h

#include "Statement.h"


//代表一个参数
//名称必须，默认值可选，直接使用create宏即可
class Argument:public ASTNode{
    private:
        const std::string id;
        const ReturnValue defaultValue;
        friend class Function;
    public:
        Argument(const std::string&,const ReturnValue& =RETURN_NONETYPE);
};

class Function{
    private:
        const std::string id;
        std::vector<std::shared_ptr<Argument>> arguments;

        //counter,count the current pushed arguments
        //must be assign to 0 each time a functioncall ends
        unsigned int index=0;
        std::shared_ptr<Suite> body;

        friend FunctionCall;
        friend FunctionDefinition_Statement;

        //usable by funccall
        void pushArg(ReturnValue);
        void pushDefault();

        //usable by funcdef
        void addArg(const std::shared_ptr<Argument>&);
    public:
        const std::string& getID() const;

        //NOTE
        //Caution! In python,just like in cpp,argument with default value should always be after
        //those without one,but because of the template method here,
        //no check about that is carried out
        //if we tend to throw a warning,the parser have to take care about that.

        //如果不想用模板，那就忽略之
        template<class... T>
        Function(const std::string& id,std::shared_ptr<Suite> body,T... arg):id(id),body(body){
            int justaholder[]={(this->arguments.push_back(arg),0)...};//此处的参数必须有名字，不一定有默认值
        }

        //2018-6-18
        //一个问题在于在调用函数的时候，选择可变参数是很难储存的
        //是否要放弃按参数名称传参的功能？（测例中没有使用，这个功能也并不重要）
        //如果可以，只允许传入按位置的参数，如果数量不够将查找默认值。
        //这样也会提升查找默认值的速度，因为传参数的长度是由index记录而固定的
        //不用再遍历一边参数了。

        //注意此处结尾必须复位index
        //设计为函数对象，使用std::invoke 调用 详见funccall
        ReturnValue operator()();//调用此函数只能是没有参数的情况,或者所需参数已经全部add

        //NOTE
        //调用显式的参数传递必须全部在按参数位置传参数之后
        //ReturnValue execFunc(const std::shared_ptr<Argument>&);

        //README
        //以下模板供parser使用，不一定需要
        //如果不需要也不会被编译
        ReturnValue operator()(ReturnValue);

        //按参数名传递 废弃
        //template<class... T>
        //ReturnValue execFunc(const std::shared_ptr<Argument>& first,T... args){
            //this->pushArg(first);
            //return execFunc(args...);
        //}

        //按参数位置传递
        template<class... T>
        ReturnValue operator()(ReturnValue first,T... args){//must be returnvalue!
            this->pushArg(first);
            return this->operator()(args...);
        }
        ~Function();
};

#endif
