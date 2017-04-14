#include <stdio.h>
#include <stdlib.h>
#include "dates.h"
#include "astro.h"

int main(void)
{
    unsigned int an ;
    struct amjdate date ;   // une date en AMJ
    float njours ;          // une date en J2000
    float jequinoxe ;       // équinoxe en J2000
    float jpleinelune ;     // prochaine pleine lune en J2000
    float jpaques ;         // Pâques en J2000

    while (true)
    {
        printf("Année : ") ;
        scanf("%u", &an) ;
        if (an == 0) break ; // sortie du programme

/*      // Test de 'bissextile'
        if (bissextile(an))
            printf("Cette année est bissextile.\n") ;
        else
            printf("Cette année n'est pas bissextile.\n") ;

        // Test de 'njours_depuis_2000'
        njours = njours_depuis_2000(an) ;
        printf("%.1f jours écoulés entre 00/01/2000 et 00/01/%u.\n",
               njours, an) ;

        // Test de 'njours_depuis_0janvier'
        date.a = an ;
        printf("Jour Mois : ") ;
        scanf("%f %u", &(date.j), &(date.m)) ;
        njours = njours_depuis_0janvier(date) ;
        printf("%.1f jours écoulés entre 00/01/%u et %04.1f/%02u/%u.\n",
               njours, date.a, date.j, date.m, date.a) ;

        // Test de 'conv_j2000'
        njours = conv_j2000(date) ;
        printf("%.1f jours écoulés entre 00/01/2000 %04.1f/%02u/%u.\n",
               njours, date.j, date.m, date.a) ;

        // Test de 'conv_amj'
        date = conv_amj(njours) ;
        printf("La date de départ était : %04.1f/%02u/%u.\n",
               date.j, date.m, date.a) ;

        // Vérification que (int)x retourne la partie entière et pas l'arrondi
        printf("%f\t%d\n", 3.99999, (int)3.99999) ;
        // Ça marche : il affiche 3 et pas 4.
  
        // calcul des équinoxes de printemps
        for (unsigned annee = 2001 ; annee <= 2100 ; annee++)
        {
            jequinoxe += ANTROP ;
            date = conv_amj(jequinoxe) ;
            printf("Équinoxe %u : ", annee) ;
            print_amjdatehm(date) ;
            printf("\n") ;
        }
*/
        // calcul de l'équinoxe de printemps pour l'année 'an'
        jequinoxe = jequ(an) ;
        date = conv_amj(jequinoxe) ;
        printf("Équinoxe %u : %f ", an, jequinoxe) ;
        print_amjdatehm(date) ;
        printf("\n") ;

        // calcul des pleines lunes suivant l'équinoxe de printemps
        jpleinelune = jpl(jequinoxe) ;
        date = conv_amj(jpleinelune) ;
        printf("Prochaine pleine lune : %f ", jpleinelune) ;
        print_amjdatehm(date) ;
        printf(" %u ", jsemaine(jpleinelune)) ; // pour vérifier 'jsemaine'
        printf("\n") ;

        // calcul de la date de Pâques
        jpaques = jpaq(jpleinelune) ;
        date = conv_amj(jpaques) ;
        printf("Pâques %u : ", an) ;
        print_amjdate(date) ;
        printf("\n") ;

    }
    return EXIT_SUCCESS ;
}