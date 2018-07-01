/*�Դ����ö��*/

#ifndef SYMBOL_H
#define SYMBOL_H

enum Symbol{
	nul,               ident,               number_int,       number_double,        str,//����������͡���ʶ�������������������ַ���

	plus,             minus,             times,                    slash,                    lmove,
	rmove,                     //������λ�������

	false_py,     true_py,          none,                     break_py,           continue_py,  
	for_py,         while_py,       def,                        return_py,           if_py,
	else_py,       elif,                  global,                  in,                           and_py,
	or_py,           not_py,          as,                           assert,                  class_py,
	del,                except,           finally_py,            from,                     import,
	is,                   lambda,         nonlocal,               pass,                     raise,
	try_py,          with,                yield,                                           //py������

	percent,       hash,               at,                           tilde,                      becomes,
	neq,               lss,                   leq,                         gtr,                         geq,
	eql,                lparen,            rparen,                  comma,                semicolon,
	caret,             period,           colon,                    tab,                        lsqr,
	rsqr,                //�����ַ�
};
//Keyword_Symbol_number=33

#endif