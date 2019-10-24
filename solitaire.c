
#include "cards.h"
#include <time.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <locale.h>

#if defined(_WIN32) || defined(__MSDOS__)
	#include "mouse_win.h"
#else
	#include "mouse_linux.h"
#endif

typedef struct{
	Tcard cards[31];
}Tdeck;

typedef struct{
	int place;
	int i;
	int u;
}Tmovement;

////estructura funcions///
void desseleccionarPilaA(int pila);
void desseleccionarPillades();
void desseleccionarPilaA(int pila);
void desseleccionarPila(int pila);
void desseleccionarBaralla();
void moure();
void moureCartaAsosPila(int pila_a,int pila);
void pasarPillades();
void moureCartaPilaPila(int pila1,int i1,int pila2);
void moureCartaPilaAsos(int i_pila,int pila,int pila_a);
void moureCartaPillarPila(int i_pila);
int buscarCartaXPillar(Tcard carta);
void misatgeError();
void seleccionarCartaPillar(int x,int y);
void seleccionarCartaAsos(int pila,int x,int y);
void moureCartaPillarAsos(int pila);
int click(int x,int y);
void seleccionarCartaPila(int pila,int x,int y);
void resetejarPillades();
int fiPartida();
void escriureTauler();
void escriurePiles();
void escriurePila(int i);
void escriureAsos();
void escriurePillades();
void iniciarTauler(/*Tdeck pilas[]*/);
void pillarCartes(/*Tdeck *baralla,Tcard cards_pillades[3],int *i_pillades*/);
void barrejarCartes();
void escriureRecuadre(int i);
void dibuixarTauler();
void inicialitzarTaules();
void init_screen();
////////////////////////////////////////////////////////////////////
///////CONSTANTS LLOCS////////
#define PILLAR 100
#define PILAS 200
#define ASOS 300
#define MAX_CARTES 52
#define AS 1
#define J 11
#define Q 12
#define K 13
#define BUIT -1
/////////////////////////////

/////////////////////////VARIABLES GLOBALS/////////////////////////////////
	int qtA[4]={0,0,0,0};
	int iPila[7]={0,0,0,0,0,0,0};
	int i_pillades=0,iPillar=-1,qt_pillades=24,seleccionades=0,pillarAct=2,pillarEnrrere=0;
	//int cResta=1,
	int reiniciar=0,clicks=0;
	Tcard cards[MAX_CARTES];
	Tcard cartes_barrejades[52];
	Tdeck pilas[7];
	Tdeck baralla;
	Tcard c_seleccionades[2];
	Tcard cartes_pillades[3];
	Tdeck pilaA[4];
	Tmovement selec[2];
///////////////////////////////////////////////////////////////////////////


void init_screen(void){
	setlocale(LC_ALL, "");
	WINDOW* w=initscr();
	noecho();
	curs_set(FALSE);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	wbkgd(w, COLOR_PAIR(1));
}

