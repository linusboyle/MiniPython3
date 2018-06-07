#ifndef OPERATOR_H
#define OPERATOR_H

enum boolop
{
    AND,
    OR,
};


enum unaryop
{
    NOT,
    INVERT,//BITWISE NOT
    UADD,
    USUB,
};

enum binop
{
    ADD,
    SUB,
    MULT,
    DIV,
    FLOORDIV,
    MOD,
    POW,
    LSHIFT,
    RSHIFT,
    BITOR,
    BITAND,
    BITXOR,//^
    //MATMULT which is @
};

enum compareop
{
    EQ,
    NOTEQ,
    LT,
    GT,
    LTE,
    GTE,
};
#endif
