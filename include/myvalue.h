#pragma once
#include <string>
#include <memory>
#include <vector>
#include "AST.h"

struct myvalue
{
	bool intflag;
	int num_int;
	double num_double;
	std::string str;
	std::shared_ptr<ASTNode> p;
	std::vector<std::shared_ptr<Statement>> svec;
	std::vector<std::shared_ptr<Expression>> evec;
	std::vector<std::shared_ptr<Argument>> avec;
	
	myvalue(){}
	myvalue(int x) : num_int(x) {}
	myvalue(double x) : num_double(x) {}
	myvalue(std::string x) : str(x) {}
};