void inicialitzarTaules(){
	int i_pal,i=1,i_nombre;
	//while(i<MAX_CARTES){
		for(i_pal=0;i_pal!=4;i_pal++){
			i_nombre=1;
			while(i_nombre!=14){
				cards[i].number=i_nombre;
				cards[i].suit=i_pal;
				cards[i].uncovered=0;
				//cards[i].color=0;
				cards[i].color=i_pal%2;
				cards[i].scrambled=0;
				cards[i].selected=0;
				//printf("%d-%d,%d\n",i,cards[i].number,cards[i].suit);getch();
				i_nombre++;
				i++;
			}
		}
		//inicialitzar baralla
		for(i=0;i!=31;i++){
			baralla.cards[i].number=BUIT;
		}
		//inicialitzar pilas de As
		for(i=0;i!=4;i++){
			for(i_nombre=0;i_nombre!=31;i_nombre++){
				pilaA[i].cards[i_nombre].number=BUIT;
			}
			qtA[i]=0;
		}
		for(i=0;i!=3;i++){
			cartes_pillades[i].number=BUIT;
		}
 //}
}
void dibuixarTauler(){
	textcolor(8);
	drawRectangle(1,1,7,8);
	drawRectangle(11,1,7,8);
	drawRectangle(21,1,7,8);
	drawRectangle(31,1,7,8);
	
	drawRectangle(70,1,7,8);
	
	drawRectangle(70,10,1,1);
	hgotoxy(71,11);printf("R");
	
	drawRectangle(1,13,7,8);
	drawRectangle(11,13,7,8);
	drawRectangle(21,13,7,8);
	drawRectangle(31,13,7,8);
	drawRectangle(41,13,7,8);
	drawRectangle(51,13,7,8);
	drawRectangle(61,13,7,8);
}
void escriureRecuadre(int i){
	textcolor(8);
	switch(i){
		case 0:drawRectangle(1,13,7,8);break;
		case 1:drawRectangle(11,13,7,8);break;
		case 2:drawRectangle(21,13,7,8);break;
		case 3:drawRectangle(31,13,7,8);break;
		case 4:drawRectangle(41,13,7,8);break;
		case 5:drawRectangle(51,13,7,8);break;
		case 6:drawRectangle(61,13,7,8);break;
	}
	attron(COLOR_PAIR(1));
	refresh();
}
void barrejarCartes(){
	int i,i2,u;
	//remenar les cards
	for(i=0;i!=MAX_CARTES;i++){
		do{
			i2=(rand()%MAX_CARTES)+1;
		}while(cards[i2].scrambled==1);
		cartes_barrejades[i]=cards[i2];
		cards[i2].scrambled=1;
	}
	//posar les cards a les piles
	u=0;
	for(i=0;i!=7;i++){
		for(i2=0;i2!=i+1;i2++){
			pilas[i].cards[i2]=cartes_barrejades[u];
			//iPila[i]++;
			u++;
		}
	}
	//posar les cards per pillar
	for(i=0;u!=MAX_CARTES;i++){
		baralla.cards[i]=cartes_barrejades[u];
		baralla.cards[i].uncovered=0;
		u++;
	}
}

void pillarCartes(/*Tdeck *baralla,Tcard cartes_pillades[3],int *i_pillades*/){
	int i,x=62,y=2,e=-1;
	pillarAct=0;
	//cResta=0;
	if(seleccionades>0&&selec[0].place==PILLAR){
		selec[0].place=BUIT;
		seleccionades=0;
		cartes_pillades[pillarAct].selected=0;
	}
	if(i_pillades<qt_pillades){
		iPillar=-1;
		//e=-1;
		for(i=0;i!=3;i++){
			cartes_pillades[i].number=BUIT;
		}
		//cResta=0;
		for(i=0;i!=3&&i_pillades<qt_pillades;i_pillades++){
			if(baralla.cards[i_pillades].number!=BUIT/*&&i_pillades!=*/){
				cartes_pillades[i]=baralla.cards[i_pillades];
				cartes_pillades[i].uncovered=1;
				i++;
				iPillar++;
				pillarEnrrere++;
				//pillarAct++;
				//cResta++;
			}
		}
		//u++;
		/*for(i=2;i!=-1;i--){
			if(cartes_pillades[i].number==BUIT){
				cartes_pillades[i]=cartes_pillades[i-1];
				cartes_pillades[i-1].number=BUIT;
			}
		}*/
		//if(i_pillades<=)
		
			
		//printf("X");getch();
		if(cartes_pillades[2].number==BUIT){
			pasarPillades();
			if(cartes_pillades[2].number==BUIT){
				pasarPillades();
			}
		}
		escriurePillades();
		//escriureTauler();
	}
	else{
		resetejarPillades();
	}
	//printf("%d",baralla.cards[i_pillades-1].number);
	refresh();
}

void pasarPillades(/*Tcard cartes_pillades[],Tdeck baralla*/){
	int i,t;
	for(i=2;i!=-1;i--){
		if(cartes_pillades[i].number==BUIT&&i!=0){
			cartes_pillades[i]=cartes_pillades[i-1];
			cartes_pillades[i-1].number=BUIT;
		}
	}
	while(cartes_pillades[0].number==BUIT){
		i=0;
		while(i!=3&&cartes_pillades[i].number==BUIT){
			i++;
		}
		//printf("(%d)",cartes_pillades[i].number);getch();
		t=buscarCartaXPillar(cartes_pillades[i])-1;
		while(t>=0&&baralla.cards[t].number==BUIT){
			t--;
		}
		cartes_pillades[i-1]=baralla.cards[t];
	}
	//escriurePillades();
	refresh();
}

