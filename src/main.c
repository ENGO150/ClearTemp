/*
    This file runs void clearTemp() from src/api.c with used args (except the first one [with index 0])
*/

#include <string.h>

#include <api.h>
#include <flags.h>

int main(__attribute__((unused)) int argc, char * argv[])
{
    //CREATE ARGS ARRAY
    char args[arg1Size][arg2Size];

    //INITIALIZE ARGS ARRAY
    for (int i = 1; i < arg1Size; i++)
    {
        if (argv[i])
        {
            strcpy(args[i - 1], argv[i]);
        } else
        {
            strcpy(args[i - 1], "\0");
        }
    }

    //START API VOID WITH ARGS
    clearTemp(args);
    return 0;
}
