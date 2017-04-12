/* headers */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#include "lattice.h"
#include "clusters.h"
#include "io_helpers.h"

/* main body function */
int main(int argc, char ** argv)
{
    int i;
    int n;
    int L; /* square lattice size */
    int N; /* number of trials */
    int precision; /* minimum step in the probability when searching is 1/2**precision */
    unsigned int random_seed; /* random number generator seed */
    double p_critical; /* estimated critical probability */
    double p; /* occupation probability of each lattice site */
    int * lattice; /* lattice array */
    char percolated; /* whether the lattice has percolated */

    /* read input arguments; if none provided fallback to default values */
    if (argc == 4 || argc == 5) {
        L = atoi(argv[1]);
        N = atoi(argv[2]);
        precision = atoi(argv[3]);
        if (argc == 5) {
            random_seed = atoi(argv[4]);
        } else {
            random_seed = (unsigned int)time(NULL);
        }
    } else {
        L = 10;
        N = 50000;
        precision = 16;
        random_seed = (unsigned int)time(NULL);
    }

    /* initialilze variable values */
    p_critical = 0;

    /* allocate lattice without initializing its values */
    lattice = allocate_lattice(L, L, 0);

    /* initialzie RNG seed */
    srand(random_seed);

    /* search critical point */
    for (n = 0; n < N; n++) {
        p = 0.5;

        for (i = 2; i <= precision; i++) {
            populate_lattice(p, lattice, L, L, 0);
            label_clusters(lattice, L, L);
            percolated = has_percolating_cluster(lattice, L, L);
            if (percolated) {
                p = p - 1.0/pow(2, i);
            } else {
                p = p + 1.0/pow(2, i);
            }
        }

        p_critical += p;

        /* progress report to stdout */
        if ((n+1) % 100 == 0) {
            printf("finished iter %d/%d\n", n+1, N);
        }
    }

    p_critical = p_critical / N;

    /* return estimated value */
    printf("p critical: %f\n", p_critical);
}
