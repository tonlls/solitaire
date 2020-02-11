#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include <stdarg.h>

#if defined(_WIN32) || defined(__MSDOS__)
	#include "windows/graphics_win.h"
#else
	#include "linux/graphics_linux.h"
#endif

void init_screen();
void end_screen();

int print(const char*,...);
void hgotoxy(int,int);
void color(int);

void draw_square(int,int,int,int);
void draw_horizontal_line(int,int,int);
void draw_vertical_line(int,int,int);
void clear_space(int,int,int,int);

#endif