#define TRUE 1
#define FALSE 0

#include <stdlib.h>
#include "str_library.h"
#include "menu.h"
#include <stdio.h>
#include <readline/readline.h>

int CharCompar(void *s1, void *s2)
{
    char *is1 = (char *)s1;
    char *is2 = (char *)s2;

    if(is1[0] == is2[0]) return TRUE;
    return FALSE;
}

void Print(void *str)
{
    char *istr = (char *)str;

    printf("%s\n", istr);
}

void menu(int *status)
{
    static void *str1;
    static void *str2;
    static struct StringInfo *charInfo;
    static char *strEnd;
    static char *separator;

    if(*status == FIRST)
    {
        strEnd = (char *)malloc(sizeof(char));
        separator = (char *)malloc(sizeof(char));

        strEnd[0] = '\0';
        separator[0] = ' ';

        charInfo = CreateType(sizeof(char), (void *)strEnd, &CharCompar, &Print);
        str1 = NULL;
        str2 = NULL;
    }

    printf("1. Enter a string\n");
    printf("2. Print strings\n");
    printf("3. Get substring\n");
    printf("4. Concatenate strings\n");
    printf("5. Get token from string\n");
    printf("6. Exit\n");

    int choose;
    scanf("%d", &choose);

    switch(choose)
    {
        case CREATE:
        {
            printf("Choose the sting you want to enter:\n");
            printf("1. First\n");
            printf("2. Second\n");

            int strNumber;
            scanf("%d", &strNumber);

            switch(strNumber)
            {
                case 1:

                    if(str1)
                    {
                        printf("Previus string will be removed\n");
                        RemoveString(str1);
                    }

                    char *bufferStr1 = readline("Enter the string: ");
                    str1 = CreateString((void *)bufferStr1, charInfo);

                    *status = SUCCES;
                    return;

                case 2:

                    if(str2)
                    {
                        printf("Previus string will be removed\n");
                        RemoveString(str2);
                    }

                    char *bufferStr2 = readline("Enter the string: ");
                    str2 = CreateString((void *)bufferStr2, charInfo);

                    *status = SUCCES;
                    return;

                default:

                    *status = INVAL_INPUT;
                    return;
            }
        }

        case PRINT:
            
            if(PrintString(str1))
                printf("First String is empty\n");

            if(PrintString(str2))
                printf("Second string is empty\n");

            *status = SUCCES;
            return;


        case SUBSTRING:
        {
            int left;
            int right;
            struct String *strBuffer;

            printf("Enter first index: ");
            scanf("%d", &left);

            printf("Enter second index: ");
            scanf("%d", &right);

            strBuffer = SubString(str1, left, right);

            if(!strBuffer)
            {
                *status = INVAL_INPUT;
                return;
            }

            if(str2)
            {
                printf("Previus string 2 will be removed\n");
                RemoveString(str2);
            }

            str2 = strBuffer;

            *status = SUCCES;
            return;
        }
        
        case CONCAT:
        case TOKEN:
        case EXIT:

            if(str1)
                RemoveString(str1);
                
            if(str2)
                RemoveString(str2);
            
            *status = EXIT_STATUS;
            return;

        default:
            
            *status = INVAL_INPUT;
            return;
    }
}
