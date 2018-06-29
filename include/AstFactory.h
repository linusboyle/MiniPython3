#ifndef ASTFACTORY_H
#define ASTFACTORY_H

#include <stack>
#include "Function.h"

#ifndef factory
#   define factory AstFactory::getinstance()
#endif

class SymbolTable{
    private:
        std::map<std::string,ReturnValue> table;
    public:
        void deleteRecord(const std::string&);
        void setValue(const std::string&,ReturnValue);
        ReturnValue getValue(const std::string&);
};

//单例类
class AstFactory{
    public:
        static AstFactory& getinstance();

        void addStatement(const std::shared_ptr<Statement>&);
        void addFunction(const std::shared_ptr<Function>&);

        //TODO
        //重构函数实现，采用可变模板传参数
        //DONE
        //废弃：改功能由调用本身来完成

        const std::shared_ptr<Function>& getFunc(const std::string&);

        //template<class... Arg>
        //ReturnValue callFunc(const std::string& id,Arg... arg){
            //for(int i=0,n=funcs.size();i!=n;++i){
                //if(funcs[i]->getID()==id){
                    //context.push(id);

                    ////if not created or is aborted,create it
                    //if(table.count(id)==0||table[id]==nullptr){
                        //table[id]=new SymbolTable();
                    //}

                    //ReturnValue result=funcs[i]->execFunc(arg...);

                    ////switch back to original context
                    //context.pop();

                    ////abort the local context
                    //delete table[id];

                    //return result;
                //}
            //}
            //return RETURN_ERROR;
        //}

        void createScope(const std::string&);
        void deleteScope(const std::string&);

        int run();

        void deleteRecord(const std::string&);
        void setValue(const std::string&,ReturnValue);
        ReturnValue getValue(const std::string&);
    private:
        std::map<std::string,SymbolTable*> table;
        std::vector<std::shared_ptr<Statement>> stats;
        std::vector<std::shared_ptr<Function>> funcs;

        std::stack<std::string> context;

        AstFactory();//内置函数放在这里




        AstFactory(const AstFactory&)=delete;
        AstFactory(AstFactory&&)=delete;
        AstFactory& operator=(const AstFactory&)=delete;
        AstFactory& operator=(AstFactory&&)=delete;
        ~AstFactory();
};

#endif
