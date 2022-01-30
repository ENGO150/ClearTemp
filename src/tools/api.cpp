/*
    This source file contains the ClearTemp core
*/

#include "../../include/api.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>

#include "../../include/utils.hpp"
#include "../../include/flags.hpp"

using namespace utils;

void clearTemp(std::list<std::string> args)
{
    srand(time(0)); //MAKE RAND() REALLY RANDOM (SET TIME SEED)
    setUser(); //Initialize usernameFlag

    if (!isOsCompatible()) //EXIT IF YOU AREN'T USING SUPPORTED OPERATING SYSTEM (SUPPORTED IS WINDOWS AND LINUX)
    {
        printErrTranslate("not_compatible_os", 1);
    }

    std::string compatibleFlags[compatibleL] =
    {       //0        //1         //2      //3        //4      //5      //6     //7         //8
            "console", "username", "block", "unblock", "excex", "debug", "exit", "language", "logs"
    };

    std::string compatibleLangs[langL] =
    {
            //0   //1
            "en", "cz"
    };

    /*//CHECK IF TEMP FOLDER EXISTS
    if (!opendir(loadTemp().c_str()))
    {
        printErrTranslate("temp_folder_err", 7);
    }*/

    if (!(std::filesystem::is_directory(loadTemp()) && std::filesystem::is_directory(loadTemp())))
    {
        printErrTranslate("temp_folder_err", 7);
    }

    //CHECK FOR INVALID FLAGS
    loadInvalidFlags(compatibleFlags, args);

    //VARIABLES
    std::string usedFileBuffer; //THIS WILL BE USED FOR STORING PATH OF USED FILE
    bool excex; //LOOK FOR EXCEX FLAG FOR MORE INFO
    int deleted = 0; //THERE WILL BE COUNTED EVERY REMOVED FILE (DIRECTORY IS COUNTED AS ONE FILE)
    int cannotDelete = 0; //THERE WILL BE COUNTED EVERY FILE, THAT CANNOT BE REMOVED

    //LOAD FLAGS
    if (args.size() > 0)
    {
        //LOGS
        if (argsContainsFlag(compatibleFlags[8], args))
        {
            setLogFlag(true);

            //GENERATE LOGGING FILE
            generateLogFile();
        }

        //LANGUAGE
        if (argsContainsFlag(compatibleFlags[7], args))
        {//GET FLAG TEXT
            std::string lang = loadFlagText(compatibleFlags[7], args);

            //CHECK IF lang IS VALID
            loadInvalidLang(compatibleLangs, lang);

            setLangFlag(lang);
            
            printTranslate("using_lang");
        }

        //DEBUG
        if (argsContainsFlag(compatibleFlags[5], args))
        {
            setDebugFlag(true);

            printTranslate("debug");
        }

        //CONSOLE
        if (argsContainsFlag(compatibleFlags[0], args))
        {
            setConsoleFlag(true);

            printTranslate("console");
        }

        //USERNAME (WINDOWS HAS TEMP FOR EVERY USER ON COMPUTER SEPARATED)
        if (argsContainsFlag(compatibleFlags[1], args))
        {
            //LINUX IS USED (LINUX HAS /tmp DIRECTORY, WHICH IS FOR EVERY USER)
            if (os == 2)
            {
                printErrTranslate("username_linux", 2);
            }

            setUsernameFlag(loadFlagText(compatibleFlags[1], args));
        }

        //BLOCK FLAG (PREVENTING TEMP FROM REMOVING IT BY THIS PROGRAM)
        if (argsContainsFlag(compatibleFlags[2], args))
        {
            usedFileBuffer = loadTemp() + "/.bf.ecfg"; //GET BLOCK FILE

            //TEMP IS ALREADY BLOCKED
            if (std::fstream(usedFileBuffer))
            {
                printErrTranslate("temp_already_blocked", 3);
            }

            //BLOCKING
            if (!getDebugFlag()) //SKIP THIS, IF DEBUGGING IS ENABLED
            {
                std::string password; //THERE WILL BE FLAG TEXT
                std::string passwordEncrypted; //THIS WILL BE password, BUT ENCRYPTED WITH ENCRYPTION KEY (getEncryptionKey())

                //GET password
                password = loadFlagText(compatibleFlags[2], args);

                //ENCRYPT password
                for (int i = 0; i < password.length(); i++)
                {
                    //ADD IT TO passwordEncrypted
                    passwordEncrypted += (char) (password[i] + getEncryptionKey());
                }
                
                //CREATE BLOCK FILE AND WRITE THE PASSWORD INTO IT
                std::fstream(usedFileBuffer, std::ios::out) << passwordEncrypted;
            }

            printTranslate("temp_blocked");
            exitProgram(101);
        }

        //UNBLOCK FLAG (OPOSITE OF BLOCK FLAG [yeah, no shit])
        if (argsContainsFlag(compatibleFlags[3], args))
        {
            usedFileBuffer = loadTemp() + "/.bf.ecfg"; //GET BLOCK FILE

            //TEMP IS ALREADY UNBLOCKED (OR IT EVER WASN'T BLOCKED)
            if (!std::fstream(usedFileBuffer))
            {
                printErrTranslate("temp_already_unblocked", 5);
            }

            //UNBLOCKING
            if (!getDebugFlag()) //SKIP THIS, IF DEBUGGING IS ENABLED
            {
                std::string password; //THERE WILL BE FLAG TEXT
                std::string passwordEncrypted; //THIS WILL BE password, BUT ENCRYPTED WITH ENCRYPTION KEY (getEncryptionKey())
                std::string passwordUsed; //THERE WILL BE PASSWORD FOUND IN BLOCK FILE

                //GET password
                password = loadFlagText(compatibleFlags[3], args);

                //GET passwordUsed
                std::fstream(usedFileBuffer, std::ios::in) >> passwordUsed;

                //ENCRYPT password
                for (int i = 0; i < passwordUsed.length(); i++)
                {
                    //ADD IT TO passwordEncrypted
                    passwordEncrypted += (char) (password[i] + getEncryptionKey());
                }

                //password DOESN'T MATCH passwordEncrypted
                if (passwordEncrypted != passwordUsed)
                {
                    printErrTranslate("wrong_password", 4);
                }

                //REMOVE BLOCK FILE
                std::remove(usedFileBuffer.c_str());
            }

            printTranslate("temp_unblocked");
            exitProgram(102);
        }

        //EXCEX FLAG (EXITING ON ANY 'CANNOT DELETE')
        if (argsContainsFlag(compatibleFlags[4], args))
        {
            excex = true;

            printTranslate("excex");
        }

        //EXIT FLAG (SHOWS WHY PROGRAM ENDED)
        if (argsContainsFlag(compatibleFlags[6], args))
        {
            setExitFlag(true);

            printTranslate("exit");
        }

        print("\n");
    }

    //CHECK IF BLOCK FILE EXISTS
    if (std::fstream(loadTemp() + "/.bf.ecfg"))
    {
        printErrTranslate("temp_blocked_err", 6);
    }

    //LOAD ALL TEMP FILES
    for (auto & file : std::filesystem::directory_iterator(loadTemp()))
    {
        bool removed = true;

        if (!getDebugFlag()) //REMOVE, IF DEBUGGING IS DISABLED
        {
            removed = false;

            //REMOVING
            if (!file.is_directory()) //REGULAR FILE
            {
                removed = !std::remove(file.path().c_str());
            } else //DIRECTORY
            {
                try
                {
                    std::filesystem::remove_all(file.path());
                }
                catch(std::exception & e)
                {
                    //CANNOT REMOVE
                    removed = false;
                }
            }
        }

        if (removed) //SUCCESSFULLY REMOVED
        {
            print(getDB("removed_file") + file.path().filename().c_str() + "\n");

            deleted++;
        } else //CANNOT REMOVE
        {
            //EXCEX
            if (excex)
            {
                exitProgram(103);
            }

            print(getDB("cant_remove") + file.path().filename().c_str() + "\n");

            cannotDelete++;
        }
    }

    //FINAL MESSAGE
    std::string message;

    message = std::regex_replace(getDB("final_1"), std::regex("\\{DELETED}"), std::to_string(deleted));
    message += std::regex_replace(getDB("final_2"), std::regex("\\{CANNOT}"), std::to_string(cannotDelete));

    print("\n" + message + "\n");

    exitProgram(0);
}
