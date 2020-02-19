#ifndef _GRAPH_
#define _GRAPH_

#include <stdio.h>
#include "conio.h"
#define BLACK_PAIR 0
#define RED_PAIR 12

int print (const char *format, ...);
void init_screen(void);

void text_background(int color);
void color(int color);
void hgotoxy(int x,int y);
#endif