/*python �ʷ�������*/

#define Keyword_Symbol_number 33
#include"Scanner.h"
#include"Symbol.h"
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include<tuple>
using namespace std;



Scanner::Scanner(){
	cout<<"Scanner constructing...";

	/*���õ��ַ�����*/
	ssym=new Symbol[256];
	ssym['+']=Symbol::plus;
	ssym['-']=Symbol::minus;
	ssym['*']=Symbol::times;
	ssym['/']=Symbol::slash;
	ssym['&']=Symbol::and_py;
	ssym['|']=Symbol::or_py;
	ssym['!']=Symbol::not_py;
	ssym['^']=Symbol::caret;
	ssym['=']=Symbol::becomes;
	ssym['%']=Symbol::percent;
	ssym['#']=Symbol::hash;
	ssym['@']=Symbol::at;
	ssym['~']=Symbol::tilde;
	ssym['<']=Symbol::lss;
	ssym['>']=Symbol::gtr;
	ssym['(']=Symbol::lparen;
	ssym[')']=Symbol::rparen;
	ssym[',']=Symbol::comma;
	ssym[';']=Symbol::semicolon;
	ssym['.']=Symbol::period;
	ssym[':']=Symbol::colon;
	ssym['\t']=Symbol::tab;
	ssym['[']=Symbol::lsqr;
	ssym[']']=Symbol::rsqr;
	ssym['\n']=Symbol::newline;

	/*���ñ������б����ڲ���*/
	word=new string[Keyword_Symbol_number]{"False", "None", "True",  "and", "as", "assert",
		                                                                                       "break", "class", "continue", "def", "del", "elif",
										                                                       "else", "except", "finally", "for", "from", "global",
										                                                       "if", "import", "in", "is", "lambda", "nonlocal", "not",
									                                                          "or", "pass", "raise", "return", "try", "while", "with", "yield"};

	/*���ñ����ַ���*/
	wsym=new Symbol[Keyword_Symbol_number ];
	wsym[0]=Symbol::false_py;
	wsym[1]=Symbol::none;
	wsym[2]=Symbol::true_py;
	wsym[3]=Symbol::and_py;
	wsym[4]=Symbol::as;
	wsym[5]=Symbol::assert;
	wsym[6]=Symbol::break_py;
	wsym[7]=Symbol::class_py;
	wsym[8]=Symbol::continue_py;
	wsym[9]=Symbol::def;
	wsym[10]=Symbol::del;
	wsym[11]=Symbol::elif;
	wsym[12]=Symbol::else_py;
	wsym[13]=Symbol::except;
	wsym[14]=Symbol::finally_py;
	wsym[15]=Symbol::for_py;
	wsym[16]=Symbol::from;
	wsym[17]=Symbol::global;
	wsym[18]=Symbol::if_py;
	wsym[19]=Symbol::import;
	wsym[20]=Symbol::in;
	wsym[21]=Symbol::is;
	wsym[22]=Symbol::lambda;
	wsym[23]=Symbol::nonlocal;
	wsym[24]=Symbol::not_py;
	wsym[25]=Symbol::or_py;
	wsym[26]=Symbol::pass;
	wsym[27]=Symbol::raise;
	wsym[28]=Symbol::return_py;
	wsym[29]=Symbol::try_py;
	wsym[30]=Symbol::while_py;
	wsym[31]=Symbol::with;
	wsym[32]=Symbol::yield;

	cout<<"finished."<<endl;
}



Scanner::Scanner(ifstream& input) : Scanner(){
	cout<<"Scanner(ifstream&)...";
	if(input.is_open()){
		in<<input.rdbuf();
	}
	else cout<<"#Error! Scanner::Scanner(ifstream&)#"<<endl;
	cout<<"finished"<<endl;
}



Scanner::Scanner(istream& input) : Scanner(){
	cout<<"Scanner(istream&)...";
	string tmp;
	input>>tmp;
	in<<tmp;
	cout<<"finished"<<endl;
}



void Scanner::get_char(){
	try{
		if(cc==ll){
			line="";
			while(line==""){
				char buffer[256];
				if(in.getline(buffer, 256)){
					line.assign(buffer);
					line+="\n";
					//ȥ��tab�����Լ�tabע�͵����
					int i=0; bool check=false;
					while(line[i]!='\n'&&line[i]!='#'){
						if(isalnum(line[i])){
							check=true;
							break;
						}
						i++;
					}
					if(!check) line="";//
				}else{
					cout<<"Scanner: No more scripts."<<endl;
					in.clear();
					break;
				}
			}
			ll=line.length();
			cc=0;
		}
	}catch(...){
		throw "#Errors! Scanner::get_char()#\n";
	}
	if(ll!=0){
		ch=line[cc];
		cc++;
	}else{
		ch='\0';
		is_empty=true;
		return;
	}
}



void Scanner::get_sym(){
	while(ch==' '/*||ch=='\n'*/||ch=='#'){     //���Կո��Լ�ע�ͣ����Ҵ�ͷ
		if(ch!='#') get_char();
		else{
			cc=ll;
			ch='\n';
			break;
		}
	}
	if(is_empty){return;}
	else if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||(ch=='_')){
		check_keyword_or_ident();     //�ؼ��ֻ��ʶ��
	}
	else if(ch>='0'&&ch<='9'){
		check_number();     //����
	}
	else if(ch=='\''||ch=='\"'){
		check_str();     //�ַ���
	}
	else {
		check_operator();     //������
	}
}