void iniciarTauler(/*Tdeck pilas[]*/){
	int x=2,y=14,i,i2;
	for(i=0;i!=7;i++){
		for(i2=0;i2!=i+1;i2++){
			iPila[i]++;
			if(i==i2){
				pilas[i].cards[i2].uncovered=1;
			}
			drawCard(pilas[i].cards[i2],x,y);
			y=y+2;
		}
		y=14;
		x=x+10;
	}
	refresh();
}

void escriurePillades(){
	int i,x=56,y=2;
	//cResta=1;
	clearSpace(56,2,70,9);
	for(i=0;i!=3;i++){
		//printf("%d",cartes_pillades[i].number);getch();
		if(cartes_pillades[i].number!=BUIT&&cartes_pillades[i].number!=0){
			cartes_pillades[i].uncovered=1;
			drawCard(cartes_pillades[i],x,y);
			x=x+3;
			//cResta++;
		}
	}
	refresh();
}

void escriureAsos(){
	int x=2,y=2,i;
	//clearSpace(2,2,42,2);
	for(i=0;i!=4;i++){
		clearSpace(x,2,x+8,9);
		if(pilaA[i].cards[qtA[i]].number!=BUIT){
			drawCard(pilaA[i].cards[qtA[i]],x,y);
		}
		x=x+10;
	}
	refresh();
}
void escriurePila(int i){
	int x,y=14,i2;
	x=i*10+2;
	clearSpace(x,14,x+8,50);
	escriureRecuadre(i);
	for(i2=0;i2!=iPila[i];i2++){
		drawCard(pilas[i].cards[i2],x,y);
		y=y+2;
	}
	refresh();
}
void escriurePiles(){
	int x=-8,y=14,i,i2;
	clearSpace(2,14,72,100);
	for(i=0;i!=7;i++){
		escriurePila(i);
		/*x=x+10;
		y=14;
		for(i2=0;i2!=iPila[i];i2++){
			drawCard(pilas[i].cards[i2],x,y);
			y=y+2;
		}*/
		
	}
	//printf("%d-%d",x,y);getch();
	refresh();
}

void escriureTauler(){
	int x=2,y=14,i,i2;
	//system("cls");
	clear();
	dibuixarTauler();
	//escriure les piles
	escriurePiles();
	/*for(i=0;i!=7;i++){
		for(i2=0;i2!=iPila[i];i2++){
			drawCard(pilas[i].cards[i2],x,y);
			y=y+2;
		}
		y=14;
		x=x+10;
	}*/
	//escriure cards pillades
	escriurePillades();
	/*x=62;y=2;
	for(i=0;i!=3;i++){
		if(cartes_pillades[i].number!=BUIT){
			drawCard(cartes_pillades[i],x,y);
			x=x-3;
		}
	}*/
	//escriure pilas de A
	//getch();
	escriureAsos();
	/*x=2;y=2;
	for(i=0;i!=4;i++){
		if(pilaA[i].cards[qtA[i]].number!=BUIT){
			drawCard(pilaA[i].cards[qtA[i]],x,y);
		}
		x=x+10;
	}*/
	refresh();
}


int fiPartida(/*Tdeck pilaA[4]*/){
	int i,fi=0;
	for(i=0;i!=4;i++){
		if(pilaA[i].cards[1].number==1&&pilaA[i].cards[13].number==13&&pilaA[i].cards[1].suit==pilaA[i].cards[13].suit){
			fi++;
		}
	}
	if(fi==4){
		return 1;
	}
	return 0;
}

void resetejarPillades(/*Tcard cartes_pillades[],int *i_pillades,int *cResta*/){
	//cResta=0;
	int i=0;
	for(i=0;i!=3;i++){
		cartes_pillades[i].number=BUIT;
		cartes_pillades[i].uncovered=0;
	}
	i_pillades=0;
	escriurePillades();
}

