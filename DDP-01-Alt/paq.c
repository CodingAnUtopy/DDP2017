/* Programme principal de calcul de la date de Pâques de 2001 à 2100 */

#include <stdlib.h>
#include <stdio.h>

#include "dates.h"
#include "astro.h"

int main(void)
{
    unsigned jequinoxe ;    // date équinoxe (en nb de jours depuis 0 janv. 2000)
    unsigned jpleinelune ;  // date pleine lune qui suit (idem)
    unsigned jpaques ;      // date de Pâques (idem)
    struct amjdate dpaques ;    // date de Pâques en jour/mois/année
    for (unsigned annee = 2001 ; annee <= 2100 ; annee++)
    {
        jequinoxe = jequ(annee) ;
        jpleinelune = jpl(jequinoxe) ;
        jpaques = jpaq(jpleinelune) ;
        dpaques = conv_amj(jpaques) ;
        print_amjdate(dpaques) ;
        printf("\n") ;
    }
    return EXIT_SUCCESS ;
}