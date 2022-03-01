#include <string.h>
#include <stdlib.h>

struct StringInfo;
struct String;

struct StringInfo *Create(size_t);
struct String *From(char *, size_t, struct StringInfo *);

size_t GetLength(struct String *);
char *GetString(struct String *);

struct String *Concat(struct String *s1, struct String *s2);
struct String *SubString(struct String str, size_t left, size_t right);
struct String *StringSplit(struct String str, char separator);