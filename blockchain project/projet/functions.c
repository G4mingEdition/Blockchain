#include "projet.h"

/** ========== VARIABLES GLOBALES ========== **/
extern BLOCK *tabBlocks;
extern char *transactions[NB_TRANSACTIONS];
extern int nb_blocks, nb_transactions;
extern int last_jj, last_mm, last_aa;

char *creerTransaction(char *donneur, char *beneficiaire, int montant, char *date)
{
    /** VARIABLES **/
    char *transaction = NULL;
    int found_donneur, found_beneficiaire, solde_donneur, solde_beneficiaire;
    int jj, mm, aa;
    int tot_date, tot_last_date;

    /** INITIALISATIONS **/
    found_donneur = 1; found_beneficiaire = 0; solde_donneur = 9999999; solde_beneficiaire = 0;
    jj = 0; mm = 0; aa = 0; tot_date = 0; tot_last_date = 0;

    /** CALCUL DES DATES **/
    sscanf(date, "%d/%d/%d", &jj, &mm, &aa);
    tot_date = (jj + (mm * 100) + (aa * 10000));
    tot_last_date = (last_jj + (last_mm * 100) + (last_aa * 10000));

    if(montant > 0 && strcmp(donneur, beneficiaire) != 0 && checkDate(jj, mm, aa) == 1 && tot_date >= tot_last_date)
    {
        rechercheSoldeUtilisateur(&found_donneur, &solde_donneur, donneur);
        rechercheSoldeUtilisateur(&found_beneficiaire, &solde_beneficiaire, beneficiaire);

        if(found_donneur == 1 || strcmp(donneur, "Banque") == 0)
        {
            if(solde_donneur >= montant || strcmp(donneur, "Banque") == 0)
            {
                transaction = formatjson(donneur, beneficiaire, montant, solde_donneur, solde_beneficiaire, date);
                last_jj = jj;
                last_mm = mm;
                last_aa = aa;
            }
            else
            {
                textattr(DARKGRAY*16+YELLOW);
                gotoxy(1,4); printf("Solde du donneur insuffisant.");
            }
        }
        else
        {
            textattr(DARKGRAY*16+YELLOW);
            gotoxy(1,4); printf("Donneur introuvable.");
        }
    }
    else if(montant <= 0)
    {
        textattr(DARKGRAY*16+RED);
        gotoxy(1,4); printf("ERREUR: Montant invalide.");
    }
    else if (strcmp(donneur, beneficiaire) == 0)
    {
        textattr(DARKGRAY*16+RED);
        gotoxy(1,4); printf("ERREUR: Utilisateurs identiques.");
    }
    else
    {
        textattr(DARKGRAY*16+RED);
        gotoxy(1,4); printf("ERREUR: Date invalide.");
    }

    return(transaction);
}

int checkDate(int jj, int mm, int aa)
{
    /** VARIABLES **/
    int isValid;

    /** INITIALISATIONS **/
    isValid = 1;

    if(jj!=0 && mm!=0 && aa!=0)
    {
        if(mm==2)
        {
            if(aa%4==0 && aa%100!=0)
            {
                if(jj<1 || jj>29)
                    isValid = 0;
            }
            else if(aa%400==0)
            {
                if(jj<1 || jj>29)
                    isValid = 0;
            }
            else if(jj<1 || jj>28)
                isValid = 0;
        }
        else if(mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)
        {
            if(jj<1 || jj>31)
                isValid = 0;
        }
        else if(mm==4 || mm==6 || mm==9 || mm==11)
        {
            if(jj<1 || jj>30)
                isValid = 0;
        }
        else
            isValid=0;
    }
    else
        isValid=0;

    return(isValid);
}

