#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "str_library.h"
#include "error_treat.h"
#include "menu.h"
#include "testing.h"

int main()
{
    #ifdef TESTS_ON
    test();
    #endif

    int status = FIRST;
    while(status)
    {
        menu(&status);

        if(status == EXIT_STATUS)
            return 0;

        ErrorPrint(status);
    }

    return 0;
}