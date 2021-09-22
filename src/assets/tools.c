/*
    Here you can find all the utilities like isOsCompatible() and much more.

    ! I DO NOT RECOMMEND USING THESE IN YOUR PROJECT !


    Note: *almost* every void here is explained in tools.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../../lib/engodatabase/edb.h"

#include "../../include/tools.h"

//Used OS; 1 = Windows, 2 = Linux (UNIX), 3 = Mac, 0 = Incompatible
#ifdef _WIN32 //WINDOWS
int os = 1;
#elif __unix__ //LINUX (UNIX)
int os = 2;
/*#elif __APPLE__ //MAC | MAC IS NO LONGER SUPPORTED !!!
int os = 3;
*/#endif

bool isOsCompatible()
{
    return os != 0;
}

char * replaceString(const char * word, const char * wordFind, const char * wordReplace, char ** store)
{
    char * result;
    unsigned long i, cnt = 0;
    unsigned long wordFindL = strlen(wordReplace);
    unsigned long wordReplaceL = strlen(wordFind);

    for (i = 0; word[i] != '\0'; i++)
    {
        if (strstr(&word[i], wordFind) == &word[i])
        {
            cnt++;

            i += wordReplaceL - 1;
        }
    }

    result = (char *) malloc(i + cnt * (wordFindL - wordReplaceL) + 1);

    i = 0;
    while (*word)
    {
        if (strstr(word, wordFind) == word)
        {
            strcpy(&result[i], wordReplace);
            i += wordFindL;
            word += wordReplaceL;
        }
        else
        {
            result[i++] = *word++;
        }
    }

    result[i] = '\0';
    if (store != NULL)
    {
        *store = result;
        free(result);
        return * store;
    }

    free(store);
    return result;
}

char * getDB(char object[])
{
    char * finalString[256];

    char lang[strlen("../res/xx.edb")];
    strcpy(lang, "../res/");
    strcat(lang, langFlag);
    strcat(lang, ".edb");

    readString(object , fopen(lang, "r"), finalString);
    return * finalString;
}

void exitProgram(int code)
{
    if (exitFlag)
    {
        //TODO: fix replacing
        char replacing[] = "0"/*code*/;
        char reason[256];

        //GETTING REASON
        switch (code)
        {
            //GOOD
            case 104:
                strcpy(reason, getDB(":)"));
                break;
            case 103:
                strcpy(reason, getDB("excex_exit"));
                break;
            case 102:
                strcpy(reason, getDB("temp_unblocked_exit"));
                break;
            case 101:
                strcpy(reason, getDB("temp_blocked_exit"));
                break;
            case 0:
                strcpy(reason, getDB("temp_deleted_exit"));
                break;

                //BAD
            case 1:
                strcpy(reason, getDB("not_compatible_os_exit"));
                break;
            case 2:
                strcpy(reason, getDB("username_linux_exit"));
                break;
            case 3:
                strcpy(reason, getDB("temp_already_blocked_exit"));
                break;
            case 4:
                strcpy(reason, getDB("wrong_password_exit"));
                break;
            case 5:
                strcpy(reason, getDB("temp_already_unblocked_exit"));
                break;
            case 6:
                strcpy(reason, getDB("temp_blocked_err_exit"));
                break;
            case 7:
                strcpy(reason, getDB("temp_folder_err_exit"));
                break;
            case 8:
                strcpy(reason, getDB("no_flag_text_exit"));
                break;
            case 9:
                strcpy(reason, getDB("no_flag_exit"));
                break;
            case 10:
                strcpy(reason, getDB("flag_used_exit"));
                break;
            case 11:
                strcpy(reason, getDB("edit_file_exit"));
                break;
            case 12:
                strcpy(reason, getDB("invalid_flag_exit"));
                break;
            case 13:
                strcpy(reason, getDB("invalid_arg_exit"));
                break;
            case 14:
                strcpy(reason, getDB("invalid_json_exit"));
                break;

                //ELSE
            default:
                strcpy(reason, getDB("reason_exit"));
                break;
        }

        strcat(replacing, reason);

        //MESSAGE
        //TODO: Fix last letter
        printf("%s\n", replaceString(getDB("console_exit"), "{CODE}", replacing, NULL));
    }

    if ((rand() % (100 + 1) > 75) && (code == 0 || code > 100))
    {
        printf("%s", getDB("thanks"));

        if (rand() % (1000 + 1) == 420)
        {
            print("look");
        }
    }

    if (consoleFlag)
    {
        char * repeat = NULL; //UNUSED
        print("press_enter");

        //WAIT FOR ENTER
        scanf("%s", repeat, stdin);
        free(repeat);
    }

    exit(code); //EXIT
}

char * getUser()
{
    //TODO: Fix the whole method
    print("enter_username");

    char * username = NULL;
    scanf("%s", username);
    printf("%s", username);

    return username;
}

void print(char object[])
{
    printf("%s\n", getDB(object));
}

void printErr(char object[], int exitCode)
{
    fprintf(stderr, "%s\n", getDB(object));
    exitProgram(exitCode);
}

//int getEncryptionKey()
//{
//    //TODO: Fix
//    FILE * configFile;
//    char fileLoc[256];
//
//    //WINDOWS
//    if (os == 1)
//    {
//        strcpy(fileLoc, "C:/Users/");
//    } else if (os == 2) //LINUX
//    {
//        strcpy(fileLoc, "/home/");
//    }
//
//    strcat(fileLoc, getUser());
//    strcat(fileLoc, "/.block.ecfg");
//
//    return 0;
//}