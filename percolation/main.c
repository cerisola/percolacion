/* headers */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* auxiliary functions declarations */
char * allocate_lattice(int rows, int columns);

void populate_lattice(double probability, char * lattice, int rows, int columns);

void print_lattice(char * lattice, int rows, int columns);

/* main body function */
int main()
{
    int L; /* square lattice size */
    double p; /* occupation probability of each lattice site */

    /* initialize random number generator seed */
    srand(time(NULL));

    /* allocate lattice */
    L = 10;
    char *lattice = allocate_lattice(L, L);

    /* populate lattice with given probability */
    p = 0.4;
    populate_lattice(p, lattice, L, L);

    /* print the generated lattice for visualization */
    print_lattice(lattice, L, L);

    /* free memory before leaving */
    free(lattice);

    return 0;
}

/* auxiliary functions definitions */
char * allocate_lattice(int rows, int columns)
{
    char *lattice;
    int i, j;

    lattice = (char *) malloc(rows*columns*sizeof(char));
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            lattice[i + j*rows] = 0;
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
                lattice[i + j*rows] = 1;
            }
        }
    }

    return;
}

void print_lattice(char * lattice, int rows, int columns)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            if (lattice[i + j*rows] == 1) {
                putchar('x');
            } else {
                putchar('o');
            }
            if (j < columns - 1) {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}
