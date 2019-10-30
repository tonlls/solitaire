#include <ncurses.h>
#include <locale.h>

#define BLACK_PAIR 1
#define RED_PAIR 2
void mlog(const char *str){
	FILE *f;
	f=fopen("log.log","a+");
	fwrite(str,strlen(str)*sizeof(char),1,f);
	fwrite("\n",strlen("\n")*sizeof(char),1,f);
	fclose(f);
}
int print (const char *format, ...){
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
	//resize_term(10	,1);
	
	WINDOW* w=initscr();
	start_color();
	init_colors();
	//noecho();
	//curs_set(FALSE);
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