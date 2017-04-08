#include "lattice.h"
#include <stdlib.h>

int * allocate_lattice(int rows, int columns, int initialize)
{
    int *lattice;
    int i;

    lattice = (int *) malloc(rows*columns*sizeof(int));

    if (!initialize) {
        return lattice;
    }

    for (i = 0; i < rows*columns; i++) {
        lattice[i] = 0;
    }

    return lattice;
}

void populate_lattice(double probability, int * lattice, int rows, int columns,
                      unsigned int seed)
{
    int i;
    double q;

    if (seed > 0) {
        srand(seed);
    }

    for (i = 0; i < rows*columns; i++) {
        q = ((double)rand())/RAND_MAX;
        if (q <= probability) {
            lattice[i] = 1;
        } else {
            lattice[i] = 0;
        }
    }

    return;
}
