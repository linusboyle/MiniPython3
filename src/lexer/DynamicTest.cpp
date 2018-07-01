/*交互式输入测试*/

/*你可以运行此程序*
 *并且动态输入python命令*
 *来测试词法分析器的交互式分析功能*/

#include<iostream>
#include<string>
#include<tuple>
#include"Scanner.h"
#include"Symbol.h"
using namespace std;

Scanner scanner;

int main(){
	Symbol sym;
	int num_int;
	double num_double;
	string str;
	string SymbolToString[65]
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
		"rsqr"                "newline"
	};


	cout<<"---------Python Scanner Test----------"<<endl;
	cout<<"press Ctrl C to exit this program in cmd.\n"<<endl;

	while(true){
		cout<<">>>";
		scanner.stream_input(cin);
		while(!scanner.return_flag()){
			tie(sym,num_int,num_double,str)=scanner.return_output();
			string tmp="<";
			tmp+=SymbolToString[int(sym)];
			if(sym==Symbol::number_int){tmp+=" ";tmp+=to_string(num_int);}
			else if(sym==Symbol::number_double){tmp+=" ";tmp+=to_string(num_double);}
			else {tmp+=" ";tmp+=str;}
			tmp+=">";
			cout<<tmp<<endl;
		}
	}
	return 0;
}