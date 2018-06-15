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
        void addStatement(Statement*);
        void addFunction(Function*);
        ReturnValue callFunc(const std::string&,std::list<ReturnValue>*);
        int run();

        void deleteRecord(const std::string&);
        void setValue(const std::string&,ReturnValue);
        ReturnValue getValue(const std::string&);
    private:
        std::map<std::string,SymbolTable*> table;
        std::vector<Statement*> stats;
        std::vector<Function*> funcs;

        std::stack<std::string> context;

        AstFactory();
        AstFactory(const AstFactory&)=delete ;
        AstFactory& operator=(const AstFactory&)=delete ;
        ~AstFactory();
};

#endif
