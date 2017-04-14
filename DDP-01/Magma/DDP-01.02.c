// DDP-01.02 : Stats sur les dates
// Date : 08/04/2017
// Pseudo : magma
// OS : Windows 10
// CC : mingw32

#include <stdio.h>

#define YEAR_START      2001
#define YEAR_END        2100
#define YEAR_COUNT     (YEAR_END - YEAR_START + 1)
#define MARCH_MONTH     3  //Mars est le 3eme mois
#define MARCH_OFFSET    22 //Paques ne tombe jamais avant le 22 Mars
#define MARCH_MAX_DATE  10 //10 dates de Paques possible en Mars (du 22 au 31 Mars)
#define APRIL_MAX_DATE  25 //25 dates de Paques possible en Avril (du 1er au 25 Avril)

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
  int march_array[YEAR_COUNT][MARCH_MAX_DATE] = {0};
  int april_array[YEAR_COUNT][APRIL_MAX_DATE] = {0};
  int march_freq_array[MARCH_MAX_DATE] = {0};
  int april_freq_array[APRIL_MAX_DATE] = {0};

  for(int year = YEAR_START; year <= YEAR_END; year++){
    int day, month;
    easter(year, &month, &day);

    if(month == MARCH_MONTH){
      march_array[year - YEAR_START][day - MARCH_OFFSET]++;
      for(int i = 0; i < MARCH_MAX_DATE; i++){
        march_freq_array[i] += day == i + MARCH_OFFSET;
      }
    }
    else{
      april_array[year - YEAR_START][day - 1]++;
      for(int i = 0; i < APRIL_MAX_DATE; i++){
        april_freq_array[i] += day == i + 1;
      }
    }
  }

  for(int i = 0; i < MARCH_MAX_DATE; i++){
    printf("03/%02d %2d  ", i + MARCH_OFFSET, march_freq_array[i]);
    for(int j = 0; j < YEAR_COUNT; j++){
      if(march_array[j][i]){
        printf("%d ", j + YEAR_START);
      }
    }
    putchar('\n');
  }

  for(int i = 0; i < APRIL_MAX_DATE; i++){
    printf("04/%02d %2d  ", i + 1, april_freq_array[i]);
    for(int j = 0; j < YEAR_COUNT; j++){
      if(april_array[j][i]){
        printf("%d ", j + YEAR_START);
      }
    }
    putchar('\n');
  }

  return 0;
}

/*
03/22  0
03/23  1  2008
03/24  0
03/25  2  2035 2046
03/26  3  2062 2073 2084
03/27  2  2005 2016
03/28  3  2027 2032 2100
03/29  3  2043 2054 2065
03/30  4  2059 2070 2081 2092
03/31  5  2002 2013 2024 2086 2097
04/01  3  2018 2029 2040
04/02  2  2051 2056
04/03  3  2067 2078 2089
04/04  4  2010 2021 2083 2094
04/05  4  2015 2026 2037 2048
04/06  3  2042 2053 2064
04/07  2  2075 2080
04/08  3  2007 2012 2091
04/09  3  2023 2034 2045
04/10  4  2039 2050 2061 2072
04/11  4  2004 2066 2077 2088
04/12  4  2009 2020 2093 2099
04/13  2  2031 2036
04/14  3  2047 2058 2069
04/15  5  2001 2063 2074 2085 2096
04/16  4  2006 2017 2028 2090
04/17  3  2022 2033 2044
04/18  3  2049 2055 2060
04/19  3  2071 2076 2082
04/20  5  2003 2014 2025 2087 2098
04/21  4  2019 2030 2041 2052
04/22  2  2057 2068
04/23  1  2079
04/24  2  2011 2095
04/25  1  2038
*/
