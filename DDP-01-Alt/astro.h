#ifndef ASTRO_H
#define ASTRO_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define EQ2000   80.316157  // date J2000 de l'équinoxe de printemps 2000
#define PL2000   21.195139  // date J2000 de la première pleine lune de 2000
#define ANTROP  365.242187  // durée de l'année tropique
#define PSYNOD   29.530589  // période synodique de la Lune

float jequ(unsigned an) ;
    // retourne la date J2000 de l'équinoxe de printemps de l'année 'an'

float jpl(float njours) ;
    // retourne la date J2000 de la pleine lune qui suite 'njours'

unsigned jsemaine(float njours) ;
    // jour de la semaine entre 0 et 6 (0 = dimanche, 6 = samedi)

float jpaq(float jpleinelune) ;  // calcul le J2000 de Pâques

#endif