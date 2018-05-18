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
#include "PyInterpreter.h"
#include <iostream>

PyInterpreter::PyInterpreter(int& argc,char** argv):commandlineparser(argc,argv)
{
}

void PyInterpreter::setMode()
{
    if(commandlineparser.optionExist("-h"))
    {
        mode=MODE_HELP;
        return;
    }
    switch(commandlineparser.getArgc())
    {
        //FIXME
        //here's a problem taking input "-v" alone
        case 1:
        {
            mode=MODE_INTERACTIVE;
            break;
        }
        case 2:
        {
            mode=MODE_SCRIPT;
            break;
        }
        default:
        {
            mode=MODE_ERROR;
            break;
        }
    }
}

void PyInterpreter::printHelp()
{
    std::cout<<"Mini Python3 Interpreter"<<std::endl<<"Copyright 2018 HZL,LCC,CYH,ZZH"<<std::endl<<std::endl
        <<"interpreter [-h][SCIPTPATH]"<<std::endl<<std::endl
        <<"  -h:print this help and exit"<<std::endl
        <<"  SCIPTPATH:the python3 script file path"<<std::endl
        <<"NOTE:without file input interpreter will start interactive mode"<<std::endl;
}

bool PyInterpreter::streamInit(const std::string& filepath)
{
    fin.open(filepath,std::ios::in);
    return fin.is_open();
}

void PyInterpreter::loop()
{
    while(!fin.eof())
    {
        //TODO
        //read from string and pass it to analyser
        std::string input;
        std::getline(fin,input);
    }
}

void PyInterpreter::exec()
{
    setMode();
    switch(mode)
    {
        case MODE_ERROR:
            {
                std::cout<<"Wrong command,please see the help page"<<std::endl;
                printHelp();
                break;
            }
        case MODE_HELP:
            {
                printHelp();
                break;
            }
        case MODE_INTERACTIVE:
            {
                //NOTE:
                //I have redirect fin to cin,for consistency and reuse of function loop();
                fin.std::ios::rdbuf(std::cin.rdbuf());
                loop();
                break;
            }
        case MODE_SCRIPT:
            {
                if(streamInit(commandlineparser.getFileName()))
                {
                    loop();
                }
                else
                {
                    std::cout<<"File "<<commandlineparser.getFileName()<<" does not exist,check the path"<<std::endl;
                    return;
                }
                break;
            }
        default:
            {
                std::cout<<"unknown error,check enumeration"<<std::endl;
                break;
            }
    }
}
