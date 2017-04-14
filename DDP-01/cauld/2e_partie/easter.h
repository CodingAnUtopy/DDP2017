#ifndef EASTER_H
#define EASTER_H

#include <stdio.h>


typedef unsigned int uint;

typedef struct YearData YearData;
typedef struct ArrayYearData ArrayYearData;

typedef struct
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
} Date;


Date getEasterDate(uint year);
size_t arrayPositionFromDate(Date date);
Date dateFromArrayPosition(uint n);
uint max(uint *array, size_t size);

YearData *earliest(uint *array, size_t size, uint yearMin, uint yearMax);
YearData *latest(uint *array, size_t size, uint yearMin, uint yearMax);
void freeYearData(YearData *data);

ArrayYearData *mostFrequent(uint *array, size_t size, uint yearMin, uint yearMax);
ArrayYearData *missingDays(uint *array, size_t size, uint yearMin, uint yearMax);
void freeArrayYearData(ArrayYearData *array);

void displayResult(YearData *result, const char *text);
void displayMostFrequent(ArrayYearData *result);
void displayMissingDays(ArrayYearData *result);

#endif // EASTER_H
