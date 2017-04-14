/*

    DDP-01.02 : Stats sur les dates - Niveau : Confirmé
    ---------------------------------------------------
                                          par Kefka1988

    Dans cette partie on va essayer d'établir quelques Fun Facts sur les dates de Pâques au XXIème siècle.
    Connaissant les dates il va falloir afficher :

    -   la date (MM/DD) et les années (YYYY) pour lesquelles Pâques tombe au plus tôt
    -   la date (MM/DD) et les années (YYYY) pour lesquelles Pâques tombe au plus tard
    -   les dates (MM/DD) les plus fréquentes et les années (YYYY) concernées
        sachant que la date de Pâques ne peut tomber qu'entre le 03/22 et le 04/25,
        les dates (MM/DD) comprises entre ces bornes pour lesquelles Pâques ne tombera pas au XXIème siècle.

*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "struct.h"
#include "constantes.h"
#include "DDP-01.01.h"
#include "DDP-01.02.h"

/*
    Fonctions de comparaison
    ------------------------
    Les fonctions retournent une valeur, donc rendent la main, pas besoin de exit() !
    - compare_date_mmdd_yyyy : mois -> jour -> annee
    - compare_nb_occurence : nbOccurence -> mois -> jour
    - compare_date_occurence : mois -> jour -> nbOccurence
*/

static int compare_date_mmdd_yyyy_dec(const void *a, const void *b)
{
    const struct tm *pa = a;
    const struct tm *pb = b;

    if(pb->tm_mon > pa->tm_mon)
        return 1;
    else if(pb->tm_mon < pa->tm_mon)
        return -1;
    else if(pb->tm_mday > pa->tm_mday)
        return 1;
    else if(pb->tm_mday < pa->tm_mday)
        return -1;
    else if(pb->tm_year > pa->tm_year)
        return 1;
    else if(pb->tm_year < pa->tm_year)
        return -1;
    else
        return 0;
}
static int compare_nb_occurence(const void *a, const void *b)
{
    const ListeJoursPaques *pa = a;
    const ListeJoursPaques *pb = b;

    if(pa->nbOccurence > pb->nbOccurence)
        return 1;
    else if(pa->nbOccurence < pb->nbOccurence)
        return -1;
    if(pa->mois > pb->mois)
        return 1;
    else if(pa->mois < pb->mois)
        return -1;
    if(pa->jour > pb->jour)
        return 1;
    else if(pa->jour < pb->jour)
        return -1;
    else
        return 0;
}
static int compare_nb_occurence_dec(const void *a, const void *b)
{
    const ListeJoursPaques *pa = a;
    const ListeJoursPaques *pb = b;

    if(pb->nbOccurence > pa->nbOccurence)
        return 1;
    else if(pb->nbOccurence < pa->nbOccurence)
        return -1;
    if(pa->mois > pb->mois)
        return 1;
    else if(pa->mois < pb->mois)
        return -1;
    if(pa->jour > pb->jour)
        return 1;
    else if(pa->jour < pb->jour)
        return -1;
    else
        return 0;
}
static int compare_date_occurence(const void *a, const void *b)
{
    const ListeJoursPaques *pa = a;
    const ListeJoursPaques *pb = b;

    if(pa->mois > pb->mois)
        return 1;
    else if(pa->mois < pb->mois)
        return -1;
    if(pa->jour > pb->jour)
        return 1;
    else if(pa->jour < pb->jour)
        return -1;
    if(pa->nbOccurence > pb->nbOccurence)
        return 1;
    else if(pa->nbOccurence < pb->nbOccurence)
        return -1;
    else
        return 0;
}
static int compare_date_occurence_dec(const void *a, const void *b)
{
    const ListeJoursPaques *pa = a;
    const ListeJoursPaques *pb = b;

    if(pa->mois < pb->mois)
        return 1;
    else if(pa->mois > pb->mois)
        return -1;
    if(pa->jour < pb->jour)
        return 1;
    else if(pa->jour > pb->jour)
        return -1;
    if(pb->nbOccurence > pa->nbOccurence)
        return 1;
    else if(pb->nbOccurence < pa->nbOccurence)
        return -1;
    else
        return 0;
}
/*
    Fonctions de type printf
    ------------------------
*/
void printf_tab_struct_tm_yyyymmdd(struct tm *tab, int taille)
{
    int i = 0;

    for(i = 0; i < taille; i++)
        printf("%04d/%02d/%02d\n", tab[i].tm_year + 1900, tab[i].tm_mon + 1, tab[i].tm_mday);
}
void printf_occurence_jourPaques(ListeJoursPaques *liste, int tailleListe, struct tm *date, int tailleDate, int mode)
{
    int i = 0, cpt = 0, j = 0;

    if(liste == NULL || date == NULL || tailleListe <= 0 || tailleDate <= 0 || mode < -1 || mode > 2) /*
                                                                mode -1 = plus tot
                                                                mode 0 = manquant
                                                                mode 1 = plus tard
                                                                mode 2 = plus fréquent */
        exit(EXIT_FAILURE);
/*
    On trie la liste selon le mode, par nombre d'occurence,
    et on affiche à l'écran
*/
    switch(mode)
    {
        case -1: // afficher une date, avec compteur et les année(s) correspondante(s)
            qsort(liste, tailleListe, sizeof *liste, compare_date_occurence);

            for(i = 0; i < tailleListe; i++)
            {
                if(liste[i].nbOccurence != 0)
                {
                    printf("%02d/%02d (%d) ", liste[i].mois, liste[i].jour, liste[i].nbOccurence);
                    printf_annee_jourPaques(&liste[i]);
                    printf("\n");
                    break;
                }
                else
                    continue;
            }
            break;
        case 0: // afficher les dates, sur la même ligne, et le compteur
            qsort(liste, tailleListe, sizeof *liste, compare_nb_occurence);

            for(i = 0; i < tailleListe; i++)
            {
                if(liste[i].nbOccurence == 0)
                {
                    printf("%02d/%02d ", liste[i].mois, liste[i].jour);
                    cpt++;
                }
                else
                {
                    printf("(%d)\n", cpt);
                    break;
                }
            }
            break;
        case 1: // afficher une date, avec compteur et les année(s) correspondante(s)
            qsort(liste, tailleListe, sizeof *liste, compare_date_occurence_dec);

            for(i = 0; i < tailleListe; i++)
            {
                if(liste[i].nbOccurence != 0)
                {
                    printf("%02d/%02d (%d) ", liste[i].mois, liste[i].jour, liste[i].nbOccurence);
                    printf_annee_jourPaques(&liste[i]);
                    printf("\n");
                    break;
                }
                else
                    continue;
            }
            break;
        case 2: // afficher les dates, avec les années correspondantes, pour le nombre d'occurence max
            qsort(liste, tailleListe, sizeof *liste, compare_nb_occurence_dec);
            j = liste[0].nbOccurence;

            for(i = 0; i < tailleListe; i++)
            {
                if(liste[i].nbOccurence == j)
                {
                    printf("%02d/%02d (%d) ", liste[i].mois, liste[i].jour, liste[i].nbOccurence);
                    printf_annee_jourPaques(&liste[i]);
                    printf("\n");
                    cpt++;
                }
                else
                    break;
            }
            break;
    } // FIN SWITCH()
} // FIN printf_occurence_jourPaques()
void printf_annee_jourPaques(ListeJoursPaques *liste)
{
    if(liste == NULL)
        exit(EXIT_FAILURE);

    AnneeDeJoursPaques *a = liste->premier;

    printf("[ ");
    while(a != NULL)
    {
        printf("%d ", a->date->tm_year + 1900);
        a = a->suivant;
    }
    printf("]");
}
/*
    Fonctions d'initialisation et de calcul
    ---------------------------------------
*/
struct tm *init_tab_datePaquesGreg(int debut, int fin)
{
    struct tm *tab = malloc((fin - debut + 1) * sizeof(*tab));;
    int i = 0, n = 0;