void seleccionarCartaPila(int pila,int x,int y){
	int i=0,u=0,i2=0,surt=0,e=0;
	//printf("(%d)",iPila[pila]);getch();
	if(iPila[pila]==0&&y>12&&y<22&&seleccionades==1){
		//printf("ultima carta");getch();
		selec[1].place=PILAS;
		selec[1].i=pila;
		seleccionades++;
		//escriureTauler();
	}
	else{
		for(i=0;i!=iPila[pila]&&surt==0;i++){
			if(i==iPila[pila]-1){
				u=6;
			}
			else{
				u=1;
			}
			if(i!=0){
				e=1;
			}
			else{
				e=0;
			}
			//printf("%d",iPila[pila]);getch();
			if(y>=i*2+14&&y<=i*2+14+u){
				//printf("2");getch();
				if(pilas[pila].cards[i].uncovered==1){
					if(pilas[pila].cards[i].selected==1){
						pilas[pila].cards[i].selected=0;
						//c_seleccionades[seleccionades-1].number=BUIT;
						seleccionades--;
						/*for(e=i;e!=iPila[pila];e++){
							pilas[pila].cards[e].selected=0;
						}*/
						desseleccionarPila(pila);
					}
					else{
						pilas[pila].cards[i].selected=1;
						//c_seleccionades[seleccionades-1]=pilas[pila].cards[i];
						seleccionades++;
						for(e=i;e!=iPila[pila];e++){
							pilas[pila].cards[e].selected=1;
						}
						
					}
					if(seleccionades==1){
						selec[0].place=PILAS;
						selec[0].i=pila;
						selec[0].u=i;
						//escriureTauler();
					}
					else if(seleccionades==2){
						selec[1].place=PILAS;
						selec[1].i=pila;
					}
					escriurePila(pila);
					//escriureTauler();
				}
			}
		}
	}
}

int click(int x,int y){
	/*printf("pos1");getch();
	escriurePillades();
	printf("pos2");getch();*/
	int i=-1,u=0,i2=0,surt=0,e=0,pila=0;  ///erroor al pillar cards
	if(x>=70&&y>=10&&x<=72&&y<=12){
		reiniciar=1;
	}
	//mirem si clica per pillar cards
	else if(x>=70&&x<=78&&y>=1&&y<=10){
		if(i_pillades==24){
			resetejarPillades();
			i_pillades=0;
			//iPillar=0;
		}
		else{
			pillarCartes();
		}
		//pillarCartes();
	}
	//mirem si clica una pila
	else if(x>=2&&x<=69&&y>=13){
		//mirem si clica la pila 0
		if(x>=2&&x<=9){
		//mirem a quina carta clica de la pila 0
			seleccionarCartaPila(0,x,y);
		}
		//mirem si clica a la pila 1
		else if(x>=12&&x<=19){
			//mirem a quina carta clica de la pila 1
			seleccionarCartaPila(1,x,y);
		}
		//mirm si clica la pila 2
		else if(x>=22&&x<=29){
		//mirem a quina carta clica de la pila 2
			seleccionarCartaPila(2,x,y);
		}
		else if(x>=32&&x<=39){
		//mirem a quina carta clica de la pila 3
			seleccionarCartaPila(3,x,y);
		}
		else if(x>=42&&x<=49){
		//mirem a quina carta clica de la pila 4
			seleccionarCartaPila(4,x,y);
		}
		else if(x>=52&&x<=59){
		//mirem a quina carta clica de la pila 5
			seleccionarCartaPila(5,x,y);
		}
		else if(x>=62&&x<=69){
		//mirem a quina carta clica de la pila 6
			seleccionarCartaPila(6,x,y);
		}
	}
	//mirem si vol agafar una carta de les de pillar
	else if(x>=56&&x<=69&&y>=1&&y<=10){
		seleccionarCartaPillar(x,y);
	}
	//mirem si clica a alguna pila de asos
	else if(x>=2&&y>=2&&x<=41&&y<=10){
		if(x>=2&&x<=11){
			//printf("0");getch()
			seleccionarCartaAsos(0,x,y);
		}
		else if(x>=12&&x<=21){
			seleccionarCartaAsos(1,x,y);
		}
		else if(x>=22&&x<=31){
			seleccionarCartaAsos(2,x,y);
		}
		else if(x>=32&&x<=41){
			seleccionarCartaAsos(3,x,y);
		}
	}
}

