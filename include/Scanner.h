/*python 词法分析器*/

#ifndef SCANNER_H
#define SCANNER_H
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include<tuple>
#include<vector>
#include"Symbol.h"
using namespace std;

class Scanner{
private:
	/*读入的单个字符*/
	char ch=' ';

	/*当前分析的行*/
	string line="";

	/*当前行的长度（line length）*/
	int ll=0;

	/*当前字符在行中的位置（character counter）*/
	int cc=0;

	/*当前的单词符号*/
	Symbol sym;

	/*保留字列表*/
	string* word;

	/*保留字对应的符号值*/
	Symbol* wsym;

	/*单字符的符号值*/
	Symbol* ssym;

	/*输入流*/
	stringstream in;

	/*分析完全flag*/
	bool is_empty=false;

	/*tab计数栈*/
	vector<int> tab_counter;

	/*tab回退数*/
	int tab_back=0;

public:
	/*标识符名字（如果是标识符）*/
	string id="";

	/*数值大小（如果是数字）*/
	int num_int=0;
	double num_double=0.0;

	/*字符串内容（如果是字符串）*/
	string str_content="";

	/*词法分析器的构造与初始化*/
	Scanner();
	Scanner(ifstream&);
	Scanner(istream&);

	/*读取一个字符*/
	void get_char();

	/*获取词法符号*/
	void get_sym();

	/*分析关键字或者标识符*/
	void check_keyword_or_ident();

	/*分析数字*/
	void check_number();

	/*分析字符串*/
	void check_str();

	/*分析操作符*/
	void check_operator();

	/*分析缩进个数*/
	int check_tab(int);

	/*交互输入流*/
	void stream_input(istream&);

	/*返回分析结果*/
	tuple<Symbol,int,double,string> return_output();

	/*返回分析完全flag*/
	bool return_flag();

	/*析构函数*/
	~Scanner();

};
#endif
