compile: csnake.h main.c draw.c logic.c
	gcc -o csnake.out main.c draw.c logic.c csnake.h -lncurses
