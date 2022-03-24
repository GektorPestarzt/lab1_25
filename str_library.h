struct StringInfo;
struct String;

struct StringInfo *CreateType(size_t, void *, void *, void *);
struct String *CreateString(void *, struct StringInfo *);

size_t GetDataLength(struct String *);
size_t GetLength(struct String *);
void *GetString(struct String *);
int PrintString(struct String *);
void RemoveString(struct String *);

struct String *Copy(struct String *);
struct String *ConCat(struct String *, struct String *);
struct String *SubString(struct String *, size_t, size_t);
struct String *StringTok(struct String *, void *);
int FindSubStr(struct String *, struct String *);
struct Struct *Split(struct String *);