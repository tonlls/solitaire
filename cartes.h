#include <stdio.h>  
#include <windows.h>  
#include "conio.c"

typedef struct{
	int nombre;
	int pal;
	int color;
	int destapada;
	int barrejada;
	int seleccionada;
}Tcarta;



void hgotoxy(int x,int y){  
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);
}

void dimoni(int x,int y,int i){
	textcolor(12);
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
	//getch();
}

void esborrarEspai(int x1,int y1,int x2,int y2){
	//textbackground(3);
	int x,y;
	for(y=y1;y!=y2;y++){
		for(x=x1;x!=x2;x++){
			hgotoxy(x,y);
			printf(" ");
		}
	}
	hgotoxy(1,1);
}

void dibuixarRecuadre(int x,int y,int altura,int amplada){
	int i,ix;
	hgotoxy(x,y);
	//textcolor(8);
	printf("%c",218);
	for(i=x;i!=x+amplada;i++){
			printf("%c",196);
	}
	printf("%c",191);
	for(i=y;i!=y+altura;i++){
		ix=x+amplada+1;
		hgotoxy(x,i+1);
		printf("%c",179);
		hgotoxy(ix,i+1);
		printf("%c",179);
	}
	hgotoxy(x,y+altura+1);
	printf("%c",192);
		for(i=x;i!=x+amplada;i++){
				printf("%c",196);
		}
	printf("%c",217);
}

void dibuixarCarta(Tcarta carta,int x,int y){
	int pal,color;
	esborrarEspai(x,y,x+8,y+7);
	if(carta.destapada==1){
		switch(carta.pal){
			case 0:pal=3;color=12;break;//cors-vermell
			case 1:pal=5;color=0;break;//trebols-negre
			case 2:pal=4;color=12;break;//rombes-vermell
			case 3:pal=6;color=0;break;//picas-negre
		}
		textcolor(color);
		hgotoxy(x+1,y+1);
		switch(carta.nombre){
			case 1:printf("A    %c",pal);break;
			case 11:printf("J    %c",pal);break;
			case 12:printf("Q    %c",pal);break;
			case 13:printf("K    %c",pal);break;
			default:
				if(carta.nombre==10){
					printf("%d   %c",carta.nombre,pal);
				}
				else{
					printf("%d    %c",carta.nombre,pal);
				}
			break;
		}
		/*if(carta.nombre==10){
			hgotoxy(x+4,y+5);
			printf("%c%d",pal,carta.nombre);
		}
		else{*/
			hgotoxy(x+1,y+5);
			switch(carta.nombre){
				case 1:printf("%c    A",pal);break;
				case 11:printf("%c    J",pal);break;
				case 12:printf("%c    Q",pal);break;
				case 13:printf("%c    K",pal);break;
				default:
					if(carta.nombre==10){
						printf("%c   %d",pal,carta.nombre);
					}
					else{
						printf("%c    %d",pal,carta.nombre);
					}
				break;
			}
		//}	
	}
	if(carta.seleccionada==1){
		textcolor(12);
	}
	else{
		textcolor(0);
	}
	dibuixarRecuadre(x,y,5,6);
	//textbackground(5);
	//esborrarEspai(x,y,x+8,y+7);
}


