/*
    Here you can find all the utilities like isOsCompatible() and much more.
    ! I DO NOT RECOMMEND USING THESE IN YOUR PROJECT !

    Note: *almost* every void here is explained in tools.h
*/

#include "../../include/utils.hpp"

#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <filesystem>

#include <nlohmann/json.hpp>

#include "../../include/flags.hpp"

using namespace std;

fstream loggingFile;

void writeLog(string text) //WRITE LOG IF IS LOGGING ENABLED
{
    if (!getLogFlag()) return; //LOGGING IS DISABLED

    //WRITE LOG
    loggingFile.write(text.c_str(), text.length());
}

namespace utils
{
    string getDB(string object)
    {
        fstream dat_file("res/" + getLangFlag() + ".json", ios::in);

        nlohmann::json database;
        dat_file >> database;

        return database[object];
    }

    void print(string text)
    {
        cout << text;

        writeLog(text);
    }

    void printErr(string text, int exitCode)
    {
        cerr << text;

        writeLog(text);

        exitProgram(exitCode);
    }

    void printTranslate(string text)
    {
        cout << getDB(text) << endl;

        writeLog(getDB(text) + "\n");
    }

    void printErrTranslate(string text, int exitCode)
    {
        cerr << getDB(text) << endl;

        writeLog(getDB(text) + "\n");

        exitProgram(exitCode);
    }

    void exitProgram(int code)
    {
        if (getExitFlag())
        {
            string reason;

            //GETTING REASON
            switch (code)
            {
                //GOOD
                case 104:
                    reason = getDB(":)");
                    break;
                case 103:
                    reason = getDB("excex_exit");
                    break;
                case 102:
                    reason = getDB("temp_unblocked_exit");
                    break;
                case 101:
                    reason = getDB("temp_blocked_exit");
                    break;
                case 0:
                    reason = getDB("temp_deleted_exit");
                    break;

                //BAD
                case 1:
                    reason = getDB("not_compatible_os_exit");
                    break;
                case 2:
                    reason = getDB("username_linux_exit");
                    break;
                case 3:
                    reason = getDB("temp_already_blocked_exit");
                    break;
                case 4:
                    reason = getDB("wrong_password_exit");
                    break;
                case 5:
                    reason = getDB("temp_already_unblocked_exit");
                    break;
                case 6:
                    reason = getDB("temp_blocked_err_exit");
                    break;
                case 7:
                    reason = getDB("temp_folder_err_exit");
                    break;
                case 8:
                    reason = getDB("no_flag_text_exit");
                    break;
                case 9:
                    reason = getDB("no_flag_exit");
                    break;
                case 10:
                    reason = getDB("flag_used_exit");
                    break;
                case 11:
                    reason = getDB("edit_file_exit");
                    break;
                case 12:
                    reason = getDB("invalid_flag_exit");
                    break;
                case 13:
                    reason = getDB("invalid_arg_exit");
                    break;
                case 14:
                    reason = getDB("invalid_json_exit");
                    break;
                case 15:
                    reason = getDB("maximum_logs_exit");
                    break;

                    //ELSE
                default:
                    reason = getDB("reason_exit");
                    break;
            }

            //MESSAGE
            print(regex_replace(getDB("console_exit"), regex("\\{CODE}"), to_string(code)) + " " + reason + "\n");
        }

        if ((rand() % (100 + 1) > 75) && (code == 0 || code > 100))
        {
            print("\n" + getDB("thanks") + "\n");

            if (rand() % (1000 + 1) == 420)
            {
                print("look");
            }
        }

        if (getConsoleFlag())
        {
            print("\n" + getDB("press_enter") + "\n");

            //WAIT FOR ENTER (\n)
            while (getchar() != '\n');
        }

        exit(code); //EXIT
    }

