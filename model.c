#include "model.h"
#include "graphics.h"
bool has_next(const t_card *card){
	if(card->next==NULL)
		return false;
	return true;
}
void reset_cardsxy(t_stack *stack){
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
int move_card(t_stack *dest,t_card *card){
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
void set_cardxy(const t_stack *stack,t_card* card){
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
int add_card_ref(t_stack *stack,t_card *card){
	if(stack->last!=NULL){
		card->past=stack->last;
		(stack->last)->next=card;
	}
	if((stack->length)==0){
		stack->first=card;
	}
	card->next=NULL;
	set_cardxy(stack,card);
	stack->last=card;

	if(stack->orientation==VERTICAL)
		stack->y1=stack->last->y+CARD_HEIGHT-1;
	if(stack->orientation==HORIZONTAL)
		stack->x1=stack->last->x+CARD_WIDTH-1;
	stack->length++;
}
int add_card(t_stack *stack,t_card mcard){
	t_card *card=malloc(sizeof(t_card));
	set_cardxy(stack,card);
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
t_card* search_card(const t_stack stack,const int x,const int y){
	
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
void _init_stack(t_stack *stack,int x,int y,int orientation,bool has_border,bool is_expanded,void *func){
	stack->first=NULL;
	stack->last=NULL;
	(stack->length)=0;
	stack->has_border=true;
	stack->is_expanded=true;
	//stack->
}