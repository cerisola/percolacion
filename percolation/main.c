/* headers */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* auxiliary functions declarations */
char * allocate_lattice(int rows, int columns);

void populate_lattice(double probability, char * lattice, int rows, int columns);

void print_lattice(char * lattice, int rows, int columns, int with_borders);

/* main body function */
int main()
{
    int L; /* square lattice size */
    double p; /* occupation probability of each lattice site */
    char *lattice; /* lattice array */

    /* initialize random number generator seed */
    srand(time(NULL));

    /* allocate lattice */
    L = 10;
    lattice = allocate_lattice(L, L);

    /* populate lattice with given probability */
    p = 0.4;
    populate_lattice(p, lattice, L, L);

    /* print the generated lattice for visualization */
    print_lattice(lattice, L, L, 1);

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

void print_lattice(char * lattice, int rows, int columns, int with_borders)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        if (with_borders) {
            for (j = 0; j < columns; j++) {
                printf("----");
            }
            printf("-\n");
        }
        for (j = 0; j < columns; j++) {
            if (with_borders) {
                putchar('|');
                putchar(' ');
            }
            if (lattice[i + j*rows] == 1) {
                putchar('x');
            } else {
                if (with_borders) {
                    putchar(' ');
                } else {
                    putchar('o');
                }
            }
            if (with_borders) {
                putchar(' ');
                if (j == columns - 1) {
                    putchar('|');
                }
            } else {
                if (j < columns - 1) {
                    putchar(' ');
                }
            }
        }
        putchar('\n');
    }
    if (with_borders) {
        for (j = 0; j < columns; j++) {
            printf("----");
        }
        printf("-\n");
    }
}
