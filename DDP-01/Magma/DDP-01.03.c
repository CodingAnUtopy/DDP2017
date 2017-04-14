// DDP-01.03 : Vers l'infini et au-dela
// Date : 07/04/2017
// Pseudo : magma
// OS : Windows 10
// CC : mingw32

#include <stdio.h>

#define YEAR_START           0 //Annee zero !!! (Le calendrier Gregorien a ete promulgue en France en 1582 ...)
#define YEAR_END       5700000 //Duree du cycle en annees
#define MARCH_MONTH          3 //Mars est le 3eme mois
#define MARCH_OFFSET        22 //Paques ne tombe jamais avant le 22 Mars
#define MARCH_MAX_DATE      10 //10 dates de Paques possible en Mars (du 22 au 31 Mars)
#define APRIL_MAX_DATE      25 //25 dates de Paques possible en Avril (du 1er au 25 Avril)

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
  int march_array[MARCH_MAX_DATE] = {0};
  int april_array[APRIL_MAX_DATE] = {0};

  //On calcule ...
  for(int year = YEAR_START; year <= YEAR_END; year++){
    int day, month;
    easter(year, &month, &day);

    if(month == MARCH_MONTH){
      for(int i = 0; i < MARCH_MAX_DATE; i++){
        march_array[i] += day == i + MARCH_OFFSET;
      }
    }
    else{
      for(int i = 0; i < APRIL_MAX_DATE; i++){
        april_array[i] += day == i + 1;
      }
    }
  }

  //On affiche ...
  for(int i = 0; i < MARCH_MAX_DATE; i++){
    printf("03/%02d : %6d  ", i + MARCH_OFFSET, march_array[i]);
    for(int j = 0; j < march_array[i] / 10000; j++){
      putchar('*');
    }
    putchar('\n');
  }

  for(int i = 0; i < APRIL_MAX_DATE; i++){
    printf("04/%02d : %6d  ", i + 1, april_array[i]);
    for(int j = 0; j < april_array[i] / 10000; j++){
      putchar('*');
    }
    putchar('\n');
  }

  return 0;
}

/*

03/22 :  27550  **
03/23 :  54150  *****
03/24 :  81225  ********
03/25 : 110200  ***********
03/26 : 133000  *************
03/27 : 165300  ****************
03/28 : 186200  ******************
03/29 : 192850  *******************
03/30 : 189525  ******************
03/31 : 189525  ******************
04/01 : 192850  *******************
04/02 : 186200  ******************
04/03 : 192850  *******************
04/04 : 186200  ******************
04/05 : 192850  *******************
04/06 : 189525  ******************
04/07 : 189525  ******************
04/08 : 192850  *******************
04/09 : 186201  ******************
04/10 : 192850  *******************
04/11 : 186200  ******************
04/12 : 192850  *******************
04/13 : 189525  ******************
04/14 : 189525  ******************
04/15 : 192850  *******************
04/16 : 186200  ******************
04/17 : 192850  *******************
04/18 : 197400  *******************
04/19 : 220400  **********************
04/20 : 189525  ******************
04/21 : 162450  ****************
04/22 : 137750  *************
04/23 : 106400  **********
04/24 :  82650  ********
04/25 :  42000  ****

*/
