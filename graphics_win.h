#include <stdio.h>

#define BLACK_PAIR 0
#define RED_PAIR 12

int print (const char *format, ...){
	va_list arg;
	int done; 
	va_start (arg, format);
	done = vfprintf (stdout,format, arg);
	va_end (arg);
	return done;
}
void init_screen(void){
	setlocale(LC_ALL, "");
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
	textcolor(color);
}
void hgotoxy(int x,int y){
	HANDLE hcon;  
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y= y;  
	SetConsoleCursorPosition(hcon,dwPos);
}