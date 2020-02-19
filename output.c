#ifndef _OUTPUT_C_
#define _OUTPUT_C_

#include <string.h>
#include "output.h"
#include "graphics.h"
void draw_card(const t_card card){
	int x=card.x;
	int y=card.y;
	color(card.color);
	clear_space(x+1,y+1,x+CARD_WIDTH-1,y+CARD_HEIGHT-1);
	if(!card.covered){
		hgotoxy(x+1,y+1);
		print("%s",card.number);
		hgotoxy(x+CARD_WIDTH-2,y+1);
		print("%s",card.suit);
		hgotoxy(x+1,y+CARD_HEIGHT-2);
		print("%s",card.suit);
		hgotoxy(x+CARD_WIDTH-1-strlen(card.number),y+CARD_HEIGHT-2);
		print("%s",card.number);
	}
	if(card.selected)
		color(RED_PAIR);
	else
		color(BLACK_PAIR);
	draw_square(card.x,card.y,CARD_HEIGHT,CARD_WIDTH);
	color(BLACK_PAIR); 
}

void draw_stack(const t_stack *stack){
	t_card *card=(stack->first);
	if(stack->has_border)
		draw_square(stack->x0,stack->y0,STACK_BORDER_HEIGHT,STACK_BORDER_WIDTH);
	if(!stack->is_expanded)
		draw_card(*(*stack).last);
	else{
		while(card!=NULL){
			draw_card(*card);
			card=card->next;
		}
	}	
}
void draw_board(){
	//Aces
	draw_square(1,1,CARD_HEIGHT+2,CARD_WIDTH+2);
	draw_square(11,1,CARD_HEIGHT+2,CARD_WIDTH+2);
	draw_square(21,1,CARD_HEIGHT+2,CARD_WIDTH+2);
	draw_square(31,1,CARD_HEIGHT+2,CARD_WIDTH+2);
	
	//Game
	draw_square(1,12,CARD_HEIGHT+2,CARD_WIDTH+2);
	draw_square(11,12,CARD_HEIGHT+2,CARD_WIDTH+2);
	draw_square(21,12,CARD_HEIGHT+2,CARD_WIDTH+2);
	draw_square(31,12,CARD_HEIGHT+2,CARD_WIDTH+2);
	draw_square(41,12,CARD_HEIGHT+2,CARD_WIDTH+2);
	draw_square(51,12,CARD_HEIGHT+2,CARD_WIDTH+2);
	draw_square(61,12,CARD_HEIGHT+2,CARD_WIDTH+2);
	
	//Deck
	draw_square(71,1,CARD_HEIGHT+2,CARD_WIDTH+2);

	//reset
	draw_square(82,4,3,3);
	hgotoxy(83,5);
	print("R");
}
#endif