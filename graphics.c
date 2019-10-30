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
void draw_sqare(int x,int y,int heith,int widht){
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
void draw_card(const t_card *card){
	int x=card->x;
	int y=card->y;
	color(card->color);
	clear_space(x+1,y+1,x+CARD_WIDTH-1,y+CARD_HEIGHT-1);
	if(!card->covered){
		hgotoxy(x+1,y+1);
		print("%s",card->number);
		hgotoxy(x+CARD_WIDTH-2,y+1);
		print("%s",card->suit);
		hgotoxy(x+1,y+CARD_HEIGHT-2);
		print("%s",card->suit);
		hgotoxy(x+CARD_WIDTH-1-strlen(card->number),y+CARD_HEIGHT-2);
		print("%s",card->number);
	}
	if(card->selected)
		color(RED_PAIR);
	else
		color(BLACK_PAIR);
	draw_sqare(card->x,card->y,CARD_HEIGHT,CARD_WIDTH);
	color(BLACK_PAIR);
}

void draw_stack(const t_stack *stack){
	t_card *card=(stack->first);
	if(stack->has_border)
		draw_sqare(stack->x0,stack->y0,STACK_BORDER_HEIGHT,STACK_BORDER_WIDTH);
	if(!stack->is_expanded)
		draw_card(stack->last);
	else{
		while(card!=NULL){
			draw_card(card);
			card=card->next;
		}
	}	
}

