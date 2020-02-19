#ifndef _MODEL_C_
#define _MODEL_C_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "model.h"
#include "graphics.h"

#define MAX_CARD 13
#pragma region CARD
void uncover_card(t_card* card){
	card->covered=false;
	//redraw();
}
char* get_number(int number){
	switch (number){
		case 1:return "A";
		case 2:return "2";
		case 3:return "3";
		case 4:return "4";
		case 5:return "5";
		case 6:return "6";
		case 7:return "7";
		case 8:return "8";
		case 9:return "9";
		case 10:return "10";
		case 11:return "J";
		case 12:return "Q";
		case 13:return "K";
	}
	return "?"; 
}
char* get_suit(int suit){
	switch(suit){
		case 1:return SPADE;
		case 2:return CLUB;
		case 3:return HEART;
		case 4:return DIAMOND;
	}
	return "?";
}
int get_color(char* suit){
	if(strcmp(suit,HEART)==0||strcmp(suit,DIAMOND)==0)
		return RED_PAIR;
	else if(strcmp(suit,SPADE)==0||strcmp(suit,CLUB))
		return BLACK_PAIR;
	return -1;
}

void init_card_ref(t_card *card,int number,int suit){
	card->suit=get_suit(suit);
	card->color=get_color(card->suit);
	card->number=get_number(number);
	card->scrambled=false;
	card->covered=true;
	card->next=NULL;
	card->selected=false;
	card->past=NULL;
}

t_card* init_card(int number,int suit){
	t_card *c=malloc(sizeof(t_card));
	init_card_ref(c,number,suit);
	return c;
}
#pragma endregion CARD
#pragma region STACK
void reset_cards_xy(t_stack *stack){
	t_card *card=stack->first;
	int x=stack->x0-2;
	int y=stack->y0-1;
	for(int i=0;i<stack->length;i++){
		if(stack->is_expanded){
			if(stack->orientation==HORIZONTAL){
				card->x=x+i*CARD_COVERED_WIDTH;
				card->y=y;
			}
			else{
				card->x=x;
				card->y=y+i*CARD_COVERED_HEIGHT;
			}
		}
	}
}
t_card* get_card(t_stack stack, int index){
	t_card* current;
	if(stack.length<=0||index>=stack.length)
		return NULL;
	if(index+1==stack.length)
		return stack.last;
	current=stack.first;
	for(int i=0;i<index;i++){
		current=current->next;
	}
	return current;
}
/*
	moves a card wich can have linked cards
*/
int stack_move_card(t_stack *dest,t_card *card){
	t_card *current=card;
	//dest->last
	while(current!=NULL){
		dest->last->next=current;
		current->past=dest->last;
		dest->last=current;
		(dest->length)++;
		current=current->next;
	}
}
void stack_set_card_xy(const t_stack *stack,t_card* card){
	if(stack->length==0){
		card->x=stack->x0+1;
		(card->y)=stack->y0+1;
		return;
	}
	if(stack->orientation==HORIZONTAL){
		card->x=stack->last->x-CARD_COVERED_WIDTH;
		//card->x=stack->x1+CARD_WIDTH-CARD_COVERED_WIDTH;
		(card->y)=stack->y0+1;
	}
	if(stack->orientation==VERTICAL){
		card->x=stack->x0+1;//+CARD_WIDHT-CARD_COVERED_WIDHT;
		//card->y=(stack->y1)+CARD_HEIGHT-CARD_COVERED_HEIGHT;
		card->y=stack->last->y+CARD_COVERED_HEIGHT;
	}
}
int stack_add_card_ref(t_stack *stack,t_card *card){
	if(stack->last!=NULL){
		card->past=stack->last;
		(stack->last)->next=card;
	}
	if((stack->length)==0){
		stack->first=card;
	}
	card->next=NULL;
	stack_set_card_xy(stack,card);
	stack->last=card;

	if(stack->orientation==VERTICAL)
		stack->y1=stack->last->y+CARD_HEIGHT-1;
	if(stack->orientation==HORIZONTAL)
		stack->x1=stack->last->x+CARD_WIDTH-1;
	stack->length++;
}
int stack_add_card(t_stack *stack,t_card mcard){
	t_card *card=malloc(sizeof(t_card));
	stack_set_card_xy(stack,card);
	if(stack->last!=NULL){
		card->past=stack->last;
		(stack->last)->next=card;
	}
	if((stack->length)==0){
		stack->first=card;
	}
	card->next=NULL;
	card->color=mcard.color;
	card->suit=strdup(mcard.suit);
	card->number=strdup(mcard.number);

	stack->last=card;

	if(stack->orientation==VERTICAL)
		stack->y1=stack->last->y+CARD_HEIGHT-1;
	if(stack->orientation==HORIZONTAL)
		stack->x1=stack->last->x+CARD_WIDTH-1;
	stack->length++;
}
t_stack* search_stack(t_stack stacks[],int stacks_length,int x,int y){
	for(int i=0;i<stacks_length;i++){
		if((x>=stacks[i].x0 && x<=stacks[i].x1)&&(y>=stacks[i].y0 && y<=stacks[i].y1))
			return &stacks[i];
	}
	return NULL;
}
t_card* stack_search_card(const t_stack stack,const int x,const int y){
	
}
void _init_stack(t_stack *stack,int x,int y,int orientation,bool has_border,bool is_expanded,void *func){
	stack->first=NULL;
	stack->last=NULL;
	(stack->length)=0;
	stack->has_border=true;
	stack->is_expanded=true;
}
void init_stack(t_stack *stack,int x,int y,int orientation,bool has_border,bool is_expanded){
	stack->first=NULL;
	stack->last=NULL;
	(stack->length)=0;
	stack->x0=x;
	stack->y0=y;
	stack->x1=x+STACK_BORDER_WIDTH-1;
	stack->y1=y+STACK_BORDER_HEIGHT-1;
	stack->orientation=orientation;
	stack->has_border=has_border;
	stack->is_expanded=is_expanded;
}
#pragma endregion STACK

