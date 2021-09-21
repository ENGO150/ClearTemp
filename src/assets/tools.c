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

char * replaceWord(const char* s, const char* oldW, const char* newW)
{
    char* result;
    unsigned long i, cnt = 0;
    unsigned long newWL = strlen(newW);
    unsigned long oldWL = strlen(oldW);

    for (i = 0; s[i] != '\0'; i++)
    {
        if (strstr(&s[i], oldW) == &s[i])
        {
            cnt++;

            i += oldWL - 1;
        }
    }

    result = (char *) malloc(i + cnt * (newWL - oldWL) + 1);

    i = 0;
    while (*s)
    {
        if (strstr(s, oldW) == s)
        {
            strcpy(&result[i], newW);
            i += newWL;
            s += oldWL;
        }
        else
        {
            result[i++] = *s++;
        }
    }

    result[i] = '\0';
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
        char * replacing = NULL/*code*/;
        char * reason = NULL;

        //GETTING REASON
        switch (code)
        {
            //GOOD
            case 104:
                reason = ":)";
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

                //ELSE
            default:
                reason = getDB("reason_exit");
                break;
        }

        strcat(replacing, reason);

        //MESSAGE
        printf("%s\n", replaceWord(getDB("console_exit"), "{CODE}", replacing));
    }

    if ((rand() % 101 > 75) && (code == 0 || code > 100))
    {
        printf("%s", getDB("thanks"));

        if (rand() % 1001 == 420)
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

    scanf("%s", usernameFlag);

    return usernameFlag;
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