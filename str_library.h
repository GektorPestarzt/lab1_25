struct StringInfo;
struct String;

struct StringInfo *CreateType(size_t, void *, void *, void *);
struct String *CreateString(void *, struct StringInfo *);

size_t GetLength(struct String *);
void *GetString(struct String *);
int PrintString(struct String *);
void RemoveString(struct String *);

struct String *Concat(struct String *, struct String *);
struct String *SubString(struct String *, size_t, size_t);
struct String *StringTok(struct String *, void *);