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

//enumeration of all the possible returntype
//It is an imitation of Object-Oriented feature
enum _return_type_
{
    RETURN_ERROR,
    RETURN_NONETYPE,
    RETURN_INT,
    RETURN_FLOAT,
    RETURN_STRING,
    RETURN_BOOLEAN,
};

class ReturnValue
{
    public:
        //different types of value
        int integer_value;
        double double_value;
        std::string string_value;
        bool boolean_value;
        //Keyword keyword_value;
        //Operator operator_value;

        //indicate the type
        enum _return_type_ type=RETURN_NONETYPE;

        //all kinds of constructors
        ReturnValue(_return_type_=RETURN_NONETYPE);
        ReturnValue(double);
        ReturnValue(int);
        ReturnValue(bool);
        //I dont want to take char as input,which will be convert to int
        ReturnValue(char)=delete;
        ReturnValue(std::string);

        //NOTE
        //explicit here
        //explicit ReturnValue(Keyword&);
        //explicit ReturnValue(Operator&);

        //this will convert the int_value to true or false based on >0 or =0
        //bool convertBool();

        //CHANGED
        //now it will be bool to int
        int convert2int() const;

        bool checkfalse() const;

        ~ReturnValue();

        //all kinds of operator overload
        //if the type is not compatible they will throw RETURN_ERROR
        friend bool _same_type(const ReturnValue&,const ReturnValue&);

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



        friend ReturnValue operator<(const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator>(const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator==(const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator!=(const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator>=(const ReturnValue&,const ReturnValue&);
        friend ReturnValue operator<=(const ReturnValue&,const ReturnValue&);
        //friend ReturnValue operator+ (const ReturnValue&,const ReturnValue&);
        //friend ReturnValue operator+ (const ReturnValue&,const ReturnValue&);
};


//list all the keyword in python3
//not all of them will be implemented,though
//enum _py_keywords_
//{
    //NOT_KEYWORD,
    //KEYWORD_TRUE,
    //KEYWORD_FALSE,
    //KEYWORD_NONE,
    //KEYWORD_AND,
    //KEYWORD_AS,
    //KEYWORD_ASSERT,
    //KEYWORD_BREAK,
    //KEYWORD_CLASS,
    //KEYWORD_CONTINUE,
    //KEYWORD_DEF,
    //KEYWORD_DEL,
    //KEYWORD_ELIF,
    //KEYWORD_ELSE,
    //KEYWORD_EXCEPT,
    //KEYWORD_FINALLY,
    //KEYWORD_FOR,
    //KEYWORD_FROM,
    //KEYWORD_GLOBAL,
    //KEYWORD_IF,
    //KEYWORD_IMPORT,
    //KEYWORD_IN,
    //KEYWORD_IS,
    //KEYWORD_LAMBDA,
    //KEYWORD_NONLOCAL,
    //KEYWORD_NOT,
    //KEYWORD_OR,
    //KEYWORD_PASS,
    //KEYWORD_RAISE,
    //KEYWORD_RETURN,
    //KEYWORD_TRY,
    //KEYWORD_WHILE,
    //KEYWORD_WITH,
    //KEYWORD_YIELD,
//};



//likewise
//enum _py_operators_
//{
    ////ARITHMETIC
    //PLUS,
    //SUBSTRACT,
    //MULTIPLY,
    //DIVIDE_INT,
    //DIVIDE_FLOAT,
    //MODULUS,
    //EXPONENT,
    ////COMPARISON
    //GREATER,
    //LESS,
    //EQUAL,
    //NOT_EQUAL,
    //GREATER_EQUAL,
    //LESS_EQUAL,
    ////LOGICAL
    //AND,
    //OR,
    //NOT,
    ////BITWISE
    //BIT_AND,
    //BIT_OR,
    //BIT_NOT,
    //BIT_XOR,
    //RIGHT_SHIFT,
    //LEFT_SHIFT,
    ////NOTE
    ////IM SURE I NEED MORE
    //NOT_OPERATOR,
//};

//class Newline:public ASTNode
//{
    //public:
        //Newline(ASTNode* =nullptr);
        //ReturnValue exec();
//};

//class Number:public ASTNode
//{
    //private:
        //int number_value;
    //public:
        //Number(int value);
        //int exec();
//};

//class String:public ASTNode
//{
    //private:
        //std::string stringliteral;
    //public:
        //String(std::string literal);
        //std::string exec();
//};

//wrapper for keyword,inherit astnode
//class Keyword:public ASTNode
//{
    //private:
        //enum _py_keywords_ type;
    //public:
        //Keyword(enum _py_keywords_=NOT_KEYWORD);
        //_py_keywords_ getType();
        ////ReturnValue exec();
//};

//likewise
//class Operator:public ASTNode
//{
    //private:
        //enum _py_operators_ type;
    //public:
        //Operator(enum _py_operators_=NOT_OPERATOR);
        //_py_operators_ getType();
        ////ReturnValue exec();
//};
#endif
