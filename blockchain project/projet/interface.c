#include "projet.h"

#define GRISCLAIR_SUR_NOIR textattr((BLACK*16)+LIGHTGRAY)
#define BLANC_SUR_GRISCLAIR textattr((LIGHTGRAY*16)+WHITE)
#define COLLEFT  1
#define LINTOP   1

#define FALSE 0
#define TRUE 1

#define ENTER     1000
#define EXIT      2000
#define KEY_F1    1200
#define KEY_F2    1201
#define KEY_F3    1202
#define KEY_F4    1203
#define KEY_F5    1204
#define KEY_F6    1205
#define KEY_F7    1206
#define KEY_F8    1207
#define KEY_F9    1208
#define KEY_F10   1209
#define KEY_F11   1210
#define KEY_F12   1211

#define KEY_FLD   1100
#define KEY_FLG   1101
#define KEY_FLH   1102
#define KEY_FLB   1103

#define HORIZONTAL 1
#define VERTICAL   2

/* ================================  PROTOTYPES ==============================================*/
struct item
{
    char *libel;            // Item
    int li;                 // No ligne
    int co;                 // No colonne
    struct item *sousmenu;  // Pointeur vers sous-menu
    int exit;               // Quitter: VRAI ou FAUX
};

int affichmenu(struct item *menu, struct item *pcour, int direction, int bg);
unsigned int getMyKeys(void);

int interface(int emplacement)
{
  struct item menu1_1[]={{"   Verifier  ",LINTOP+4,COLLEFT,NULL,FALSE},
                        {"",LINTOP+5,COLLEFT,NULL,TRUE},
                        {"",0,0,NULL,FALSE}};

  struct item menu1_2[]={{" Recent      ",LINTOP+4,COLLEFT+13,NULL,FALSE},
                        {" Complet     ",LINTOP+5,COLLEFT+13,NULL,FALSE},
                        {" Periode     ",LINTOP+6,COLLEFT+13,NULL,FALSE},
                        {"",LINTOP+7,COLLEFT+16,NULL,TRUE},
                        {"",0,0,NULL,FALSE}};

  struct item menu1_3[]={{" Ajouter     ",LINTOP+4,COLLEFT+26,NULL,FALSE},
                        {"",LINTOP+5,COLLEFT+26,NULL,TRUE},
                        {"",0,0,NULL,FALSE}};

  struct item menu1_4[]={{" Solde       ",LINTOP+4,COLLEFT+39,NULL,FALSE},
                        {"",LINTOP+5,COLLEFT+39,NULL,TRUE},
                        {"",0,0,NULL,FALSE}};

  struct item menu1_5[]={{"    A propos ",LINTOP+4,COLLEFT+52,NULL,FALSE},
                        {"",LINTOP+5,COLLEFT+39,NULL,TRUE},
                        {"",0,0,NULL,FALSE}};

  struct item menu1[]={{"Fichier",LINTOP+1,COLLEFT+3,&menu1_1[0],FALSE},
                       {"Historique",LINTOP+1,COLLEFT+14,&menu1_2[0],FALSE},
                       {"Transaction",LINTOP+1,COLLEFT+27,&menu1_3[0],FALSE},
                       {"Utilisateur",LINTOP+1,COLLEFT+40,&menu1_4[0],FALSE},
                       {"Aide",LINTOP+1,COLLEFT+56,&menu1_5[0],FALSE},
                       {"Quitter",LINTOP+1,COLLEFT+70,NULL,FALSE},
                       {"",0,0,NULL,FALSE}};

   struct item *ptr1=NULL, *ptr2=NULL;
  int cur_item1, cur_item2, indic1, indic2, sortie, retour;

       ptr1=&menu1[emplacement];
       textbackground(RED); MYclrwin(1,1,80,3);
       textbackground(DARKGRAY); MYclrwin(1,4,80,4);
       textbackground(LIGHTGRAY); MYclrwin(1,5,80,25);

     // Affichage du menu principal
     cur_item1=affichmenu(menu1,ptr1,HORIZONTAL,RED);
     indic1=cur_item1+1;
     ptr1=menu1+cur_item1;

    if ((ptr1->exit)==FALSE)
    {
        if((ptr1->sousmenu)!=NULL)
        {
            ptr2=ptr1->sousmenu;
            sortie = 0;
            do
            {
                // Affichage du sous menu
                cur_item2=affichmenu(ptr1->sousmenu,ptr2,VERTICAL,DARKGRAY);
                indic2=(indic1*10)+(cur_item2+1);
                ptr2=(ptr1->sousmenu)+cur_item2;
                retour = indic2;

                if((ptr2->exit)==FALSE) { textbackground(LIGHTGRAY); MYclrwin(1,5,80,25); }
                sortie = 1;
            } while (sortie == 0);
        }
        else
        {
            retour = 6;
        }
    }

    BLANC_SUR_GRISCLAIR;
    return(retour);
}

