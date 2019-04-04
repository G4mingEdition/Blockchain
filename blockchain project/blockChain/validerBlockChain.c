#include "blockChain.h"

/** VALIDATION DE LA BLOCKCHAIN **/
int validerBlockChain(BLOCK blocks[], int nbBlocks)
{
    /** VARIABLES **/
    int valide, check_alloc, i, j, numBloc;
    BLOCK *block = NULL;
    char *contenu = NULL;
    char *chaine = NULL;

    /** INITIALISATIONS **/
    i = 0; j = 0; valide = 1; check_alloc = 1;

    while (i < nbBlocks && valide ==  1 && check_alloc == 1) // Boucle qui passe dans la chaine + sortie lorsque block invalide
    {
        if((block = (BLOCK *) malloc(sizeof(BLOCK))))
        {
            strcpy(block->hashCode, blocks[i].hashCode);
            chaine = dechiffrer(blocks[i].contenuBloc.transactions[0], sizeof(CONTENU_BLOC));
            contenu = block->contenuBloc.transactions[0];
            for(j=0; j<=sizeof(CONTENU_BLOC)-1; j++)
                contenu[j] = chaine[j];

            /* V�RIFICATION DU PREMIER BLOC */
            if (i == 0)
            {
                if (block->contenuBloc.hashCodePrec[0] == '\0') // v�rification du hashcode pr�c�dent
                {
                    numBloc = atoi(block->contenuBloc.numBlocString); // transformation du num�ro du bloc en entier
                    if (numBloc == (i+1)) // v�rification du num�ro du bloc
                    {
                        if (validerBlock(&blocks[0]) == 1) // v�rification de la validit� du bloc
                            valide = 1;
                        else
                            valide = -1;
                    }
                    else
                        valide = -1;
                }
                else
                    valide = -1;
            }
            /* V�RIFICATION DES AUTRES BLOCS */
            else
            {
                if (strcmp(block->contenuBloc.hashCodePrec, blocks[i-1].hashCode) == 0 )  // v�rification du hashcode pr�c�dent
                {
                    numBloc = atoi(block->contenuBloc.numBlocString); // transformation du num�ro du bloc en entier
                    if (numBloc == (i+1)) // v�rification du num�ro du bloc
                    {
                        if (validerBlock(&blocks[i]) == 1) // v�rification de la validit� du bloc
                            valide = 1;
                        else
                            valide = -(i+1);
                    }
                    else
                        valide = -(i+1);
                }
                else
                    valide = -(i+1);
            }

            free(block);
        }
        else
        {
            check_alloc = 0;
            printf("Memoire insuffisante.\n");
        }
        i++;
    }
    return (valide);
}
