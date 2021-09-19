/*
    Here you can find all the utilities like isOsCompatible() and much more.

    ! I DO NOT RECOMMEND USING THESE IN YOUR PROJECT !


    Note: *almost* every void here is explained in tools.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../../lib/engodatabase/edb.h"

#include "../../include/tools.h"

//Used OS; 1 = Windows, 2 = Linux (UNIX), 3 = Mac, 0 = Incompatible
#ifdef _WIN32 //WINDOWS
int os = 1;
#elif __unix__ //LINUX (UNIX)
int os = 2;
/*#elif __APPLE__ //MAC | MAC IS NO LONGER SUPPORTED !!!
int os = 3;
*/#endif

bool isOsCompatible()
{
    return os != 0;
}

void exitProgram(int code)
{
    //TODO: Add exitFlag from api.h; This is just test

    printf("Exiting with code %d.", code);

    exit(code);
}

char * getDB(char object[])
{
    char * final[256];
    readString(object , fopen("../res/en.edb", "r"), final);
    return * final;
}

void print(char object[])
{
    printf("%s\n", getDB(object));
}

void printErr(char object[], int exitCode)
{
    fprintf(stderr, "%s\n", getDB(object));
    exitProgram(exitCode);
}

char * getUser()
{
    //TODO: Edit with usernameFlag flag + add json + Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)

    if (usernameFlag == NULL)
    {
        print("enter_username");

        char username_[64];
        scanf("%s", username_);

        printf("%s", username_);

        strcpy(usernameFlag, username_);
    } else
    {
        printf("B");
    }

    return "A";
    return usernameFlag;
}

int getEncryptionKey()
{
    FILE * configFile;
    char fileLoc[256];

    //WINDOWS
    if (os == 1)
    {
        strcpy(fileLoc, "C:/Users/");
    } else if (os == 2) //LINUX
    {
        strcpy(fileLoc, "/home/");
    }

    strcat(fileLoc, getUser());
    strcat(fileLoc, "/.block.ecfg");

    return 0;
}