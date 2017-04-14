/*

    DDP-01.01 : Calcul des dates - Niveau : Débutant
    ------------------------------------------------
                                       par Kefka1988

    Le sujet est simple : il faut calculer et afficher
    toutes les dates de Pâques du XXIème siècle (selon le rite romain, calendrier grégorien).
    La sortie attendue du programme est la liste des dates de Pâques entre le 01/01/2001 et le 31/12/2100
    par ordre croissant, une date par ligne, la date présentée au format YYYY/MM/DD avec YYYY l'année,
    MM le mois sur 2 position et DD le quantième du mois sur 2 positions. MM et DD seront préfixés par un 0 s'ils sont inférieurs à 10.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void get_datePaquesGreg(struct tm *dateTime, int annee)
{
    if(annee < 1583) // Validité de l'algorithme
        exit(EXIT_FAILURE);

    int A = 0, B = 0, C = 0, D = 0, E = 0, F = 0,
        G = 0, H = 0, I = 0, J = 0, K = 0, L = 0,
        M = 0;

    // Algorithme de Butcher
    A = annee % 19;
    B = annee / 100;
    C = annee % 100;
    D = B / 4;
    E = B % 4;
    F = (B + 8) / 25;
    G = (B - F + 1) / 3;
    H = (19 * A + B - D - G + 15) % 30;
    I = C / 4;
    J = C % 4;
    K = (32 + 2 * E + 2 * I - H - J) % 7;
    L = (A + 11 * H + 22 * K) / 451;
    M = H + K - 7 * L + 114;

    dateTime->tm_mday = (M % 31) + 1;
    dateTime->tm_mon = (M / 31) - 1; // 0->11
    dateTime->tm_year = annee - 1900;
}
void printf_datePaquesGreg(int debut, int fin)
{
    struct tm date;
    int i = 0;

    for(i = debut; i <= fin; i++)
    {
        get_datePaquesGreg(&date, i);
        printf("%d/%02d/%02d\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday);
    }
}
void fprintf_datePaquesGreg(FILE* fichier, int debut, int fin)
{
    struct tm date;
    int i = 0;

    for(i = debut; i <= fin; i++)
    {
        get_datePaquesGreg(&date, i);
        fprintf(fichier, "%d/%02d/%02d\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday);
    }
}
