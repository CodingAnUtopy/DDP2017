#ifndef SVG_H
#define SVG_H

    #include <stdio.h>

    #include "constantes.h"

    #define SVG_FILE        "Histogramme_freq_Paques.svg"
    #define SVG_BAR_W       35
    #define SVG_BAR_SPACE   3
    #define SVG_BORDER_X    50
    #define SVG_BORDER_Y    50
    #define SVG_WIN_W       (((SVG_BAR_W + SVG_BAR_SPACE) * NB_JOURS_PAQUES) + (2 * SVG_BORDER_X) - SVG_BAR_SPACE)
    #define SVG_WIN_H       768
    #define SVG_TXT_SIZE    (SVG_BAR_W / 3)
    #define SVG_TXT_SIZE2   ((SVG_BAR_W / 3) - (SVG_BAR_W / 15))
    #define SVG_BG_COLOR    "#f9e8a7"
    #define SVG_BAR_COLOR   "#e55909"
    #define SVG_BAR_STROKE  "#26464D"

    void SVG_debut(FILE* fichier);
    void SVG_fin(FILE* fichier);
    void SVG_rect(FILE* fichier, int pos_x, int pos_y, int size_x, int size_y);
    void SVG_background(FILE* fichier);
    void SVG_date(FILE* fichier, int pos_x, int pos_y, int mois, int jour);
    void SVG_freq(FILE* fichier, int pos_x, int pos_y, double freq);
    void SVG_txt_horizontal(FILE* fichier, int pos_x, int pos_y, char* txt, int taille_txt);
    void SVG_txt_vertical(FILE* fichier, int pos_x, int pos_y, char* txt, int taille_txt);

#endif // SVG_H
