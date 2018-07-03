/*python 词法分析器*/

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

	/*设置tab记数栈*/
	tab_counter.push_back(0);

	/*设置单字符符号*/
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

	/*设置保留字列表，用于查找*/
	word=new string[Keyword_Symbol_number]{"False", "None", "True",  "and", "as", "assert",
		                                                                                       "break", "class", "continue", "def", "del", "elif",
										                                                       "else", "except", "finally", "for", "from", "global",
										                                                       "if", "import", "in", "is", "lambda", "nonlocal", "not",
									                                                          "or", "pass", "raise", "return", "try", "while", "with", "yield"};

	/*设置保留字符号*/
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
	int tab_check=0;//用作新行tab数检查
	try{
		if(cc==ll){
			line="";
			while(line==""){
				char buffer[256];
				if(in.getline(buffer, 256)){
					line.assign(buffer);
					line+="\n";
					//去除tab空行以及tab注释的情况
					int i=0; bool check=false;
					while(line[i]!='\n'&&line[i]!='#'){
						if(isalnum(line[i])){
							check=true;
							break;
						}
						i++;
					}
					if(!check) line="";//end
					else{    
						//前置tab记数
						int j=0;
						while(line[j]=='\t') j++;
						line=line.substr(j, line.length()-j);
						//end
						tab_check=check_tab(j);
					}
				}else{
					//cout<<"Scanner: No more scripts."<<endl;
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
	//tab数记录
	if(tab_check==1){//tab进
		ch=-128;
		return;
	}
	else if(tab_check<0){//tab回
		ch=-128-tab_check;//记录回复的层数
		return;
	}
	//end
	if(ll!=0){
		ch=line[cc];
		cc++;
	}else{
		ch='\0';
		is_empty=1;
		return;
	}
}



void Scanner::get_sym(){
	//如果有多个待返回的dedent，先返回
	if(tab_back>0){
		tab_back--;
		return;
	}
	while(ch==' '/*||ch=='\n'*/||ch=='#'){     //忽略空格以及注释，查找词头
		if(ch!='#') get_char();
		else{
			cc=ll;
			ch='\n';
			break;
		}
	}
	if(is_empty>0){return;}
	else if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||(ch=='_')){
		check_keyword_or_ident();     //关键字或标识符
	}
	else if(ch>='0'&&ch<='9'){
		check_number();     //数字
	}
	else if(ch=='\''||ch=='\"'){
		check_str();     //字符串
	}
	else if(ch==-128){//处理indent
		sym=Symbol::indent;
		id="indent";
		ch=' ';
	}
	else if(ch>=-127&&ch<0){//处理dedent
		sym=Symbol::dedent;
		id="dedent";
		tab_back=ch+127;
		ch=' ';
	}
	else {
		check_operator();     //操作符
	}
}



void Scanner::check_keyword_or_ident(){
	string tmp="";
	do{       
		//读入字符
		tmp.push_back(ch);
		get_char();
	}while((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||(ch=='_'));
	//搜索保留字,binary_search
	int position=-1;
	int bottom=0, top=Keyword_Symbol_number-1;
	while(bottom<=top){
		int mid=(bottom+top)/2;
		if(word[mid]<tmp) bottom=mid+1;
		else if(word[mid]>tmp) top=mid-1;
		else {position=mid;break;}
	}
	//更新符号信息
	if(position<0){
		//一般标识符
		sym=Symbol::ident;
		id=tmp;
	}
	else{
		//关键字
		sym=wsym[position];
		id=word[position];
	}
}



void Scanner::check_number(){
	int dot=0;      //dot表示有无小数点
	string tmp="";
	do{
		//读入字符
		tmp.push_back(ch);
		get_char();
		if(ch=='.') dot+=1;
	}while((ch>='0'&&ch<='9')||(ch=='.'&&dot<2));
	//检查数值语法
	bool not_number_rule=(tmp[0]=='0'&&tmp[1]!='.'&&tmp.length()!=1)||(tmp[tmp.length()-1]=='.');
	if(not_number_rule){
		cout<<"SyntaxError: invalid token"<<endl;
		exit(1);
	}
	//更新符号信息
	if(dot==0){
		//整数
		sym=Symbol::number_int;
		num_int=stoi(tmp);
		id=tmp;
	}
	else{
		//浮点数
		sym=Symbol::number_double;
		num_double=stod(tmp);
		id=tmp;
	}
}



void Scanner::check_str(){
	//假设为单引号隔离字符串
	bool is_apostrophe=(ch=='\'');
	//待确认的引号数目
	int counter=2;

	string tmp="";
	do{
		tmp.push_back(ch);

		//寻找单引号结束处
		if(ch=='\''&&is_apostrophe){
			//检查反斜杠（转义）
			int back_slant_counter=0;
			int i=2;
			while(tmp[tmp.length()-i]=='\\'){
				back_slant_counter+=1;
				i+=1;
			}
			if((back_slant_counter%2)==0) counter-=1;
		}

		//寻找双引号结束处
		if(ch=='\"'&&!is_apostrophe){
			//检查反斜杠
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
	//更新符号信息
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
	case '<':             //小于或者小于等于或左移运算
		get_char();
		if(ch=='='){
			sym=Symbol::leq;
			id="<=";
			ch=' ';
		}else if(ch=='<'){    //左移或左移等于
			get_char();
			if(ch=='='){
				sym=Symbol::lmoveeq;
				id="<<=";
				ch=' ';
			}else{
				sym=Symbol::lmove;
				id="<<";
			}
		}else{
			sym=Symbol::lss;
			id="<";
		}
		break;
	case '>':            //大于或大于等于或右移运算
		get_char();
		if(ch=='='){
			sym=Symbol::geq;
			id=">=";
			ch=' ';
		}else if(ch=='>'){    //右移或右移等于
			get_char();
			if(ch=='='){
				sym=Symbol::rmoveeq;
				id=">>=";
				ch=' ';
			}else{
				sym=Symbol::rmove;
				id=">>";
			}
		}else{
			sym=Symbol::gtr;
			id=">";
		}
		break;
	case '!':             //不等于或感叹号（无语义）
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
	case '=':           //等于或赋值
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
	case '+':        //加号或加等于
		get_char();
		if(ch=='='){
			sym=Symbol::pluseq;
			id="+=";
			ch=' ';
		}else{
			sym=Symbol::plus;
			id="+";
		}
		break;
	case '-':        //减号或减等于
		get_char();
		if(ch=='='){
			sym=Symbol::minuseq;
			id="-=";
			ch=' ';
		}else{
			sym=Symbol::minus;
			id="-";
		}
		break;
	case '*':        //乘号或乘等于或乘乘
		get_char();
		if(ch=='='){
			sym=Symbol::timeseq;
			id="*=";
			ch=' ';
		}else if(ch=='*'){  //乘乘或乘乘等于
			get_char();
			if(ch=='='){
				sym=Symbol::dbtimeseq;
				id="**=";
				ch=' ';
			}else{
				sym=Symbol::dbtimes;
				id="**";
				//ch=' ';
			}
		}else{
			sym=Symbol::times;
			id="*";
		}
		break;
	case '/':         //除号或除等于或除除
		get_char();
		if(ch=='='){
			sym=Symbol::slasheq;
			id="/=";
			ch=' ';
		}else if(ch=='/'){  //除除或除除等于
			get_char();
			if(ch=='='){
				sym=Symbol::dbslasheq;
				id="//=";
				ch=' ';
			}else{
				sym=Symbol::dbslash;
				id="//";
				//ch=' ';
			}
		}else{
			sym=Symbol::slash;
			id="/";
		}
		break;
	case '%':    //模或模等于
		get_char();
		if(ch=='='){
			sym=Symbol::percenteq;
			id="%=";
			ch=' ';
		}else{
			sym=Symbol::percent;
			id="%";
		}
		break;
	case '|':      //或或或等于
		get_char();
		if(ch=='='){
			sym=Symbol::oreq;
			id="|=";
			ch=' ';
		}else{
			sym=Symbol::or_py;
			id="|";
		}
		break;
	case '&':     //与或与等于
		get_char();
		if(ch=='='){
			sym=Symbol::andeq;
			id="&=";
			ch=' ';
		}else{
			sym=Symbol::and_py;
			id="&";
		}
		break;
	case '^':    //抑或或抑或等于
		get_char();
		if(ch=='='){
			sym=Symbol::careteq;
			id="^=";
			ch=' ';
		}else{
			sym=Symbol::caret;
			id="^";
		}
		break;
	default:          //其他的单字符
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



int Scanner::check_tab(int tab_num){
	if(tab_num>tab_counter.back()){
		tab_counter.push_back(tab_num);
		return 1;  //indent
	}
	else if(tab_num==tab_counter.back()){
		return 0;  //do nothing
	}
	else if(tab_num<tab_counter.back()/*&&tab_num==tab_counter[tab_counter.size()-2]*/){
		int ret=0;
		while(tab_counter.back()!=tab_num){
			tab_counter.pop_back();
			ret++;
		}
		return -ret;  //dedent
	}
	else {
		cout<<"#tab error!#"<<endl;
		exit(1);
	}  //wrong
}



void Scanner::stream_input(istream& input){
	//用于交互式编程时的即时输入
	is_empty=0;
	ch=' ';
	char tmp[256];
	input.getline(tmp,256);
	in<<tmp<<'\n';
}



tuple<Symbol,int,double,string> Scanner::return_output(){
	get_sym();
	if(is_empty>0){
		if(is_empty==1){
			is_empty=2;
			return make_tuple(Symbol::newline,0,0,"newline");
		}
		//若代码分析完，调用返回(nul,0,0,"")
		tab_counter.pop_back();
		if(tab_counter.size()!=0) return make_tuple(Symbol::dedent,0,0,"dedent");
		else{
			is_empty=3;
			cout<<"No more scripts."<<endl;
			return make_tuple(Symbol::nul,0,0,"");
		}
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
	return is_empty==3;
}



Scanner::~Scanner(){
	delete [] word;
	delete [] wsym;
	delete [] ssym;
	cout<<"Scanner destructed."<<endl;
}
