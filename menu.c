#define TRUE 1
#define FALSE 0

#include <stdlib.h>
#include "str_library.h"
#include "menu.h"
#include <stdio.h>
#include <readline/readline.h>

char *SpaceDel(char *str)
{
        int i, j, b, N = strlen(str);
        char *new_ = NULL;

        for(i = 0; i < N; i++) if(str[i] != ' ') break;
        for(j = N - 1; j >= 1; j--) if(str[j] != ' ') break;

        if(j < i)
        {
                free(new_);
                return NULL;
        }

        new_ = (char *) calloc(j - i + 2, sizeof(char));

        for(b = 0; i <= j; i++)
        {
                new_[b] = str[i];
                b++;
        }

        free(str);

        return new_;
}

int CorrectInput()
{
        char *temp = NULL;

        temp = SpaceDel(readline(NULL));

        if(temp == "" || temp == NULL || strlen(temp) > 1)
        {
                free(temp);
                return -1;
        }

        int n = *temp - '0';

        free(temp);
        return n;
}


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
    static struct String *str1;
    static struct String *str2;
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

    switch(CorrectInput())
    {
        case CREATE:
        {
            printf("Choose the string you want to enter:\n");
            printf("1. First\n");
            printf("2. Second\n");

            switch(CorrectInput())
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
        {
            struct String *strBuffer;

            strBuffer = ConCat(str1, str2);

            if(!strBuffer)
            {
                *status = EMPTY_STRING;
                return;
            }

            if(str1)
            {
                printf("Previus string 1 will be removed\n");
                RemoveString(str1);
            }

            str1 = strBuffer;

            *status = SUCCES;
            return;
        }

        case TOKEN:
        {
            struct String *strBuffer;

            strBuffer = StringTok(str1, separator);

            if(!strBuffer)
            {
                *status = EMPTY_STRING;
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

        case EXIT:

            if(str1)
                RemoveString(str1);
                
            if(str2)
                RemoveString(str2);

            free(strEnd);
            free(separator);
            free(charInfo);
            
            *status = EXIT_STATUS;
            return;

        default:
            
            *status = INVAL_INPUT;
            return;
    }
}
