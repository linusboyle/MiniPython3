#ifndef ASTFACTORY_H
#define ASTFACTORY_H

#include "Function.h"
#include <stack>

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
        void addStatement(std::shared_ptr<Statement>);
        void addFunction(std::shared_ptr<Function>);
        ReturnValue callFunc(const std::string&,std::list<ReturnValue>*);
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
        AstFactory(const AstFactory&)=delete ;
        AstFactory& operator=(const AstFactory&)=delete ;
        ~AstFactory();
};

#endif
