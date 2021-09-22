/*
    This is header file for src/assets/tools.c
*/

#ifndef CLEARTEMP_TOOLS_H
#define CLEARTEMP_TOOLS_H

static bool consoleFlag = false; //If true doesn't close windows at end - waits for your input
static bool debugFlag = false; //If true program just pretends it's deleting temp
static bool exitFlag = true; //If true shows exitCode and exitReason (console enable is recommended)
//static char  * usernameFlag = ""; //Username for path to temp; This is used only for Windows (code 2)
static char * langFlag = "en"; //Language for getDB()

bool isOsCompatible(); //Returns false if os == 0

void print(char object[]); //This prints object from langFlag.edb using langFlag (api.h) (edb stands for "ENGO DataBase", which is my database system; lib/engodatabase/edb.h)
void printErr(char object[], int exitCode); //Does almost same thing as print(), but prints stderr
void exitProgram(int code); //Exits program with code (look for exitFlag in api.h for more)

char * getDB(char object[]); //Returns "object" from database; look for "langFlag"
char * replaceString(const char * word, const char * wordFind, const char * wordReplace, char ** store); //This void finds wordFind in word, then replaces it with wordReplace and if store isn't NULL, stores that value in store, otherwise it returns the value

//int getEncryptionKey(); //This void creates encryption config and returns "secret" value
#endif
