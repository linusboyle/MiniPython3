#include "Function.h"

class SymbolTable{
    private:
        std::map<std::string,ReturnValue> table;
    public:
        //void addRecord(std::string,ReturnValue);
        void deleteRecord(const std::string&);
        void setValue(const std::string&,ReturnValue);
        ReturnValue getValue(const std::string&);
};

class AstFactory{
    public:
        static AstFactory& getinstance();
        //void init();
        void addStatement(Statement*);
        void addFunction(Function*);
        //std::string getContext();
        ReturnValue callFunc(const std::string&,std::list<ReturnValue>*);
        int run();

        //void addRecord(std::string,ReturnValue);
        void deleteRecord(const std::string&);
        void setValue(const std::string&,ReturnValue);
        ReturnValue getValue(const std::string&);
    private:
        std::map<std::string,SymbolTable*> table;
        std::vector<Statement*> stats;
        std::vector<Function*> funcs;

        std::string context;

        AstFactory();
        AstFactory(const AstFactory&)=delete ;
        AstFactory& operator=(const AstFactory&)=delete ;
        ~AstFactory();
};
