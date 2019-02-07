#include"mouseBETA.h"
#include"cartes.h"
#include<time.h>
#include<stdio.h>


typedef struct{
	Tcarta cartes[31];
}Tbaralla;

typedef struct{
	int lloc;
	int i;
	int u;
}Tmov;

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
void moureCartaPillarPila(int i_pila);
int buscarCartaXPillar(Tcarta carta);
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
void iniciarTauler(/*Tbaralla pilas[]*/);
void pillarCartes(/*Tbaralla *baralla,Tcarta cartes_pillades[3],int *i_pillades*/);
void barrejarCartes();
void escriureRecuadre(int i);
void dibuixarTauler();
void inicialitzarTaules();
void maximitzar_finestra();
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
	Tcarta cartes[MAX_CARTES];
	Tcarta cartes_barrejades[52];
	Tbaralla pilas[7];
	Tbaralla baralla;
	Tcarta c_seleccionades[2];
	Tcarta cartes_pillades[3];
	Tbaralla pilaA[4];
	Tmov selec[2];
///////////////////////////////////////////////////////////////////////////


void maximitzar_finestra(void){
	//sleep(1);
	//getch();
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_SPACE,0x39,0,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
    keybd_event(VK_SPACE,0x39,KEYEVENTF_KEYUP,0);
    keybd_event(0x58,0x58,0,0);
	keybd_event(0x58,0x58,KEYEVENTF_KEYUP,0);
}

void inicialitzarTaules(){
	int i_pal,i=1,i_nombre;
	//while(i<MAX_CARTES){
		for(i_pal=0;i_pal!=4;i_pal++){
			i_nombre=1;
			while(i_nombre!=14){
				cartes[i].nombre=i_nombre;
				cartes[i].pal=i_pal;
				cartes[i].destapada=0;
				//cartes[i].color=0;
				cartes[i].color=i_pal%2;
				cartes[i].barrejada=0;
				cartes[i].seleccionada=0;
				//printf("%d-%d,%d\n",i,cartes[i].nombre,cartes[i].pal);getch();
				i_nombre++;
				i++;
			}
		}
		//inicialitzar baralla
		for(i=0;i!=31;i++){
			baralla.cartes[i].nombre=BUIT;
		}
		//inicialitzar pilas de As
		for(i=0;i!=4;i++){
			for(i_nombre=0;i_nombre!=31;i_nombre++){
				pilaA[i].cartes[i_nombre].nombre=BUIT;
			}
			qtA[i]=0;
		}
		for(i=0;i!=3;i++){
			cartes_pillades[i].nombre=BUIT;
		}
 //}
}
void dibuixarTauler(){
	textcolor(8);
	dibuixarRecuadre(1,1,7,8);
	dibuixarRecuadre(11,1,7,8);
	dibuixarRecuadre(21,1,7,8);
	dibuixarRecuadre(31,1,7,8);
	
	dibuixarRecuadre(70,1,7,8);
	
	dibuixarRecuadre(70,10,1,1);
	hgotoxy(71,11);printf("R");
	
	dibuixarRecuadre(1,13,7,8);
	dibuixarRecuadre(11,13,7,8);
	dibuixarRecuadre(21,13,7,8);
	dibuixarRecuadre(31,13,7,8);
	dibuixarRecuadre(41,13,7,8);
	dibuixarRecuadre(51,13,7,8);
	dibuixarRecuadre(61,13,7,8);	
}
void escriureRecuadre(int i){
	textcolor(8);
	switch(i){
		case 0:dibuixarRecuadre(1,13,7,8);break;
		case 1:dibuixarRecuadre(11,13,7,8);break;
		case 2:dibuixarRecuadre(21,13,7,8);break;
		case 3:dibuixarRecuadre(31,13,7,8);break;
		case 4:dibuixarRecuadre(41,13,7,8);break;
		case 5:dibuixarRecuadre(51,13,7,8);break;
		case 6:dibuixarRecuadre(61,13,7,8);break;
	}
}
void barrejarCartes(){
	int i,i2,u;
	//remenar les cartes
	for(i=0;i!=MAX_CARTES;i++){
		do{
			i2=(rand()%MAX_CARTES)+1;
		}while(cartes[i2].barrejada==1);
		cartes_barrejades[i]=cartes[i2];
		cartes[i2].barrejada=1;
	}
	//posar les cartes a les piles
	u=0;
	for(i=0;i!=7;i++){
		for(i2=0;i2!=i+1;i2++){
			pilas[i].cartes[i2]=cartes_barrejades[u];
			//iPila[i]++;
			u++;
		}
	}
	//posar les cartes per pillar
	for(i=0;u!=MAX_CARTES;i++){
		baralla.cartes[i]=cartes_barrejades[u];
		baralla.cartes[i].destapada=0;
		u++;
	}
}

