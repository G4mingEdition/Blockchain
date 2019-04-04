#include "projet.h"

/** ========== VARIABLES GLOBALES ========== **/
extern BLOCK *tabBlocks;
extern char *transactions[NB_TRANSACTIONS];
extern int nb_blocks, nb_transactions;
extern int last_jj, last_mm, last_aa;

void affichRecent()
{
    /** VARIABLES **/
    int i, j, y;
    char *contenu = NULL;
    char *chaine = NULL;

    /** INITIALISATION **/
    i = 0; j = 0; y = 0;

    if(nb_transactions > 0 || nb_blocks > 0)
    {
        /* AFFICHAGE DU TABLEAU DE TRANSACTIONS */
        if(nb_transactions > 0)
        {
            i = nb_transactions-1;
            while(i >= 0)
            {
                textbackground(DARKGRAY); MYclrwin(1, 6+(4*y), 80, 8+(4*y));
                gotoxy(1, 6+(4*y)); printf("%s", transactions[i]);
                i--;
                y++;
            }
        }
        /* AFFICHAGE DE LA BLOCKCHAIN */
        if(nb_blocks > 0)
        {
            i = nb_blocks-1;
            /* PARCOURS DES BLOCS DE LA BLOCKCHAIN */
            while(i >= 0 && y < 5)
            {
                j = NB_TRANSACTIONS-1;
                /* DÉCHIFFREMENT DE LA TRANSACTION */
                contenu = tabBlocks[i].contenuBloc.transactions[0]; // le pointeur pointe sur le début du contenu du bloc
                chaine = dechiffrer(contenu, sizeof(CONTENU_BLOC)); // déchiffrement du contenu
                /* PARCOURS DES TRANSACTIONS D'UN BLOC */
                while(j >= 0 && y < 5)
                {
                    textbackground(DARKGRAY); MYclrwin(1, 6+(4*y), 80, 8+(4*y));
                    gotoxy(3, 6+(4*y)); printf("%s", &chaine[TAILLE_TRANSACTION*j]);
                    j--;
                    y++;
                }
                free(chaine);
                i--;
            }
        }
    }
    else
    {
        textattr(DARKGRAY*16+RED);
        gotoxy(1,4); printf("ERREUR: Aucune transaction trouv%ce.", 130);
    }
}

void affichComplet()
{
    /** VARIABLES **/
    int i, j;
    char *contenu = NULL;
    char *chaine = NULL;
    BLOCK *block = NULL;

    /** INITIALISATION **/
    i = 0; j = 0;

    if(nb_blocks > 0)
    {
        if((block = (BLOCK *) malloc(sizeof(BLOCK))))
        {
            /* PARCOURS DES BLOCS DE LA BLOCKCHAIN */
            i = 0;
            while(i <= nb_blocks-1)
            {
                /* COPIE DU BLOCK */
                strcpy(block->hashCode, tabBlocks[i].hashCode);
                chaine = dechiffrer(tabBlocks[i].contenuBloc.transactions[0], sizeof(CONTENU_BLOC));
                contenu = block->contenuBloc.transactions[0];
                for(j=0; j<=sizeof(CONTENU_BLOC)-1; j++)
                    contenu[j] = chaine[j];
                free(chaine);

                textbackground(DARKGRAY); MYclrwin(1,7,80,22);
                gotoxy(1,7); printf("Num block : %s", block->contenuBloc.numBlocString);
                gotoxy(1,8); printf("Hash code : %s", block->hashCode);

                /* PARCOURS DES TRANSACTIONS D'UN BLOC */
                j = 0;
                gotoxy(1,11);
                while(j <= NB_TRANSACTIONS-1)
                {
                    printf("%s\n", block->contenuBloc.transactions[j]);
                    j++;
                }
                gotoxy(1,22);
                if(i == 0)
                    printf("Hash code block precedent : NULL\n");
                else
                    printf("Hash code block precedent : %s\n", block->contenuBloc.hashCodePrec);
                if(i <= nb_blocks-2)
                {
                    VIDER_CT; getch();
                    textbackground(DARKGRAY); MYclrwin(1,7,80,22);
                    VIDER_CT; getch();
                }
                i++;
            }
        }
        else
        {
            textattr(DARKGRAY*16+RED);
            gotoxy(1,4); printf("ERREUR: M%cmoire insuffisante.", 130);
        }
    }
    else
    {
        textattr(DARKGRAY*16+RED);
        gotoxy(1,4); printf("ERREUR: Aucune transaction trouv%ce.", 130);
    }
}


