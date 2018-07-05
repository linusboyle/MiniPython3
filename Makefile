ROOT=$(shell pwd)
CXX=g++
CFLAGS=-I$(ROOT)/include -g -std=c++17
LIBPATH=$(ROOT)/lib
export

.PHONY:clean

all:ast lexer tests main gui

ast:
	make -C src/ast

lexer:
	make -C src/lexer

tests:
	make -C test

main:
	make -C src

gui:
	cd src/gui && qmake -makefile && cd $(ROOT)
	make -C src/gui

clean:
	make clean -C src/ast
	make clean -C src/gui
	make clean -C test 
	rm src/gui/Makefile
