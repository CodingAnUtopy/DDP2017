#ifndef DDP_01_01
#define DDP_01_01

    void get_datePaquesGreg(struct tm *dateTime, int annee); // Modifie -struct tm *dateTime-, en y retournant la date de pâques pour l'année -int annee-
    void printf_datePaquesGreg(int debut, int fin); // Affiche à l'écran les dates de pâques pour les années allant de -int debut- à -int fin-
    void fprintf_datePaquesGreg(FILE* fichier, int debut, int fin); // Écrit dans -FILE* ficher- les dates de pâques pour les années allant de -int debut- à -int fin-

#endif // DDP_01_01
