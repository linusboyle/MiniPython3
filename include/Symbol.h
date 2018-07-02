/*对词类的枚举*/

#ifndef SYMBOL_H
#define SYMBOL_H

enum Symbol{
	nul,               ident,               number_int,       number_double,        str,//无语义的类型、标识符、整数、浮点数、字符串

	plus,             minus,             times,                    slash,                    lmove,
	rmove,                     //算术和位移运算符

	false_py,     true_py,          none,                     break_py,           continue_py,  
	for_py,         while_py,       def,                        return_py,           if_py,
	else_py,       elif,                  global,                  in,                           and_py,
	or_py,           not_py,          as,                           assert,                  class_py,
	del,                except,           finally_py,            from,                     import,
	is,                   lambda,         nonlocal,               pass,                     raise,
	try_py,          with,                yield,                                           //py保留字

	percent,       hash,               at,                           tilde,                      becomes,
	neq,               lss,                   leq,                         gtr,                         geq,
	eql,                lparen,            rparen,                  comma,                semicolon,
	caret,             period,           colon,                    tab,                        lsqr,
	rsqr,               newline,         indent,                  dedent //其他字符
};
//Keyword_Symbol_number=33

#endif