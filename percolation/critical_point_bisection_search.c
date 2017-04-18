/* Copyright 2017 Federico Cerisola */
/* MIT License (see root directory) */

/* headers */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#include "random.h"
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
    double * p_critical; /* estimated critical probabilities */
    double p_critical_average; /* average of the estimated critical probabilities */
    double p; /* occupation probability of each lattice site */
    int * lattice; /* lattice array */
    char percolated; /* whether the lattice has percolated */
    int output_interval;

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
    p_critical = (double *)malloc(N*sizeof(double));
    p_critical_average = 0;

    output_interval = N / 10;

    /* allocate lattice without initializing its values */
    lattice = allocate_lattice(L, L, 0);

    /* initialzie RNG seed */
    srand_pcg(random_seed);

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

        p_critical[n] = p;
        p_critical_average += p;

        /* progress report to stdout */
        if ((n+1) % output_interval == 0) {
            printf("finished iter %d/%d\n", n+1, N);
        }
    }

    p_critical_average = p_critical_average / N;

    /* return estimated value and write results to file */
    printf("p critical average: %f\n", p_critical_average);
    write_critical_point_bisection_search_results("print/data", p_critical, N,
                                                  precision, L, L, 0.5, random_seed);

    /* free memory before leaving */
    free(p_critical);
    free(lattice);

    return 0;
}
