#ifndef FUNCTION_h
#define FUNCTION_h

#include "Statement.h"
#include <list>

class Function{
    private:
        std::string id;
        int _args_count;
        std::string* args_name;
        std::shared_ptr<Suite> body;
    public:
        std::string getID();
        Function(std::string,int,std::string*,std::shared_ptr<Suite>);
        ReturnValue execFunc(std::list<ReturnValue>*);
        ~Function();
};

#endif
