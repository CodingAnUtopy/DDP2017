#include "astro.h"

float jequ(unsigned an)
    // retourne la date J2000 de l'équinoxe de printemps de l'année 'an'
{
    if (an < 2000)
    {
        fprintf(stderr, "jpl : nombre de jours incorrect.\n") ;
        return -1.0 ;
    }
    return EQ2000 + ANTROP * (an - 2000.0) ;
}

float jpl(float njours)
    // retourne la date J2000 de la pleine lune qui suit 'njours'
{
    unsigned npl = 0 ;  // numéro de la prochaine pleine lune
    if (njours < 0.0)
    {
        fprintf(stderr, "jpl : nombre de jours incorrect.\n") ;
        return -1.0 ;
    }
    npl = (unsigned)( (njours - PL2000) / PSYNOD ) + 1 ;
    return PL2000 + PSYNOD * npl ;
}

unsigned jsemaine(float njours)
    // jour de la semaine entre 0 et 6 (0 = dimanche, 6 = samedi)
{
    unsigned nj = (unsigned) njours ; // partie entière de njours
    return (5 + nj) % 7 ;
}

float jpaq(float jpleinelune)    // calcul le J2000 de Pâques
{
    return jpleinelune + 7.0 - jsemaine(jpleinelune) ;
}