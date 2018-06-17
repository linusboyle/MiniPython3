//Include this file before using ast
//you should not include other files though
//to tell the truth,it will throw compilation error
//do not try that :)

#ifndef ABSTRACT_SYNTAX_TREE_H
    #define ABSTRACT_SYNTAX_TREE_H

    #include "Statement.h"
    #include "AstFactory.h"
    //that's enough XD

    //a strange and stupid template
    template<class T>
    const std::shared_ptr<T>& clone(const std::shared_ptr<T>& old){
        return std::dynamic_pointer_cast<T>(old->shared_from_this());
    }

    #define CREATE(x,y...) std::make_shared<x>(y)

#endif

//why do you open this file?
