#include <string.h>
//#include "str_library.h"

struct StringInfo
{
    size_t size;
};

struct String
{
    struct StringInfo stringInfo;
    void *string;
    size_t length;
};

struct StringInfo *Create(size_t size)
{
    struct StringInfo *stringInfo = (struct StringInfo *)malloc(sizeof(struct StringInfo));
    stringInfo->size = size;

    return stringInfo;
}

struct String *From(char *str_original, size_t length, struct StringInfo *stringInfo)
{
    struct String *str = (struct String *)malloc(sizeof(struct String));
    str->length = length;
    str->string = str_original;

    return str;
}

size_t GetLength(struct String *str)
{
    if(str)
        return str->length;
    //????????
}

char *GetString(struct String *str)
{
    if(str)
        return str->string;
    //????????
}

