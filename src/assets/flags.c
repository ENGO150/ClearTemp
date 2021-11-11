/*
    This source file contains all getters and setters for flags.h


    Note: *almost* every void here is explained in flags.h
*/

#include <string.h>

#include "../../include/flags.h"

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

char * getLangFlag()
{
    return langFlag;
}

char * getLogTextFlag()
{
    return logTextFlag;
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

char * setLangFlag(char object[])
{
    strcpy(langFlag, object);

    return langFlag;
}

char * setLogTextFlag(char object[])
{
    strcpy(logTextFlag, object);

    return logTextFlag;
}
