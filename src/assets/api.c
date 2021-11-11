/*
    This source file contains the ClearTemp core
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>

#include "../../include/api.h"
#include "../../include/tools.h"
#include "../../include/flags.h"

int rmdir(); //IGNORE THAT, IT'S HERE JUST TO SUPPRESS Wimplicit-function-declaration WARNING

void clearTemp(char args[arg1Size][arg2Size])
{
    srand(time(NULL)); //MAKE RAND() REALLY RANDOM (SET TIME SEED)

    if (!isOsCompatible())
    {
        printTranslateErr("not_compatible_os", 1);
    }

    //VARS
    int deleted = 0;
    int cannotDelete = 0;
    const int key = getEncryptionKey();

    char fileUsed[128];
    char tempFileUsed[256];
    char * username = "";
    char buffer[128];

    struct dirent * de;
    DIR * dr;

    struct stat pathStat;

    bool excex = false;

    const char compatibleArgs[compatible1L][compatible2L] =
    {       //0        //1         //2      //3        //4      //5      //6     //7         //8
            "console", "username", "block", "unblock", "excex", "debug", "exit", "language", "logs"
    };

    const char compatibleLangs[lang1L][lang2L] =
    {
            //0   //1
            "en", "cz"
    };

    //CHECK FOR INVALID FLAGS
    loadInvalidFlags(compatibleArgs, args);

    //LOAD fileUsed
    strcpy(fileUsed, loadTemp(username));

    //THERE ARE FLAGS
    if (strcmp(args[0], "\0") != 0)
    {
        //LOGS FLAG
        if (argsContainsFlag(compatibleArgs[8], args))
        {
            setLogFlag(true);

            //GET TIME
            char timeS[strlen(getLogTextFlag())];
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            sprintf(timeS, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon, tm.tm_mday);

            generateLogFile(timeS, args);
        }
        
        //LANGUAGE FLAG - SET LANG
        if (argsContainsFlag(compatibleArgs[7], args))
        {
            //LOAD FLAG
            char langBuffer[3];
            loadFlagText(compatibleArgs[7], args, langBuffer);

            //LOWER CASE
            for (int i = 0; i < strlen(langBuffer); i++)
            {
                langBuffer[i] = (char) tolower(langBuffer[i]);
            }

            //CHECK FOR INVALID
            loadInvalidLang(compatibleLangs, langBuffer);

            setLangFlag(langBuffer);

            printTranslate("using_lang");
        }

        //DEBUG FLAG - DOESN'T ACTUALLY DELETES FILES
        if (argsContainsFlag(compatibleArgs[5], args))
        {
            setDebugFlag(true);

            printTranslate("debug");
        }

        //CONSOLE FLAG
        if (argsContainsFlag(compatibleArgs[0], args))
        {
            setConsoleFlag(true);

            printTranslate("console");
        }

        //USERNAME FLAG - WINDOWS TEMP FOLDER FOR USER
        if (argsContainsFlag(compatibleArgs[1], args))
        {
            //LINUX IS USED
            if (os == 2)
            {
                printTranslateErr("username_linux", 2);
            }

            loadFlagText(compatibleArgs[1], args, username);
        }

        //BLOCK FLAG - PREVENTING TEMP FROM REMOVING BY THIS PROGRAM
        if (argsContainsFlag(compatibleArgs[2], args))
        {
            //LOAD BLOCK FILE
            strcpy(tempFileUsed, fileUsed);
            strcat(tempFileUsed, "/.bf.ecfg");

            //TEMP IS ALREADY BLOCKED
            if (fopen(tempFileUsed, "r") != NULL)
            {
                printTranslateErr("temp_already_blocked", 3);
            }

            //BLOCKING
            if (!getDebugFlag()) //IGNORING IF DEBUG IS ENABLED
            {
                char password[flagTextL];
                char passwordEncrypted[flagTextL];

                //GET PASSWORD ('BLOCK' FLAG TEXT)
                loadFlagText(compatibleArgs[2], args, password);

                //CREATE BLOCK FILE
                FILE * blockFile = fopen(tempFileUsed, "w");

                //ENCRYPT PASSWORD
                for (int i = 0; i < strlen(password); i++)
                {
                    passwordEncrypted[i] = (char) (password[i] + key);
                }

                //WRITE
                fprintf(blockFile, "%s\n", passwordEncrypted);
                fclose(blockFile);
            }

            printTranslate("temp_blocked");
            exit(101);
        }

        //UNBLOCK FLAG - REMOVING BLOCK
        if (argsContainsFlag(compatibleArgs[3], args))
        {
            //LOAD BLOCK FILE
            strcpy(tempFileUsed, fileUsed);
            strcat(tempFileUsed, "/.bf.ecfg");

            //CHECK IF TEMP IS BLOCKED
            if (fopen(tempFileUsed, "r") != NULL)
            {
                //UNBLOCKING
                if (!getDebugFlag())
                {
                    char password[flagTextL];
                    char passwordDecrypted[flagTextL];

                    char passwordUsed[flagTextL];

                    //LOAD PASSWORD
                    loadFlagText(compatibleArgs[3], args, password);

                    //GET passwordUsed
                    fscanf(fopen(tempFileUsed, "r"), "%s", passwordUsed);

                    //DECRYPT PASSWORD
                    for (int i = 0; i < flagTextL; i++)
                    {
                        //NULL
                        if (password[i] == '\0') break;

                        passwordDecrypted[i] = (char) (passwordUsed[i] - key);
                    }

                    //PASSWORD DOESN'T MATCH
                    if (strcmp(password, passwordDecrypted) != 0)
                    {
                        printTranslateErr("wrong_password", 4);
                    }

                    //REMOVE BLOCK FILE
                    remove(tempFileUsed);
                }

                printTranslate("temp_unblocked");
                exitProgram(102);
            } else
            {
                printTranslateErr("temp_already_unblocked", 5);
            }
        }

        //EXCEX FLAG - EXITING ON ANY DELETING EXCEPTION
        if (argsContainsFlag(compatibleArgs[4], args))
        {
            excex = true;

            printTranslate("excex");
        }

        //EXIT FLAG - SHOWS WHY THE PROGRAM IS EXITING
        if (argsContainsFlag(compatibleArgs[6], args))
        {
            setExitFlag(true);

            printTranslate("exit");
        }

        print("\n");
    }

    //ADD BLOCK FILE
    strcpy(tempFileUsed, fileUsed);
    strcat(tempFileUsed, "/.bf.ecfg");

    //CHECK IF TEMP IS BLOCKED
    if (fopen(tempFileUsed, "r") != NULL)
    {
        printTranslateErr("temp_blocked_err", 6);
    }

    //CHECK FOR TEMP FOLDER
    if (fopen(fileUsed, "r") == NULL)
    {
        printTranslateErr("temp_folder_err", 7);
    }

    //LIST FILES
    dr = opendir(fileUsed);

    //REMOVE FILES
    while ((de = readdir(dr)) != NULL)
    {
        //IS . OR ..
        if ((strcmp(de->d_name, ".") == 0) || (strcmp(de->d_name, "..") == 0)) continue;

        //GET FILE LOCATION
        strcpy(tempFileUsed, fileUsed);
        strcat(fileUsed, "/");
        strcat(tempFileUsed, de->d_name);

        int removed = 0;
        if (!getDebugFlag()) //REMOVE IF DEBUG IS DISABLED
        {
            //LOAD PATH TO pathStat
            stat(tempFileUsed, &pathStat);

            //FILE
            if (S_ISREG(pathStat.st_mode) != 0)
            {
                removed = remove(tempFileUsed);
            } else //DIRECTORY (DOESN'T REMOVE DIRECTORIES IN DIRECTORIES)
            {
                //TODO: REPLACE WITH SOMETHING 'GOOD'

                removed = rmdir(tempFileUsed);
            }
        }

        //REMOVED
        if (removed == 0)
        {
            //GET MESSAGE
            strcpy(buffer, getDB("removed_file"));
            strcat(buffer, " ");
            strcat(buffer, de->d_name);

            //PRINT
            print("%s\n", buffer);

            deleted++;
        } else //CANNOT REMOVE
        {
            //GET MESSAGE
            strcpy(buffer, getDB("cant_remove"));
            strcat(buffer, " ");
            strcat(buffer, de->d_name);

            //PRINT
            print("%s\n", buffer);

            //EXCEX
            if (excex)
            {
                exitProgram(103);
            }

            cannotDelete++;
        }
    }

    //FINAL
    char final[256];
    char deletedS[128];

    //LOAD FINAL MESSAGE
    char cannotDeleteS[128];
    sprintf(deletedS, "%d", deleted);
    sprintf(cannotDeleteS, "%d", cannotDelete);

    strcpy(final, getDB("final"));
    strcpy(final, replaceString(final, "{LINE}", "\n", NULL));
    strcpy(final, replaceString(final, "{DELETED}", deletedS, NULL));
    strcpy(final, replaceString(final, "{CANNOT}", cannotDeleteS, NULL));

    print("%s\n", final);

    closedir(dr);

    exitProgram(0);
}
