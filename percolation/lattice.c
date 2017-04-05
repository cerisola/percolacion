#include "lattice.h"
#include <stdlib.h>

char * allocate_lattice(int rows, int columns)
{
    char *lattice;
    int i, j;

    lattice = (char *) malloc(rows*columns*sizeof(char));
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            lattice[i*columns + j] = 0;
        }
    }

    return lattice;
}

void populate_lattice(double probability, char * lattice, int rows, int columns)
{
    int i, j;
    double q;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            q = ((double)rand())/RAND_MAX;
            if (q <= probability) {
                lattice[i*columns + j] = 1;
            }
        }
    }

    return;
}
