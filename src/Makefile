.PHONY:clean

CXX=g++
CFLAGS=-I../include -g -std=c++11

ASTSRC=Statement.cpp ReturnValue.cpp Expression.cpp ASTNode.cpp Literal.cpp Function.cpp AstFactory.cpp
OBJECTS=$(ASTSRC:%.cpp=%.o)

TARGET=assign_test ast_test create_test boolean_test calc_test condition_test If_test while_test

all:$(TARGET)

assign_test:$(OBJECTS) assign_test.cpp
	$(CXX) $(CFLAGS) $(OBJECTS) assign_test.cpp -o assign_test

ast_test:$(OBJECTS) ast_test.cpp
	$(CXX) $(CFLAGS) $(OBJECTS) ast_test.cpp -o ast_test

create_test:$(OBJECTS) create_test.cpp
	$(CXX) $(CFLAGS) $(OBJECTS) create_test.cpp -o create_test

boolean_test:$(OBJECTS) boolean_test.cpp
	$(CXX) $(CFLAGS) $(OBJECTS) boolean_test.cpp -o boolean_test

calc_test:$(OBJECTS) calc_test.cpp
	$(CXX) $(CFLAGS) $(OBJECTS) calc_test.cpp -o calc_test

condition_test:$(OBJECTS) condition_test.cpp
	$(CXX) $(CFLAGS) $(OBJECTS) condition_test.cpp -o condition_test

If_test:$(OBJECTS) If_test.cpp
	$(CXX) $(CFLAGS) $(OBJECTS) If_test.cpp -o If_test

while_test:$(OBJECTS) while_test.cpp
	$(CXX) $(CFLAGS) $(OBJECTS) while_test.cpp -o while_test

$(OBJECTS):$(ASTSRC)
	$(CXX) -c $(CFLAGS) $(ASTSRC)

clean:
	rm $(TARGET) $(OBJECTS)
