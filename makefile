compile: csnake.h main.c draw.c logic.c
	gcc -o csnake main.c draw.c logic.c csnake.h -lncurses
