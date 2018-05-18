#include "Statement.h"
//#include <iostream>

ReturnValue Pass_Statement::exec()
{
    //do nothing special
    return RETURN_NONETYPE;
}

ReturnValue Expression_Statement::exec()
{
    return getChild(0)->exec();
}

Expression_Statement::Expression_Statement(Expression* content):Statement(1)
{
    add(content);
}

//ReturnValue Simple_Statement::exec()
//{
    //for(int i=0,n=getChildNumber();i!=n;++i)
    //{
         //dynamic_cast<Statement*>(getChild(i))->exec();
    //}
    //return ReturnValue();
//}

//void Simple_Statement::addChild(Statement* child)
//{
    //auto child_small_stmt=dynamic_cast<Small_Statement*>(child);
    //if(child_small_stmt!=nullptr)
    //{
        //add(child_small_stmt);
    //}
    //else
    //{
        //std::cout<<"RuntimeError:Child type noncompatible"<<std::endl;
        //exit(1);
    //}
//}

////NOTE
////I am not sure if this will work
//Simple_Statement::Simple_Statement(int count,...):Statement(count)
//{
    //va_list valist;

    //va_start(valist,count);

    //for(int i=0;i<count;++i)
    //{
        //addChild(va_arg(valist,Statement*));
    //}
//}


//Small_Statement::Small_Statement():Statement(1){};

//ReturnValue Small_Statement::exec()
//{
    //return dynamic_cast<Statement*>(getChild(0))->exec();
//}
