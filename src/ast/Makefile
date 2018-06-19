.PHONY:clean

ASTSRC=Statement.cpp ReturnValue.cpp Expression.cpp ASTNode.cpp Literal.cpp Function.cpp AstFactory.cpp
OBJECTS=$(ASTSRC:%.cpp=%.o)
export

all:$(OBJECTS) lib test

$(OBJECTS):$(ASTSRC)
	$(CXX) -c $(CFLAGS) $(ASTSRC)

lib:$(OBJECTS)
	ar rcs $(LIBPATH)/libast.a $(OBJECTS)

test:
	make -C $(ROOT)/test

clean:
	rm $(OBJECTS)
	make -C $(ROOT)/test clean
