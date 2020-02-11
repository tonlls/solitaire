#ifndef _GRAPH_C_
#define _GRAPH_C_


#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include "./graphics_win.h"

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
	HANDLE hStdin; 
	DWORD fdwMode;
	hStdin = GetStdHandle(STD_INPUT_HANDLE); 
	fdwMode =  ENABLE_MOUSE_INPUT; 
	SetConsoleMode(hStdin, fdwMode);
	//system("MODE CON COLS=80 LINES=160");//getch();
	//gotoxy(1,1);
	//SetConsoleTitleA("SOLITARI");
	_setcursortype(_NOCURSOR);
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
#endif