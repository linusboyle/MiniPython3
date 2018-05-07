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
        <<"interpreter [-h][SCIPTPATH]"<<std::endl
        <<"-h:print this help and exit"<<std::endl
        <<"SCIPTPATH:the python3 script file path"<<std::endl
        <<"Note:without file input interpreter will start interactive mode"<<std::endl;
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
                std::cout<<"Wrong command,Please see the help page"<<std::endl;
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
                //TODO
                fin.std::ios::rdbuf(std::cin.rdbuf());
                loop();
                break;
            }
        case MODE_SCRIPT:
            {
                if(streamInit(commandlineparser.getFileName()))
                {
                    //TODO
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
