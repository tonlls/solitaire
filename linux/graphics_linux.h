#ifndef _GRAPH_H_
#define _GRAPH_H_

#define BLACK_PAIR 1
#define RED_PAIR 2

void end_screen();
int print (const char *format, ...);
void init_colors(void);
void init_screen(void);

void text_background(int color);
void color(int color);
void hgotoxy(int x,int y);
#endif