/*
    This source file contains the ClearTemp core
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

#include "../../include/api.h"
#include "../../include/tools.h"

void clearTemp(char args[arg1Size][arg2Size])
{
    srand(time(NULL)); //MAKE RAND() REALLY RANDOM

    if (!isOsCompatible())
    {
        printErr("not_compatible_os", 1);
    }

    //VARS
    int deleted = 0;
    int cannotDelete = 0;
    //const int key = getEncryptionKey();

    char fileUsed[128];
    char tempFileUsed[256];
    char * username = "";
    char buffer[128];

    struct dirent * de;
    DIR * dr;

    bool excex = false;

    const char compatibleArgs[compatibleL][16] =
    {       //0        //1         //2      //3        //4      //5      //6     //7
            "console", "username", "block", "unblock", "excex", "debug", "exit", "language"
    };

    loadInvalidFlags(compatibleArgs, args);

    //TODO: ADD FLAGS!!!

    strcpy(fileUsed, loadTemp(username));

    //ADD BLOCK FILE
    strcpy(tempFileUsed, fileUsed);
    strcat(tempFileUsed, "/.block.engo");

    //CHECK IF TEMP IS BLOCKED
    if (fopen(tempFileUsed, "r") != NULL)
    {
        printErr("temp_blocked_err", 6);
    }

    //CHECK FOR TEMP FOLDER
    if (fopen(fileUsed, "r") == NULL)
    {
        printErr("temp_folder_err", 7);
    }

    //LIST FILES
    dr = opendir(fileUsed);

    //REMOVE FILES
    while ((de = readdir(dr)) != NULL)
    {
        //GET FILE LOCATION
        strcpy(tempFileUsed, fileUsed);
        strcat(fileUsed, "/");
        strcat(tempFileUsed, de->d_name);

        int removed = 0;
        if (!debugFlag)
        {
            removed = remove(tempFileUsed);
        }

        //REMOVED
        if (removed == 0)
        {
            //GET MESSAGE
            strcpy(buffer, getDB("removed_file"));
            strcat(buffer, " ");
            strcat(buffer, de->d_name);

            //PRINT
            printf("%s\n", buffer);
            deleted++;
        } else //CANNOT REMOVE
        {
            //GET MESSAGE
            strcpy(buffer, getDB("cant_remove"));
            strcat(buffer, " ");
            strcat(buffer, de->d_name);

            //PRINT
            printf("%s\n", buffer);

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

    char cannotDeleteS[128];
    sprintf(deletedS, "%d", deleted);
    sprintf(cannotDeleteS, "%d", cannotDelete);

    strcpy(final, getDB("final"));
    strcpy(final, replaceString(final, "{LINE}", "\n", NULL));
    strcpy(final, replaceString(final, "{DELETED}", deletedS, NULL));
    strcpy(final, replaceString(final, "{CANNOT}", cannotDeleteS, NULL));

    printf("%s\n", final);

    exitProgram(0);
}
