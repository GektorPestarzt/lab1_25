#include <stdio.h>
#include "str_library.h"

int main()
{
    struct StringInfo *stringInfo = Create(sizeof(char));
    struct String *str = From("123", 3, stringInfo);

    printf("%s\n", GetString(str));

    return 0;
}