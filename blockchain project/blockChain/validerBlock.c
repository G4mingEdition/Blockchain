#include "blockChain.h"

/** VALIDATION D'UN BLOC **/
int validerBlock(BLOCK *pBlock)
{
    /** VARIABLES **/
    char hashCode[TAILLE_HASH_CODE];
    char *contenu = NULL;
    char *chaine = NULL;
    int valide;

    /** INITIALISATIONS **/
    valide = 1; hashCode[0] = '\0';

    /** VÉRIFICATION DU HASHCODE **/
    contenu = pBlock->contenuBloc.transactions[0];
    chaine = hacher(contenu, sizeof(CONTENU_BLOC)); // génération du hashCode à partir du contenu chiffré
    if(chaine != NULL)
    {
        strcpy(hashCode, chaine);
        free(chaine); // libération de l'emplacement ram alloué par le hachage
        if(strcmp(pBlock->hashCode, hashCode) == 0) // Si les hashCodes correspondent
            valide = 1;
        else // Si les hashCodes sont différents
            valide = 0;
    }

    return (valide);
}
