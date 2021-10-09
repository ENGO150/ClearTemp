/*
    This is my own database system
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "edb.h"

void readString(char objectRaw[], FILE * edbLoc, char ** objectFinal)
{
    //EDB FILE DOESN'T EXISTS
    if (edbLoc == NULL)
    {
        fprintf(stderr, "edbLoc is NULL!");
        exit(1);
    }

    char object[strlen(objectRaw + 2)];
    strcpy(object, objectRaw); //COPY objectRaw TO object
    strcat(object, ": "); //ADD ": " TO object

    const int bufferL = 256; //LINE LENGTH
    char buffer[bufferL]; //LINE
    while(fgets(buffer, bufferL, edbLoc)) //READ edbLoc LINE BY LINE
    {
        for (int i = 0; i < strlen(object); i++)
        {
            if (buffer[i] != object[i]) break; //DOESN'T MATCH

            if ((strlen(object) - 1) == i)
            {
                //END OF MATCHING
                char finalObject[strlen(buffer) - i];
                for (int l = (i + 1); l < (strlen(buffer) + 1); l++)
                {
                    finalObject[l - (i + 1)] = buffer[l];
                }

                //REMOVE \n
                if (finalObject[strlen(finalObject) - 1] == '\n')
                {
                    finalObject[strlen(finalObject) - 1] = '\0';
                }

                fclose(edbLoc);
                *objectFinal = finalObject;
                return;
            }
        }
    }

    fclose(edbLoc);
    *objectFinal = "ERR";
}
