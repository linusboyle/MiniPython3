.PHONY:clean

all:assign_test

assign_test:assign_test.cpp Statement.cpp ReturnValue.cpp Expression.cpp ASTNode.cpp Literal.cpp Function.cpp AstFactory.cpp
	g++ assign_test.cpp Statement.cpp ReturnValue.cpp Expression.cpp ASTNode.cpp Literal.cpp Function.cpp AstFactory.cpp -I../include -o assign_test -g

clean:
	rm assign_test
