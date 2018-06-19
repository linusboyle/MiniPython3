#ifndef FUNCTION_h
#define FUNCTION_h

#include "Statement.h"

class Argument{
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
        unsigned int index=0;
        std::shared_ptr<Suite> body;

        //void pushArg(const std::shared_ptr<Argument>&);
        void pushArg(ReturnValue);
        void pushDefault();

        //bool _has_explicit=false;
    public:
        const std::string& getID() const;

        //NOTE
        //Caution! In python,just like in cpp,argument with default value should always be after
        //those without one,but because of the template method here,
        //no check about that is carried out
        //if we tend to throw a warning,the parser have to take care about that.
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
        ReturnValue operator()();//调用此函数只能是没有参数的情况

        //NOTE
        //调用显式的参数传递必须全部在按参数位置传参数之后
        //ReturnValue execFunc(const std::shared_ptr<Argument>&);

        ReturnValue operator()(ReturnValue);

        //按参数名传递
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
