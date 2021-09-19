/*
    This file runs void clearTemp() from src/api.c
*/

#include "../include/api.h"

int main(__attribute__((unused)) int argc, char * argv[])
{
    clearTemp(*argv);
    return 0;
}
