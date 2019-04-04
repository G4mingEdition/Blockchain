#ifndef JSON_H_INCLUDED
#define JSON_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define RESULTAT_OK 0
#define RESULTAT_ERREUR 1
#define DOUBLONS 1
#define NB_MARQUES 45
#define MEMOIRE_INSUFFISANTE 0
#define TAILLE_MAX_200 200
#define TAILLE_MAX_1650 1650


#endif // JSON_H_INCLUDED

extern unsigned jsonPrimitive(char *chaineJson, char *nomAttribut, char *resultat, unsigned dim,char *messageErreur);
extern unsigned jsonArray(char *chaineJson, char *nomAttribut, char resultats[][TAILLE_MAX_1650], unsigned *nbElements, char *messageErreur);
extern unsigned jsonArrayFile(char *nomFichierIn, char *nomAttribut, char *nomFichierOut, char *messageErreur);
