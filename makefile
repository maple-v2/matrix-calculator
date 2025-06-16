
mainmat : mainmat.c mymat.h mymat.c extrafunc.c
	gcc  -Wall -ansi -pedantic mainmat.c mymat.c extrafunc.c -o mainmat
clean : rm*~


