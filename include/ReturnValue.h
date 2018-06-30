/*
Simple Python Interpreter implementation by cpp
Copyright (C) 2018 LCC,ZZH,HZL,CYH

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses.
*/

#ifndef RETURNVALUE_H
#define RETURNVALUE_H

#include <string>
#include <iostream>
#include <vector>

#define DEBUG std::cout<<"from file "<<__FILE__<<",line "<<__LINE__<<":"
//enumeration of all the possible returntype
//It is an imitation of Object-Oriented feature
enum _return_type_
{
    RETURN_ERROR    ,//error
    RETURN_NONETYPE ,//none,converted to false if possible
    RETURN_INT      ,
    RETURN_FLOAT    ,//actually double
    RETURN_STRING   ,
    RETURN_BOOLEAN  ,

    //these three is for control flow
    //in common conditions it's the same as error
    RETURN_BREAK    ,
    RETURN_CONTINUE ,
    RETURN_RETURN   ,

    RETURN_TUPLE    ,
    RETURN_LIST     ,
};

class ReturnValue
{
    private:
        //FIXME
        //the values should all be private
        //and provide get and set functions
        //consider about that later
    public:
        //different types of value
        int integer_value=0;
        double double_value=0.0;
        std::string string_value = "";
        bool boolean_value=false;

        //used when it's a RETURN_RETURN
        ReturnValue* true_value=nullptr;
        //used both by tuple and list,infact the list and tuple are both fake,being a wrapper around std::vector.
        //based on the diffence of type,it will allow or not allow inserting
        std::vector<ReturnValue>* container=nullptr;
        //indicate the type
        enum _return_type_ type=RETURN_NONETYPE;

        //all kinds of constructors
        ReturnValue(_return_type_=RETURN_NONETYPE,ReturnValue* value=nullptr);
        ReturnValue(_return_type_,const std::vector<ReturnValue>&);
        ReturnValue(double);
        ReturnValue(int);
        ReturnValue(bool);
        //I dont want to take char as input,which will be converted to int
        ReturnValue(char)=delete;

        ReturnValue(std::string);

        //interpret the value to bool or int if possible
        int convert2int() const;
        bool convert2bool() const;

        //FIXME
        //consider using pointer in this class
        ~ReturnValue();

        //all kinds of operator overload
        //if the type is not compatible they will throw RETURN_ERROR

        //utility function
        friend bool _same_type(const ReturnValue&,const ReturnValue&);

        //Arith
        friend ReturnValue operator+ (const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator- (const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator* (const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator/ (const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator% (const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator| (const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator& (const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator^ (const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator~ (const ReturnValue&);
        friend ReturnValue operator<< (const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator>> (const ReturnValue&,const ReturnValue&);

        //Compare
        friend ReturnValue operator<(const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator>(const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator==(const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator!=(const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator>=(const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator<=(const ReturnValue&,const ReturnValue&);

        friend std::ostream& operator<<(std::ostream&,const ReturnValue&);
};

#endif
