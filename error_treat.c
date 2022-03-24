#include <stdio.h>
#include "menu.h"

void ErrorPrint(int status)
{
    if(status == SUCCES)
        return;

    switch(status)
    {
        case INVAL_INPUT:
            printf("Incorrect input, try again\n");
            return;

        case EMPTY_STRING:
            printf("String is empty, enter a string\n");
            return;

        default:
            printf("Unknown error\n");
            return;
    }
}