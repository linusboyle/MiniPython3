.PHONY:clean

TARGET=assign_test ast_test create_test boolean_test calc_test condition_test If_test while_test funcdef_test

all:$(TARGET) ../lib/libast.a
	@echo ast test has been compiled:$(TARGET)

assign_test: assign_test.cpp
	$(CXX) $(CFLAGS) assign_test.cpp -o assign_test -L$(LIBPATH) -l:libast.a

ast_test: ast_test.cpp
	$(CXX) $(CFLAGS) ast_test.cpp -o ast_test -L$(LIBPATH) -l:libast.a

create_test: create_test.cpp
	$(CXX) $(CFLAGS) create_test.cpp -o create_test -L$(LIBPATH) -l:libast.a

boolean_test: boolean_test.cpp
	$(CXX) $(CFLAGS) boolean_test.cpp -o boolean_test -L$(LIBPATH) -l:libast.a 

calc_test: calc_test.cpp
	$(CXX) $(CFLAGS) calc_test.cpp -o calc_test -L$(LIBPATH) -l:libast.a

condition_test: condition_test.cpp
	$(CXX) $(CFLAGS) condition_test.cpp -o condition_test -L$(LIBPATH) -l:libast.a

If_test: If_test.cpp
	$(CXX) $(CFLAGS) If_test.cpp -o If_test -L$(LIBPATH) -l:libast.a

while_test: while_test.cpp
	$(CXX) $(CFLAGS) while_test.cpp -o while_test  -L$(LIBPATH) -l:libast.a

funcdef_test: funcdef_test.cpp
	$(CXX) $(CFLAGS) funcdef_test.cpp -o funcdef_test  -L$(LIBPATH) -l:libast.a

clean:
	rm $(TARGET)
