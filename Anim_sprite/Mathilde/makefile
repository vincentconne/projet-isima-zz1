#compilateur
CC=gcc
#option
CFLAGS= -g -Wall -Wextra 
LDFLAGS= -lSDL2 -lSDL2_image

#règle de production finale du TP
prog:main.o
	@$(CC) -o prog main.o $(LDFLAGS)
#règle de production pour chaque fichier
main.o:main.c
	@$(CC) -c main.c $(CFLAGS)

#règle qui efface l'executable et les fichiers objets
clean: 
	@rm -rf prog main.o