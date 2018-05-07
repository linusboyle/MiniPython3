/*
Simple Python Interpreter implementation by cpp
Copyright (C) 2018 LCC,ZZH,HZL,CYH

general abstract interpreter class


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
#ifndef PYINTERPRETER_H
#define PYINTERPRETER_H

#include "CommandLineParser.h"
#include <fstream>

enum interpreter_mode
{
    MODE_HELP,
    MODE_ERROR,
    MODE_INTERACTIVE,
    MODE_SCRIPT,
};

class PyInterpreter
{
    private:
        CommandLineParser commandlineparser;
        enum interpreter_mode mode;
        std::fstream fin;
    public:
        PyInterpreter(int& argc,char** argv);
        void exec();
        void setMode();
        void printHelp();
        bool streamInit(const std::string& filepath);
        void loop();
};

#endif
