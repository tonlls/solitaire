#ifndef _GRAPHICS_C_
#define _GRAPHICS_C_
#include "graphics.h"
#include <string.h>

void draw_horizontal_line(int x,int y,int length){
	hgotoxy(x,y);
	for(int i=0;i<length;i++){
		print("─");
	}
}
void draw_vertical_line(int x,int y,int length){
	for(int i=0;i<length;i++){
		hgotoxy(x,y+i);
		print("│");
	}
}
void draw_square(int x,int y,int heith,int widht){
	hgotoxy(x,y);
	print("┌");
	draw_horizontal_line(x+1,y,widht-2);
	print("┐");
	draw_vertical_line(x,y+1,heith-2);
	draw_vertical_line(x+widht-1,y+1,heith-2);
	hgotoxy(x,y+heith-1);
	print("└");
	draw_horizontal_line(x+1,y+heith-1,widht-2);
	print("┘");
}
void clear_space(int x1,int y1,int x2,int y2){
	for(int y=0;y<y2-y1;y++){
		hgotoxy(x1,y1+y);
		for(int x=0;x<x2-x1;x++){
			print(" ");
		}
	}
}
#endif