all:
	gcc -std=c99  -Wint-to-void-pointer-cast -o prog main.c lazy.c list.c pairs.c
