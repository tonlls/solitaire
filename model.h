#ifndef _MODEL_H_
#define _MODEL_H_

#include <stdbool.h>
#include "graphics.h"
//struct t_stack;

#define SPADE "♠"
#define CLUB "♣"
#define HEART "♥"
#define DIAMOND "♦"

#define MAX_CARDS 52
#define ACE_STACKS 4
#define GAME_STACKS 7
#define SWAP_STACKS 1

#define HORIZONTAL 1
#define VERTICAL 2

#define CARD_WIDTH 8
#define CARD_HEIGHT 7
#define CARD_COVERED_WIDTH 2
#define CARD_COVERED_HEIGHT 2
#define STACK_BORDER_WIDTH 10
#define STACK_BORDER_HEIGHT 9


typedef struct T_card{
	int x;
	int y;
	struct T_card *next;
	struct T_card *past;
	char* number;
	char* suit;
	int color;
	bool selected;
	bool covered;
	bool scrambled;
}t_card;

typedef struct T_deck{
	t_card *cards[MAX_CARDS];
	int length;
}t_deck;

typedef struct T_stack{
	int x0;
	int x1;
	int y0;
	int y1;
	t_card *first;
	t_card *last;
	int length;
	short orientation;
	bool has_border;
	bool is_expanded;
	void (*on_click)(int x,int y);
}t_stack;

typedef struct T_game{
	t_stack aces_stacks[ACE_STACKS];
	t_stack game_stacks[GAME_STACKS];
	t_deck main_deck;
}t_game;

void init_main_deck(t_deck*);
void shuffle_deck(t_deck*);
#endif