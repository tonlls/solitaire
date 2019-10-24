#include <curses.h>

void start(int *x,int *y){
	keypad(stdscr, TRUE);
	// Don't mask any mouse events
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	while(1){ 
		int c = wgetch(stdscr);
		if (c == KEY_MOUSE) {
			MEVENT event;
			if (getmouse(&event) == OK) {
				//snprintf(buffer, max_size, "Mouse at row=%d, column=%d bstate=0x%08lx",event.y, event.x, event.bstate);
				(*x)=event.x;
				(*y)=event.y;
				break;
			}
		}
	}
}