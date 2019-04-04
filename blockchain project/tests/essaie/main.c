#include <stdio.h>
#include <myconio.h>
#include <string.h>
#include "..\blockChain\blockChain.h"

/** CONSTANTES **/
#define DIM 3

int main(void)
{
    /** VARIABLES **/
    int i, j, nb_blocs, valideChain;
    char *contenu = NULL;
    char *chaine = NULL;
    char *transactions[9] = {"Transaction 1","Transaction 2","Transaction 3","Transaction 4","Transaction 5","Transaction 6","Transaction 7","Transaction 8","Transaction 9"};
    BLOCK *bloc = NULL;
    BLOCK blocs[DIM];

    /** CRÉATION DE LA BLOCCHAIN **/
    i = 0; valideChain = 1; nb_blocs = DIM;
    while(i<=nb_blocs-1)
    {
        if(i == 0)
            bloc = creerBlock(transactions, 3, NULL, (i+1));
        else
            bloc = creerBlock(transactions, 3, blocs[i-1].hashCode, (i+1));
        /* COPIE DU BLOC */
        strcpy(blocs[i].hashCode, bloc->hashCode);
        contenu = blocs[i].contenuBloc.transactions[0];
        chaine = bloc->contenuBloc.transactions[0];
        for(j=0; j<=sizeof(CONTENU_BLOC)-1; j++)
            contenu[j] = chaine[j];
        free(bloc);
        i++;
    }
    /** VALIDATION DE LA BLOCKCHAIN **/
    valideChain = validerBlockChain(blocs, i);

    /** DÉCHIFFREMENT DU CONTENU DES BLOCS **/
    for(i=0; i<=nb_blocs-1; i++)
    {
        contenu = blocs[i].contenuBloc.transactions[0];
        chaine = dechiffrer(contenu, sizeof(CONTENU_BLOC)); // déchiffrement du contenu
        for(j=0; j<=sizeof(CONTENU_BLOC)-1; j++) // copie de chaque caractère déchiffré dans le contenu
            contenu[j] = chaine[j];
        free(chaine); // libération de l'emplacement ram alloué par le chiffrement
    }

    /** AFFICHAGE DES BLOCS **/
    for(i=0; i<=nb_blocs-1; i++)
    {
        textcolor(LIGHTRED); textbackground(WHITE); MYclrwin(1, 1+i*8, 30, 1+i*8);
        printf("\t    BLOC %s\n", blocs[i].contenuBloc.numBlocString);
        textcolor(WHITE); textbackground(LIGHTGRAY); MYclrwin(1, 2+i*8, 30, 7+i*8);
        printf("HASHCODE:\t%s\n", blocs[i].hashCode);
        printf("HASHCODEPREC:\t%s\n", blocs[i].contenuBloc.hashCodePrec);
        printf("TRANSACTIONS:\t%s\n", blocs[i].contenuBloc.transactions[0]);
        printf("\t\t%s\n", blocs[i].contenuBloc.transactions[1]);
        printf("\t\t%s\n", blocs[i].contenuBloc.transactions[2]);
        if(valideChain != 1 && valideChain == ((i+1)*-1))
            printf("STATUS:\t\tinvalide\n\n");
        else
            printf("STATUS:\t\tvalide\n\n");
    }

    getch();
    textattr(BLACK*16+LIGHTGRAY);
    return (0);
}