void pillarCartes(/*Tbaralla *baralla,Tcarta cartes_pillades[3],int *i_pillades*/){
	int i,x=62,y=2,e=-1;
	pillarAct=0;
	//cResta=0;
	if(seleccionades>0&&selec[0].lloc==PILLAR){
		selec[0].lloc=BUIT;
		seleccionades=0;
		cartes_pillades[pillarAct].seleccionada=0;
	}
	if(i_pillades<qt_pillades){
		iPillar=-1;
		//e=-1;
		for(i=0;i!=3;i++){
			cartes_pillades[i].nombre=BUIT;
		}
		//cResta=0;
		for(i=0;i!=3&&i_pillades<qt_pillades;i_pillades++){
			if(baralla.cartes[i_pillades].nombre!=BUIT/*&&i_pillades!=*/){
				cartes_pillades[i]=baralla.cartes[i_pillades];
				cartes_pillades[i].destapada=1;
				i++;
				iPillar++;
				pillarEnrrere++;
				//pillarAct++;
				//cResta++;
			}
		}
		//u++;
		/*for(i=2;i!=-1;i--){
			if(cartes_pillades[i].nombre==BUIT){
				cartes_pillades[i]=cartes_pillades[i-1];
				cartes_pillades[i-1].nombre=BUIT;
			}
		}*/
		//if(i_pillades<=)
		
			
		//printf("X");getch();
		if(cartes_pillades[2].nombre==BUIT){
			pasarPillades();
			if(cartes_pillades[2].nombre==BUIT){
				pasarPillades();
			}
		}
		escriurePillades();
		//escriureTauler();
	}
	else{
		resetejarPillades();
	}
	//printf("%d",baralla.cartes[i_pillades-1].nombre);
}

void pasarPillades(/*Tcarta cartes_pillades[],Tbaralla baralla*/){
	int i,t;
	for(i=2;i!=-1;i--){
		if(cartes_pillades[i].nombre==BUIT&&i!=0){
			cartes_pillades[i]=cartes_pillades[i-1];
			cartes_pillades[i-1].nombre=BUIT;
		}
	}
	while(cartes_pillades[0].nombre==BUIT){
		i=0;
		while(i!=3&&cartes_pillades[i].nombre==BUIT){
			i++;
		}
		//printf("(%d)",cartes_pillades[i].nombre);getch();
		t=buscarCartaXPillar(cartes_pillades[i])-1;
		while(t>=0&&baralla.cartes[t].nombre==BUIT){
			t--;
		}
		cartes_pillades[i-1]=baralla.cartes[t];
	}
	//escriurePillades();
}

void iniciarTauler(/*Tbaralla pilas[]*/){
	int x=2,y=14,i,i2;
	for(i=0;i!=7;i++){
		for(i2=0;i2!=i+1;i2++){
			iPila[i]++;
			if(i==i2){
				pilas[i].cartes[i2].destapada=1;
			}
			dibuixarCarta(pilas[i].cartes[i2],x,y);
			y=y+2;
		}
		y=14;
		x=x+10;
	}
}

void escriurePillades(){
	int i,x=56,y=2;
	//cResta=1;
	esborrarEspai(56,2,70,9);
	for(i=0;i!=3;i++){
		//printf("%d",cartes_pillades[i].nombre);getch();
		if(cartes_pillades[i].nombre!=BUIT&&cartes_pillades[i].nombre!=0){
			cartes_pillades[i].destapada=1;
			dibuixarCarta(cartes_pillades[i],x,y);
			x=x+3;
			//cResta++;
		}
	}
}

