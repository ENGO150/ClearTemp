/*
    This source file contains all getters and setters for flags.h


    Note: *almost* every void here is explained in flags.h
*/

#include <string.h>

#include <flags.h>

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

char * getLangFlag()
{
    return langFlag;
}

//SETTERS
bool setConsoleFlag(bool object)
{
    consoleFlag = object;
}

bool setDebugFlag(bool object)
{
    debugFlag = object;
}

bool setExitFlag(bool object)
{
    exitFlag = object;
}

char * setLangFlag(char object[])
{
    strcpy(langFlag, object);

    return langFlag;
}