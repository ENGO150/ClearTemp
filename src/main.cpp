/*
    This file runs void clearTemp() from src/tools/api.cpp with used args (except the first one [with index 0])
*/

#include <list>
#include <string>

#include "../include/api.hpp"

int main(int argc, char * argv[])
{
    std::list<std::string> args;

    for (int i = 1; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
    
    clearTemp(args);
        
    return 0;
}