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

void clearSpace(int x1,int y1,int x2,int y2){
	//textbackground(3);
	int x,y;
	for(y=y1;y!=y2;y++){
		for(x=x1;x!=x2;x++){
			hgotoxy(x,y);
			print(" ");
		}
	}
	hgotoxy(1,1);
}

void drawRectangle(int x,int y,int altura,int amplada){
	int i,ix;

	hgotoxy(x,y);
	//textcolor(8);
	print("┌");
	for(i=x;i!=x+amplada;i++){
			print("─");
	}
	print("┐");
	for(i=y;i!=y+altura;i++){
		ix=x+amplada+1;
		hgotoxy(x,i+1);
		print("│");
		hgotoxy(ix,i+1);
		print("│");
	}
	hgotoxy(x,y+altura+1);
	print("└");
	for(i=x;i!=x+amplada;i++){
			print("─");
	}
	print("┘");
}

void drawCard(Tcard carta,int x,int y){
	int mcolor;
	char* suit;
	clearSpace(x,y,x+8,y+7);
	if(carta.uncovered==1){
		switch(carta.suit){
			case 0:suit=HEART;mcolor=RED_PAIR;break;//cors-vermell
			case 1:suit=CLUB;mcolor=BLACK_PAIR;break;//trebols-negre
			case 2:suit=DIAMOND;mcolor=RED_PAIR;break;//rombes-vermell
			case 3:suit=SPADE;mcolor=BLACK_PAIR;break;//picas-negre
		}
		color(mcolor);
		hgotoxy(x+1,y+1);
		switch(carta.number){
			case 1:print("A    %s",suit);break;
			case 11:print("J    %s",suit);break;
			case 12:print("Q    %s",suit);break;
			case 13:print("K    %s",suit);break;
			default:
				if(carta.number==10){
					print("%d   %s",carta.number,suit);
				}
				else{
					print("%d    %s",carta.number,suit);
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
				case 1:print("%s    A",suit);break;
				case 11:print("%s    J",suit);break;
				case 12:print("%s    Q",suit);break;
				case 13:print("%s    K",suit);break;
				default:
					if(carta.number==10){
						print("%s   %d",suit,carta.number);
					}
					else{
						print("%s    %d",suit,carta.number);
					}
				break;
			}
		//}	
	}
	if(carta.selected==1){
		color(RED_PAIR);
	}
	else{
		color(BLACK_PAIR);
	}
	drawRectangle(x,y,5,6);
	color(BLACK_PAIR);
}