int affichmenu(struct item *menu, struct item *pcour, int direction, int bg)
{
  int keycode, i, cur_item, nb_item;

     textbackground(bg); textcolor(WHITE);
     for (i=0;menu[i].li!='\0';i++) { gotoxy(menu[i].co,menu[i].li); printf("%s",menu[i].libel); }
     nb_item=i;

     cur_item=pcour-menu;
     textcolor(YELLOW);
     gotoxy(menu[cur_item].co,menu[cur_item].li); printf("%s",menu[cur_item].libel);
     gotoxy(80,25);

     do
     {
       keycode=getMyKeys();
       if (keycode!=ENTER || keycode!=EXIT)
       {
         switch(keycode)
         {
            case KEY_F1  :  if (nb_item>=2) { pcour=menu;   keycode=ENTER; } break;
            case KEY_F2  :  if (nb_item>=3) { pcour=menu+1; keycode=ENTER; } break;
            case KEY_F3  :  if (nb_item>=4) { pcour=menu+2; keycode=ENTER; } break;
            case KEY_F4  :  if (nb_item>=5) { pcour=menu+3; keycode=ENTER; } break;
            case KEY_F5  :  if (nb_item>=6) { pcour=menu+4; keycode=ENTER; } break;
            case KEY_F6  :  if (nb_item>=7) { pcour=menu+5; keycode=ENTER; } break;
            case KEY_F7  :  if (nb_item>=8) { pcour=menu+6; keycode=ENTER; } break;
            case KEY_F8  :  if (nb_item>=9) { pcour=menu+7; keycode=ENTER; } break;
            case KEY_F9  :  if (nb_item>=10) { pcour=menu+8; keycode=ENTER; } break;
            case KEY_F10 :  if (nb_item>=11) { pcour=menu+9; keycode=ENTER; } break;
            case KEY_F11 :  if (nb_item>=12) { pcour=menu+10; keycode=ENTER; } break;
            case KEY_F12 :  pcour=menu+(nb_item-1); keycode=ENTER; break;

            case KEY_FLD :  if(direction==HORIZONTAL)
                                if ((pcour+1)<(menu+nb_item)) pcour++;
                            break;

            case KEY_FLG :  if(direction==HORIZONTAL)
                                if (pcour>menu)  pcour--;
                            break;

            case KEY_FLB :  if(direction==VERTICAL)
                                if ((pcour+1)<(menu+nb_item-1)) pcour++;
                            break;


            case KEY_FLH :  if(direction==VERTICAL)
                                if (pcour>menu)  pcour--; break;

            default      :  break;
         }
         cur_item=pcour-menu;

         // Affichage du menu
         textcolor(WHITE);
         for (i=0;menu[i].li!='\0';i++) { gotoxy(menu[i].co,menu[i].li); printf("%s",menu[i].libel); }
         textcolor(YELLOW);
         gotoxy(menu[cur_item].co,menu[cur_item].li); printf("%s",menu[cur_item].libel);
         gotoxy(80,25);
       }
      } while(keycode!=ENTER);

      return(cur_item);
}

unsigned int getMyKeys(void)
{
 #define F1  59
 #define F2  60
 #define F3  61
 #define F4  62
 #define F5  63
 #define F6  64
 #define F7  65
 #define F8  66
 #define F9  67
 #define F10 68
 #define F11 133
 #define F12 134
 #define ESC 27

 #define CURS_RIGHT 77
 #define CURS_LEFT 75
 #define CURS_TOP 72
 #define CURS_BOTTOM 80

    unsigned char car;
    unsigned int retour, boucle;

        do
        {
            while(kbhit()) getch();
            boucle=0;
            if((car=getch())==224)
            {
                car=getch();
                switch(car)
                {
                    case CURS_RIGHT : retour=1100; break;
                    case CURS_LEFT  : retour=1101; break;
                    case CURS_TOP   : retour=1102; break;
                    case CURS_BOTTOM: retour=1103; break;
                    case F11        : retour=1210; break;
                    case F12        : retour=1211; break;
                    default         : boucle=1;
                }
            }
            else if (car == 0)
            {
                  car=getch();
                  switch(car)
                  {
                    case F1 : retour=1200; break;
                    case F2 : retour=1201; break;
                    case F3 : retour=1202; break;
                    case F4 : retour=1203; break;
                    case F5 : retour=1204; break;
                    case F6 : retour=1205; break;
                    case F7 : retour=1206; break;
                    case F8 : retour=1207; break;
                    case F9 : retour=1208; break;
                    case F10: retour=1209; break;
                    default: boucle=1;
                  }
            }
            else if(car==ESC)
            {
                retour=1211;
                boucle=0;
            }
            else if(car=='\r') retour=1000;
                     else          boucle=1;
        } while (boucle);

        return(retour);
}
