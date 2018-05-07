#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(int& argc,char** argv)
{
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
