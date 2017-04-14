#ifndef STRUCT
#define STRUCT

    typedef struct AnneeDeJoursPaques AnneeDeJoursPaques;
    struct AnneeDeJoursPaques
    {
        struct tm *date;
        AnneeDeJoursPaques *suivant;
    };
    typedef struct ListeJoursPaques ListeJoursPaques;
    struct ListeJoursPaques
    {
        int nbOccurence;
        int jour;
        int mois;
        AnneeDeJoursPaques *premier;
    };

#endif // STRUCT
