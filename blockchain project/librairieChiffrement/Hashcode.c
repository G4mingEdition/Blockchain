#include "chiffrement.h"

char* hacher(char *pBytes, int taille)
{
	/** VARIABLES **/
    unsigned int i;
    unsigned long nbr;
    char *HashChaine = NULL;

    /** INITIALISATIONS **/
    i = 0; nbr = 0;

    if((HashChaine = (char *) malloc(sizeof(char)*11)))
    {
        /** INITIALISATION DU PSEUDO-RANDOM **/
        srand(taille);

        /** GÉNÉRATION DU NOMBRE **/
        for(i=0; i<taille; i++)
        {
            if (i%3==0)
            {
                nbr += pBytes[i] * ((i + (pBytes[i]) * (taille - i ))) * 1000000;
            }
            if (i%3==1)
            {
                nbr += pBytes[i] + (pBytes[i] + (pBytes[i] * -7)* 100000000);
            }
            if (i%3==2)
            {
                srand(pBytes[taille/2]);   /** INITIALISATION DU PSEUDO-RANDOM **/
                nbr += pBytes[i] * (rand()%i + 94)*100000;
            }
        }
        if (nbr < 0) // si le nombre généré est négatif, on le fait devenir positif
        {
            nbr *= -1;
        }
        if(nbr < 1000000000) // si le nombre est inférieur à 1 000 000 000 alors on lui ajoute ce nombre pour avoir les 10 chiffres
        {
            nbr += 1000000000;
        }

        /** TRANSFORMATION **/
        sprintf(HashChaine,"%lu", nbr); // transformation du nombre en chaîne de caractères

        /** AJOUT DE LETTRES **/
        for(i=0; i<10; i++)
        {
            if (i%3==0 && (taille-i)%2 < 0.7)
            {
                HashChaine[i] += 5;
                if (HashChaine[i] > 57)
                {
                    HashChaine[i] = 48 + (HashChaine[i]-57);
                }
            }
            else
            {
                if ((rand()%(i+1)) >= nbr%(i+1))
                {
                    HashChaine[i] += 17 + i;
                }
                else
                {
                    HashChaine[i] += 49 + i;
                }
            }
        }

        HashChaine[10] = '\0';
    }
    else
        printf("HC: Memoire insuffisante.\n");

    return (HashChaine);
}
