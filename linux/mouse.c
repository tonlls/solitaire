#ifndef _MOUSE_C_
#define _MOUSE_C_

#include <curses.h>
#include "./mouse.h"
void start(int *x,int *y){
	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	while(1){ 
		int c = wgetch(stdscr);
		if (c == KEY_MOUSE) {
			MEVENT event;
			if (getmouse(&event) == OK) {
				(*x)=event.x;
				(*y)=event.y;
				break;
			}
		}
	}
}
#endif