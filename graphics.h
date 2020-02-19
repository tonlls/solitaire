#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include <stdarg.h>

#if defined(_WIN32) || defined(__MSDOS__)
	#include "windows/graphics.h"
#else
	#include "linux/graphics.h"
#endif

void init_screen();
void end_screen();

int print(const char*,...);
void hgotoxy(int x,int y);
void color(int);

void draw_square(int x,int y,int h,int w);
void draw_horizontal_line(int x,int y,int len);
void draw_vertical_line(int x,int y,int heigth);
void clear_space(int x1,int y1,int x2,int y2);

#endif