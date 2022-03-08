#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "str_library.h"
#include "error_treat.h"
#include "menu.h"

int main()
{
    int status = FIRST;
    while(status)
    {
        menu(&status);

        if(status == EXIT)
            return 0;

        ErrorPrint(status);
    }

    return 0;
}