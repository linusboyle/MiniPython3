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
#ifndef  COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H
#include <string>
#include <vector>
#include <algorithm>

class CommandLineParser
{
    private:
        std::vector<std::string> tokens;
    public:
        CommandLineParser(int& argc,char** argv);
        int getArgc();
        const std::string& getFileName();
        bool optionExist(const std::string& option);
        const std::string& getOption(const std::string &option);
};

#endif
