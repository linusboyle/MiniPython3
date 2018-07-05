#include "PyInterpreter.h"
#include "myvalue.h"
#include "simple.tab.h"

static Scanner* sc;

int yylex()
{
	yylval = *(new myvalue(1));

	Symbol sym;
	int num_int;
	double num_double;
	string str;

	std::tie(sym, num_int, num_double, str) = sc -> return_output();
	//cout << "sym = " << sym << " ";
	//if (sym == Symbol::newline) cout << endl;
	if (sym == Symbol::ident) yylval.str = str;
	if (sym == Symbol::number_int) {yylval.intflag = true;yylval.num_int = num_int;}
	if (sym == Symbol::number_double) {yylval.intflag = false;yylval.num_double = num_double;}
	if (sym == Symbol::str) yylval.str = str;

	if (sym == Symbol::pluseq) yylval.num_int = 0;
	if (sym == Symbol::minuseq) yylval.num_int = 1;
	if (sym == Symbol::timeseq) yylval.num_int = 2;
	if (sym == Symbol::slasheq) yylval.num_int = 3;
	if (sym == Symbol::percenteq) yylval.num_int = 5;
	if (sym == Symbol::andeq) yylval.num_int = 10;
	if (sym == Symbol::oreq) yylval.num_int = 9;
	if (sym == Symbol::careteq) yylval.num_int = 11;
	if (sym == Symbol::lmoveeq) yylval.num_int = 7;
	if (sym == Symbol::rmoveeq) yylval.num_int = 8;
	if (sym == Symbol::dbtimeseq) yylval.num_int = 6;
	if (sym == Symbol::dbslasheq) yylval.num_int = 4;
	//augassign: "+=" | "-=" | "*=" | "/=" | "%=" | "&=" | "|=" | "^=" | "<<=" | ">>=" | "**=" | "//=";
	if (sym == Symbol::lss) yylval.num_int = 2;
	if (sym == Symbol::gtr) yylval.num_int = 3;
	if (sym == Symbol::eql) yylval.num_int = 0;
	if (sym == Symbol::geq) yylval.num_int = 5;
	if (sym == Symbol::leq) yylval.num_int = 4;
	if (sym == Symbol::neq) yylval.num_int = 1;
	//comp_op: '<'|'>'|"=="|">="|"<="|"!=";

	switch (sym)
	{
		case Symbol::nul : return 0;
		case Symbol::ident : return NAME;
		case Symbol::number_int : return NUMBER;
		case Symbol::number_double : return NUMBER;
		case Symbol::str : return STRING;
		case Symbol::plus : return 43; // +
		case Symbol::minus : return 45; // -
		case Symbol::times : return 42; // *
		case Symbol::slash : return 47; // /
		case Symbol::lmove : return 293; // <<
		case Symbol::rmove : return 294; // >>

		case Symbol::false_py : return 299; // False
		case Symbol::true_py : return 298; // True
		case Symbol::none : return 297; // None
		case Symbol::break_py : return 278; // break
		case Symbol::continue_py : return 279; // continue
		case Symbol::for_py : return 284; // for
		case Symbol::while_py : return 283; // while
		case Symbol::def : return 264; // def
		case Symbol::return_py : return 280; // return
		case Symbol::if_py : return 281; // if
		case Symbol::else_py : return 282; // else
		case Symbol::elif : return 0;
		case Symbol::global : return 0;
		case Symbol::in : return 285; // in
		case Symbol::and_py : return 287; // and
		case Symbol::or_py : return 286; // or
		case Symbol::not_py : return 288; // not
		case Symbol::as : return 0;
		case Symbol::assert : return 0;
		case Symbol::class_py : return 0;
		case Symbol::del : return 277; // del
		case Symbol::except : return 0;
		case Symbol::finally_py : return 0;
		case Symbol::from : return 0;
		case Symbol::import : return 0;
		case Symbol::is : return 0;
		case Symbol::lambda : return 0;
		case Symbol::nonlocal : return 0;
		case Symbol::pass : return 0;
		case Symbol::raise : return 0;
		case Symbol::try_py : return 0;
		case Symbol::with : return 0;
		case Symbol::yield : return 0;

		case Symbol::percent : return 37; // %
		case Symbol::hash : return 0; // #
		case Symbol::at : return 0; // @
		case Symbol::tilde : return 126; // ~
		case Symbol::becomes : return 61; // =
		case Symbol::neq : return 292; // !=
		case Symbol::lss : return 60; // <
		case Symbol::leq : return 291; // <=
		case Symbol::gtr : return 62; // >
		case Symbol::geq : return 290; // >=
		case Symbol::eql : return 289; // ==
		case Symbol::lparen : return 40; // (
		case Symbol::rparen : return 41; // )
		case Symbol::comma : return 44; // ,
		case Symbol::semicolon : return 59; // ;
		case Symbol::caret : return 94; // ^
		case Symbol::period : return 0; // .
		case Symbol::colon : return 58; // :
		case Symbol::tab : return 0; // \t
		case Symbol::lsqr : return 91; // [
		case Symbol::rsqr : return 93; // ]
		case Symbol::newline : return NEWLINE;
		case Symbol::indent : return INDENT;
		case Symbol::dedent : return DEDENT;

		case Symbol::pluseq : return 265; // +=
		case Symbol::minuseq : return 266; // -=
		case Symbol::timeseq : return 267; // *=
		case Symbol::slasheq : return 268; // /=
		case Symbol::dbtimes : return 296; // **
		case Symbol::dbtimeseq : return 275; // **=
		case Symbol::dbslash : return 295; // //
		case Symbol::dbslasheq : return 276; // //=
		case Symbol::percenteq : return 269; // %=
		case Symbol::oreq : return 271; // |=
		case Symbol::andeq : return 270; // &=
		case Symbol::lmoveeq : return 273; // <<=
		case Symbol::rmoveeq : return 274; // >>=
		case Symbol::careteq : return 272; // ^=

		default: return 0;
	}
	return 0;
}

