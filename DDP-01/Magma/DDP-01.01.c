// DEFI DE PAQUES - DDP-01.01 : Calcul des dates
// Date : 01/04/2017
// Pseudo : magma

#include <stdio.h>

#define YEAR_START 2001
#define YEAR_END   2100

void easter(int year, int *month, int *day)
{
  //Meeus/Jones/Butcher Gregorian algorithm

  int a  =  year % 19;
  int b  =  year / 100;
  int c  =  year % 100;
  int d  =  b / 4;
  int e  =  b % 4;
  int f  = (b + 8) / 25;
  int g  = (b - f + 1) / 3;
  int h  = (19 * a + b - d - g + 15) % 30;
  int i  =  c / 4;
  int k  =  c % 4;
  int L  = (32 + 2 * e + 2 * i - h - k) % 7;
  int m  = (a + 11 * h + 22 * L) / 451;

  *month =  (h + L - 7 * m + 114) / 31;
  *day   = ((h + L - 7 * m + 114) % 31) + 1;
}

int main(void)
{
  for(int year = YEAR_START; year <= YEAR_END; year++)
  {
    int day, month;
    easter(year, &month, &day);
    printf("%d/%02d/%02d\n", year, month, day);
  }

  return 0;
}
