/*python �ʷ�������*/

#ifndef SCANNER_H
#define SCANNER_H
#include"Scanner.h"
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include<tuple>
#include"Symbol.h"
using namespace std;



class Scanner{
private:
	/*����ĵ����ַ�*/
	char ch=' ';

	/*��ǰ��������*/
	string line="";

	/*��ǰ�еĳ��ȣ�line length��*/
	int ll=0;

	/*��ǰ�ַ������е�λ�ã�character counter��*/
	int cc=0;

	/*��ǰ�ĵ��ʷ���*/
	Symbol sym;

	/*�������б�*/
	string* word;

	/*�����ֶ�Ӧ�ķ���ֵ*/
	Symbol* wsym;

	/*���ַ��ķ���ֵ*/
	Symbol* ssym;

	/*������*/
	stringstream in;

	/*������ȫflag*/
	bool is_empty=false;

public:
	/*��ʶ�����֣�����Ǳ�ʶ����*/
	string id="";

	/*��ֵ��С����������֣�*/
	int num_int=0;
	double num_double=0.0;

	/*�ַ������ݣ�������ַ�����*/
	string str_content="";

	/*�ʷ��������Ĺ������ʼ��*/
	Scanner();
	Scanner(ifstream&);
	Scanner(istream&);

	/*��ȡһ���ַ�*/
	void get_char();

	/*��ȡ�ʷ�����*/
	void get_sym();

	/*�����ؼ��ֻ��߱�ʶ��*/
	void check_keyword_or_ident();

	/*��������*/
	void check_number();

	/*�����ַ���*/
	void check_str();

	/*����������*/
	void check_operator();

	/*����������*/
	void stream_input(istream&);

	/*���ط������*/
	tuple<Symbol,int,double,string> return_output();

	/*���ط�����ȫflag*/
	bool return_flag();

	/*��������*/
	~Scanner();

};
#endif