void saisirChaine(char *chaine, int taille_chaine, int x, int y, int whichChar, int font_color, int text_color)
{
    /** VARIABLES **/
    int i, size_color;

    taille_chaine--;
    size_color = taille_chaine-1;
    if(taille_chaine>=1 && x>=1 && y>=1)
    {
        textbackground(font_color); textcolor(text_color);
        gotoxy(x, y);
        for (i=0; chaine[i-1]!=13; i++) // chaine entry
        {
            VIDER_CT;
            if(i<=taille_chaine-1)
            {
                chaine[i] = getche();
                if(i == 0)
                    MYclrwin(x+1, y, x+size_color, y);
                if(chaine[i] == 8 && i>1) // deleting a character
                {
                    i-=1;
                    MYclrwin(x+i, y, x+size_color, y);
                    i-=1;
                }
                else if(chaine[i] == 8 && i == 1) // deleting a character
                {
                    i-=1;
                    MYclrwin(x+i, y, x+size_color, y);
                    i-=1;
                }
                else if(chaine[i] == 8 && i <= 0) // deleting a character
                {
                    MYclrwin(x+i, y, x+size_color, y);
                    i-=1;
                }
                else if(chaine[0] == 13) // impossible de saisir une chaine "vide"
                {
                    chaine[0]='\0';
                    gotoxy(x,y);
                    i-=1;
                }
                else if(whichChar == ONLYLETTERS && !isalpha(chaine[i]) && chaine[i] != 13 && chaine[i] != 32)
                {
                    MYclrwin(x+i, y, x+size_color, y);
                    i-=1;
                }
                else if(whichChar == NOLETTERS && isalpha(chaine[i]))
                {
                    MYclrwin(x+i, y, x+size_color, y);
                    i-=1;
                }
            }
            else
            {
                chaine[taille_chaine]=getch();
                if(chaine[taille_chaine] == 8) // deleting a character
                {
                    i-=1;
                    MYclrwin(x+i, y, x+size_color, y);
                    i-=1;
                }
                else if(chaine[taille_chaine] != 13)
                    i = i-1;
            }
        }
        if(i < taille_chaine)
            chaine[i-1]='\0';
        else
            chaine[taille_chaine]='\0';
    }
    else if(x<1)
    {
        gotoxy(1,4); textattr(DARKGRAY*16+RED); printf("ERREUR: x<1");
    }
    else if(y<1)
    {
        gotoxy(1,4); textattr(DARKGRAY*16+RED); printf("ERREUR: y<1");
    }
    else if(taille_chaine<1)
    {
        gotoxy(1,4); textattr(DARKGRAY*16+RED); printf("ERREUR: taille_chaine<1");
    }
    else
    {
        gotoxy(1,4); textattr(DARKGRAY*16+RED); printf("ERREUR");
    }

    gotoxy(1, 1); textattr(BLACK*16+LIGHTGRAY);
}

char *formatjson(char *donneur, char *beneficiaire, int montant, int solde_donneur, int solde_beneficiaire, char *date)
{
    /** VARIABLES **/
    char *json = NULL;

    if((json = (char*) malloc(TAILLE_TRANSACTION)))
    {
        /** MODIFICATION DES SOLDES **/
        solde_donneur -= montant;
        solde_beneficiaire += montant;

        /** FORMATAGE JSON **/
        sprintf(json, "{ \"donneur\": \"%s\" , \"solde_donneur\" : \"%d\" , \"beneficiaire\" : \"%s\" , \"solde_beneficiaire\" : \"%d\" , \"montant\" : \"%d\" , \"date\" : \"%s\" }", donneur, solde_donneur, beneficiaire, solde_beneficiaire, montant, date);
    }
    else
    {
        textattr(DARKGRAY*16+RED);
        gotoxy(1,4); printf("ERREUR: M%cmoire insuffisante.", 130);
    }

    return(json);
}

