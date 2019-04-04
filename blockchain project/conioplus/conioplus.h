#ifndef CONIO
#define CONIO
#include <conio.h>

void clreol(void);
void clrscr(void);
void delline(void);
void textattr(int _attr);
void textbackground(int _color);
void textcolor(int _color);
int wherex(void);
int wherey(void);
void MYclrwin(int left, int top, int right, int bottom);
void gotoxy(int x, int y);

enum COLORS { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
              DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
              LIGHTMAGENTA, YELLOW, WHITE } ;
#endif

