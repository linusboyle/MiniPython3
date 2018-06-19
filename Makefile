ROOT=$(shell pwd)
CXX=g++
CFLAGS=-I$(ROOT)/include -g -std=c++17
LIBPATH=$(ROOT)/lib
export

.PHONY:clean

all:ast

ast:
	make -C src/ast

clean:
	make clean -C src/ast