void rechercheSoldeUtilisateur(int *found_utilisateur, int *solde_utilisateur, char *utilisateur)
{
    /** VARIABLES **/
    int i, j, solde;
    char *donneur = "donneur";
    char *beneficiaire = "beneficiaire";
    char *soldeDonneur = "solde_donneur";
    char *soldeBeneficiaire = "solde_beneficiaire";
    char resultat1[TAILLE_TRANSACTION];
    char resultat2[TAILLE_TRANSACTION];
    char messageErreur[100];
    char *contenu = NULL;
    char *chaine = NULL;

    /** INITIALISATION **/
    *found_utilisateur = 0; *solde_utilisateur = 0;
    i = 0; j = 0;

    /* RECHERCHE DANS LE TABLEAU DE TRANSACTIONS */
    if(transactions != NULL && nb_transactions > 0)
    {
        i = nb_transactions-1;
        while(i >= 0 && *found_utilisateur == 0)
        {
            /* RECUPÉRATION DU DONNEUR ET DU BÉNÉFICIAIRE DE LA TRANSACTION */
            jsonPrimitive(transactions[i], donneur, resultat1, TAILLE_TRANSACTION, messageErreur);
            jsonPrimitive(transactions[i], beneficiaire, resultat2, TAILLE_TRANSACTION, messageErreur);

            /* EST-CE QUE L'UTILISATEUR RECHERCHÉ EST LE DONNEUR ? */
            if(strcmp(utilisateur, resultat1) == 0)
            {
                *found_utilisateur = 1;
                jsonPrimitive(transactions[i], soldeDonneur, resultat1, TAILLE_TRANSACTION, messageErreur);
                sscanf(resultat1, "%d", &solde);
                *solde_utilisateur = solde;
            }
            /* EST-CE QUE L'UTILISATEUR RECHERCHÉ EST LE BÉNÉFICIAIRE ? */
            else if(strcmp(utilisateur, resultat2) == 0)
            {
                *found_utilisateur = 1;
                jsonPrimitive(transactions[i], soldeBeneficiaire, resultat2, TAILLE_TRANSACTION, messageErreur);
                sscanf(resultat2, "%d", &solde);
                *solde_utilisateur = solde;
            }
            i--;
        }
    }
    /* RECHERCHE DANS LA BLOCKCHAIN */
    if(tabBlocks != NULL && nb_blocks > 0 && *found_utilisateur == 0)
    {
        i = nb_blocks-1;
        /* PARCOURS DES BLOCS DE LA BLOCKCHAIN */
        while(i >= 0 &&  *found_utilisateur == 0)
        {
            j = NB_TRANSACTIONS-1;
            /* DÉCHIFFREMENT DE LA TRANSACTION */
            contenu = tabBlocks[i].contenuBloc.transactions[0]; // le pointeur pointe sur le début du contenu du bloc
            chaine = dechiffrer(contenu, sizeof(CONTENU_BLOC)); // déchiffrement du contenu
            /* PARCOURS DES TRANSACTIONS D'UN BLOC */
            while(j >= 0 && *found_utilisateur == 0)
            {
                /* RECUPÉRATION DU DONNEUR ET DU BÉNÉFICIAIRE DE LA TRANSACTION */
                jsonPrimitive(&chaine[TAILLE_TRANSACTION*j], donneur, resultat1, TAILLE_TRANSACTION, messageErreur);
                jsonPrimitive(&chaine[TAILLE_TRANSACTION*j], beneficiaire, resultat2, TAILLE_TRANSACTION, messageErreur);

                /* EST-CE QUE L'UTILISATEUR RECHERCHÉ EST LE DONNEUR ? */
                if(strcmp(utilisateur, resultat1) == 0)
                {
                    *found_utilisateur = 1;
                    jsonPrimitive(&chaine[TAILLE_TRANSACTION*j], soldeDonneur, resultat1, TAILLE_TRANSACTION, messageErreur);
                    sscanf(resultat1, "%d", &solde);
                    *solde_utilisateur = solde;
                }
                /* EST-CE QUE L'UTILISATEUR RECHERCHÉ EST LE BÉNÉFICIAIRE ? */
                else if(strcmp(utilisateur, resultat2) == 0)
                {
                    *found_utilisateur = 1;
                    jsonPrimitive(&chaine[TAILLE_TRANSACTION*j], soldeBeneficiaire, resultat2, TAILLE_TRANSACTION, messageErreur);
                    sscanf(resultat2, "%d", &solde);
                    *solde_utilisateur = solde;
                }
                j--;
            }
            free(chaine);
            i--;
        }
    }
}
