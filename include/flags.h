/*
    This header file contains all flags for api.c and tools.c
*/

#ifndef CLEARTEMP_FLAGS_H
#define CLEARTEMP_FLAGS_H

#include <stdbool.h>

//CONSTANT VARIABLES
#define compatible1L 8 //Length of first dimension of compatibleArgs in api.c
#define compatible2L 16  //Length of second dimension of compatibleArgs in api.c

#define arg1Size 16
#define arg2Size 256

#define lang1L 3
#define lang2L 3

//VARIABLES
static bool consoleFlag = false; //If true doesn't close windows at end - waits for your input
static bool debugFlag = false; //If true, program just pretends it's deleting temp
static bool exitFlag = false; //If true shows exitCode and exitReason (console enable is recommended)

static char langFlag[] = "en"; //Language for getDB() in tools.h;

//GETTERS
bool getConsoleFLag();
bool getDebugFLag();
bool getExitFLag();

char * getLangFLag();

//SETTERS
bool setConsoleFLag(bool object);
bool setDebugFLag(bool object);
bool setExitFLag(bool object);

char * setLangFlag(char object[]);

#endif