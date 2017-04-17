/*
    DDP-01.03 : Vers l'infini et au-del� - Niveau : Confirm� ent�t� et document�
    ----------------------------------------------------------------------------
                                                                  par Kefka 1988

    Les dates de P�ques suivent un cycle de 5 700 000 ans.
    Cette derni�re partie va simplement consister � obtenir les fr�quence des dates de P�ques sur cette p�riode.
    Rien de bien compliqu�, mais le programme devra cr�er une sortie au format SVG qui repr�sentera un histogramme des fr�quences.

    Cette sortie, une fois affich�e dans un viewer, pourra ressembler � :
    http://nc233.com/wp-content/uploads/2016/11/graphe_date_paques.png

    Rien ne vous emp�che d'�tre plus cr�atifs ou plus artistiques � l'exemple manque cruellement du couleurs �

    La difficult� principale va r�sider ici � produire la sortie au format SVG sans utiliser de biblioth�que externe.
    Il va donc falloir lire la doc � mais je vous rassure ce n'est pas bien compliqu�, ce n'est qu'un format texte � ou presque.
    Si cela vous fait trop peur alors vous pouvez vous rabattre sur un affichage en mode texte
    en consid�rant que ma console a au moins 80 colonnes et 40 lignes.

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