void moureCartaPillarAsos(int pila){
	int u;
	if(qtA[pila]==0){
		if(cartes_pillades[pillarAct].number==1){
			cartes_pillades[pillarAct].selected=0;

			u=buscarCartaXPillar(cartes_pillades[pillarAct]);
			qtA[pila]++;
			pilaA[pila].cards[qtA[pila]]=cartes_pillades[pillarAct];
			
			baralla.cards[u].number=BUIT;
			cartes_pillades[pillarAct].number=BUIT;
			
			//pilaA[pila].cards[qtA[pila]].uncovered=1;

			//printf("%d",pilaA[pila].cards[qtA[pila]+1].number);getch();
			//printf("%d",cResta);getch();
			//cResta++;
			iPillar--;
			seleccionades=0;
			selec[0].place=BUIT;
			selec[1].place=BUIT;

			//escriureTauler();
		}
		else{
			cartes_pillades[pillarAct].selected=0;
			seleccionades=0;
		}
	}
	else if(cartes_pillades[pillarAct].number-1==pilaA[pila].cards[qtA[pila]].number&&cartes_pillades[pillarAct].suit==pilaA[pila].cards[qtA[pila]].suit){
		//printf("no A");getch();
		cartes_pillades[pillarAct].selected=0;
		qtA[pila]++;
		pilaA[pila].cards[qtA[pila]].selected=0;
		pilaA[pila].cards[qtA[pila]]=cartes_pillades[pillarAct];
		u=buscarCartaXPillar(cartes_pillades[pillarAct]);
		
		baralla.cards[u].number=BUIT;
		cartes_pillades[pillarAct].number=BUIT;
		//cResta++;
		iPillar--;
		seleccionades=0;
		selec[0].place=BUIT;
		selec[1].place=BUIT;
		
		//escriureTauler();
	}
	desseleccionarPilaA(pila);
	desseleccionarPillades();
	pasarPillades();
	escriurePillades();
	escriureAsos();

}

void seleccionarCartaAsos(int pila,int x,int y){
	//printf("A");getch();
	selec[seleccionades].u=pila;
	if(qtA[pila]==0){
		if(seleccionades==1){
			selec[1].place=ASOS;
			seleccionades++;
		}
	}
	else{
		if(pilaA[pila].cards[qtA[pila]].selected==0){
			pilaA[pila].cards[qtA[pila]].selected=1;
			seleccionades++;
		}
		else{
			pilaA[pila].cards[qtA[pila]].selected=0;
			desseleccionarPilaA(pila);
			seleccionades--;
		}
		if(seleccionades==1){
			selec[0].place=ASOS;
			//escriureTauler();
		}
		else {
			selec[1].place=ASOS;
		}
	}
	escriureAsos();
}


void seleccionarCartaPillar(int x,int y){
	pillarAct=2;
	while(cartes_pillades[pillarAct].number==BUIT){
		pillarAct--;
	}
	/*printf("fuck");getch();
	escriurePillades();
	printf("fuck 22222");getch();*/
	
	
	/*while(pillarAct!=-1&&cartes_pillades[pillarAct].number==BUIT){
		pillarAct--;
	}*/
	if(seleccionades==0){
		if(cartes_pillades[pillarAct].selected==0){
			//printf("%d",cartes_pillades[iPillar].number);getch();
			cartes_pillades[pillarAct].selected=1;
			//c_seleccionades[seleccionades-1]=cartes_pillades[0];
			seleccionades++;
		}
		if(seleccionades==1){
			selec[0].place=PILLAR;
		}
	}
	else{
		if(cartes_pillades[pillarAct].selected==1){
			cartes_pillades[pillarAct].selected=0;
			//c_seleccionades[seleccionades-1].number=BUIT;
			seleccionades--;
			desseleccionarPillades();
		}
	}
	//printf("X");getch();
		escriurePillades();
}
int buscarCartaXPillar(Tcard carta){
	int i=0;
	for(i=0;i!=25;i++){
		//printf("%d-(%d)",baralla.cards[i].number,carta.number);getch();
		if(baralla.cards[i].suit==carta.suit&&baralla.cards[i].number==carta.number){
			//printf("TROBAT");getch();
			return i;
		}
	}
	//misatgeError();
	/*
	if(i!=qt_pillades){
		return i;
	}*/
}

