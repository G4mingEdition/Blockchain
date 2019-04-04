#include "testlib.h"

/** STRUCTURE **/
struct test
{
    char mots[11];
    int total;
};

void test_hachage(unsigned int nb_mots)
{
    /** VARIABLES **/
    struct test tab[nb_mots];
    int i, j, imax, found, cpt;
    char nom[100];
    char nomHash[11];
    FILE *fdico = NULL;

    i = 0; imax = 0;
    fdico = fopen("dico.txt", "rt");
        while(i < nb_mots && fgets(nom, 60, fdico))
        {
            strcpy(nomHash, hacher(nom, strlen(nom)));
            j = 0;
            found = 0;
            while(j <= imax && found == 0)
            {
                if(strcmp(nomHash, tab[j].mots) == 0)
                {
                    tab[j].total++;
                    found = 1;
                }
                j++;
            }
            if(found == 0)
            {
                strcpy(tab[imax].mots, nomHash);
                tab[imax].total = 0;
                imax++;
            }

            i++;
        }
    fclose(fdico);

    cpt = 0;
    for(j=0; j<imax-1; j++)
    {
        if(tab[j].total >= 1)
        {
            cpt+=tab[j].total;
            printf("%s\n", tab[j].mots);
        }
    }
    printf("Collisions: %d/%d", cpt, imax);
}