void escriureAsos(){
	int x=2,y=2,i;
	//esborrarEspai(2,2,42,2);
	for(i=0;i!=4;i++){
		esborrarEspai(x,2,x+8,9);
		if(pilaA[i].cartes[qtA[i]].nombre!=BUIT){
			dibuixarCarta(pilaA[i].cartes[qtA[i]],x,y);
		}
		x=x+10;
	}
}
void escriurePila(int i){
	int x,y=14,i2;
	x=i*10+2;
	esborrarEspai(x,14,x+8,50);
	escriureRecuadre(i);
	for(i2=0;i2!=iPila[i];i2++){
		dibuixarCarta(pilas[i].cartes[i2],x,y);
		y=y+2;
	}
}
void escriurePiles(){
	int x=-8,y=14,i,i2;
	esborrarEspai(2,14,72,100);
	for(i=0;i!=7;i++){
		escriurePila(i);
		/*x=x+10;
		y=14;
		for(i2=0;i2!=iPila[i];i2++){
			dibuixarCarta(pilas[i].cartes[i2],x,y);
			y=y+2;
		}*/
		
	}
	//printf("%d-%d",x,y);getch();
}

void escriureTauler(){
	int x=2,y=14,i,i2;
	system("cls");
	dibuixarTauler();
	//escriure les piles
	escriurePiles();
	/*for(i=0;i!=7;i++){
		for(i2=0;i2!=iPila[i];i2++){
			dibuixarCarta(pilas[i].cartes[i2],x,y);
			y=y+2;
		}
		y=14;
		x=x+10;
	}*/
	//escriure cartes pillades
	escriurePillades();
	/*x=62;y=2;
	for(i=0;i!=3;i++){
		if(cartes_pillades[i].nombre!=BUIT){
			dibuixarCarta(cartes_pillades[i],x,y);
			x=x-3;
		}
	}*/
	//escriure pilas de A
	getch();
	escriureAsos();
	/*x=2;y=2;
	for(i=0;i!=4;i++){
		if(pilaA[i].cartes[qtA[i]].nombre!=BUIT){
			dibuixarCarta(pilaA[i].cartes[qtA[i]],x,y);
		}
		x=x+10;
	}*/
}


int fiPartida(/*Tbaralla pilaA[4]*/){
	int i,fi=0;
	for(i=0;i!=4;i++){
		if(pilaA[i].cartes[1].nombre==1&&pilaA[i].cartes[13].nombre==13&&pilaA[i].cartes[1].pal==pilaA[i].cartes[13].pal){
			fi++;
		}
	}
	if(fi==4){
		return 1;
	}
	return 0;
}

void resetejarPillades(/*Tcarta cartes_pillades[],int *i_pillades,int *cResta*/){
	//cResta=0;
	int i=0;
	for(i=0;i!=3;i++){
		cartes_pillades[i].nombre=BUIT;
		cartes_pillades[i].destapada=0;
	}
	i_pillades=0;
	escriurePillades();
}