void misatgeError(){
	//system("cls"); 
	printf("S'ha produit un error contacti amb el creador(Ton Lluci� Senserrich)");
}

void moureCartaPillarPila(int i_pila){
	int u;
	//printf("%d",iPila[i_pila]);getch();
	if(iPila[i_pila]==0&&cartes_pillades[pillarAct].number==13){
		//printf("baixarOK");getch();
		//pilas[i_pila].cards[iPila[i_pila]].selected=0;
		cartes_pillades[pillarAct].selected=0;
		pilas[i_pila].cards[iPila[i_pila]]=cartes_pillades[pillarAct];
		u=buscarCartaXPillar(cartes_pillades[pillarAct]);
		///printf("33");getch();
		pilas[i_pila].cards[iPila[i_pila]].selected=0;
		baralla.cards[u].number=BUIT;
		cartes_pillades[pillarAct].number=BUIT;
		iPila[i_pila]++;
		//pilas[i_pila].cards[iPila[i_pila]-1].uncovered=1;
		//escriureTauler();
	}
 	else if(cartes_pillades[pillarAct].number+1==pilas[i_pila].cards[iPila[i_pila]-1].number&&cartes_pillades[pillarAct].color!=pilas[i_pila].cards[iPila[i_pila]-1].color){
		//printf("RO");getch();
		cartes_pillades[pillarAct].selected=0;
		pilas[i_pila].cards[iPila[i_pila]]=cartes_pillades[pillarAct];
		pilas[i_pila].cards[iPila[i_pila]].selected=0;
		pilas[i_pila].cards[iPila[i_pila]-1].selected=0;
		
		u=buscarCartaXPillar(cartes_pillades[pillarAct]);

		baralla.cards[u].number=BUIT;
		cartes_pillades[pillarAct].number=BUIT;
		//compactarBaralla();
		//qt_pillades--;
		//cResta++;
		iPillar--;
		iPila[i_pila]++;
		seleccionades=0;
		selec[0].place=BUIT;
		selec[1].place=BUIT;

		//escriureTauler();
 	}
	else{
		pilas[i_pila].cards[iPila[i_pila]-1].selected=0;
		cartes_pillades[iPillar].selected=0;
		seleccionades=0;
		selec[0].place=BUIT;
		selec[1].place=BUIT;
		//escriureTauler();
	}
	desseleccionarPila(i_pila);
	desseleccionarPillades();
	escriurePillades();
	pasarPillades();
	escriurePillades();
	escriurePila(i_pila);
	
}

//////////--error al printar les pillades

void moureCartaPilaPila(int pila1,int i1,int pila2){
	//printf("PilaPila");getch();
	int i=0,u=0;
	if(iPila[pila2]==0&&pilas[pila1].cards[i1].number==13){
		//pilas[pila2].cards[iPila[pila2]+1].selected=0;
		for(i=i1;i!=iPila[pila1];i++){
			pilas[pila1].cards[i].selected=0;
			pilas[pila2].cards[iPila[pila2]]=pilas[pila1].cards[i];
			pilas[pila1].cards[i].number=BUIT;
			iPila[pila2]++;
			u++;
			//iPila[pila1]--;
		}
		iPila[pila1]=iPila[pila1]-u;
		pilas[pila1].cards[iPila[pila1]-1].uncovered=1;
		for(i=0;i!=iPila[pila2];i++){
			pilas[pila2].cards[i].selected=0;
		}
	}
	else if(pilas[pila1].cards[i1].number==pilas[pila2].cards[iPila[pila2]-1].number-1&&pilas[pila1].cards[i1].color!=pilas[pila2].cards[iPila[pila2]-1].color){
		pilas[pila2].cards[iPila[pila2]-1].selected=0;
		for(i=i1;i!=iPila[pila1];i++){
			pilas[pila2].cards[iPila[pila2]]=pilas[pila1].cards[i];
			pilas[pila2].cards[iPila[pila2]].selected=0;
			pilas[pila1].cards[i].number=BUIT;
			iPila[pila2]++;
			u++;
			//iPila[pila1]--;
		}
			iPila[pila1]=iPila[pila1]-u;
			pilas[pila1].cards[iPila[pila1]-1].uncovered=1;
	}
	else{
		pilas[pila2].cards[iPila[pila2]-1].selected=0;
		pilas[pila1].cards[i1].selected=0;
		for(i=i1;i!=iPila[pila1];i++){
			pilas[pila1].cards[i].selected=0;
		}
	}
	seleccionades=0;
	selec[0].place=BUIT;
	selec[1].place=BUIT;
	//escriureTauler();
	desseleccionarPila(pila1);
	desseleccionarPila(pila2);
	escriurePila(pila1);
	escriurePila(pila2);
}

