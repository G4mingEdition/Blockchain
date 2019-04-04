#include "projet.h"

/*  130 = é
    133 = à
    138 = è
    135 = ç
    136 = ê  */

/** ========== VARIABLES GLOBALES ========== **/
BLOCK *tabBlocks = NULL;
char *transactions[NB_TRANSACTIONS];
int nb_blocks = 0, nb_transactions = 0;
int last_jj = 0, last_mm = 0, last_aa = 0;

int main(void)
{
    /** VARIABLES **/
    char utilisateur[TAILLE_UTILISATEUR];
    char donneur[TAILLE_UTILISATEUR];
    char beneficiaire[TAILLE_UTILISATEUR];
    char date[TAILLE_DATE];
    char dateDebut[TAILLE_DATE];
    char dateFin[TAILLE_DATE];
    int choix, emplacement, montant, found_utilisateur, solde_utilisateur;
    int touche, isValid;

    /** INITIALISATIONS **/
    choix = 1; emplacement = 0; touche = 0; isValid = 0;
    found_utilisateur = 0; solde_utilisateur = 0;

    system("mode con LINES=25 COLS=80"); // modification de la taille de la console
    /* MENI D'INTRODUCTION */
    textbackground(LIGHTGRAY); MYclrwin(1,1,80,25);
    textbackground(RED); MYclrwin(28,10,51,15);
    textcolor(YELLOW); gotoxy(30,11); printf("B L O C K  C H A I N");
    textcolor(WHITE); gotoxy(31,13); printf("denis christopher");
    textcolor(WHITE); gotoxy(34,14); printf("pr%cvot sean", 130);
    textbackground(DARKGRAY); MYclrwin(28,16,51,16);
    do
    {
        textcolor(WHITE); gotoxy(30,16); printf("appuyez sur <enter>");
        VIDER_CT; gotoxy(80,25); touche = getch();
    }while(touche != 13);

    do
    {
        choix = interface(emplacement); emplacement = (choix/10)-1;
        gotoxy(3,6);
        switch (choix)
        {
            /** MENU FICHIER **/
            case 11:
                textbackground(DARKGRAY); MYclrwin(2,6,79,8);
                textcolor(YELLOW); gotoxy(3,6); printf("TRANSACTIONS");
                textcolor(WHITE); gotoxy(3,7); printf("Transactions effectu%ces: %d", 130, ((nb_blocks*3)+nb_transactions));
                textcolor(WHITE); gotoxy(3,8); printf("Transactions en cours: %d/3", nb_transactions);
                textbackground(DARKGRAY); MYclrwin(2,10,79,12);
                textcolor(YELLOW); gotoxy(3,10); printf("BLOCKCHAIN");
                textcolor(WHITE); gotoxy(3,11); printf("Blocs cr%c%cs: %d", 130, 130, nb_blocks);
                textcolor(WHITE); gotoxy(3,12); printf("Statut: ");
                gotoxy(11,12);
                if(tabBlocks != NULL)
                {
                    isValid = validerBlockChain(tabBlocks, nb_blocks);
                    if(isValid != 1)
                    {
                        isValid = isValid * (-1);
                        textcolor(RED); printf("Bloc %d corrompu.", isValid);
                    }
                    else
                    {
                        textcolor(LIGHTGREEN); printf("Valide.");
                    }
                }
                else
                {
                    textcolor(WHITE); printf("Veuillez cr%cer au moins un bloc (3 transactions).", 130);
                }
                VIDER_CT; getch();
                break;

            /** MENU HISTORIQUE **/
            case 21:
                affichRecent();
                VIDER_CT; getch();
                break;
            case 22:
                affichComplet();
                VIDER_CT; getch();
                break;
            case 23:
                textbackground(DARKGRAY); MYclrwin(2,7,79,17);
                textcolor(WHITE); gotoxy(3,8); printf("Date de d%cbut:", 130);
                textcolor(WHITE); gotoxy(3,11); printf("Date de fin:");
                textattr(WHITE*16+BLACK); MYclrwin(3,12,1+TAILLE_DATE,12); MYclrwin(3,12,1+TAILLE_DATE,12);
                textcolor(LIGHTGRAY); gotoxy(3,9); printf("jj/mm/aaaa");
                textcolor(LIGHTGRAY); gotoxy(3,12); printf("jj/mm/aaaa");
                /* SASIES */
                saisirChaine(dateDebut, TAILLE_DATE, 3, 9, NOLETTERS, WHITE, BLACK);
                saisirChaine(dateFin, TAILLE_DATE, 3, 12, NOLETTERS, WHITE, BLACK);

                textbackground(LIGHTGRAY); MYclrwin(1,5,80,25);
                textcolor(WHITE);
                affichPeriode(dateDebut, dateFin);
                VIDER_CT; getch();
                break;

            /** MENU TRANSACTION **/
            case 31:
                /* INTERFACE */
                textbackground(WHITE); MYclrwin(2,6,79,6);
                textcolor(BLACK); gotoxy(24,6);
                if(last_jj != 0 && last_mm != 0 && last_aa != 0)
                    printf("Derni%cre transaction: %d/%d/%d", 138, last_jj, last_mm, last_aa);
                else
                    printf("Derni%cre transaction: /", 138);
                textbackground(DARKGRAY); MYclrwin(2,7,79,17);
                textcolor(WHITE); gotoxy(3,8); printf("Nom du donneur: ");
                textcolor(WHITE); gotoxy(3,11); printf("Nom du b%cn%cficiaire: ", 130, 130);
                textcolor(WHITE); gotoxy(40,8); printf("Montant: ");
                textcolor(WHITE); gotoxy(40,11); printf("Date: ");
                textcolor(WHITE); gotoxy(3,15); printf("%ctat: ", 144);
                textattr(WHITE*16+BLACK); MYclrwin(3,9,1+TAILLE_UTILISATEUR,9); MYclrwin(3,12,1+TAILLE_UTILISATEUR,12); MYclrwin(40,9,46,9); MYclrwin(40,12,38+TAILLE_DATE,12); MYclrwin(3,16,24,16);
                textcolor(LIGHTGRAY); gotoxy(3,9); printf("Banque");
                textcolor(LIGHTGRAY); gotoxy(3,12); printf("HELHa");
                textcolor(LIGHTGRAY); gotoxy(40,9); printf("0");
                textcolor(LIGHTGRAY); gotoxy(40,12); printf("jj/mm/aaaa");
                /* SASIES */
                montant = 0;
                saisirChaine(donneur, TAILLE_UTILISATEUR, 3, 9, ONLYLETTERS, WHITE, BLACK);
                saisirChaine(beneficiaire, TAILLE_UTILISATEUR, 3, 12, ONLYLETTERS, WHITE, BLACK);
                textattr(WHITE*16+BLACK); gotoxy(40,9); fflush(stdin); scanf("%d", &montant);
                saisirChaine(date, TAILLE_DATE, 40, 12, NOLETTERS, WHITE, BLACK);
                /* TRAITEMENT */
                transactions[nb_transactions] = creerTransaction(donneur, beneficiaire, montant, date);
                gotoxy(3,16); textattr(WHITE*16+BLACK);
                if(transactions[nb_transactions] != NULL)
                {
                    textcolor(LIGHTGREEN);
                    printf("Transaction valid%ce.", 130);
                    nb_transactions++;
                    if(nb_transactions == 3)
                    {
                        /* CRÉATION ET AJOUT D'UN BLOC DANS LA BLOCKCHAIN */
                        nb_blocks++;
                        if(nb_blocks == 1)
                        {
                            if((tabBlocks = (BLOCK *) malloc(sizeof(BLOCK))))
                                tabBlocks[nb_blocks-1] = *creerBlock(transactions, nb_transactions, NULL, nb_blocks);
                            else
                            {
                                textattr(DARKGRAY*16+RED);
                                gotoxy(1,4); printf("ERREUR: M%cmoire insuffisante.", 130);
                            }
                        }
                        else
                        {
                            if((tabBlocks = (BLOCK *) realloc(tabBlocks, (sizeof(BLOCK)*nb_blocks))))
                                tabBlocks[nb_blocks-1] = *creerBlock(transactions, nb_transactions, tabBlocks[nb_blocks-2].hashCode, nb_blocks);
                            else
                            {
                                textattr(DARKGRAY*16+RED);
                                gotoxy(1,4); printf("ERREUR: M%cmoire insuffisante.", 130);
                            }
                        }
                        free(transactions[0]);
                        free(transactions[1]);
                        free(transactions[2]);
                        nb_transactions = 0;
                    }
                }
                else
                {
                    textcolor(RED);
                    printf("Transaction invalide.");
                }
                VIDER_CT; getch();
                break;

            /** MENU UTILISATEUR **/
            case 41:
                textbackground(DARKGRAY); MYclrwin(2,6,79,12);
                textcolor(WHITE); gotoxy(3,7); printf("Nom d'utilisateur: ");
                textcolor(WHITE); gotoxy(3,10); printf("Solde: ");
                textattr(WHITE*16+BLACK); MYclrwin(3,8,1+TAILLE_UTILISATEUR,8); MYclrwin(3,11,14,11);
                textcolor(LIGHTGRAY); gotoxy(3,8); printf("Banque");
                saisirChaine(utilisateur, TAILLE_UTILISATEUR, 3, 8, ONLYLETTERS, WHITE, BLACK);
                rechercheSoldeUtilisateur(&found_utilisateur, &solde_utilisateur, utilisateur);
                textattr(WHITE*16+BLACK); gotoxy(3,11);
                if(found_utilisateur == 1)
                    printf("%d", solde_utilisateur);
                else
                {
                    textcolor(RED); printf("Introuvable.");
                }
                VIDER_CT; getch();
                break;

            /** MENU AIDE **/
            case 51:
                /* NAVIGATION */
                textbackground(DARKGRAY); MYclrwin(2,6,79,10);
                textcolor(YELLOW); gotoxy(3,6); printf("NAVIGATION");
                textcolor(WHITE); gotoxy(3,7); printf("- F1 %c F5: permet d'acc%cder directement aux sous-menus.", 133, 130);
                gotoxy(3,8); printf("- Fl%cches directionnelles: permet de naviguer dans les menus.", 138);
                gotoxy(3,9); printf("- Enter: permet de valider un menu ou une action.");
                gotoxy(3,10); printf("- Escape: permet de quitter un menu ou le programme si hors sous-menus.");
                /* HISTORIQUE */
                textbackground(DARKGRAY); MYclrwin(2,12,79,16);
                textcolor(YELLOW); gotoxy(3,12); printf("HISTORIQUE");
                textcolor(WHITE); gotoxy(3,13); printf("- R%ccent: affiche les 5 derni%cres transactions.", 130, 138);
                gotoxy(3,14); printf("- Complet: affiche toutes les transactions.");
                gotoxy(3,15); printf("- P%criode: affiche toutes les transactions sur une p%criode d%ctermin%ce.", 130, 130, 130, 130);
                gotoxy(3,16); printf("- Format d'une date valide: jj/mm/aaaa.");
                /* TRANSACTION */
                textbackground(DARKGRAY); MYclrwin(2,18,79,23);
                textcolor(YELLOW); gotoxy(3,18); printf("TRANSACTION");
                textcolor(WHITE); gotoxy(3,19); printf("- Impossible d'enregistrer une transaction dont la date est ant%crieur %c la", 130, 133);
                gotoxy(5,20); printf("date de la derni%cre transaction.", 138);
                gotoxy(3,21); printf("- Si un utilisateur n'existe pas, il est cr%c%c et son solde est %c 0.", 130, 130, 133);
                gotoxy(3,22); printf("- Le montant ne peut d%cpasser le solde du donneur (sauf Banque).", 130);
                gotoxy(3,23); printf("- Format d'une date valide: jj/mm/aaaa.");
                VIDER_CT; getch();
                break;
        }
        gotoxy(80,25);
    }while(choix != 6);
    return (0);
}
