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

    /** V�RIFICATION DU HASHCODE **/
    contenu = pBlock->contenuBloc.transactions[0];
    chaine = hacher(contenu, sizeof(CONTENU_BLOC)); // g�n�ration du hashCode � partir du contenu chiffr�
    if(chaine != NULL)
    {
        strcpy(hashCode, chaine);
        free(chaine); // lib�ration de l'emplacement ram allou� par le hachage
        if(strcmp(pBlock->hashCode, hashCode) == 0) // Si les hashCodes correspondent
            valide = 1;
        else // Si les hashCodes sont diff�rents
            valide = 0;
    }

    return (valide);
}
