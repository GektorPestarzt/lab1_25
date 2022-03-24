enum
{
    SUBSTRING_TEST = 1,
    CONCATENATE_TEST = 2,
    TOKEN_TEST = 3
};

struct TestingData
{
    char *str1;
    size_t sizeStr1;
    char *str2;
    size_t sizeStr2;
    int mode;
    size_t conLeft, conRight;
    char *strResult;
    size_t sizeResult;
};

int test(void);