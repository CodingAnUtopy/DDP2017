#ifndef DDP_01_02
#define DDP_01_02

    #include "struct.h"

    // affichage
    void printf_tab_struct_tm_yyyymmdd(struct tm *tab, int taille);
    void printf_occurence_jourPaques(ListeJoursPaques *liste, int tailleListe, struct tm *date, int tailleDate, int mode);
    void printf_annee_jourPaques(ListeJoursPaques *liste);
    // Calcul et init
    int compterNbOccurence(ListeJoursPaques *liste, int tailleListe, struct tm *date, int tailleDate);
    struct tm *init_tab_datePaquesGreg(int debut, int fin);
    ListeJoursPaques *init_tab_listeJoursPaques();
    // liste chaînée
    void ajouterAnneeDeJoursPaques(ListeJoursPaques *liste, struct tm *date);
    void freeAnnee(ListeJoursPaques *liste);

#endif // DDP_01_02
