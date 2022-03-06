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

size_t GetLength(struct String *str)
{
    if(!str)
    {
        return 0;
    }

    if(!str->length)
    {
        int i = 0;
        while(!(str->stringInfo->Compar(str->string + i * str->stringInfo->size, str->stringInfo->strEnd))) i++;

        str->length = i;
    }

    return str->length;
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

    str->stringInfo->Print(str->string);
    return 0;
}

struct String *CreateString(void *str_original, struct StringInfo *stringInfo)
{
    if(!str_original)
        return NULL;

    struct String *str = (struct String *)malloc(sizeof(struct String));
    
    
    str->string = str_original;
    str->stringInfo = stringInfo;
    str->length = GetLength(str);

    return str;
}

struct String *Concat(struct String *s1, struct String *s2)
{
    if(!s1 || !s2)
        return NULL;

    if(s1->stringInfo != s2->stringInfo)
        return NULL;

    struct String *result = malloc(sizeof(struct String));

    result->length = s1->length + s2->length;
    result->stringInfo = s1->stringInfo;
    result->string = calloc(s1->length + s2->length, result->stringInfo->size);

    memcpy(result->string, s1->string, s1->length * s1->stringInfo->size);
    memcpy(result->string + s1->length * s1->stringInfo->size, s2->string, (s2->length) * s2->stringInfo->size);

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
    result->string = calloc(result->length, result->stringInfo->size);

    memcpy(result->string, str->string + left * str->stringInfo->size, result->length);

    return result;
}

struct String *StringTok(struct String *str, void *separator)


{
    if(!str)
        return NULL;

    if(str->stringInfo->Compar(str->string, str->stringInfo->strEnd)) //string[0] == '\0'
        return NULL;

    void *tok = str->string;

    while(!NULL)
    {

        if(str->stringInfo->Compar(str->string, str->stringInfo->strEnd)) //string[0] == '\0'
        {
            return CreateString(tok, str->stringInfo);
        }

        if(str->stringInfo->Compar(str->string, separator)) //string[0] == ' '
        {
            memcpy(str->string, str->stringInfo->strEnd, str->stringInfo->size);

            str->length--;
            str->string++;
            
            return CreateString(tok, str->stringInfo);
        }

        str->string++;
        str->length--;
    }
}

void RemoveString(struct String *str)
{
    if(str == NULL || str->string == NULL) //str->length
    {
        return;
    }

    free(str->string);
    free(str);

    str = NULL;
}