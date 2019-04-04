#include "blockChain.h"

/** CRÉATION D'UN BLOC **/
BLOCK* creerBlock(char* transactions[], int nbTransactions, char *pHashCodePrec, int numBloc)
{
    /** VARIABLES **/
    BLOCK *bloc = NULL;
    int i, n_transaction;
    char *hashCode = NULL;
    char *contenu = NULL;
    char *chaine = NULL;

    /** INITIALISATIONS **/
    i = 0; n_transaction = 0;

    if((bloc = (BLOCK *) malloc(sizeof(BLOCK))))
    {
        /** CRÉATION DU BLOC **/
        while(i<=nbTransactions-1) // copie des transactions dans le bloc
        {
            strcpy( bloc->contenuBloc.transactions[n_transaction], transactions[i] );
            n_transaction++;
            i++;
        }
        sprintf(bloc->contenuBloc.numBlocString, "%d", numBloc); // numéro du bloc
        if(numBloc>1) // hashCode du bloc précédent
            strcpy(bloc->contenuBloc.hashCodePrec, pHashCodePrec);
        else // cas particulier, le bloc 1 n'a pas de hashCodePrec
            bloc->contenuBloc.hashCodePrec[0] = '\0';

        /** CHIFFREMENT DU CONTENU **/
        contenu = bloc->contenuBloc.transactions[0]; // le pointeur pointe sur le début du contenu du bloc
        chaine = chiffrer(contenu, sizeof(CONTENU_BLOC)); // chiffrement du contenu
        for(i=0; i<=sizeof(CONTENU_BLOC)-1; i++) // copie de chaque caractère chiffré dans le contenu
            contenu[i] = chaine[i];
        free(chaine); // libération de l'emplacement ram alloué par le chiffrement

        /** GÉNÉRATION DU HASHCODE **/
        hashCode = hacher(contenu, sizeof(CONTENU_BLOC)); // génération du hashCode à partir du contenu du bloc
        if(hashCode != NULL)
        {
            strcpy(bloc->hashCode, hashCode);
            free(hashCode); // libération de l'emplacement ram alloué par le hachage
        }
    }
    else
        printf("Memoire insuffisante.\n");

    return (bloc);
}
