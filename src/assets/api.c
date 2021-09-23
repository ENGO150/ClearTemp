/*
    This source file contains the ClearTemp core
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../include/api.h"
#include "../../include/tools.h"

void clearTemp(char args[])
{
    srand(time(NULL)); //MAKE RAND() REALLY RANDOM

    if (!isOsCompatible())
    {
        printErr("not_compatible_os", 1);
    }

    //VARS
    int deleted = 0;
    int cannotDelete = 0;
    int key = getEncryptionKey();

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
