#include "graphics.h"
#include "model.h"
#include "output.h"
void main(){

	//test();
	init_screen();
	t_card c;
	t_stack s,ss;
	c.color=RED_PAIR;
	c.number="K";
	c.suit=SPADE;
	c.x=c.y=10;
	c.selected=false;
	c.covered=false;
	init_stack(&s,10,10,VERTICAL,true,true);
	init_stack(&ss,15,10,VERTICAL,true,true);
	add_card(&s,c);
	draw_stack(&s);
	getch();
	add_card(&s,c);
	draw_card(c);
	draw_stack(&s);
	getch();
	end_screen();
}