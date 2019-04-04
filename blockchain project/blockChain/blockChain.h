#ifndef BLOCKCHAIN_H_INCLUDED
#define BLOCKCHAIN_H_INCLUDED

/** ========== LIBRAIRIES ========== **/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include "..\librairieChiffrement\chiffrement.h"

#define NB_TRANSACTIONS 3
#define TAILLE_TRANSACTION 1024
#define TAILLE_HASH_CODE 11

typedef struct
{
    char transactions[NB_TRANSACTIONS][TAILLE_TRANSACTION];
    char hashCodePrec[TAILLE_HASH_CODE];
    char numBlocString[12];
} CONTENU_BLOC;

typedef struct
{
    char hashCode[TAILLE_HASH_CODE];
    CONTENU_BLOC contenuBloc;
} BLOCK;

/** ========== PROTOTYPES ========== **/
extern  BLOCK* creerBlock( char* transactions[], int nbTransactions, char *pHashCodePrec, int numBloc);
extern int validerBlock(BLOCK *pBlock);
extern int validerBlockChain(BLOCK blocks[], int nbBlocks);

#endif // BLOCKCHAIN_H_INCLUDED
