# compilateur 
CC=gcc
# option
CFLAGS= -g -Wall -Wextra  -I/opt/homebrew/Cellar/sdl2/2.0.22/include
LDFLAGS= -lSDL2  -L/opt/homebrew/Cellar/sdl2/2.0.22/lib

# règle de production finale du TP 
prog:main.o
	@$(CC) main.o -o prog  $(LDFLAGS)
# règles de production pour chaque fichier
main.o:main.c
	@$(CC) -c main.c $(CFLAGS)

# règle qui efface l'exécutable et les fichiers objets
clean:
	@rm -rf prog main.o 