/*
    This is my own database system
*/

#include <stdio.h>
#include <string.h>

#include <edb.h>

void readString(char objectRaw[], FILE * edbLoc, char ** objectFinal)
{
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
                for (int l = (i + 1); l < strlen(buffer); l++)
                {
                    finalObject[l - (i + 1)] = buffer[l];


                    //TODO: Fix end of array
                    //printf("finalObject[%d] byl nastaven na %c\n%s\n\n", l - (i + 1), buffer[l], finalObject);
                }

                *objectFinal = finalObject;
                return;
            }
        }
    }

    fclose(edbLoc);
    *objectFinal = NULL;
}
