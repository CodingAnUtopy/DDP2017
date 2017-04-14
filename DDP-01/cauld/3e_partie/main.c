#include <stdio.h>

typedef unsigned int uint;

typedef struct
{
    uint year;
    uint month;
    uint day;
} Date;

Date geteasterDate(uint year);
size_t arrayPositionFromDate(Date date);
Date dateFromArrayPosition(uint n);


// pré-condition year >= 1583
Date geteasterDate(uint year)
{
    /*
       algorithme:
       https://fr.wikipedia.org/wiki/Calcul_de_la_date_de_P%C3%A2ques_selon_la_m%C3%A9thode_de_Meeus
    */

    Date easterDate;

    uint n = year % 19;
    uint c = year / 100;
    uint u = year % 100;
    uint s = c / 4;
    uint t = c % 4;
    uint p = (c + 8) / 25;
    uint q = (c - p + 1) / 3;
    uint e = (19 * n + c - s - q + 15) % 30;
    uint b = u / 4;
    uint d = u % 4;
    uint L = (32 + 2 * t + 2 * b - e - d) % 7;
    uint h = (n + 11 * e + 22* L) / 451;
    uint m = (e + L - 7 * h + 114) / 31;
    uint j = (e + L - 7 * h + 114) % 31;


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

int main(void)
{
    uint occurrence[35] = {0};

    for(uint y = 2001; y < 2001 + 5700000; y++)
    {
        Date easterDate = geteasterDate(y);
        occurrence[arrayPositionFromDate(easterDate)]++;
    }


    printf("Fréquence sur une période de 5.700.000 années: \n");

    for(uint i = 0; i < 35; i++)
    {
        Date date = dateFromArrayPosition(i);
        printf("%02u/%02u : %u\n", date.month, date.day, occurrence[i]);
    }

    return 0;
}
