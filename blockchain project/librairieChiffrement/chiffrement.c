#include "chiffrement.h"

char* chiffrer(char *pChaine, int taille)
{
    /** VARIABLES **/
    char *pChaineChiffree = NULL;
    int i;

    /** INITIALISATIONS **/
    i = 0;

    if((pChaineChiffree = (char *) malloc(taille)))
    {
        /** TRANSFERT **/
        for(i=0; i<=taille-1; i++)
            pChaineChiffree[i] = pChaine[i];

        /** CHIFFREMENT **/
        for(i=0; i<=taille-1; i++)
        {
            if (i == 0) pChaineChiffree[i] = ~pChaineChiffree[i]; // inversion des bits
            else if (i%2 == 0) pChaineChiffree[i] = ~pChaineChiffree[i] ^ i; // inversion des bits + ou exclusif
            else pChaineChiffree[i] = pChaineChiffree[i] ^ i; // ou exclusif
        }
    }
    else printf("C: Memoire insuffisante.\n");

    return(pChaineChiffree);
}

char* dechiffrer(char *pChaineChiffree, int taille)
{
    /** VARIABLES **/
    char *pChaineDechiffree = NULL;
    int i;

    if((pChaineDechiffree = (char *) malloc(taille)))
    {
        /** TRANSFERT **/
        for(i=0; i<=taille-1; i++)
            pChaineDechiffree[i] = pChaineChiffree[i];

        /** CHIFFREMENT **/
        for(i=0; i<=taille-1; i++)
        {
            if (i == 0) pChaineDechiffree[i] = ~pChaineDechiffree[i]; // inversion des bits
            else if (i%2 == 0) pChaineDechiffree[i] = ~pChaineDechiffree[i] ^ i; // inversion des bits + ou exclusif
            else pChaineDechiffree[i] = pChaineDechiffree[i] ^ i; // ou exclusif
        }
    }
    else printf("D: Memoire insuffisante.\n");

    return(pChaineDechiffree);
}
