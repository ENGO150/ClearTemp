/*
    This source file contains the ClearTemp core
*/

#include "../../include/api.h"
#include "../../include/tools.h"

void clearTemp(char args[])
{
    if (!isOsCompatible())
    {
        printErr("not_compatible_os", 1);
    }

    print("final");
}