void yyerror(string msg)
{
	cout << "ERROR : " << msg << endl;
	return;
}

PyInterpreter::PyInterpreter(int argc,char** argv){
    commandlineparser=new CommandLineParser(argc,argv);
}

 void PyInterpreter::printHelp(){
     std::cout<<"Mini Python3 Interpreter,2018 All Right Reserved"<<std::endl;
     std::cout<<"This Program Is Under GPL.v3,to See More,Visit GNU Website"<<std::endl;
     std::cout<<"Writtern by Chen Yihao,Lv Chuancheng,Zhang Zihe,Han Zhilei,as Project in Object-Oriented Programming Class"<<std::endl;
     std::cout<<"To Learn More about This Program,see doc/ Folder"<<std::endl;
     std::cout<<std::endl;
     std::cout<<std::endl;
     std::cout<<std::endl;
     std::cout<<"Usage:minipy [-h|-v][FILE]"<<std::endl;
     std::cout<<"-h:Print This Help And Exit"<<std::endl;
     std::cout<<"-v:Print Version And Exit"<<std::endl;
     std::cout<<"FILE:the File You Want To RUN"<<std::endl;
     std::cout<<std::endl;
     std::cout<<std::endl;
     std::cout<<"This Program does not Have Interactive Mode"<<std::endl;
}

void PyInterpreter::streamInit(const std::string& filepath){
    fin.open(filepath);
}

PyInterpreter::~PyInterpreter(){
    delete commandlineparser;
}

void PyInterpreter::exec(){
    if(commandlineparser->optionExist("-h")){
        printHelp();
        return;
    }
    else if(commandlineparser->optionExist("-v")){
        std::cout<<"Version Beta,Patch Level 51,Go to github for Record"<<std::endl;
        std::cout<<"https://github.com/linusboyle/MiniPython3"<<std::endl;
        return;
    }
    else if(commandlineparser->getArgumentNumber()==0){
        std::cout<<"Error Parsing,Read the Help Below:"<<std::endl;
        printHelp();
        return;
    }
    else {
        streamInit(commandlineparser->getFileName());
        sc=new Scanner(fin);
        yyparse();
        int result=factory.run();
        if(result>0){
            std::cout<<"During RunTime Your Code Throw Error.This is not a Fatal One According To Our Analysis"<<std::endl;
            std::cout<<"This may Happen Due to Minor Grammar That We don't Implement,But Chances are That You may Make Some Mistakes as Well"<<std::endl;
            std::cout<<"The Error is From the "<<result<<"th Statement,Further Discussion Should Be Carried Out Yourself"<<std::endl;
        }
        return;
    }
}
