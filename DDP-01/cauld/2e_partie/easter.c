#include "easter.h"

#include <stdlib.h>

struct YearData
{
    uint dayIndex;
    uint *year;
    size_t yearCount;
};

struct ArrayYearData
{
    YearData *data;
    size_t size;
};

static YearData *findYear(uint dayIndex, uint yearMin, uint yearMax);
static ArrayYearData *initArrayYearData(size_t nDay, uint yearMin, uint yearMax);



// pré-condition year >= 1583
Date getEasterDate(uint year)
{
    /* algorithme:
       https://fr.wikipedia.org/wiki/Calcul_de_la_date_de_P%C3%A2ques_selon_la_m%C3%A9thode_de_Meeus
    */

    Date easterDate;

    unsigned int n = year % 19;
    unsigned int c = year / 100;
    unsigned int u = year % 100;
    unsigned int s = c / 4;
    unsigned int t = c % 4;
    unsigned int p = (c + 8) / 25;
    unsigned int q = (c - p + 1) / 3;
    unsigned int e = (19 * n + c - s - q + 15) % 30;
    unsigned int b = u / 4;
    unsigned int d = u % 4;
    unsigned int L = (32 + 2 * t + 2 * b - e - d) % 7;
    unsigned int h = (n + 11 * e + 22* L) / 451;
    unsigned int m = (e + L - 7 * h + 114) / 31;
    unsigned int j = (e + L - 7 * h + 114) % 31;


    easterDate.year = year;
    easterDate.month = m;
    easterDate.day = j + 1;

    return easterDate;
}

size_t arrayPositionFromDate(Date date)
{
    size_t position = 0;

    if(date.month == 3)
        position = date.day - 22;

    if(date.month == 4)
        position = date.day + 9;

    return position;
}

Date dateFromArrayPosition(uint n)
{
    Date date = {0, 0, 0};

    if(n <= 9)
    {
        date.day = 22 + n;
        date.month = 3;
    }
    else
    {
        date.day = n - 9;
        date.month = 4;
    }

    return date;
}

uint max(uint *array, size_t size)
{
    uint max = array[0];

    for(size_t i = 1; i < size; i++)
        if(max < array[i])
            max = array[i];

    return max;
}

YearData *earliest(uint *array, size_t size, uint yearMin, uint yearMax)
{
    uint earliest = 0;

    for(size_t i = 0; i < size; i++)
    {
        if(array[i] != 0)
        {
            earliest = (uint)i;
            break;
        }
    }

    return findYear(earliest, yearMin, yearMax);
}

YearData *latest(uint *array, size_t size, uint yearMin, uint yearMax)
{
    uint latest = 0;

    for(size_t i = size; i > 0; i--)
    {
        if(array[i - 1] != 0)
        {
            latest = (uint)(i - 1);
            break;
        }
    }

    return findYear(latest, yearMin, yearMax);
}

void freeYearData(YearData *data)
{
    free(data->year);
    free(data);
}

ArrayYearData *mostFrequent(uint *array, size_t size, uint yearMin, uint yearMax)
{
    uint occurrenceMax = max(array, size);


    // cherche le nombre de jours qui sont les plus fréquents
    size_t nDay = 0;

    for(size_t i = 0; i < size; i++)
        if(array[i] == occurrenceMax)
          nDay++;


    ArrayYearData *t = initArrayYearData(nDay, yearMin, yearMax);

    if(!t)
        return NULL;


    size_t n = 0;

    for(size_t i = 0; i < size; i++)
    {
        if(array[i] == occurrenceMax)
        {

            t->data[n].dayIndex = (uint)i;

            size_t j = 0;

            for(uint y = yearMin; y <= yearMax; y++)
            {

                Date easterDate = getEasterDate(y);

                if(arrayPositionFromDate(easterDate) == i)
                {
                    t->data[n].year[j] = easterDate.year;
                    j++;
                }
            }

            t->data[n].yearCount = j;

            n++;
        }
    }

    return t;
}

ArrayYearData *missingDays(uint *array, size_t size, uint yearMin, uint yearMax)
{
    // comptabilise le nombre de jours manquants
    size_t nDay = 0;

    for(uint i = 0; i < size; i++)
        if(array[i] == 0)
           nDay++;


    ArrayYearData *t = initArrayYearData(nDay, yearMin, yearMax);

    if(!t)
        return NULL;


    uint n = 0;

    for(uint i = 0; i < size; i++)
    {
        if(array[i] == 0)
        {
            t->data[n].dayIndex = i;
            n++;
        }
    }

    return t;
}

void freeArrayYearData(ArrayYearData *array)
{
    for(size_t i = 0; i < array->size; i++)
        free(array->data[i].year);

    free(array->data);
    free(array);
}

void displayResult(YearData *result, const char *text)
{
    printf("%s\n", text);

    Date date = dateFromArrayPosition(result->dayIndex);
    printf("%02u/%02u (%zu) [ ", date.month, date.day, result->yearCount);

    for(uint i = 0; i < result->yearCount; i++)
        printf("%u ", result->year[i]);

    printf("]\n\n");
}

void displayMostFrequent(ArrayYearData *result)
{
    printf("jours les plus fréquents :\n");

    for(size_t i = 0; i < result->size; i++)
    {
        Date date = dateFromArrayPosition(result->data[i].dayIndex);

        printf("%02u/%02u (%zu) [ ", date.month, date.day, result->data[i].yearCount);
        for(size_t j = 0; j < result->data[i].yearCount; j++)
        {
            printf("%u ", result->data[i].year[j]);
        }

        printf("]\n");
    }

    printf("\n");
}

void displayMissingDays(ArrayYearData *result)
{
    printf("jours manquants :\n");

    for(size_t i = 0; i < result->size; i++)
    {
        Date date = dateFromArrayPosition(result->data[i].dayIndex);

        printf("%02u/%02u ", date.month, date.day);
    }

    printf("(%zu)\n", result->size);
}


// fonctions static
YearData *findYear(uint dayIndex, uint yearMin, uint yearMax)
{
    // fonction commune aux fonctions earliest et latest
    YearData *result = malloc(sizeof(YearData));
    if(!result)
    {
        perror("malloc");
        return NULL;
    }

    uint *year = malloc((yearMax - yearMin + 1) * sizeof(uint));
    if(!year)
    {
        free(result);
        perror("malloc");
        return NULL;
    }

    uint n = 0;

    for(uint y = yearMin; y <= yearMax; y++)
    {
        Date easterDate = getEasterDate(y);

        if(arrayPositionFromDate(easterDate) == dayIndex)
        {
            year[n] = easterDate.year;
            n++;
        }
    }

    result->dayIndex = dayIndex;
    result->year = year;
    result->yearCount = n;

    return result;
}

ArrayYearData *initArrayYearData(size_t nDay, uint yearMin, uint yearMax)
{
    ArrayYearData *array = malloc(sizeof(ArrayYearData));
    if(!array)
    {
        perror("malloc");
        return NULL;
    }

    array->size = nDay;
    array->data = malloc(nDay * sizeof(YearData));

    if(!(array->data))
    {
        free(array);
        perror("malloc");
        return NULL;
    }

    for(size_t i = 0; i < nDay; i++)
        array->data[i].year = NULL;


    for(size_t i = 0; i < nDay; i++)
    {
        array->data[i].year = malloc((yearMax - yearMin + 1) * sizeof(uint));

        if(!(array->data[i].year))
        {
            perror("malloc");
            for(size_t j = 0; j < nDay; j++)
                free(array->data[j].year);

            free(array->data);
            free(array);
            return NULL;
        }
    }

    return array;
}
