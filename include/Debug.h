#ifndef DEBUG_H
#define DEBUG_H

#include "ReturnValue.h"
#include "Literal.h"

std::ostream& operator<<(std::ostream& out,const ReturnValue& from)
{
    switch(from.type)
    {
        case RETURN_ERROR:
            out<<"RETURN_ERROR"<<std::endl;
            return out;
        case RETURN_NONETYPE:
            out<<"RETURN_NONETYPE"<<std::endl;
            return out;
        case RETURN_INT:
            out<<"RETURN_INT "<<from.integer_value<<std::endl;
            return out;
        case RETURN_STRING:
            out<<"RETURN_STRING "<<from.string_value<<std::endl;
            return out;
        case RETURN_FLOAT:
            out<<"RETURN_FLOAT "<<from.double_value<<std::endl;
            return out;
        case RETURN_BOOLEAN:
            out<<"RETURN_BOOLEAN ";
            if(from.boolean_value)
                out<<"true"<<std::endl;
            else
                out<<"false"<<std::endl;
            return out;
        case RETURN_BREAK:
            out<<"RETURN_BREAK "<<std::endl;
            return out;
        case RETURN_CONTINUE:
            out<<"RETURN_CONTINUE "<<std::endl;
            return out;
        case RETURN_RETURN:
            out<<"RETURN_RETURN ";
            if(from.true_value){
                out<<from.true_value;
            }
            return out;
    }
}

#define DEBUG std::cout<<"from file "<<__FILE__<<",line "<<__LINE__<<":"

#endif //DEBUG_H