void seleccionarCartaPila(int pila,int x,int y){
	int i=0,u=0,i2=0,surt=0,e=0;
	//printf("(%d)",iPila[pila]);getch();
	if(iPila[pila]==0&&y>12&&y<22&&seleccionades==1){
		//printf("ultima carta");getch();
		selec[1].lloc=PILAS;
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
				if(pilas[pila].cartes[i].destapada==1){
					if(pilas[pila].cartes[i].seleccionada==1){
						pilas[pila].cartes[i].seleccionada=0;
						//c_seleccionades[seleccionades-1].nombre=BUIT;
						seleccionades--;
						/*for(e=i;e!=iPila[pila];e++){
							pilas[pila].cartes[e].seleccionada=0;
						}*/
						desseleccionarPila(pila);
					}
					else{
						pilas[pila].cartes[i].seleccionada=1;
						//c_seleccionades[seleccionades-1]=pilas[pila].cartes[i];
						seleccionades++;
						for(e=i;e!=iPila[pila];e++){
							pilas[pila].cartes[e].seleccionada=1;
						}
						
					}
					if(seleccionades==1){
						selec[0].lloc=PILAS;
						selec[0].i=pila;
						selec[0].u=i;
						//escriureTauler();
					}
					else if(seleccionades==2){
						selec[1].lloc=PILAS;
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
	int i=-1,u=0,i2=0,surt=0,e=0,pila=0;  ///erroor al pillar cartes
	if(x>=70&&y>=10&&x<=72&&y<=12){
		reiniciar=1;
	}
	//mirem si clica per pillar cartes
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
		if(cartes_pillades[pillarAct].nombre==1){
			cartes_pillades[pillarAct].seleccionada=0;

			u=buscarCartaXPillar(cartes_pillades[pillarAct]);
			qtA[pila]++;
			pilaA[pila].cartes[qtA[pila]]=cartes_pillades[pillarAct];
			
			baralla.cartes[u].nombre=BUIT;
			cartes_pillades[pillarAct].nombre=BUIT;
			
			//pilaA[pila].cartes[qtA[pila]].destapada=1;

			//printf("%d",pilaA[pila].cartes[qtA[pila]+1].nombre);getch();
			//printf("%d",cResta);getch();
			//cResta++;
			iPillar--;
			seleccionades=0;
			selec[0].lloc=BUIT;
			selec[1].lloc=BUIT;

			//escriureTauler();
		}
		else{
			cartes_pillades[pillarAct].seleccionada=0;
			seleccionades=0;
		}
	}
	else if(cartes_pillades[pillarAct].nombre-1==pilaA[pila].cartes[qtA[pila]].nombre&&cartes_pillades[pillarAct].pal==pilaA[pila].cartes[qtA[pila]].pal){
		//printf("no A");getch();
		cartes_pillades[pillarAct].seleccionada=0;
		qtA[pila]++;
		pilaA[pila].cartes[qtA[pila]].seleccionada=0;
		pilaA[pila].cartes[qtA[pila]]=cartes_pillades[pillarAct];
		u=buscarCartaXPillar(cartes_pillades[pillarAct]);
		
		baralla.cartes[u].nombre=BUIT;
		cartes_pillades[pillarAct].nombre=BUIT;
		//cResta++;
		iPillar--;
		seleccionades=0;
		selec[0].lloc=BUIT;
		selec[1].lloc=BUIT;
		
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
			selec[1].lloc=ASOS;
			seleccionades++;
		}
	}
	else{
		if(pilaA[pila].cartes[qtA[pila]].seleccionada==0){
			pilaA[pila].cartes[qtA[pila]].seleccionada=1;
			seleccionades++;
		}
		else{
			pilaA[pila].cartes[qtA[pila]].seleccionada=0;
			desseleccionarPilaA(pila);
			seleccionades--;
		}
		if(seleccionades==1){
			selec[0].lloc=ASOS;
			//escriureTauler();
		}
		else {
			selec[1].lloc=ASOS;
		}
	}
	escriureAsos();
}


void seleccionarCartaPillar(int x,int y){
	pillarAct=2;
	while(cartes_pillades[pillarAct].nombre==BUIT){
		pillarAct--;
	}
	/*printf("fuck");getch();
	escriurePillades();
	printf("fuck 22222");getch();*/
	
	
	/*while(pillarAct!=-1&&cartes_pillades[pillarAct].nombre==BUIT){
		pillarAct--;
	}*/
	if(seleccionades==0){
		if(cartes_pillades[pillarAct].seleccionada==0){
			//printf("%d",cartes_pillades[iPillar].nombre);getch();
			cartes_pillades[pillarAct].seleccionada=1;
			//c_seleccionades[seleccionades-1]=cartes_pillades[0];
			seleccionades++;
		}
		if(seleccionades==1){
			selec[0].lloc=PILLAR;
		}
	}
	else{
		if(cartes_pillades[pillarAct].seleccionada==1){
			cartes_pillades[pillarAct].seleccionada=0;
			//c_seleccionades[seleccionades-1].nombre=BUIT;
			seleccionades--;
			desseleccionarPillades();
		}
	}
	//printf("X");getch();
		escriurePillades();
}
int buscarCartaXPillar(Tcarta carta){
	int i=0;
	for(i=0;i!=25;i++){
		//printf("%d-(%d)",baralla.cartes[i].nombre,carta.nombre);getch();
		if(baralla.cartes[i].pal==carta.pal&&baralla.cartes[i].nombre==carta.nombre){
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
	system("cls"); 
	printf("S'ha produit un error contacti amb el creador(Ton Llucià Senserrich)");
}

void moureCartaPillarPila(int i_pila){
	int u;
	//printf("%d",iPila[i_pila]);getch();
	if(iPila[i_pila]==0&&cartes_pillades[pillarAct].nombre==13){
		//printf("baixarOK");getch();
		//pilas[i_pila].cartes[iPila[i_pila]].seleccionada=0;
		cartes_pillades[pillarAct].seleccionada=0;
		pilas[i_pila].cartes[iPila[i_pila]]=cartes_pillades[pillarAct];
		u=buscarCartaXPillar(cartes_pillades[pillarAct]);
		///printf("33");getch();
		pilas[i_pila].cartes[iPila[i_pila]].seleccionada=0;
		baralla.cartes[u].nombre=BUIT;
		cartes_pillades[pillarAct].nombre=BUIT;
		iPila[i_pila]++;
		//pilas[i_pila].cartes[iPila[i_pila]-1].destapada=1;
		//escriureTauler();
	}
 	else if(cartes_pillades[pillarAct].nombre+1==pilas[i_pila].cartes[iPila[i_pila]-1].nombre&&cartes_pillades[pillarAct].color!=pilas[i_pila].cartes[iPila[i_pila]-1].color){
		//printf("RO");getch();
		cartes_pillades[pillarAct].seleccionada=0;
		pilas[i_pila].cartes[iPila[i_pila]]=cartes_pillades[pillarAct];
		pilas[i_pila].cartes[iPila[i_pila]].seleccionada=0;
		pilas[i_pila].cartes[iPila[i_pila]-1].seleccionada=0;
		
		u=buscarCartaXPillar(cartes_pillades[pillarAct]);

		baralla.cartes[u].nombre=BUIT;
		cartes_pillades[pillarAct].nombre=BUIT;
		//compactarBaralla();
		//qt_pillades--;
		//cResta++;
		iPillar--;
		iPila[i_pila]++;
		seleccionades=0;
		selec[0].lloc=BUIT;
		selec[1].lloc=BUIT;

		//escriureTauler();
 	}
	else{
		pilas[i_pila].cartes[iPila[i_pila]-1].seleccionada=0;
		cartes_pillades[iPillar].seleccionada=0;
		seleccionades=0;
		selec[0].lloc=BUIT;
		selec[1].lloc=BUIT;
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
	if(iPila[pila2]==0&&pilas[pila1].cartes[i1].nombre==13){
		//pilas[pila2].cartes[iPila[pila2]+1].seleccionada=0;
		for(i=i1;i!=iPila[pila1];i++){
			pilas[pila1].cartes[i].seleccionada=0;
			pilas[pila2].cartes[iPila[pila2]]=pilas[pila1].cartes[i];
			pilas[pila1].cartes[i].nombre=BUIT;
			iPila[pila2]++;
			u++;
			//iPila[pila1]--;
		}
		iPila[pila1]=iPila[pila1]-u;
		pilas[pila1].cartes[iPila[pila1]-1].destapada=1;
		for(i=0;i!=iPila[pila2];i++){
			pilas[pila2].cartes[i].seleccionada=0;
		}
	}
	else if(pilas[pila1].cartes[i1].nombre==pilas[pila2].cartes[iPila[pila2]-1].nombre-1&&pilas[pila1].cartes[i1].color!=pilas[pila2].cartes[iPila[pila2]-1].color){
		pilas[pila2].cartes[iPila[pila2]-1].seleccionada=0;
		for(i=i1;i!=iPila[pila1];i++){
			pilas[pila2].cartes[iPila[pila2]]=pilas[pila1].cartes[i];
			pilas[pila2].cartes[iPila[pila2]].seleccionada=0;
			pilas[pila1].cartes[i].nombre=BUIT;
			iPila[pila2]++;
			u++;
			//iPila[pila1]--;
		}
			iPila[pila1]=iPila[pila1]-u;
			pilas[pila1].cartes[iPila[pila1]-1].destapada=1;
	}
	else{
		pilas[pila2].cartes[iPila[pila2]-1].seleccionada=0;
		pilas[pila1].cartes[i1].seleccionada=0;
		for(i=i1;i!=iPila[pila1];i++){
			pilas[pila1].cartes[i].seleccionada=0;
		}
	}
	seleccionades=0;
	selec[0].lloc=BUIT;
	selec[1].lloc=BUIT;
	//escriureTauler();
	desseleccionarPila(pila1);
	desseleccionarPila(pila2);
	escriurePila(pila1);
	escriurePila(pila2);
}

void moureCartaPilaAsos(i_pila,pila,pila_a){
	int i;
	//printf("%d (%d)",i_pila,iPila[pila]);getch();
	if((pilas[pila].cartes[i_pila].nombre-1==pilaA[pila_a].cartes[qtA[pila_a]].nombre&&pilas[pila].cartes[i_pila].pal==pilaA[pila_a].cartes[qtA[pila_a]].pal||pilas[pila].cartes[i_pila].nombre==1)&&i_pila==iPila[pila]-1){
		//printf("GET");getch();
		pilas[pila].cartes[i_pila].seleccionada=0;
		pilaA[pila_a].cartes[qtA[pila_a]+1]=pilas[pila].cartes[i_pila];
		pilas[pila].cartes[i_pila].nombre==BUIT;
		iPila[pila]--;
		qtA[pila_a]++;
		if(pilas[pila].cartes[iPila[pila]-1].destapada==0){
			pilas[pila].cartes[iPila[pila]-1].destapada=1;
		}
	}
	else{
		for(i=i_pila;i!=iPila[pila];i++){
			pilas[pila].cartes[i].seleccionada=0;
		}
		pilaA[pila_a].cartes[qtA[pila_a]].seleccionada=0;
	}
	seleccionades=0;
	selec[0].lloc=BUIT;
	selec[1].lloc=BUIT;
	desseleccionarPila(pila);
	desseleccionarPilaA(pila_a);
	escriurePila(pila);
	escriureAsos();
	//escriureTauler();
}

void moureCartaAsosPila(int pila_a,int pila){       //error al baixar cartes de asos
			//printf("(%d)(%d)",pilaA[pila_a].cartes[qtA[pila_a]].nombre,pilas[pila].cartes[iPila[pila]-1].nombre);getch();
	if((pilas[pila].cartes[iPila[pila]-1].nombre==pilaA[pila_a].cartes[qtA[pila_a]].nombre+1&&pilas[pila].cartes[iPila[pila]-1].color!=pilaA[pila_a].cartes[qtA[pila_a]].color)||(iPila[pila]==0&&pilaA[pila_a].cartes[qtA[pila_a]].nombre==13)){
		//printf("pas2");getch();
		pilas[pila].cartes[iPila[pila]-1].seleccionada=0;
		pilas[pila].cartes[iPila[pila]].seleccionada=0;
		pilas[pila].cartes[iPila[pila]]=pilaA[pila_a].cartes[qtA[pila_a]];
		pilaA[pila_a].cartes[qtA[pila_a]].nombre=BUIT;
		//escriureAsos();
		qtA[pila_a]--;
		iPila[pila]++;
	}
	pilas[pila].cartes[iPila[pila]].seleccionada=0;
	//pilas[pila].cartes[iPila[pila]-2].seleccionada=0;
	selec[0].lloc=BUIT;
	selec[1].lloc=BUIT;
	//escriureTauler();
	desseleccionarPila(pila);
	desseleccionarPilaA(pila_a);
	escriurePila(pila);
	escriureAsos();
}

void moure(){
		//printf("VV");getch();
	if(selec[0].lloc==PILAS&&selec[1].lloc==PILAS){
		moureCartaPilaPila(selec[0].i,selec[0].u,selec[1].i);
	}
	else if(selec[0].lloc==PILLAR&&selec[1].lloc==PILAS){
		moureCartaPillarPila(selec[1].i);
	}
	else if(selec[0].lloc==PILLAR&&selec[1].lloc==ASOS){
		moureCartaPillarAsos(selec[1].u);
	}
	else if(selec[0].lloc==PILAS&&selec[1].lloc==ASOS){
		moureCartaPilaAsos(selec[0].u,selec[0].i,selec[1].u);
	}
	else if(selec[0].lloc==ASOS&&selec[1].lloc==PILAS){
		moureCartaAsosPila(selec[0].u,selec[1].i);
	}
}
void desseleccionarBaralla(){
	int i;
	for(i=0;i!=25;i++){//desseleccionar cartes baralla
		baralla.cartes[i].seleccionada=0;
	}
}
void desseleccionarPila(int pila){
	int i;
	for(i=0;i!=MAX_CARTES/*iPila[pila]+1*/;i++){
		pilas[pila].cartes[i].seleccionada=0;
	}
	//escriurePila(pila);
}
void desseleccionarPilaA(int pila){
	int i;
	for(i=0;i!=qtA[pila]+1;i++){
		pilaA[pila].cartes[i].seleccionada=0;
	}
	//escriureAsos();
}

void desseleccionarPillades(){
	cartes_pillades[0].seleccionada=0;
	cartes_pillades[1].seleccionada=0;
	cartes_pillades[2].seleccionada=0;
	//escriurePillades();
}

void guanyat(){
	int i;
	system("MODE CON COLS=90 LINES=160");
	textbackground(15);
	for(i=0;i!=6;i++){
		system("cls");
		//printf("%d(%d)",i,i%2);
		dimoni(50,20,i);
		if((i%2)!=0)hgotoxy(33,32);else hgotoxy(37,32);
		printf("Nanu ets un CRACK");
		sleep(1);
		//getch();
	}
	for(i=33;i!=0;i--){
		hgotoxy(i,32);
		textcolor((rand()%14)+1);
		printf("Nanu ets un CRACK");
		sleep(1);
		hgotoxy(i,32);
		printf("                 ");
		i--;i--;
	}
	for(i=1;i!=34;i++){
		hgotoxy(i-3,32);
		printf("                 ");
		hgotoxy(i,32);
		textcolor((rand()%14)+1);
		printf("Nanu ets un CRACK");
		sleep(1);
		i++;i++;
	}
}

void main(){
	int i,i2;
	int x_click,y_click;
	
	HANDLE hStdin; 
	DWORD fdwMode;	
	
	hStdin = GetStdHandle(STD_INPUT_HANDLE); 
	fdwMode =  ENABLE_MOUSE_INPUT; 
	SetConsoleMode(hStdin, fdwMode);
	
	system("MODE CON COLS=80 LINES=160");//getch();
	gotoxy(1,1);
	SetConsoleTitleA("SOLITARI");
	_setcursortype(_NOCURSOR);
	
	maximitzar_finestra();
//	guanyat();getch();
	//getch();
	
	do{
		qtA[0]=0;qtA[1]=0;qtA[2]=0;qtA[3]=0;
		iPila[0]=0;iPila[1]=0;iPila[2]=0;iPila[3]=0;iPila[4]=0;iPila[5]=0;iPila[6]=0;
		i_pillades=0;iPillar=-1;qt_pillades=24;seleccionades=0;pillarAct=2;pillarEnrrere=0;reiniciar=0;
		//cResta=1;
		
		reiniciar=0;
		srand(time(NULL));
		textbackground(15);
		system("cls");
		Tcarta cartes[MAX_CARTES];
		Tcarta cartes_barrejades[MAX_CARTES];

		inicialitzarTaules();

		barrejarCartes();
		dibuixarTauler();
		iniciarTauler(pilas);
		while(fiPartida()==0&&reiniciar!=1){
			seleccionades=0;
			selec[0].lloc=BUIT;
			selec[1].lloc=BUIT;
			//desseleccionarPillades();//desseleccionar les cartes per pillar
			desseleccionarBaralla();//desseleccionar cartes baralla
			for(i=0;i!=7;i++){//desseleccionar cartes pila
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
			system("cls");
			reiniciar=0;
			guanyat();
			getch();
			//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n            creador ---> Ton Llucià Senserrich ");getch();
		}
	}while(reiniciar==1);
}
//////////////////////////////////
//-baixar una carta dels asos que es del mateix color
//-al baixar una carta de les pillades no escriu el tauler
//-pots seleccionar els les pillades com a 2a seleccio

