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

//the command line argument parser class
#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(int& argc,char** argv)
{
    //convert to cpp style
    for(int i=0;i<argc;i++)
    {
        tokens.push_back(std::string(argv[i]));
    }
}

bool CommandLineParser::optionExist(const std::string& option)
{
    return std::find(tokens.begin(),tokens.end(),option)!=this->tokens.end();
}

const std::string& CommandLineParser::getOption(const std::string& option)
{
    auto itr=std::find(tokens.begin(),tokens.end(),option);
    if(itr!=this->tokens.end()&&++itr!=this->tokens.end())
    {
        return *itr;
    }
    const static std::string empty_string="";
    return empty_string;
}

int CommandLineParser::getArgc()
{
    return tokens.size();
}

const std::string& CommandLineParser::getFileName()
{
    return tokens[1];
}
