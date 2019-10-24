#include <stdio.h>  
#include <string.h>
#include <locale.h>


#if defined(_WIN32) || defined(__MSDOS__)
	#define LINUX 0
	#include "conio.c"
	#include <windows.h> 
	#define WHITE 15
	#define BLACK 0
	#define RED 12
#else
	#define LINUX 1
	#include <ncurses.h>
	#define WHITE COLOR_WHITE
	#define BLACK COLOR_BLACK
	#define RED COLOR_RED
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


void textbackground(int x){

}
void textcolor(int x){
	init_pair(1, x, COLOR_WHITE);
	attron(COLOR_PAIR(1));
}
void textcolor_off(){
	attroff(COLOR_PAIR(1));
	reset_color_pairs();
	
}
void hgotoxy(int x,int y){
	move(y,x);
}

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

void clearSpace(int x1,int y1,int x2,int y2){
	//textbackground(3);
	int x,y;
	for(y=y1;y!=y2;y++){
		for(x=x1;x!=x2;x++){
			hgotoxy(x,y);
			printw(" ");
		}
	}
	hgotoxy(1,1);
}

void drawRectangle(int x,int y,int altura,int amplada){
	int i,ix;

	hgotoxy(x,y);
	//textcolor(8);
	printw("┌");
	for(i=x;i!=x+amplada;i++){
			printw("─");
	}
	printw("┐");
	for(i=y;i!=y+altura;i++){
		ix=x+amplada+1;
		hgotoxy(x,i+1);
		printw("│");
		hgotoxy(ix,i+1);
		printw("│");
	}
	hgotoxy(x,y+altura+1);
	printw("└");
	for(i=x;i!=x+amplada;i++){
			printw("─");
	}
	printw("┘");
}

void drawCard(Tcard carta,int x,int y){
	int color;
	char* suit;
	clearSpace(x,y,x+8,y+7);
	if(carta.uncovered==1){
		switch(carta.suit){
			case 0:suit=HEART;color=RED;break;//cors-vermell
			case 1:suit=CLUB;color=BLACK;break;//trebols-negre
			case 2:suit=DIAMOND;color=RED;break;//rombes-vermell
			case 3:suit=SPADE;color=BLACK;break;//picas-negre
		}
		textcolor(color);
		hgotoxy(x+1,y+1);
		switch(carta.number){
			case 1:printw("A    %s",suit);break;
			case 11:printw("J    %s",suit);break;
			case 12:printw("Q    %s",suit);break;
			case 13:printw("K    %s",suit);break;
			default:
				if(carta.number==10){
					printw("%d   %s",carta.number,suit);
				}
				else{
					printw("%d    %s",carta.number,suit);
				}
			break;
		}
		/*if(carta.number==10){
			hgotoxy(x+4,y+5);
			printf("%c%d",suit,carta.number);
		}
		else{*/
			hgotoxy(x+1,y+5);
			switch(carta.number){
				case 1:printw("%s    A",suit);break;
				case 11:printw("%s    J",suit);break;
				case 12:printw("%s    Q",suit);break;
				case 13:printw("%s    K",suit);break;
				default:
					if(carta.number==10){
						printw("%s   %d",suit,carta.number);
					}
					else{
						printw("%s    %d",suit,carta.number);
					}
				break;
			}
		//}	
	}
	if(carta.selected==1){
		textcolor(RED);
	}
	else{
		textcolor(BLACK);
	}
	drawRectangle(x,y,5,6);
	//textcolor(BLACK);
	//attroff(COLOR_PAIR(0));
	endwin();
	refresh();
	//attroff(COLOR_PAIR(1));
	//textbackground(5);
	//clearSpace(x,y,x+8,y+7);
}


