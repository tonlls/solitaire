#include <stdio.h>  
#include <string.h>
#include <locale.h>


#if defined(_WIN32) || defined(__MSDOS__)
	#define LINUX 0
	#include "conio.c"
	#include <windows.h> 
#else
	#define LINUX 1
	#include <ncurses.h>
	#include "graphics_linux.h"
#endif

#define SPADE "♠"
#define CLUB "♣"
#define HEART "♥"
#define DIAMOND "♦"

typedef struct{
	int number;
	int suit;
	int color;
	int uncovered;
	int scrambled;
	int selected;
}Tcard;




void demon(int x,int y,int i){
	/*textcolor(12);
	hgotoxy(x,y);
	printf("             ,        ,");hgotoxy(x,y+1);
	printf("            /(        )%c",92);hgotoxy(x,y+2);
	 printf("            %c %c___   / |",92,92);hgotoxy(x,y+3);
  printf("            /   ");textcolor(0);printf("_");textcolor(12);printf(" '-/  %c",92);hgotoxy(x,y+4);
	printf("            (");textcolor(0);printf("/%c/ %c",92,92);textcolor(12);printf(" %c   /%c",92,92);hgotoxy(x,y+5);
	textcolor(0);printf("            / /   |");textcolor(12);printf(" `    %c",92);hgotoxy(x,y+6);
	textcolor(0);printf("            O O   )");textcolor(12);printf(" /    |");hgotoxy(x,y+7);
	textcolor(0);printf("            `%c^%c%c'",196,196,196);textcolor(12);printf(" <     /");hgotoxy(x,y+8);
	printf("           (_.)  _  )   /");hgotoxy(x,y+9);
	printf("            '.___/`    /");hgotoxy(x,y+10);
	printf("              `-----' /");hgotoxy(x,y+11);
	if((i%2)==0){
		printf("    <----. __ / __   %c",92);hgotoxy(x,y+12);
		printf("    <----|===O)))==) %c) /===========",92);hgotoxy(x,y+13);
		printf("    <----'`--' `.__,' %c",92);hgotoxy(x,y+14);
	}
	else{
		printf("<----.     __ / __   %c",92);hgotoxy(x,y+12);
		printf("<----|=======O)))==) %c) /=======",92);hgotoxy(x,y+13);//32 caracters
		printf("<----'    `--' `.__,' %c",92);hgotoxy(x,y+14);
	}
	printf("              |        |");hgotoxy(x,y+15);
	printf("               %c       /",92);hgotoxy(x,y+16);
	printf("          ______( (_  / %c______",92);hgotoxy(x,y+17);
	printf("        ,'  ,-----'   |        %c",92);hgotoxy(x,y+18);
	printf("        `--{__________)        %c/",92);hgotoxy(x,y+19);
	//getch();*/
	
}
