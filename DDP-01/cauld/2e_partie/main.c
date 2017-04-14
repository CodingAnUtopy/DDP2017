#include "easter.h"


int main(void)
{
    uint yearMin = 2001;
    uint yearMax = 2100;
    uint occurrence[35] = {0};

    for(uint y = yearMin; y <= yearMax; y++)
    {
        Date easterDate = getEasterDate(y);
        occurrence[arrayPositionFromDate(easterDate)]++;
    }


    // les fonctions qui retourne un pointeur ne sont pas vérifiées !
    // supposons qu' il n'y a jamais de problème
    YearData *t = earliest(occurrence, 35, yearMin, yearMax);
    displayResult(t, "au plus tôt :");
    freeYearData(t);

    t = latest(occurrence, 35, yearMin, yearMax);
    displayResult(t, "au plus tard :");
    freeYearData(t);


    ArrayYearData *data = mostFrequent(occurrence, 35, yearMin, yearMax);
    displayMostFrequent(data);
    freeArrayYearData(data);

    data = missingDays(occurrence, 35, yearMin, yearMax);
    displayMissingDays(data);
    freeArrayYearData(data);

    return 0;
}
