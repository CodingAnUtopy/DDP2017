#ifndef ERROR_H
#define ERROR_H


enum
{
    SUCCESS = 0,
    ERROR = -1,
    MALLOC_ERROR = -2,
    FOPEN_ERROR = -3,
    STRDUP_ERROR = -4,
};

void setError(int error);
void getError(void);

#endif // ERROR_H
