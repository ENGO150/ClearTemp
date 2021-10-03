/*
    Here you can find all the utilities like isOsCompatible() and much more.

    ! I DO NOT RECOMMEND USING THESE IN YOUR PROJECT !


    Note: *almost* every void here is explained in tools.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <edb.h>

#include <tools.h>

bool isOsCompatible()
{
    return os != 0;
}

char * replaceString(const char * word, const char * wordFind, const char * wordReplace, char ** store) {
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
        } else
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
    strcat(lang, getLangFlag());
    strcat(lang, ".edb");

    readString(object , fopen(lang, "r"), finalString);
    return * finalString;
}

void exitProgram(int code)
{
    if (getExitFlag())
    {
        char replacing[5];
        char reason[256];

        sprintf(replacing, "%d", code);

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

        //MESSAGE
        printf("%s %s\n", replaceString(getDB("console_exit"), "{CODE}", replacing, NULL), reason);
    }

    if ((rand() % (100 + 1) > 75) && (code == 0 || code > 100))
    {
        printf("\n%s\n", getDB("thanks"));

        if (rand() % (1000 + 1) == 420)
        {
            print("look");
        }
    }

    if (getConsoleFlag())
    {
        printf("\n%s\n", getDB("press_enter"));

        //WAIT FOR ENTER (\n)
        while (getchar() != '\n');
    }

    exit(code); //EXIT
}

char * getUser()
{
    if (os == 1)
    {
        return getenv("USERNAME");
    } else if (os == 2)
    {
        return getenv("USER");
    }

    return NULL;
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

int getEncryptionKey() {
    char path[256];

    //GET PATH
    if (os == 1) //WINDOWS
    {
        strcpy(path, "C:/Users/");
        strcat(path, getUser());
        strcat(path, "/.ek.ecfg");
    } else if (os == 2) //LINUX
    {
        strcpy(path, "/home/");
        strcat(path, getUser());
        strcat(path, "/.ek.ecfg");
    }

    FILE * fp = fopen(path, "r");
    if (fp != NULL) goto notNull; //PATH EXISTS

    //CREATE
    printf("%s\n", replaceString(getDB("creating_config"), "{LINE}", "\n", NULL));
    fp = fopen(path, "w");

    //WRITE RANDOM NUMBER BETWEEN 0 AND 100
    int random = rand() % (100 + 1);
    fprintf(fp, "%d", random);
    fclose(fp);
    return random;

    notNull:;
    int returningKey;

    //READ CONTENT
    fscanf(fp, "%d", &returningKey);

    return returningKey;
}

char * loadTemp(char username[])
{
    //WINDOWS IS USED
    if (os == 1)
    {
        if (strcmp(username, "") == 0)
        {
            username = getUser();
        }

        char * returning[128];
        strcpy(*returning, "C:/Users/");
        strcat(*returning, username);
        strcat(*returning, "/AppData/Local/Temp");

        return *returning;
    } else if (os == 2) //LINUX IS USED
    {
        return "/tmp";
    }

    return "ERR";
}

void loadInvalidFlags(const char compatible[compatible1L][compatible2L], char args[arg1Size][arg2Size])
{
    //CHECK IF ARGS AREN'T EMPTY
    if (strcmp(args[0], "\0") == 0) return;

    //CHECK FOR _ IN ARGS
    for (int i = 0; i < arg1Size; i++)
    {
        //ARG IS EMPTY
        if (strcmp(args[i], "\0") == 0) break;

        for (int j = 0; j < arg2Size; j++)
        {
            //ARG IS EMPTY
            if (args[i][j] == '\0') break;

            //CONTAINS _
            if (args[i][j] == '_')
            {
                printErr("invalid_char", 12);
            }
        }
    }

    //LOAD argsL
    int argsL = 0;
    for (int i = 0; i < arg1Size; i++)
    {
        if (strcmp(args[i], "\0") == 0) break;

        argsL++;
    }

    //NEW COMPATIBLE
    char compatibleArgs[compatible1L][compatible2L + 2];
    for (int i = 0; i < compatible1L; i++)
    {
        //ARG IS EMPTY
        if (strcmp(compatible[i], "\0") == 0) break;

        //ADD
        strcpy(compatibleArgs[i], "--");
        strcat(compatibleArgs[i], compatible[i]);
    }

    //REMAINING ARGS
    char remainingArgs[arg1Size][arg2Size];

    //ADD ARGS TO REMAINING
    for (int i = 0; i < arg1Size; i++)
    {
        //ARG IS EMPTY
        if (strcmp(args[i], "\0") == 0) break;

        //ADD
        strcpy(remainingArgs[i], args[i]);
    }

    //LOAD REMAINING ARGS
    for (int i = 0; i < arg1Size; i++)
    {
        //REMAINING IS EMPTY
        if (strcmp(remainingArgs[i], "\0") == 0) break;

        //LOAD COMPATIBLE
        for (int j = 0; j < compatible1L; j++)
        {
            //COMPATIBLE IS EMPTY
            if (strcmp(compatibleArgs[j], "\0") == 0) break;

            //REMAINING CONTAINS COMPATIBLE                     //THIS IS JUST TEST!!!
            if ((strcmp(remainingArgs[i], compatibleArgs[j]) == 0) || (strcmp(remainingArgs[i], compatibleArgs[j]) == (int) (':')))
            {
                //REMOVE ARG FROM REMAINING
                strcpy(remainingArgs[i], "\0");
            }
        }
    }

    //CHECK FOR COMPATIBLE
    bool invalid = false;
    for (int i = 0; i < argsL; i++)
    {
        if (strcmp(remainingArgs[i], "\0") != 0)
        {
            invalid = true;
            break;
        }
    }

    //RETURN IF COMPATIBLE
    if (!invalid) return;

    //:)
    if (strcmp(remainingArgs[0], "sus") == 0)
    {
        printf("Oh, so you're a sussy boi?\n\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\n");
        exitProgram(104);
    }

    char buffer[64];
    for (int i = 0; i < compatible1L; i++)
    {
        if (strcmp(remainingArgs[i], "\0") != 0)
        {
            strcpy(buffer, remainingArgs[i]);
            break;
        }
    }

    fprintf(stderr, "%s", replaceString(getDB("invalid_flag"), "{FLAG}", buffer, NULL));
    exitProgram(12);
}

bool argsContainsFlag(const char flag[compatible2L], char args[arg1Size][arg2Size])
{
    char text[32];
    bool error = false;
    bool returning = false;

    //ADD 'FLAG' TO TEXT
    strcpy(text, "--");
    strcat(text, flag);

    for (int i = 0; i < arg1Size; i++)
    {
        //ARG IS EMPTY
        if (strcmp(args[i], "\0") == 0) break;

        //CHECK IF ARGS CONTAINS FLAG      //THIS IS JUST TEST!!!
        if ((strcmp(args[i], text) == 0) || (strcmp(args[i], text) == (int) (':')))
        {
            //IS DOUBLE-USED
            if (error)
            {
                fprintf(stderr, "%s", replaceString(getDB("flag_used"), "{FLAG}", flag, NULL));
                exitProgram(10);
            }

            error = true;
            returning = true;
        }
    }

    return returning;
}

void loadFlagText(const char flag[compatible2L], char args[arg1Size][arg2Size], char * target)
{
    char flagNew[compatible2L + 2];
    char buffer[flagTextL];
    char bufferString[2];

    //ADD 'FLAG' TO flagNew
    strcpy(flagNew, "--");
    strcat(flagNew, flag);

    int flagPos = -1;

    //LOAD flagPos
    for (int i = 0; i < arg1Size; i++)
    {
        //FLAG IS EMPTY
        if (strcmp(args[i], "\0") == 0) break;

        //MATCH
        if ((strcmp(args[i], flagNew) == 0) || (strcmp(args[i], flagNew) == (char) (':')))
        {
            //SET flagPos
            flagPos = i;
            break;
        }
    }

    //flagPos DIDN'T CHANGE = THERE IS NO TEXT/FLAG (OR : IN FLAG)
    if (flagPos == -1)
    {
        fprintf(stderr, "%s\n", replaceString(getDB("invalid_text"), "{FLAG}", flag, NULL));
        exitProgram(8);
    }

    //LOAD FLAG TEXT (buffer)
    for (unsigned long i = strlen(flagNew) + 1; i < arg2Size; i++)
    {
        //ARG IS EMPTY
        if (args[flagPos][i] == '\0') break;

        buffer[i - (strlen(flagNew) + 1)] = args[flagPos][i];
    }

    //buffer DIDN'T CHANGE = THERE IS NO TEXT
    if (buffer[0] == '\0')
    {
        fprintf(stderr, "%s\n", replaceString(getDB("invalid_text"), "{FLAG}", flag, NULL));
        exitProgram(8);
    }

    //RETURN VALUE
    for (unsigned long i = strlen(flagNew) + 1; i < arg2Size; i++)
    {
        if (args[flagPos][i] == '\0') break;

        //CAST CHAR TO STRING
        sprintf(bufferString, "%c", buffer[i - (strlen(flagNew) + 1)]);

        if ((i - (strlen(flagNew) + 1)) == 0)
        {
            //COPY BUFFER TO TARGET
            strcpy(target, bufferString);
        } else
        {
            //APPEND BUFFER TO TARGET
            strcat(target, bufferString);
        }
    }
}

void loadInvalidLang(const char compatible[lang1L][lang2L], char target[])
{
    //LOAD COMPATIBLE LANGS
    for (int i = 0; i < lang1L; i++)
    {
        //LANG IS NULL (THIS SHOULDN'T HAPPEN)
        if (strcmp(compatible[i], "\0") == 0) break;

        //CONTAINS
        if (strcmp(compatible[i], target) == 0) return;
    }

    //PROGRAM CONTINUES - COMPATIBLE DOESN'T CONTAIN TARGET
    fprintf(stderr, "%s\n", replaceString(getDB("invalid_arg"), "{ARG}", target, NULL));
    exitProgram(13);
}