#ifndef _GRAPH_C_
#define _GRAPH_C_

#include <ncurses.h>
#include <locale.h>
#include "./graphics.h"

void end_screen(){
	endwin();
}
int print(const char *format, ...){
	va_list arg;
	int done; 
	
	va_start (arg, format);
	done = vw_printw(stdscr,format, arg);
	va_end (arg);
	return done;
}
void init_colors(void){
	init_pair(BLACK_PAIR, COLOR_BLACK, COLOR_WHITE);
	init_pair(RED_PAIR, COLOR_RED, COLOR_WHITE);
}
void init_screen(void){
	setlocale(LC_ALL, "");
	resize_term(10	,1);
	
	WINDOW* w=initscr();
	start_color();
	init_colors();
	noecho();
	curs_set(FALSE);
	wbkgd(w, COLOR_PAIR(BLACK_PAIR));
}

void text_background(int color){

}
void color(int color){
	attron(COLOR_PAIR(color));
}
void hgotoxy(int x,int y){
	move(y,x);
}
#endif