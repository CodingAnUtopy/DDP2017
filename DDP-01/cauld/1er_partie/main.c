#include <stdio.h>

typedef struct
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
} Date;

Date geteasterDate(unsigned int year);

// pré-condition year >= 1583
Date geteasterDate(unsigned int year)
{
    /*
       algorithme:
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

int main(void)
{
    for(unsigned int y = 2001; y <= 2100; y++)
    {
        Date easterDate = geteasterDate(y);
        printf("%4u/%02u/%02u\n", easterDate.year, easterDate.month, easterDate.day);
    }

    return 0;
}
