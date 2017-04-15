/* Copyright 2017 Federico Cerisola */
/* MIT License (see root directory) */

/* headers */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "random.h"
#include "math_extra.h"
#include "lattice.h"
#include "clusters.h"
#include "io_helpers.h"

/* main body function */
int main(int argc, char ** argv)
{
    int L; /* square lattice size */
    int * lattice; /* lattice array */
    unsigned int random_seed; /* random number generator seed */
    int cluster_sizes_total_count; /* total number of different cluster sizes, for a given probability */
    int * cluster_sizes; /* sizes of clusters, for a given probability */
    int * cluster_sizes_counts; /* count of clusters of a given size (paied in cluster_sizes), for a given probability */
    int * cluster_sizes_percolated; /* how many percolating clusters of each size there are, for a given probability */
    int cluster_sizes_total_count_aggregated; /* total number of different cluster sizes, aggregated over the sweep */
    int * cluster_sizes_aggregated; /* sizes of clusters, aggregated over the sweep */
    int * cluster_sizes_counts_aggregated; /* count of clusters of a given size (paied in cluster_sizes), aggregated over the sweep */
    int * cluster_sizes_percolated_aggregated; /* how many percolating clusters of each size there are, aggregated over the sweep */
    int N; /* number of discrete probability value to tests */
    double probability_center; /* value where to center the discrete probability values grid */
    double decay; /* exponential decay coefficient of the probability grid */
    double * probability_grid; /* discrete grid of probability values to test */
    int nrepetitions; /* how many repetitions to take for each probability */
    int * percolation_counts; /* how many times a given population probability generates a percolating cluster */
    int n;
    int i;
    int j;

    /* read input arguments; if none provided fallback to default values */
    if (argc == 6 || argc == 7) {
        L = atoi(argv[1]);
        N = atoi(argv[2]);
        probability_center = atof(argv[3]);
        decay = atof(argv[4]);
        nrepetitions = atoi(argv[5]);
        if (argc == 7) {
            random_seed = atoi(argv[6]);
        } else {
            random_seed = (unsigned int)time(NULL);
        }
    } else {
        L = 10;
        N = 120;
        probability_center = 0.59;
        decay = 4;
        nrepetitions = 20;
        random_seed = (unsigned int)time(NULL);
    }

    /* initialize remaining variables */
    cluster_sizes_total_count = 0;
    cluster_sizes = NULL;
    cluster_sizes_counts = NULL;
    cluster_sizes_percolated = NULL;
    cluster_sizes_total_count_aggregated = 0;
    cluster_sizes_aggregated = NULL;
    cluster_sizes_counts_aggregated = NULL;
    cluster_sizes_percolated_aggregated = NULL;

    probability_grid = create_exponential_centered_grid(0, 1, probability_center, N, decay);
    percolation_counts = (int *)malloc(N*sizeof(int));
    for (i = 0; i < N; i++) {
        percolation_counts[i] = 0;
    }

    srand_pcg(random_seed);

    /* allocate lattice */
    lattice = allocate_lattice(L, L, 0);

    /* calculate cluster statistics per probability */
    for (i = 0; i < N; i++) {
        for (n = 0; n < nrepetitions; n++) {
            populate_lattice(probability_grid[i], lattice, L, L, 0);
            label_clusters(lattice, L, L);
            cluster_statistics(lattice, L, L, &cluster_sizes_total_count, &cluster_sizes,
                               &cluster_sizes_counts, &cluster_sizes_percolated,
                               NULL, NULL);
            aggregate_cluster_statistics(cluster_sizes_total_count, cluster_sizes,
                                         cluster_sizes_counts, cluster_sizes_percolated,
                                         &cluster_sizes_total_count_aggregated,
                                         &cluster_sizes_aggregated,
                                         &cluster_sizes_counts_aggregated,
                                         &cluster_sizes_percolated_aggregated);

            /* add one if this lattice has a percolating cluster */
            for (j = 0; j < cluster_sizes_total_count; j++) {
                if (cluster_sizes_percolated[j]) {
                    percolation_counts[i] += 1;
                    break;
                }
            }

            free(cluster_sizes);
            free(cluster_sizes_counts);
            free(cluster_sizes_percolated);
            cluster_sizes_total_count = 0;
        }

        if (cluster_sizes_total_count_aggregated > 0) {
            free(cluster_sizes_aggregated);
            free(cluster_sizes_counts_aggregated);
            free(cluster_sizes_percolated_aggregated);
            cluster_sizes_total_count_aggregated = 0;
        }

        /* print progress to stdout */
        if ((i+1) % 20 == 0) {
            printf("finished with p_%d out of %d\n", i+1, N);
        }
    }

    /* free memory before leaving */
    free(lattice);
    free(probability_grid);
    free(percolation_counts);

    return 0;
}