    void loadInvalidFlags(string compatibleArgs[], list<string> args)
    {
        //RETURN IF THERE ARE NO ARGS
        if (args.size() == 0) return;

        list<string> compatibleList; //THERE WILL BE STORED compatibleArgs

        //CONVERT compatibleArgs TO LIST (compatibleList) + ADD TWO DASHES (--) BEFORE IT
        for (int i = 0; i < compatibleL; i++)
        {
            compatibleList.push_back("--" + compatibleArgs[i]);
        }

        //CHECK FOR '_' IN args
        for (auto &arg: args)
        {
            if (arg.find("_") != string::npos)
            {
                printErrTranslate("invalid_char", 12);
            }
        }

        list<string> argsCompatible;

        //LOAD ALL COMPATIBLE args TO argsCompatible (USING compatibleList)
        for (auto & arg: args) //LOAD ARGS
        {
            for (auto & compatible: compatibleList) //LOAD COMPATIBLES
            {
                string argNew = arg; //COPY arg
                string::size_type pos = argNew.find(":"); //FIND COLON POSITION

                if (pos != string::npos) //arg CONTAINS COLON
                {
                    argNew = argNew.substr(0, pos); //GET arg BEFORE COLON
                }

                //IF argNew MATCHES compatible, ADD IT TO argsCompatible
                if (argNew == compatible)
                {
                    argsCompatible.push_back(arg);
                    break;
                }
            }
        }

        //RETURN IF ALL FLAGS ARE COMPATIBLE
        if (argsCompatible.size() == args.size()) return;

        //:)
        if (args.size() - argsCompatible.size() == 1 && args.front().c_str() == "sus")
        {
            print("Oh, so you're a sussy boi?\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n");
            exitProgram(104);
        }

        //GET FIRST INCOMPATIBLE FLAG IN args
        string incompatible;

        for (auto & arg: args)
        {
            if (find(argsCompatible.begin(), argsCompatible.end(), arg) == argsCompatible.end())
            {
                incompatible = arg;
                break;
            }
        }

        //PRINT FIRST INCOMPATIBLE FLAG AS ERROR (WITHOUT --)
        printErr(regex_replace(getDB("invalid_flag"), regex("\\{FLAG}"), incompatible.substr(2)) + "\n", 12);
    }

    void loadInvalidLang(string compatible[], string lang)
    {
        list<string> compatibleList; //THERE WILL BE STORED compatible AS std::list

        //LOAD compatible INTO compatibleList
        for (int i = 0; i < langL; i++)
        {
            compatibleList.push_back(compatible[i]);
        }

        //RETURN IF compatible DOES CONTAIN lang
        if (find(compatibleList.begin(), compatibleList.end(), lang) != compatibleList.end()) return;

        //ERROR SECTION
        printErr(regex_replace(getDB("invalid_arg"), regex("\\{ARG}"), lang) + "\n", 13);
    }

    void generateLogFile()
    {
        //IF logs/ FOLDER DOESN'T EXISTS, GENERATE IT
        if (!(filesystem::is_directory("logs") && filesystem::is_directory("logs")))
        {
            filesystem::create_directory("logs");
        }

        //GET logName;
        string logName;
        time_t timeT = time(0);
        tm * time = localtime(&timeT);

        //SET VALID DATA
        time -> tm_year += 1900; //ADD 1900 TO YEAR
        time -> tm_mon += 1; //ADD 1 TO MONTH

        //LOAD YEAR
        logName += to_string(time -> tm_year) + "-";

        //LOAD MONTH
        if (to_string(time -> tm_mon).length() == 1) //MONTH IS BETWEEN JANUARY AND SEPTEMBER (1 - 9)
        {
            logName += "0";
        }

        logName += to_string(time -> tm_mon) + "-";

        //LOAD DAY
        if (to_string(time -> tm_mday).length() == 1) //MONTH IS FIRST AND NINTH DAY (1 - 9)
        {
            logName += "0";
        }

        logName += to_string(time -> tm_mday);

        //LOAD LATEST LOG NUMBER
        for (int i = 1; i < 100; i++)
        {
            string iS = to_string(i);

            //GET i IN 2 CHARS
            if (iS.length() == 1)
            {
                iS = "0" + iS;
            }

            string logFilePath = "logs/" + logName + "-" + iS + ".log";

            setLogTextFlag(logFilePath);

            //LOG FILE DOESN'T EXIST
            if (!fstream(logFilePath))
            {
                loggingFile.open(logFilePath, ios::out);

                break;
            }

            //LOG 99 EXISTS
            if (i == 99)
            {
                printErrTranslate("maximum_logs", 15);
            }
        }
    }

