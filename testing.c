#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str_library.h"
#include "testing.h"

int CharComparT(void *s1, void *s2)
{
    char *is1 = (char *)s1;
    char *is2 = (char *)s2;

    if(is1[0] == is2[0]) return TRUE;
    return FALSE;
}

void PrintT(void *str)
{
    char *istr = (char *)str;

    printf("%s\n", istr);
}

struct String *MakeTestString(void *str, size_t n, struct StringInfo *charInfo)
{
    void *strNew = NULL;

    if(n > 1)
    {
        strNew = malloc(n * sizeof(char));
        memcpy(strNew, str, n * sizeof(char));
    }

    if(n == 1)
    {
        strNew = calloc(1, sizeof(char));
    }

    struct String *newData = CreateString(strNew, charInfo);
}

void CheckSolution(struct TestingData *testData, int iteration)
{
    static struct StringInfo *charInfo;
    static char *strEnd;
    static char *separator;

    strEnd = (char *)malloc(sizeof(char));
    separator = (char *)malloc(sizeof(char));

    strEnd[0] = '\0';
    separator[0] = ' ';

    charInfo = CreateType(sizeof(char), (void *)strEnd, &CharComparT, &PrintT);

    struct String *str1 = MakeTestString(testData[iteration].str1, testData[iteration].sizeStr1, charInfo);
    struct String *str2 = MakeTestString(testData[iteration].str2, testData[iteration].sizeStr2, charInfo);
    struct String *resultInitial = MakeTestString(testData[iteration].strResult, testData[iteration].sizeResult, charInfo);

    struct String *result;

    switch(testData[iteration].mode)
    {
        case SUBSTRING_TEST:
            result = SubString(str1, testData[iteration].conLeft, testData[iteration].conRight);
            break;

        case CONCATENATE_TEST:
            result = ConCat(str1, str2);
            break;

        case TOKEN_TEST:
            result = StringTok(str1, separator);
            break;
    }

    if(!result && !resultInitial)
        printf("Test %d - OK\n", iteration + 1);

    else if(GetDataLength(result) == GetDataLength(resultInitial) && !memcmp(GetString(result), GetString(resultInitial), GetDataLength(result) * sizeof(char)))
        printf("Test %d - OK\n", iteration + 1);

    else printf("Test %d - ERROR\n", iteration + 1);

    RemoveString(result);
    RemoveString(resultInitial);
    RemoveString(str1);
    RemoveString(str2);

    free(strEnd);
    free(separator);
    free(charInfo);
}

int test()
{    
    // mode 1 - Get substring
    // mode 2 - Concatenate
    // mode 3 - Get token

    //1 - str1
    //2 - str2
    //3 - mode;
    //4 - conRight
    //5 - conLeft
    //6 - strResult

    struct TestingData testData[] =
    {
        {"Hello World!", 13, "", 1, 1, 3, 6, "lo W", 5 },
        {"T", 2, "", 1, 1, 0, 0, "T", 2 },
        {"TooLittle", 10, "", 1, 1, 0, 20, NULL, 0 },
        {"Wrong", 6, "", 1, 1, 5, 2, NULL, 0 },
        {"AllString", 10, "", 1, 1, 0, 8, "AllString", 10},
        {NULL, 0, "", 1, 1, 0, 0, NULL, 0 },

        {"", 1, "", 1, 2, 0, 0, "", 1 },
        {"Some", 5, "thing", 6, 2, 0, 0, "Something", 10 },
        {"A", 2, "", 1, 2, 0, 0, "A", 2 },
        {"", 1, "B", 2, 2, 0, 0, "B", 2 },
        {NULL, 0, "ST", 3, 2, 0, 0, NULL, 0 },
        {"ST", 3, NULL, 0, 2, 0, 0, NULL, 0 },
        {"VERYVERYVERYVERYVERYVERYVERY", 29, "BIGBIGBIGBIGBIGBIG", 19, 2, 0, 0, "VERYVERYVERYVERYVERYVERYVERYBIGBIGBIGBIGBIGBIG", 47 },

        {"Hello World!!!", 15, "", 1, 3, 0, 0, "Hello", 6 },
        {"", 1, "", 1, 3, 0, 0, NULL, 0 },
        {"Something", 10, "", 1, 3, 0, 0, "Something", 10 },
        {NULL, 0, "", 1, 3, 0, 0, NULL, 0 },
        {"   ", 4, "", 1, 3, 0, 0, "", 1 },
        {"12345678910 ", 13, "", 1, 3, 0, 0, "12345678910", 12 },

    };

    int i;
    for(i = 0; i < sizeof(testData) / sizeof(struct TestingData); i++)
        CheckSolution(testData, i);

    return 0;
}


