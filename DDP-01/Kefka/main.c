/*

    DDP-01 : Pâques, calendrier et stats
    ------------------------------------
                           Par Kefka1988

    https://openclassrooms.com/forum/sujet/defi-de-paques-2017-partie-1

*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "constantes.h"
#include "affichage.h"
#include "DDP-01.01.h"
#include "DDP-01.02.h"
#include "DDP-01.03.h"
#include "svg.h"

int main(void)
{
    int tailleTabDatePaques = ANNEE_FIN - ANNEE_DEBUT + 1,
        nbOccurenceTot = 0,
        i = 0,
        maxOcc = 0,
        baton_h = 0;
    double freq = 0.0;

    FILE* svg = fopen(SVG_FILE, "w");;

    struct tm *tabDatePaques = init_tab_datePaquesGreg(ANNEE_DEBUT, ANNEE_FIN);
    ListeJoursPaques *liste = init_tab_listeJoursPaques();

    // DDP-01.01
    titre("DDP-01.01", '#');

    titre("Dates de paques par annee:", '-');
    printf_tab_struct_tm_yyyymmdd(tabDatePaques, tailleTabDatePaques);

    // DDP-01.02
    titre("DDP-02.02", '#');

    nbOccurenceTot = compterNbOccurence(liste, NB_JOURS_PAQUES, tabDatePaques, tailleTabDatePaques);

    titre("Mode -1 - plus tot", '-');
    printf_occurence_jourPaques(liste, NB_JOURS_PAQUES, tabDatePaques, tailleTabDatePaques, -1);

    titre("Mode 1 - plus tard", '-');
    printf_occurence_jourPaques(liste, NB_JOURS_PAQUES, tabDatePaques, tailleTabDatePaques, 1);

    titre("Mode 2 - plus frequent", '-');
    printf_occurence_jourPaques(liste, NB_JOURS_PAQUES, tabDatePaques, tailleTabDatePaques, 2);

    titre("Mode 0 - manquant", '-');
    printf_occurence_jourPaques(liste, NB_JOURS_PAQUES, tabDatePaques, tailleTabDatePaques, 0);

    free(tabDatePaques);
    freeAnnee(liste);
    free(liste);

    // DDP-01.03
    titre("DDP-01.03", '#');

    titre("Calcul des donnees en cours...", '~');

    tailleTabDatePaques = ANNEE_FIN_2 - ANNEE_DEBUT + 1;
    tabDatePaques = init_tab_datePaquesGreg(ANNEE_DEBUT, ANNEE_FIN_2);
    liste = init_tab_listeJoursPaques();
    nbOccurenceTot = compterNbOccurence(liste, NB_JOURS_PAQUES, tabDatePaques, tailleTabDatePaques);
    maxOcc = get_maxOccPaques(liste, NB_JOURS_PAQUES);

    SVG_debut(svg);

    SVG_background(svg);
    SVG_txt_horizontal(svg, (SVG_WIN_W / 2), ((SVG_BORDER_Y / 3) + (SVG_BORDER_Y / 4)), "Histogramme des frequences de Paques (2001-5702000)", (SVG_BAR_W - (SVG_BAR_W / 5)));
    SVG_txt_horizontal(svg, (SVG_WIN_W / 2), (SVG_WIN_H - (SVG_BORDER_Y / 3)), "Dates de Paques", (SVG_BAR_W / 2));
    SVG_txt_vertical(svg, -(SVG_WIN_H / 2), (SVG_BORDER_Y / 3), "Frequence", (SVG_BAR_W / 2));

    titre("Occurence date de Paques 2001-5702000", '-');
    for(i = 0; i < NB_JOURS_PAQUES; i++)
    {
        printf("%02d/%02d : %d\n", liste[i].mois, liste[i].jour, liste[i].nbOccurence);
        baton_h = liste[i].nbOccurence * (SVG_WIN_H - (2 * SVG_BORDER_Y)) / maxOcc;
        freq = (double)liste[i].nbOccurence * 100 / (double)nbOccurenceTot;
        SVG_rect(svg, (SVG_BAR_W + SVG_BAR_SPACE) * i, SVG_WIN_H - SVG_BORDER_Y - baton_h, SVG_BAR_W, baton_h);
        SVG_date(svg, (SVG_BAR_W + SVG_BAR_SPACE) * i, SVG_WIN_H - SVG_BORDER_Y, liste[i].mois, liste[i].jour);
        SVG_freq(svg, (SVG_BAR_W + SVG_BAR_SPACE) * i, SVG_WIN_H - SVG_BORDER_Y - baton_h, freq);
    }

    SVG_fin(svg);

    titre("Generation .svg terminee!", '~');

    fclose(svg);

    free(tabDatePaques);
    freeAnnee(liste);
    free(liste);

    return EXIT_SUCCESS;
} //FIN MAIN()
