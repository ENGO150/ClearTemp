/*
    This source file contains all getters and setters for flags.h
*/

#include <string.h>

#include <flags.h>

//GETTERS
bool getConsoleFLag()
{
    return consoleFlag;
}

bool getDebugFLag()
{
    return debugFlag;
}

bool getExitFLag()
{
    return exitFlag;
}

char * getLangFLag()
{
    return langFlag;
}

//SETTERS
bool setConsoleFLag(bool object)
{
    consoleFlag = object;
}

bool setDebugFLag(bool object)
{
    debugFlag = object;
}

bool setExitFLag(bool object)
{
    exitFlag = object;
}

char * setLangFlag(char object[])
{
    strcpy(langFlag, object);

    return langFlag;
}