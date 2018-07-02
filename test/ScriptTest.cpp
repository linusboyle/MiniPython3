/*脚本输入测试*/

/*你可以通过修改当前目录下的input.txt文件*
 *并运行此程序*
 * 来测试词法分析器的脚本分析功能*/

#include<iostream>
#include<fstream>
#include<string>
#include<tuple>
#include"Scanner.h"
#include"Symbol.h"
using namespace std;

ifstream input("input.txt");
Scanner scanner(input);

int main(){
	Symbol sym;
	int num_int;
	double num_double;
	string str;
	string SymbolToString[]
	{
		"nul",               "ident",               "number_int",       "number_double",       "str",

		"plus",             "minus",             "times",                    "slash",                    "lmove",
		"rmove",

		"false_py",     "true_py",          "none",                     "break_py",           "continue_py",  
		"for_py",         "while_py",       "def",                        "return_py",           "if_py",
		"else_py",       "elif",                  "global",                  "in",                           "and_py",
		"or_py",           "not_py",          "as",                           "assert",                  "class_py",
		"del",                "except",           "finally_py",            "from",                     "import",
		"is",                   "lambda",         "nonlocal",               "pass",                     "raise",
		"try_py",          "with",                "yield",   

		"percent",       "hash",               "at",                           "tilde",                      "becomes",
		"neq",               "lss",                   "leq",                         "gtr",                         "geq",
		"eql",                "lparen",            "rparen",                  "comma",                "semicolon",
		"caret",             "period",           "colon",                    "tab",                         "lsqr",
		"rsqr",               "newline",         "indent",                  "dedent",                  "pluseq",
		"minuseq",      "timeseq",        "slasheq",                "dbtimes",                "dbtimeseq",
		"dbslash",        "dbslasheq",    "percenteq",           "oreq",                       "andeq",
		"lmoveeq",      "rmoveeq",      "careteq"
	};

	while(!scanner.return_flag()){
		cout<<"---------test---------"<<endl;
		tie(sym,num_int,num_double,str)=scanner.return_output();
		string tmp="<";
		tmp+=SymbolToString[int(sym)];
		if(sym==Symbol::number_int){tmp+=" ";tmp+=to_string(num_int);}
		else if(sym==Symbol::number_double){tmp+=" ";tmp+=to_string(num_double);}
		else {tmp+=" ";tmp+=str;}
		tmp+=">";
		cout<<tmp<<endl;
	}
	return 0;
}