void Scanner::check_keyword_or_ident(){
	string tmp="";
	do{       
		//�����ַ�
		tmp.push_back(ch);
		get_char();
	}while((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||(ch=='_'));
	//����������,binary_search
	int position=-1;
	int bottom=0, top=Keyword_Symbol_number-1;
	while(bottom<=top){
		int mid=(bottom+top)/2;
		if(word[mid]<tmp) bottom=mid+1;
		else if(word[mid]>tmp) top=mid-1;
		else {position=mid;break;}
	}
	//���·�����Ϣ
	if(position<0){
		//һ���ʶ��
		sym=Symbol::ident;
		id=tmp;
	}
	else{
		//�ؼ���
		sym=wsym[position];
		id=word[position];
	}
}



void Scanner::check_number(){
	int dot=0;      //dot��ʾ����С����
	string tmp="";
	do{
		//�����ַ�
		tmp.push_back(ch);
		get_char();
		if(ch=='.') dot+=1;
	}while((ch>='0'&&ch<='9')||(ch=='.'&&dot<2));
	//�����ֵ�﷨
	bool not_number_rule=(tmp[0]=='0'&&tmp[1]!='.'&&tmp.length()!=1)||(tmp[tmp.length()-1]=='.');
	if(not_number_rule){
		cout<<"SyntaxError: invalid token"<<endl;
		exit(1);
	}
	//���·�����Ϣ
	if(dot==0){
		//����
		sym=Symbol::number_int;
		num_int=stoi(tmp);
		id=tmp;
	}
	else{
		//������
		sym=Symbol::number_double;
		num_double=stod(tmp);
		id=tmp;
	}
}



void Scanner::check_str(){
	//����Ϊ�����Ÿ����ַ���
	bool is_apostrophe=(ch=='\'');
	//��ȷ�ϵ�������Ŀ
	int counter=2;

	string tmp="";
	do{
		tmp.push_back(ch);

		//Ѱ�ҵ����Ž�����
		if(ch=='\''&&is_apostrophe){
			//��鷴б�ܣ�ת�壩
			int back_slant_counter=0;
			int i=2;
			while(tmp[tmp.length()-i]=='\\'){
				back_slant_counter+=1;
				i+=1;
			}
			if((back_slant_counter%2)==0) counter-=1;
		}

		//Ѱ��˫���Ž�����
		if(ch=='\"'&&!is_apostrophe){
			//��鷴б��
			int back_slant_counter=0;
			int i=2;
			while(tmp[tmp.length()-i]=='\\'){
				back_slant_counter+=1;
				i+=1;
			}
			if((back_slant_counter%2)==0) counter-=1;
		}

		get_char();
	}while(counter>0);
	//���·�����Ϣ
	sym=Symbol::str;
	id=tmp;
	if(is_apostrophe){
		str_content=tmp.substr(1,tmp.length()-2);
	}else{
		str_content=tmp.substr(1,tmp.length()-2);
	}
}



void Scanner::check_operator(){
	switch(ch){
	case '<':             //С�ڻ���С�ڵ��ڻ���������
		get_char();
		if(ch=='='){
			sym=Symbol::leq;
			id="<=";
			ch=' ';
		}else if(ch=='<'){
			sym=Symbol::lmove;
			id="<<";
			ch=' ';
		}else{
			sym=Symbol::lss;
			id="<";
		}
		break;
	case '>':            //���ڻ���ڵ��ڻ���������
		get_char();
		if(ch=='='){
			sym=Symbol::geq;
			id=">=";
			ch=' ';
		}else if(ch=='>'){
			sym=Symbol::rmove;
			id=">>";
			ch=' ';
		}else{
			sym=Symbol::gtr;
			id=">";
		}
		break;
	case '!':             //�����ڻ��̾�ţ������壩
		get_char();
		if(ch=='='){
			sym=Symbol::neq;
			id="!=";
			ch=' ';
		}else{
			sym=Symbol::nul;
			id="!";
		}
		break;
	case '=':           //���ڻ�ֵ
		get_char();
		if(ch=='='){
			sym=Symbol::eql;
			id="==";
			ch=' ';
		}else{
			sym=Symbol::becomes;
			id="=";
		}
		break;
	default:          //�����ĵ��ַ�
		sym=ssym[ch];
		if(ch=='\t') id="\\t";
		else if(ch=='\n') id="\\n";
		else{
			id="";
			id.push_back(ch);
		}
		get_char();
		break;
	}
}



void Scanner::stream_input(istream& input){
	//���ڽ���ʽ���ʱ�ļ�ʱ����
	is_empty=false;
	ch=' ';
	char tmp[256];
	input.getline(tmp,256);
	in<<tmp<<'\n';
}



tuple<Symbol,int,double,string> Scanner::return_output(){
	get_sym();
	if(is_empty){
		//����������꣬���÷���(nul,0,0,"")
		return make_tuple(Symbol::nul,0,0,"");
	}
	switch(sym){
	case Symbol::number_int:
		return make_tuple(sym,num_int,0,id);
	case Symbol::number_double:
		return make_tuple(sym,0,num_double,id);
	case Symbol::str:
		return make_tuple(sym,0,0,str_content);
	default:
		return make_tuple(sym,0,0,id);
	}
}



bool Scanner::return_flag(){
	return is_empty;
}



Scanner::~Scanner(){
	delete [] word;
	delete [] wsym;
	delete [] ssym;
	cout<<"Scanner destructed."<<endl;
}
