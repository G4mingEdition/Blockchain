#include "testlib.h"
#include <myconio.h>

int main(void)
{
    /** VARIABLES **/
    unsigned int nb_mots;
    char chaine[100];
    char chaineChiffree[100];
    char chaineDechiffree[100];

    /** TEST HACHAGE **/
    printf("[HACHAGE] Nombre de mots: "); scanf("%u", &nb_mots);
    clrscr();
    test_hachage(nb_mots);

    printf("\n\nappuyez sur une touche...");
    while(kbhit()) getch();
    getch();
    clrscr();

    /** TEST (DE)CHIFFREMENT **/
    printf("[CHIFFREMENT] Entrez une chaine: "); fflush(stdin); scanf("%100[^\n]s", chaine);
    clrscr();
    strcpy(chaineChiffree, chiffrer(chaine,strlen(chaine)));
    printf("[CHIFFREMENT] %s\n", chaineChiffree);
    strcpy(chaineDechiffree, chiffrer(chaineChiffree,strlen(chaineChiffree)));
    printf("[DECHIFFREMENT] %s\n", chaineDechiffree);
    return (0);
}
