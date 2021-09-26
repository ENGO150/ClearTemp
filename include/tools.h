/*
    This is header file for src/assets/tools.c
*/

#ifndef CLEARTEMP_TOOLS_H
#define CLEARTEMP_TOOLS_H

#include <api.h>

#define compatibleL 8

static bool consoleFlag = false; //If true doesn't close windows at end - waits for your input
static bool debugFlag = false; //If true program just pretends it's deleting temp
static bool exitFlag = false; //If true shows exitCode and exitReason (console enable is recommended)

static char * langFlag = "en"; //Language for getDB()

bool isOsCompatible(); //Returns false if os == 0

void print(char object[]); //This prints object from langFlag.edb using langFlag (api.h) (edb stands for "ENGO DataBase", which is my database system; lib/engodatabase/edb.h)
void printErr(char object[], int exitCode); //Does almost same thing as print(), but prints stderr
void exitProgram(int code); //Exits program with code (look for exitFlag in api.h for more)
void loadInvalidFlags(const char compatible[compatibleL][16], char args[arg1Size][arg2Size]); //If flags contains more than compatible, program ends

char * getDB(char object[]); //Returns "object" from database; look for "langFlag"
char * replaceString(const char * word, const char * wordFind, const char * wordReplace, char ** store); //This void finds wordFind in word, then replaces it with wordReplace and if store isn't NULL, stores that value in store, otherwise it returns the value
char * loadTemp(char username[]); //This returns path to temp

//int getEncryptionKey(); //This void creates encryption in ENV and returns "secret" value
#endif
