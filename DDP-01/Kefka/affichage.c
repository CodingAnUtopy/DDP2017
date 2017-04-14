#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void titre(char* titre, char c)
{
    int n = strlen(titre), i = 0;
    char *ligne = malloc((n + 1) * sizeof(char));

    if(ligne == NULL)
        exit(EXIT_FAILURE);

    for(i = 0; i < n; i++)
        ligne[i] = c;
    ligne[n] = '\0';

    printf("\n\t%s\n\t", ligne);
    printf("%s", titre);
    printf("\n\t%s\n\n", ligne);

    free(ligne);
}