    if(tab == NULL)
        exit(EXIT_FAILURE);

    n = debut;
    for(i = 0; i <= fin - debut; i++)
        get_datePaquesGreg(&tab[i], n++);

    return tab;
}
ListeJoursPaques *init_tab_listeJoursPaques()
{
    ListeJoursPaques *tab = malloc(NB_JOURS_PAQUES * sizeof(*tab));

    if(tab == NULL)
        exit(EXIT_FAILURE);

    int i = 0, j = 0, n = 0;

    for(i = 3; i <= 4; i++)
    {
        for(j = 1; j <= 31; j++)
        {
            if(i == 3 && j < 22)
                continue;
            else if(i == 4 && j > 25)
                break;
            else
            {
                tab[n].jour = j;
                tab[n].mois = i;
                tab[n].nbOccurence = 0;
                tab[n].premier = NULL;
                n++;
            }
        }
    }
    return tab;
}
int compterNbOccurence(ListeJoursPaques *liste, int tailleListe, struct tm *date, int tailleDate)
{
    int i = 0, j = 0, n = 0;

    if(liste == NULL || date == NULL || tailleListe <= 0 || tailleDate <= 0)
        exit(EXIT_FAILURE);
/*
    On parcourt les deux tableaux, on incrémente le nombre d'occurence,
    et on ajoute un maillon dans la liste chaînée, pour chaque -ListeJoursPaques liste[i]-
*/
    qsort(date, tailleDate, sizeof *date, compare_date_mmdd_yyyy_dec); // pour ajouter la plus grande d'abord, et avoir la plus petite en début de chaïne
    for(i = 0; i < tailleListe; i++)
    {
        for(j = 0; j < tailleDate; j++)
        {
            if(liste[i].jour == date[j].tm_mday && liste[i].mois == date[j].tm_mon + 1)
            {
                liste[i].nbOccurence++;
                n++;
                ajouterAnneeDeJoursPaques(&liste[i], &date[j]);
            }
        }
    }
    return n;
}
/*
    Fonctions de liste chaînée
    --------------------------
*/
void ajouterAnneeDeJoursPaques(ListeJoursPaques *liste, struct tm *date)
{
    AnneeDeJoursPaques *nouveau = malloc(sizeof(*nouveau));

    if(nouveau == NULL || liste == NULL || date == NULL)
        exit(EXIT_FAILURE);

    nouveau->date = date;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}
void freeAnnee(ListeJoursPaques *liste)
{
    int i = 0;
    AnneeDeJoursPaques *actuel = NULL, *del = NULL;

    for(i = 0; i < NB_JOURS_PAQUES; i++)
    {
        actuel = liste[i].premier;

        if(actuel == NULL) // on verifie la non-existence d'une chaîne
            continue; //  le cas échéant i++, rien à libérer
        else // si une chaîne existe
        {
            while(actuel != NULL) // et... on recommence tant qu'il y a un maillon
            {
                del = actuel; // le maillon à supprimer est stocké dans la variable temporaire
                actuel = actuel->suivant; // on pointe sur le prochain maillon
                free(del); // on libère la mémoire
            }
        }
    }
}
