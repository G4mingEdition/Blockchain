#ifndef CHIFFREMENT_H_INCLUDED
#define CHIFFREMENT_H_INCLUDED

/** ========== LIBRAIRIES ========== **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/** ========== PROTOTYPES ========== **/
char* chiffrer(char *pChaine, int taille);
char* dechiffrer(char *pChaineChiffree, int taille);
char* hacher(char *pBytes, int taille);

#endif // CHIFFREMENT_H_INCLUDED
