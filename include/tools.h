/*
    This is header file for src/assets/tools.c
*/

#ifndef CLEARTEMP_TOOLS_H
#define CLEARTEMP_TOOLS_H

#include <flags.h>

//Used OS; 1 = Windows, 2 = Linux (UNIX), 3 = Mac, 0 = Incompatible | MAC IS NO LONGER SUPPORTED !!!
#ifdef _WIN32 //WINDOWS
    #define os 1
#elif __unix__ //LINUX (UNIX)
    #define os 2
#else //ELSE
    #define os 0
#endif

void print(char object[]); //This prints object from langFlag.edb using langFlag (api.h) (edb stands for "ENGO DataBase", which is my database system; lib/engodatabase/edb.h)
void printErr(char object[], int exitCode); //Does almost same thing as print(), but prints stderr
void exitProgram(int code); //Exits program with code (look for exitFlag in api.h for more)
void loadInvalidFlags(const char compatibleArgs[compatible1L][compatible2L], char args[arg1Size][arg2Size]); //If flags contains more than compatibleArgs, program ends
void loadInvalidLang(const char compatible[lang1L][lang2L], char target[]); //If compatible doesn't contain target, program ends
void loadFlagText(const char flag[compatible2L], char args[arg1Size][arg2Size], char * target); //Returns flag text (if flag is something:ABCD, returns ABCD)

int getEncryptionKey(); //This void creates encryption file and returns "secret" value, which is password being encrypted with

char * getDB(char object[]); //Returns "object" from database; uses langFlag from flags.c
char * replaceString(const char * word, const char * wordFind, const char * wordReplace, char ** store); //This void finds wordFind in word, then replaces it with wordReplace and if store isn't NULL, stores that value in store, otherwise it returns the value
char * loadTemp(char username[]); //This returns path to temp

bool isOsCompatible(); //Returns false if os == 0
bool argsContainsFlag(const char flag[compatible2L], char args[arg1Size][arg2Size]); //Returns true if args contains flag

#endif
