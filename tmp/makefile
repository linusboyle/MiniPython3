all: ScriptTest.exe DynamicTest.exe

DynamicTest.exe: Scanner.o DynamicTest.o
	g++ -o DynamicTest.exe Scanner.o DynamicTest.o

DynamicTest.o: DynamicTest.cpp Scanner.h Symbol.h
	g++ -c DynamicTest.cpp Scanner.h Symbol.h

ScriptTest.exe: Scanner.o ScriptTest.o
	g++ -o ScriptTest.exe ScriptTest.o Scanner.o

ScriptTest.o: ScriptTest.cpp Scanner.h Symbol.h
	g++ -c ScriptTest.cpp Scanner.h Symbol.h

Scanner.o: Scanner.cpp Scanner.h Symbol.h
	g++ -c Scanner.cpp Scanner.h Symbol.h

clean:
	del *.exe *.o *.gch