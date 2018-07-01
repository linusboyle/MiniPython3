ROOT=$(shell pwd)
CXX=g++
CFLAGS=-I$(ROOT)/include -g -std=c++17
LIBPATH=$(ROOT)/lib
export

.PHONY:clean

all:ast gui

ast:
	make -C src/ast

gui:
	cd src/gui && qmake -makefile && cd $(ROOT)
	make -C src/gui

clean:
	make clean -C src/ast
	make clean -C src/gui
	rm src/gui/Makefile