void affichPeriode(char *dateDebut, char *dateFin)
{
    /** VARIABLES **/
    int i, j, y;
    char **tab = NULL;
    char *contenu = NULL;
    char *chaine = NULL;
    char messageErreur[100];
    char dateCour[TAILLE_TRANSACTION];
    char periode_actuel[TAILLE_TRANSACTION];
    int tot_dateDebut, tot_dateFin, tot_dateCour;
    int jj, mm, aa;
    int tot_transactions_periode, tot_transactions_date;

    /** INITIALISATION **/
    i = 0; j = 0; y = 0;
    jj = 0; mm = 0; aa = 0;
    tot_dateDebut = 0; tot_dateFin = 0; tot_dateCour = 0;
    tot_transactions_periode = 0; tot_transactions_date = 0;

    if(nb_transactions > 0 || nb_blocks > 0)
    {
        /* CALCUL DES DATES */
        sscanf(dateDebut, "%d/%d/%d", &jj, &mm, &aa);
        tot_dateDebut = (jj + (mm * 100) + (aa * 10000));
        if(checkDate(jj, mm, aa) == 1)
        {
            sscanf(dateFin, "%d/%d/%d", &jj, &mm, &aa);
            tot_dateFin = (jj + (mm * 100) + (aa * 10000));
            if(checkDate(jj, mm, aa) == 1)
            {
                if(tot_dateDebut <= tot_dateFin)
                {
                    if((tab = (char **) malloc((tot_transactions_periode+1) * sizeof(char *))))
                    {
                        /* RÉCUPÉRATION DES TRANSACTIONS DE LA BLOCKCHAIN */
                        if(nb_blocks > 0)
                        {
                            i = 0;
                            /* PARCOURS DES BLOCS DE LA BLOCKCHAIN */
                            while(i <= nb_blocks-1)
                            {
                                j = 0;
                                /* DÉCHIFFREMENT DES TRANSACTIONS */
                                contenu = tabBlocks[i].contenuBloc.transactions[0]; // le pointeur pointe sur le début du contenu du bloc
                                chaine = dechiffrer(contenu, sizeof(CONTENU_BLOC)); // déchiffrement du contenu
                                /* PARCOURS DES TRANSACTIONS D'UN BLOC */
                                while(j <= NB_TRANSACTIONS-1)
                                {
                                    /* CALCUL DE LA DATE DE LA TRANSACTION */
                                    jsonPrimitive(&chaine[TAILLE_TRANSACTION*j], "date", dateCour, TAILLE_TRANSACTION, messageErreur);
                                    sscanf(dateCour, "%d/%d/%d", &jj, &mm, &aa);
                                    tot_dateCour = (jj + (mm * 100) + (aa * 10000));

                                    if(tot_dateCour >= tot_dateDebut && tot_dateCour <= tot_dateFin)
                                    {
                                        if((tab = (char **) realloc(tab, (tot_transactions_periode+1) * sizeof(char *))))
                                        {
                                            tab[tot_transactions_periode] = &chaine[TAILLE_TRANSACTION*j];
                                            tot_transactions_periode++;
                                        }
                                        else
                                        {
                                            textattr(DARKGRAY*16+RED);
                                            gotoxy(1,4); printf("ERREUR: M%cmoire insuffisante.", 130);
                                        }
                                    }
                                    j++;
                                }
                                i++;
                            }
                        }

                        /* RÉCUPÉRATION DES TRANSACTIONS DU TABLEAU DE TRANSACTIONS */
                        if(nb_transactions > 0)
                        {
                            i = 0;
                            while(i <= nb_transactions-1)
                            {
                                /* CALCUL DE LA DATE DE LA TRANSACTION */
                                jsonPrimitive(transactions[i], "date", dateCour, TAILLE_TRANSACTION, messageErreur);
                                sscanf(dateCour, "%d/%d/%d", &jj, &mm, &aa);
                                tot_dateCour = (jj + (mm * 100) + (aa * 10000));

                                if(tot_dateCour >= tot_dateDebut && tot_dateCour <= tot_dateFin)
                                {
                                    if((tab = (char **) realloc(tab, (tot_transactions_periode+1) * sizeof(char *))))
                                    {
                                        tab[tot_transactions_periode] = transactions[i];
                                        tot_transactions_periode++;
                                    }
                                    else
                                    {
                                        textattr(DARKGRAY*16+RED);
                                        gotoxy(1,4); printf("ERREUR: M%cmoire insuffisante.", 130);
                                    }
                                }
                                i++;
                            }
                        }
                    }
                    else
                    {
                        textattr(DARKGRAY*16+RED);
                        gotoxy(1,4); printf("ERREUR: M%cmoire insuffisante.", 130);
                    }

                    /* SI IL N'Y A PAS DE TRANSACTIONS */
                    if(tot_transactions_periode == 0)
                    {
                        textattr(DARKGRAY*16+YELLOW);
                        gotoxy(1,4); printf("P%criode introuvable.", 130);
                    }
                    else
                    {
                        /**SYSTEME DE RUPTURE**/

                        i = 0;
                        while(i<tot_transactions_periode)
                        {
                            jsonPrimitive(tab[i], "date", dateCour, TAILLE_TRANSACTION, messageErreur);
                            jsonPrimitive(tab[i], "date", periode_actuel, TAILLE_TRANSACTION, messageErreur);
                            tot_transactions_date = 0;
                            y = 0;
                            while(i<tot_transactions_periode && strcmp(dateCour,periode_actuel) == 0)
                            {
                                    textbackground(DARKGRAY); MYclrwin(1, 8+(4*y), 80, 10+(4*y));
                                    gotoxy(1, 8+(4*y)); printf("%s\n",tab[i]);
                                    tot_transactions_date++;
                                    i++;
                                    y++;
                                    if(i<tot_transactions_periode)
                                        jsonPrimitive(tab[i], "date", periode_actuel, TAILLE_TRANSACTION, messageErreur);
                            }
                            gotoxy(1, 6); MYclrwin(1, 6, 80, 6); printf("Nombre de transactions : %d", tot_transactions_date);
                            if(i<=tot_transactions_periode)
                            {
                                VIDER_CT; getch();
                                textbackground(LIGHTGRAY); MYclrwin(1,5,80,25);
                                VIDER_CT; getch();
                            }
                        }
                        if(i == tot_transactions_periode)
                        {
                            gotoxy(1, 6); textbackground(DARKGRAY); MYclrwin(1, 6, 80, 6); printf("Total transactions : %d", tot_transactions_periode);
                            VIDER_CT; getch();
                        }
                        free(tab);
                    }
                }
                else
                {
                    textattr(DARKGRAY*16+RED);
                    gotoxy(1,4); printf("ERREUR: P%criode invalide.", 130);
                }
            }
            else
            {
                textattr(DARKGRAY*16+RED);
                gotoxy(1,4); printf("ERREUR: Date de fin invalide.");
            }
        }
        else
        {
            textattr(DARKGRAY*16+RED);
            gotoxy(1,4); printf("ERREUR: Date de d%cbut invalide.", 130);
        }
    }
    else
    {
        textattr(DARKGRAY*16+YELLOW);
        gotoxy(1,4); printf("Aucune transaction trouv%ce.", 130);
    }
}
