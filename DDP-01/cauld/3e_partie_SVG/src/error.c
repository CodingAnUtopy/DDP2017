#include "error.h"

#include <stdio.h>

static int errorCode;

void setError(int error)
{
    errorCode = error;
}

void getError(void)
{
    switch(errorCode)
    {
        case MALLOC_ERROR:
            fprintf(stderr, "Erreur d'allocation de mémoire (malloc)\n");
            break;

        case STRDUP_ERROR:
            fprintf(stderr, "Erreur d'allocation de mémoire (strdup)\n");
            break;

        case FOPEN_ERROR:
            fprintf(stderr, "Erreur d'ouverture du fichier fopen\n");
            break;

        default:
            break;
    }
}
