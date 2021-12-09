/*
    This is header file for src/tools/utils.c
*/

#ifndef CLEARTEMP_UTILS_HPP
#define CLEARTEMP_UTILS_HPP

#include <string>
#include <list>

//Used OS; 1 = Windows, 2 = Linux (UNIX), 3 = Mac, 0 = Incompatible | MAC IS NO LONGER SUPPORTED !!!
#ifdef _WIN32 //WINDOWS
#define os 1
#elif __unix__ //LINUX (UNIX)
#define os 2
#else //ELSE
#define os 0
#endif

namespace utils
{
    void print(std::string text); //This works just like normal cout, but uses logging system
    void printErr(std::string text, int exitCode); //Works like print(), but as ERR
    void printTranslate(std::string text); //This prints object using getDB()
    void printErrTranslate(std::string text, int exitCode); //Does almost same thing as print(), but prints error (cerr)
    void exitProgram(int code); //Exits program with given code (look for exitFlag in api.cpp for more)
    void loadInvalidFlags(std::string compatibleArgs[], std::list<std::string> args); //If flags contains more than compatibleArgs, program ends
    void loadInvalidLang(std::string compatible[], std::string lang); //If compatibles doesn't contain lang, program ends
    void generateLogFile(); //Creates logs file (for example 'logs/2021-12-7-02.log', where 2021 is year, 12 is month, 7 is day and it's third log that day)

    int getEncryptionKey(); //This void creates encryption file and returns "secret" value, which is password being encrypted with

    std::string getDB(std::string object); //Returns "object" from database; uses langFlag from flags.cpp
    std::string loadTemp(); //This returns path to temp
    std::string loadFlagText(std::string flag, std::list<std::string> args); //Returns flag text (if flag is something:ABCD, returns ABCD)

    bool isOsCompatible(); //Returns false if os == 0s
    bool argsContainsFlag(std::string flag, std::list<std::string> args); //Returns true if args contains flag
}

#endif