bool has_next(const t_card *card){
	if(card->next==NULL)
		return false;
	return true;
}


//old to refactor
t_card* build_deck_o(){
	int count=0;
	char *card_types[4]={SPADE,DIAMOND,CLUB,HEART};
	t_card **deck=malloc(sizeof(t_card*)*MAX_CARDS);
	t_card *card;
	for(int i=1;i<14;i++){
		for(int j=0;j<4;j++){
			card=malloc(sizeof(t_card));
			init_card_ref(card,i,card_types[j]);
			deck[i]=card;
			i++;
		}
	}
}
/*int deck_len(const t_card* card){
	t_card* c=card;
	int i=0;
	while(c!=NULL){
		c=c->next;
		i++;
	}
	return i;
}*/

#pragma region DECK

void shuffle_deck(t_deck *deck){
	t_card *deck_c[MAX_CARDS]={0};
	int r;
	for(int i=0;i<MAX_CARDS;i++){
		do{
			r=rand()%MAX_CARDS;
		}while(deck_c[r]!=0&&deck_c[r]->scrambled==true);
		deck_c[r]=deck->cards[i];
		deck_c[r]->scrambled=true;
	}
	memcpy(deck->cards,deck_c,MAX_CARDS*sizeof(t_card*));
}

void init_main_deck(t_deck* deck){
	deck->length=0;
	for(int j=1;j<=4;j++){
		for(int i=0;i<MAX_CARD;i++){
			deck->cards[deck->length++]=init_card((i%13)+1,j);
		}
	}
	shuffle_deck(deck);
}
t_card* deck_get_last_card(t_deck* deck){
	return deck->cards[deck->length--];
}
#pragma endregion DECK
void init_game(t_game* game){
	init_main_deck(&(game->main_deck));
	for(int i=0;i<GAME_STACKS;i++){
		for(int j=1;j<=i+j;j++){
			stack_add_card_ref(&game->game_stacks[i],deck_get_last_card(&game->main_deck));
		}
		//uncover_card()
	}
}
#endif