void moureCartaPilaAsos(int i_pila,int pila,int pila_a){
	int i;
	//printf("%d (%d)",i_pila,iPila[pila]);getch();
	if((pilas[pila].cards[i_pila].number-1==pilaA[pila_a].cards[qtA[pila_a]].number&&pilas[pila].cards[i_pila].suit==pilaA[pila_a].cards[qtA[pila_a]].suit||pilas[pila].cards[i_pila].number==1)&&i_pila==iPila[pila]-1){
		//printf("GET");getch();
		pilas[pila].cards[i_pila].selected=0;
		pilaA[pila_a].cards[qtA[pila_a]+1]=pilas[pila].cards[i_pila];
		pilas[pila].cards[i_pila].number==BUIT;
		iPila[pila]--;
		qtA[pila_a]++;
		if(pilas[pila].cards[iPila[pila]-1].uncovered==0){
			pilas[pila].cards[iPila[pila]-1].uncovered=1;
		}
	}
	else{
		for(i=i_pila;i!=iPila[pila];i++){
			pilas[pila].cards[i].selected=0;
		}
		pilaA[pila_a].cards[qtA[pila_a]].selected=0;
	}
	seleccionades=0;
	selec[0].place=BUIT;
	selec[1].place=BUIT;
	desseleccionarPila(pila);
	desseleccionarPilaA(pila_a);
	escriurePila(pila);
	escriureAsos();
	//escriureTauler();
}

void moureCartaAsosPila(int pila_a,int pila){       //error al baixar cards de asos
			//printf("(%d)(%d)",pilaA[pila_a].cards[qtA[pila_a]].number,pilas[pila].cards[iPila[pila]-1].number);getch();
	if((pilas[pila].cards[iPila[pila]-1].number==pilaA[pila_a].cards[qtA[pila_a]].number+1&&pilas[pila].cards[iPila[pila]-1].color!=pilaA[pila_a].cards[qtA[pila_a]].color)||(iPila[pila]==0&&pilaA[pila_a].cards[qtA[pila_a]].number==13)){
		//printf("pas2");getch();
		pilas[pila].cards[iPila[pila]-1].selected=0;
		pilas[pila].cards[iPila[pila]].selected=0;
		pilas[pila].cards[iPila[pila]]=pilaA[pila_a].cards[qtA[pila_a]];
		pilaA[pila_a].cards[qtA[pila_a]].number=BUIT;
		//escriureAsos();
		qtA[pila_a]--;
		iPila[pila]++;
	}
	pilas[pila].cards[iPila[pila]].selected=0;
	//pilas[pila].cards[iPila[pila]-2].selected=0;
	selec[0].place=BUIT;
	selec[1].place=BUIT;
	//escriureTauler();
	desseleccionarPila(pila);
	desseleccionarPilaA(pila_a);
	escriurePila(pila);
	escriureAsos();
}

void moure(){
		//printf("VV");getch();
	if(selec[0].place==PILAS&&selec[1].place==PILAS){
		moureCartaPilaPila(selec[0].i,selec[0].u,selec[1].i);
	}
	else if(selec[0].place==PILLAR&&selec[1].place==PILAS){
		moureCartaPillarPila(selec[1].i);
	}
	else if(selec[0].place==PILLAR&&selec[1].place==ASOS){
		moureCartaPillarAsos(selec[1].u);
	}
	else if(selec[0].place==PILAS&&selec[1].place==ASOS){
		moureCartaPilaAsos(selec[0].u,selec[0].i,selec[1].u);
	}
	else if(selec[0].place==ASOS&&selec[1].place==PILAS){
		moureCartaAsosPila(selec[0].u,selec[1].i);
	}
}
void desseleccionarBaralla(){
	int i;
	for(i=0;i!=25;i++){//desseleccionar cards baralla
		baralla.cards[i].selected=0;
	}
}
void desseleccionarPila(int pila){
	int i;
	for(i=0;i!=MAX_CARTES/*iPila[pila]+1*/;i++){
		pilas[pila].cards[i].selected=0;
	}
	//escriurePila(pila);
}
void desseleccionarPilaA(int pila){
	int i;
	for(i=0;i!=qtA[pila]+1;i++){
		pilaA[pila].cards[i].selected=0;
	}
	//escriureAsos();
}

