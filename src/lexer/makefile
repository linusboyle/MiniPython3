.PHONY:clean

all: lib

lib: Scanner.o
	ar rcs $(LIBPATH)/liblexer.a Scanner.o

Scanner.o: Scanner.cpp
	g++ $(CFLAGS) -c Scanner.cpp

clean:
	rm *.o
