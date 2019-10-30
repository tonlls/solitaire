CC = gcc
out = solitaire
default: solitaire.c
	$(CC) -o $(out) solitaire.c -lncursesw
clean:
	rm $(out)
