/*
    This source file contains all getters and setters for flags.h


    Note: *almost* every void here is explained in flags.h
*/

#include "../../include/flags.hpp"

#include <string>

//GETTERS
bool getConsoleFlag()
{
    return consoleFlag;
}

bool getDebugFlag()
{
    return debugFlag;
}

bool getExitFlag()
{
    return exitFlag;
}

bool getLogFlag()
{
    return logFlag;
}

std::string getLangFlag()
{
    return langFlag;
}

std::string getLogTextFlag()
{
    return logTextFlag;
}

std::string getUsernameFlag()
{
    return username;
}

//SETTERS
bool setConsoleFlag(bool object)
{
    consoleFlag = object;

    return consoleFlag;
}

bool setDebugFlag(bool object)
{
    debugFlag = object;

    return debugFlag;
}

bool setExitFlag(bool object)
{
    exitFlag = object;

    return exitFlag;
}

bool setLogFlag(bool object)
{
    logFlag = object;

    return logFlag;
}

std::string setLangFlag(std::string object)
{
    langFlag = object;

    return langFlag;
}

std::string setLogTextFlag(std::string object)
{
    logTextFlag = object;

    return logTextFlag;
}

std::string setUsernameFlag(std::string object)
{
    username = object;

    return object;
}