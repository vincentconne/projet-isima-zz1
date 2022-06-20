# compilateur 
CC=gcc
# option
CFLAGS= -g -Wall -Wextra
LDFLAGS= -lSDL2 -lm

# règle de production finale du TP 
prog:main.o
	@$(CC) -o prog main.o $(LDFLAGS)
# règles de production pour chaque fichier
main.o:main.c
	@$(CC) -c main.c $(CFLAGS)
# règle qui efface l'exécutable et les fichiers objets
clean:
	@rm -rf prog main.o *.gch







	
