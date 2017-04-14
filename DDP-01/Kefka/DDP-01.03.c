/*
    DDP-01.03 : Vers l'infini et au-delà - Niveau : Confirmé entêté et documenté
    ----------------------------------------------------------------------------
                                                                  par Kefka 1988

    Les dates de Pâques suivent un cycle de 5 700 000 ans.
    Cette dernière partie va simplement consister à obtenir les fréquence des dates de Pâques sur cette période.
    Rien de bien compliqué, mais le programme devra créer une sortie au format SVG qui représentera un histogramme des fréquences.

    Cette sortie, une fois affichée dans un viewer, pourra ressembler à :
    http://nc233.com/wp-content/uploads/2016/11/graphe_date_paques.png

    Rien ne vous empêche d'être plus créatifs ou plus artistiques … l'exemple manque cruellement du couleurs …

    La difficulté principale va résider ici à produire la sortie au format SVG sans utiliser de bibliothèque externe.
    Il va donc falloir lire la doc … mais je vous rassure ce n'est pas bien compliqué, ce n'est qu'un format texte … ou presque.
    Si cela vous fait trop peur alors vous pouvez vous rabattre sur un affichage en mode texte
    en considérant que ma console a au moins 80 colonnes et 40 lignes.

*/

#include <stdlib.h>
#include <stdio.h>

#include "struct.h"

int get_maxOccPaques(ListeJoursPaques *liste, int taille)
{
    int i = 0, ret = 0;

    if(liste == NULL)
        return EXIT_FAILURE;

    ret = liste[0].nbOccurence;

    for(i = 0; i < taille; i++)
    {
        if(liste[i].nbOccurence > ret)
            ret = liste[i].nbOccurence;
    }

    return ret;
}
