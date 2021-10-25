/*
    This header file contains all flags for api.c and tools.c
*/

#ifndef CLEARTEMP_FLAGS_H
#define CLEARTEMP_FLAGS_H

#include <stdbool.h>

//CONSTANT VARIABLES (MAXIMUM SUPPORTED LENGTH)
#define compatible1L 8 //Length of first dimension of compatibleArgs in api.c
#define compatible2L 16  //Length of second dimension of compatibleArgs in api.c

#define arg1Size 16 //Length for first dimension of args in main.c
#define arg2Size 256 //Length for second dimension of args in main.c

#define lang1L 3 //Length for first dimension of compatibleLangs in api.c
#define lang2L 3 //Length for second dimension of compatibleLangs in api.c

#define flagTextL 64 //Length for text in flag ['flagText']

//VARIABLES
static bool consoleFlag = false; //If true doesn't close windows at end - waits for your input
static bool debugFlag = false; //If true, program just pretends it's deleting temp
static bool exitFlag = false; //If true shows exitCode and exitReason (console enable is recommended)

static char langFlag[] = "en"; //Language for getDB() in tools.h;

//GETTERS
bool getConsoleFlag(); //GETTER FOR consoleFlag
bool getDebugFlag(); //GETTER FOR debugFlag
bool getExitFlag(); //GETTER FOR exitFlag

char * getLangFlag(); //GETTER FOR langFlag

//SETTERS (CAN BE ALSO USED AS SETTER AND GETTER - RETURNS SET VALUE)
bool setConsoleFlag(bool object); //SETTER FOR consoleFlag
bool setDebugFlag(bool object); //SETTER FOR debugFlag
bool setExitFlag(bool object); //SETTER FOR exitFlag

char * setLangFlag(char object[]); //SETTER FOR langFlag

#endif
