enum EnumMenuStatus
{
    SUCCES = 1,
    EXIT_STATUS = 0,
    FIRST = 2,
    INVAL_INPUT = -1,
    EMPTY_STRING = -3,
    UNKNOWN = -2,
};


enum EnumMenuPoints
{
    CREATE = 1,
    PRINT = 2,
    SUBSTRING = 3,
    CONCAT = 4, 
    TOKEN = 5,
    EXIT = 6,
};

void menu(int *);