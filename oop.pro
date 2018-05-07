DESTDIR = ./bin
TARGET = interpreter
CONFIG = warn_on c++11 
INCLUDEPATH += ./include

path_src = ./src
path_header = ./include
SOURCES = $$path_src/*
HEADERS = $$path_header/*
