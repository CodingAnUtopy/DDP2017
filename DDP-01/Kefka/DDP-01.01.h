#ifndef DDP_01_01
#define DDP_01_01

    void get_datePaquesGreg(struct tm *dateTime, int annee); // Modifie -struct tm *dateTime-, en y retournant la date de p�ques pour l'ann�e -int annee-
    void printf_datePaquesGreg(int debut, int fin); // Affiche � l'�cran les dates de p�ques pour les ann�es allant de -int debut- � -int fin-
    void fprintf_datePaquesGreg(FILE* fichier, int debut, int fin); // �crit dans -FILE* ficher- les dates de p�ques pour les ann�es allant de -int debut- � -int fin-

#endif // DDP_01_01
