#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jeu.h"

int valeur_random(int MIN, int MAX)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }

    return (rand() % (MAX + 1 - MIN)) + MIN;
}
