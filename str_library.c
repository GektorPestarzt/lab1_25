#define TRUE 1
#define FALSE 0

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct StringInfo
{
    size_t size;
    void *strEnd;
    void *(*Compar)(void *, void *);
    void *(*Print)(void *);
};

struct String
{
    struct StringInfo *stringInfo;
    void *string;
    size_t length;
};

struct StringInfo *CreateType(size_t size, void *strEnd, void* (*Compar)(void *, void *), void* (*Print)(void *))
{
    struct StringInfo *stringInfo = (struct StringInfo *)malloc(sizeof(struct StringInfo));

    stringInfo->size = size;
    stringInfo->strEnd = strEnd;
    stringInfo->Compar = Compar;
    stringInfo->Print = Print;

    return stringInfo;
}

size_t GetDataLength(struct String *str)
{
    if(!str || !str->string)
        return 0;

    return str->length;
}

size_t GetLength(void *string, struct StringInfo *stringInfo)
{
    if(!string)
    {
        return 0;
    }

    int i = 0;
    while(!(stringInfo->Compar(string + i * stringInfo->size, stringInfo->strEnd))) i++;

    return i;
}

void *GetString(struct String *str)
{
    if(!str)
        return NULL;

    return str->string;;
}

size_t GetSize(struct String *str)
{
    if(!str)
        return 0;

    return sizeof(str->string[0]);
}

int PrintString(struct String *str)
{
    if(str == NULL || str->string == NULL)
        return 1;

    if(str->length == 0)
        return 1;

    str->stringInfo->Print(str->string);
    return 0;
}

struct String *CreateString(void *str_original, struct StringInfo *stringInfo)
{
    if(!str_original)
        return NULL;

    struct String *str = (struct String *)malloc(sizeof(struct String));

    str->length = GetLength(str_original, stringInfo);
    
    str->string = str_original;
    str->stringInfo = stringInfo;

    return str;
}

struct String *ConCat(struct String *s1, struct String *s2)
{
    if(!s1 || !s2)
        return NULL;

    if(s1->stringInfo != s2->stringInfo)
        return NULL;

    struct String *result = malloc(sizeof(struct String));

    result->length = s1->length + s2->length;
    result->stringInfo = s1->stringInfo;
    result->string = calloc(s1->length + s2->length + 1, result->stringInfo->size);

    memcpy(result->string, s1->string, s1->length * s1->stringInfo->size);
    memcpy(result->string + s1->length * s1->stringInfo->size, s2->string, s2->length * s2->stringInfo->size);

    return result;
}

struct String *SubString(struct String *str, size_t left, size_t right)
{
    if(!str)
        return NULL;

    if(right >= str->length || left > right)
        return NULL;

    struct String *result = malloc(sizeof(struct String));

    result->length = right - left + 1;
    result->stringInfo = str->stringInfo;
    result->string = calloc(result->length + 1, result->stringInfo->size);

    memcpy(result->string, str->string + left * str->stringInfo->size, result->length);

    return result;
}

void RemoveString(struct String *str)
{
    if(str == NULL)
        return;

    if(str->string == NULL)
    {
        free(str);
        return;
    }

    free(str->string);
    free(str);
}

struct String *StringTok(struct String *str, void *separator)
{
    if(!str)
        return NULL;

    if(!GetDataLength(str))
        return NULL;

    void *point = str->string;
    void *tok;
    struct String *tmp;

    void *newString;
    int count = 0;

    while(!NULL)
    {

        if(str->stringInfo->Compar(point, str->stringInfo->strEnd)) //string[0] == '\0'
        {
            tok = calloc(count + 1, str->stringInfo->size);
            memcpy(tok, str->string, count * str->stringInfo->size);
            tmp = CreateString(tok, str->stringInfo);

            free(str->string);
            str->string = NULL;
            str->length = 0;

            return tmp;
        }

        if(str->stringInfo->Compar(point, separator)) //string[0] == ' '
        {
            point += str->stringInfo->size;
            count++;

            tok = calloc(count, str->stringInfo->size);
            memcpy(tok, str->string, (count - 1) * str->stringInfo->size);
            tmp = CreateString(tok, str->stringInfo);

            newString = calloc(str->length - count + 1, str->stringInfo->size);
            memcpy(newString, point, (str->length - count) * str->stringInfo->size);

            free(str->string);
            str->string = newString;
            str->length -= count;
            
            return tmp;
        }

        point += str->stringInfo->size;
        count++;
    }
}

struct String *Copy(struct String *str)
{
    if(!str)
        return NULL;

    struct String *newStr = malloc(sizeof(struct String));
    newStr->string = malloc((str->length + 1) * str->stringInfo->size);

    newStr->stringInfo = str->stringInfo;
    newStr->length = str->length;

    memcpy(newStr->string, str->string, (str->length + 1) * str->stringInfo->size);

    return newStr;
}

struct Struct *Split(struct String *str)
{
    
}

int FindSubStr(struct String *str, struct String *subStr)
{
    if(!str || !subStr)
        return -2;

    if(subStr->length == 0 || str->length == 0)
        return -2;

    if(!str->string || !subStr->string)
        return -2;

    int i, j, check = 1;
    for(i = 0; i < str->length; ++i)
    {
        for(j = 0; j < subStr->length; ++j)
        {
            if(!str->stringInfo->Compar(str->string + (i + j) * str->stringInfo->size, subStr->string + j * str->stringInfo->size))
            {
                check = 0;
                break;
            }
        }

        if(check)
            return i;

        check = 1;
    }

    return -1;
} 