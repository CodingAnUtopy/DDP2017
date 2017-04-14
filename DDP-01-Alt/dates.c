#include "dates.h"

static const unsigned tabmois[13] =
    {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334} ;
static const unsigned tabmoisb[13] = 
    {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335} ;

bool bissextile(unsigned an)
    // vérifie si une année est bissextile
{
    bool bis = false ;  // bissextilité
    if (an % 4 == 0)
        bis = true ;    // bissextile en calendrier julien
    if ((an % 100 == 0) && (an % 400 != 0))
        bis = false ;   // pas bissextile en calendrier grégorien
    return bis ;
}

bool amjvalide(struct amjdate date)
    // vérifie si la date AMJ est valide
    // (ne vérifie pas avec précision la validité des jours)
{
    if ((date.a < 2000) || (date.m < 1) || (date.m > 12) || (date.j < 0) || (date.j > 31))
        return false ;
    else
        return true ;
}

float njours_depuis_2000(unsigned an)
    // nombre de jours entre le 0 janvier 2000 et le 0 janvier de 'an'.
{
    float nj = 0.0 ;    // nombre de jours à retourner
    if (an < 2000)
    {
        fprintf(stderr, "njours_depuis_2000 : année incorrecte.\n") ;
        return -1.0 ;
    }
    for (unsigned a = 2000 ; a < an ; a++)
    {
        if (bissextile(a))
            nj += 366.0 ;
        else
            nj += 365.0 ;
    }
    return nj ;
}

float njours_depuis_0janvier(struct amjdate date)
    // nombre de jours entre la date AMJ et le 0 janvier de l'année
{
    float nj = 0.0 ; // nombre de jours à retourner
    if (!amjvalide(date))
    {
        fprintf(stderr, "njours_depuis_0janvier : date incorrecte.\n") ;
        return -1.0 ;
    }
    nj = tabmois[date.m] + date.j ;
    if ((bissextile(date.a)) && (date.m >2))    // après le 29/02
        nj += 1.0 ;
    return nj ;
}

float conv_j2000(struct amjdate date)
    // convertit 'date' en J2000
{
    return njours_depuis_2000(date.a) + njours_depuis_0janvier(date) ;
}

struct amjdate conv_mj(unsigned an, float njours)
    // convertit 'njours' de l'année 'an' en date AMJ
{
    struct amjdate rdate ;      // date à retourner
    unsigned const* ptab = tabmois ;  // a priori l'année n'est pas bissextile
    unsigned mois ;         // mois recherché (entre 1 et 12)
    rdate.a = an ;
    if ((njours < 0.0) || (njours > 367.01))
    {
        fprintf(stderr, "conv_mj : nombre de jours incorrect.\n") ;
        rdate.m = 0 ; rdate.j = -1.0 ;
        return rdate ;
    }
    if (bissextile(an))
        ptab = tabmoisb ;
    for (mois = 1 ; mois <= 12 ; mois++)
    {
        if (ptab[mois+1] >= (unsigned)njours)
            break ;
    }
    rdate.m = mois ;
    rdate.j = njours - ptab[mois] ;
    return rdate ;
}

struct amjdate conv_amj(float njours)
    // convertit 'njours' en date AMJ
{
    unsigned an_test = 2000 ;   // année à tester
    unsigned an ;               // année correspondant à 'njours'
    float nj_test = 0 ; // nombre de jours entre 0 janvier 2000 et 0 janvier 'an_test'
    float nj ;          // nombre de jours entre 0 janvier 'an' et la date courante
    do
    {
        an_test++ ;
        nj_test  = njours_depuis_2000(an_test) ;
    } while (nj_test < njours) ;
    an = an_test - 1 ;
    nj = njours - njours_depuis_2000(an) ;
    return conv_mj(an, nj) ; 
}

void print_amjdate(struct amjdate date)     // affichage AAAA/MM/JJ
{
    printf("%4u/%02u/%02u", date.a, date.m, (unsigned)date.j) ;
}

void print_amjdatehm(struct amjdate date)   // affichage AAAA/MM/JJ HH:MM
{
    unsigned jent ; // partie entière du jour
    float heures ;  // heures décimales
    unsigned hh ;   // heures
    unsigned mm ;   // minutes
    jent = (unsigned int)date.j ;
    heures = 24.0 * (date.j - jent) ;
    hh = (unsigned)heures ;
    mm = (unsigned)(60.0 * (heures - hh) + 0.5) ;   // +0.5 afin d'arrondir
    printf("%4u/%02u/%02u %02u:%02u", date.a, date.m, jent, hh, mm) ;
}