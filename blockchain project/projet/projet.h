#ifndef PROJET_H_INCLUDED
#define PROJET_H_INCLUDED

/** ========== LIBRAIRIES ========== **/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "..\blockChain\blockChain.h"
#include "..\librairieChiffrement\chiffrement.h"
#include "..\conioplus\conioplus.h"
#include "..\JSON_librairie\json.h"

/** ========== CONSTANTES ========== **/
#define VIDER_CT while(kbhit()) getch()
#define TAILLE_UTILISATEUR 31
#define TAILLE_DATE 11
#define ALLCHARACTERS 0
#define ONLYLETTERS 1
#define NOLETTERS 2

/** ========== FONCTIONS ========== **/
int interface(int emplacement);
char *creerTransaction(char *donneur, char *beneficiaire, int montant, char *date);
int checkDate(int jj, int mm, int aa);
void saisirChaine(char *chaine, int taille_chaine, int x, int y, int whichChar, int font_color, int text_color);
char *formatjson(char *donneur, char *beneficiaire, int montant, int solde_donneur, int solde_beneficiaire, char *date);
void rechercheSoldeUtilisateur(int *found_utilisateur, int *solde_utilisateur, char *utilisateur);
void affichRecent();
void affichComplet();
void affichPeriode(char *dateDebut, char *dateFin);

#endif // PROJET_H_INCLUDED
