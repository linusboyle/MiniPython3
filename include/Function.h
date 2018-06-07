#ifndef FUNCTION_h
#define FUNCTION_h

#include "Statement.h"
#include <list>

class Function:public Suite{
    private:
        std::string id;
        int _args_count;
        std::string* args_name;
    public:
        std::string getID();
        Function(int,std::string*);
        ReturnValue execFunc(std::list<ReturnValue>*);
        ~Function();
};

#endif
