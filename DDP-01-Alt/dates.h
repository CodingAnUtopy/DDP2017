#ifndef DATES_H
#define DATES_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct amjdate
{
    unsigned a ;    // année
    unsigned m ;    // mois
    float j ;       // jour
} ;

bool bissextile(unsigned an) ;          // vérifie si une année est bissextile

bool amjvalide(struct amjdate date) ;   // vérifie si la date AMJ est valide

float njours_depuis_2000(unsigned an) ;
    // nombre de jours entre le 0 janvier 2000 et le 0 janvier de 'an'.

float njours_depuis_0janvier(struct amjdate date) ;
    // nombre de jours entre la date AMJ et le 0 janvier de l'année

float conv_j2000(struct amjdate date) ; // convertit 'date' en J2000

struct amjdate conv_mj(unsigned an, float njours) ;
    // convertit 'njours' de l'année 'an' en date AMJ

struct amjdate conv_amj(float njours) ; // convertit 'njours' en date AMJ

void print_amjdate(struct amjdate date) ;   // affichage AAAA/MM/JJ

void print_amjdatehm(struct amjdate date) ; // affichage AAAA/MM/JJ HH:MM

#endif