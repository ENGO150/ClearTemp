/*
    This header file contains all flags for api.c and tools.c
*/

#ifndef CLEARTEMP_FLAGS_HPP
#define CLEARTEMP_FLAGS_HPP

#include <string>

//CONSTANT VARIABLES (MAXIMUM SUPPORTED LENGTH)
#define compatibleL 9 //Length of compatibleFlags in api.cpp

#define langL 3 //Length of compatibleLangs in api.cpp

//VARIABLES
static bool consoleFlag = false; //If true doesn't close windows at end - waits for your input
static bool debugFlag = false; //If true, program just pretends it's deleting temp
static bool exitFlag = false; //If true shows exitCode and exitReason (console enable is recommended)
static bool logFlag = false; //If true generates logs in logs/ folder (look for logTextFlag)

static std::string langFlag = "en"; //Language for getDB() in tools.h;
static std::string logTextFlag; //If logFlag is true, void print() uses this as output file | This variable is in format: YYYY-MM-DD-XX
static std::string username; //This is used in void getUser() in utils.hpp

//GETTERS
bool getConsoleFlag(); //GETTER FOR consoleFlag
bool getDebugFlag(); //GETTER FOR debugFlag
bool getExitFlag(); //GETTER FOR exitFlag
bool getLogFlag(); //GETTER FOR logFlag

std::string getLangFlag(); //GETTER FOR langFlag
std::string getLogTextFlag(); //GETTER FOR logTextFlag
std::string getUsernameFlag(); //GETTER FOR username

//SETTERS (CAN BE ALSO USED AS SETTER AND GETTER - RETURNS SET VALUE)
bool setConsoleFlag(bool object); //SETTER FOR consoleFlag
bool setDebugFlag(bool object); //SETTER FOR debugFlag
bool setExitFlag(bool object); //SETTER FOR exitFlag
bool setLogFlag(bool object); //SETTER FOR logFlag

std::string setLangFlag(std::string object); //SETTER FOR langFlag
std::string setLogTextFlag(std::string object); //SETTER FOR logTextFlag
std::string setUsernameFlag(std::string object); //SETTER FOR username

#endif
