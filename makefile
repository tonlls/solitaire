CC = gcc

default: solitaire.c
	$(CC) -o $(out) solitaire.c output.c -lncursesw

linux:init common _linux clean
windows:init clear common
init:
	mkdir -p dist/linux
	mkdir -p dist/windows

common:
	$(CC) -c -o model.o model.c
	$(CC) -c -o graphics.o graphics.c
	$(CC) -c -o output.o output.c
	$(CC) -c -o solitaire.o solitaire.c

_linux:
	$(CC) -c -o linux/graphics_linux.o linux/graphics_linux.c
	$(CC) -o dist/linux/solitaire model.o linux/graphics_linux.o graphics.o output.o solitaire.o -lncursesw


clear:clean
	$(RM) dist/linux/*
	$(RM) dist/windows/*

clean:
	$(RM) *.o
	$(RM) linux/*.o
	$(RM) windows/*.o