    int getEncryptionKey()
    {
        string path; //THERE WILL BE CONFIG FILE PATH
        fstream configFile; //THERE WILL BE CONFIG FILE
        int returningKey; //THERE WILL BE THE KEY

        //GET path
        if (os == 1) //WINDOWS
        {
            path = "C:/Users/" + getUsernameFlag() + "/.ek.ecfg";
        } else if (os == 2)
        {
            path = "/home/" + getUsernameFlag() + "/.ek.ecfg";
        }

        if (!fstream(path)) //CONFIG FILE DOESN'T EXISTS
        {
            print(getDB("creating_config") + "\n\n");

            configFile.open(path, ios::out);

            returningKey = rand() % (100 + 1);
            configFile << returningKey;
        } else
        {
            configFile.open(path, ios::in);
            configFile >> returningKey;
        }

        return returningKey;
    }

    string loadTemp()
    {
        if (os == 1) //WINDOWS
        {
            return "C:/Users/ " + getUsernameFlag() + "/AppData/Local/Temp";
        } else if (os == 2) //LINUX
        {
            return "/tmp";
        }

        return "ERR";
    }

    string loadFlagText(string flag, list<string> args)
    {
        string fullFlag; //THERE WILL BE STORED FLAG FOUND IN args (flag IS JUST FROM LIST OF COMPATIBLE FLAGS, SO IT'S WITHOUT TEXT){
        string flagText; //THERE WILL BE TEXT AFTER FLAG

        //GET fullFlag
        for (auto & arg: args)
        {
            string argNew = arg; //COPY arg

            argNew = argNew.substr(0, argNew.find(":")); //GET arg BEFORE COLON

            //IF flag MATCHES argNew, ADD IT TO fullFlag
            if (("--" + flag) == argNew)
            {
                fullFlag = arg;
                break;
            }
        }

        string::size_type colonPos = fullFlag.find(":");

        //colonPos WASN'T FOUND (THERE'S NO FLAGTEXT)
        if (colonPos == string::npos)
        {
            err:
            printErr(regex_replace(getDB("invalid_text"), regex("\\{FLAG}"), flag) + "\n", 8);
        }

        //GET flagText
        flagText = fullFlag.substr(colonPos + 1);

        //THERE IS NO flagText
        if (flagText == "") goto err;

        return flagText;
    }

    bool isOsCompatible()
    {
        return os != 0;
    }

    bool argsContainsFlag(string flag, list<string> args)
    {
        bool found = false; //THIS CHANGES, WHEN FLAG IS FOUND; WHEN FLAG IS FOUND SECOND TIME, PROGRAM ENDS WITH ERROR

        //LOAD ALL ARGS
        for (auto & arg: args)
        {
            //GET ARG BEFORE COLON
            string::size_type colonPos = arg.find(":"); //LOOK FOR COLON

            if (colonPos != string::npos) //ARG REALLY CONTAINS COLON
            {
                //CUT ARG BEFORE COLON
                arg = arg.substr(0, colonPos);
            }

            if (("--" + flag) == arg) //ARG EQUALS FLAG
            {
                if (found) //IS DOUBLE-USED
                {
                    printErr(regex_replace(getDB("flag_used"), regex("\\{FLAG}"), flag) + "\n", 10);
                }

                found = true;
            }
        }

        return found;
    }

    void setUser()
    {
        if (os == 1)
        {
            setUsernameFlag(getenv("USERNAME"));
        } else if (os == 2)
        {
            setUsernameFlag(getenv("USER"));
        }
    }
}
