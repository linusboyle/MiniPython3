/*
Simple Python Interpreter implementation by cpp
Copyright (C) 2018 LCC,ZZH,HZL,CYH

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses.
*/


//general abstract interpreter class

#ifndef PYINTERPRETER_H
#define PYINTERPRETER_H

#include "CommandLineParser.h"
#include "Scanner.h"

//enumeration indicating the mode to run this program
//
//enum interpreter_mode
//{
    //MODE_HELP,
    //MODE_ERROR,
    //MODE_INTERACTIVE,
    //MODE_SCRIPT,
//};

class PyInterpreter
{
    private:
        CommandLineParser* commandlineparser;
        //enum interpreter_mode mode;
        //Scanner* sc;
        std::ifstream fin;
        void printHelp();
        void streamInit(const std::string& filepath);
        //void setMode();
        //void loop();
    public:
        //static PyInterpreter& getApp();
        PyInterpreter(int argc,char** argv);
        //std::tuple<Symbol,int,double,string> lex();
        void exec();
        //general loop for both modes,to exit from interactive mode call the exit(0) function;
        ~PyInterpreter();
};

#endif
