compile: csnake.h main.c
	gcc -o csnake.out main.c csnake.h -lncurses
