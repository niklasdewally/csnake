compile: csnake.h main.c draw.c
	gcc -o csnake.out main.c draw.c csnake.h -lncurses