void desseleccionarPillades(){
	cartes_pillades[0].selected=0;
	cartes_pillades[1].selected=0;
	cartes_pillades[2].selected=0;
	//escriurePillades();
}

void guanyat(){
	int i;
	//system("MODE CON COLS=90 LINES=160");
	textbackground(WHITE);
	for(i=0;i!=6;i++){
		clear();
		//printf("%d(%d)",i,i%2);
		demon(50,20,i);
		if((i%2)!=0)hgotoxy(33,32);else hgotoxy(37,32);
		printf("Nanu ets un CRACK");
		sleep(1);
		//getch();
	}
	for(i=33;i!=0;i--){
		hgotoxy(i,32);
		textcolor((rand()%14)+1);
		printw("Nanu ets un CRACK");
		sleep(1);
		hgotoxy(i,32);
		printw("                 ");
		i--;i--;
	}
	for(i=1;i!=34;i++){
		hgotoxy(i-3,32);
		printw("                 ");
		hgotoxy(i,32);
		textcolor((rand()%14)+1);
		printw("Nanu ets un CRACK");
		sleep(1);
		i++;i++;
	}
	refresh();
}

void main(){
	int i,i2;
	int x_click,y_click;
	
	init_screen();
	textcolor(BLACK);
	escriureRecuadre(1);
	textcolor_off();
	textcolor(RED);
	escriureRecuadre(2);
	textcolor_off();
	sleep(5);
	do{
		break;
		qtA[0]=0;qtA[1]=0;qtA[2]=0;qtA[3]=0;
		iPila[0]=0;iPila[1]=0;iPila[2]=0;iPila[3]=0;iPila[4]=0;iPila[5]=0;iPila[6]=0;
		i_pillades=0;iPillar=-1;qt_pillades=24;seleccionades=0;pillarAct=2;pillarEnrrere=0;reiniciar=0;
		//cResta=1;
		
		reiniciar=0;
		srand(time(NULL));
		textbackground(WHITE);
		clear();
		Tcard cards[MAX_CARTES];
		Tcard cartes_barrejades[MAX_CARTES];

		inicialitzarTaules();

		barrejarCartes();
		dibuixarTauler();
		iniciarTauler(pilas);
		refresh();
		while(fiPartida()==0&&reiniciar!=1){
			seleccionades=0;
			selec[0].place=BUIT;
			selec[1].place=BUIT;
			//desseleccionarPillades();//desseleccionar les cards per pillar
			desseleccionarBaralla();//desseleccionar cards baralla
			for(i=0;i!=7;i++){//desseleccionar cards pila
				desseleccionarPila(i);
			}
			for(i=0;i!=4;i++){//desseleccionar asos
				desseleccionarPilaA(i);
			}
			//escriureTauler();
			while(seleccionades!=2&&fiPartida()!=1&&reiniciar!=1){
	 			x_click=0;y_click=0;
				 start(&x_click,&y_click);
				//moure(&baralla,cartes_pillades,&i_pillades,&posicio);
			//printf("hoa");getch();
				click(x_click,y_click);
			}
			
			if(seleccionades==2&&fiPartida()==0&&reiniciar!=1){

				moure();
				//moureCartaPillarPila(0);
			}
		}
		if(fiPartida()==1){
			clear();
			reiniciar=0;
			guanyat();
			getch();
			//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n            creador ---> Ton Lluci� Senserrich ");getch();
		}
	}while(reiniciar==1);
	endwin();
}
//////////////////////////////////
//-baixar una carta dels asos que es del mateix color
//-al baixar una carta de les pillades no escriu el tauler
//-pots seleccionar els les pillades com a 2a seleccio

