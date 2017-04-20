/* Copyright 2017 Federico Cerisola */
/* MIT License (see root directory) */

/* headers */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "random.h"
#include "math_extra.h"
#include "lattice.h"
#include "clusters.h"
#include "io_helpers.h"

/* return std factor to reach desired confidence interval (specified as a string)
    for a normal distribution */
double Z_normal(const char * ci);

/* calculate the amount of experiments needed to reach the desired error */
unsigned int samples_for_target_ci(double p, double error, double Z);

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
    int min_repetitions; /* minimum number repetitions to take for each probability */
    int nrepetitions; /* the number of repetitions to take for each probability */
    double target_error; /* the target error in each probability estimation */
    char * ci; /* confidence interval */
    double Z; /* ci costant factor */
    time_t maxtime; /* maximum time to spend on a particular probability */
    int * percolation_counts; /* how many times a given population probability generates a percolating cluster */
    int * nrepetitions_final; /* the final amount of repetitions for each probability */
    int output_interval;
    int time_check_interval;
    time_t start_time;
    time_t current_time;
    double probability_estimation;
    int n;
    int i;
    int j;

    /* read input arguments; if none provided fallback to default values */
    if (argc < 9) {
        printf("usage: L ngrid pcenter decay mintrials error ci maxtime (seed)\n");
        return 1;
    }
    L = atoi(argv[1]);
    N = atoi(argv[2]);
    probability_center = atof(argv[3]);
    decay = atof(argv[4]);
    min_repetitions = atoi(argv[5]);
    target_error = atof(argv[6]);
    ci = argv[7];
    printf("ci = %s\n", ci);
    Z = Z_normal(ci);
    maxtime = atol(argv[8]);
    if (argc == 10) {
        random_seed = atoi(argv[9]);
    } else {
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
    nrepetitions_final = (int *)malloc(N*sizeof(int));
    for (i = 0; i < N; i++) {
        percolation_counts[i] = 0;
        nrepetitions_final[i] = 0;
    }

    output_interval = N / 10;

    srand_pcg(random_seed);

    /* allocate lattice */
    lattice = allocate_lattice(L, L, 0);

    /* calculate cluster statistics per probability */
    for (i = 0; i < N; i++) {
        start_time = time(NULL);
        nrepetitions = min_repetitions;
        time_check_interval = nrepetitions / 100;
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

            if (n == nrepetitions - 1) {
                probability_estimation = ((double)percolation_counts[i])/nrepetitions;
                nrepetitions = samples_for_target_ci(probability_estimation, target_error, Z);
                nrepetitions = nrepetitions > min_repetitions ? nrepetitions : min_repetitions;
                time_check_interval = nrepetitions / 100;
                printf("adjusting repetitions to %d for i = %d with p = %3f using Z = %f\n",
                       nrepetitions, i, probability_estimation, Z);
            }

            if ((n+1) % time_check_interval == 0) {
                current_time = time(NULL);
                if (current_time - start_time > maxtime) {
                    printf("aborting due to excess time ...\n");
                    nrepetitions = n+1;
                    break;
                }
            }
        }

        nrepetitions_final[i] = nrepetitions;

        write_probability_sweep_cluster_statistics_to_file("print/data",
                                                            cluster_sizes_aggregated,
                                                            cluster_sizes_counts_aggregated,
                                                            cluster_sizes_percolated_aggregated,
                                                            cluster_sizes_total_count_aggregated,
                                                            L, L, probability_grid[i],
                                                            random_seed,
                                                            nrepetitions, N,
                                                            probability_center,
                                                            decay);

        free(cluster_sizes_aggregated);
        free(cluster_sizes_counts_aggregated);
        free(cluster_sizes_percolated_aggregated);
        cluster_sizes_total_count_aggregated = 0;

        /* print progress to stdout */
        if ((i+1) % output_interval == 0) {
            printf("finished with p_%d out of %d\n", i+1, N);
        }
    }

    write_probability_sweep_percolation_probability("print/data", probability_grid,
                                                    percolation_counts, N,
                                                    probability_center, decay,
                                                    nrepetitions_final, L, L, random_seed);

    /* free memory before leaving */
    free(lattice);
    free(probability_grid);
    free(percolation_counts);
    free(nrepetitions_final);

    return 0;
}

double Z_normal(const char * ci)
{
    if (strcmp(ci, "90.00") == 0) {
        return 1.644854;
    } else if (strcmp(ci, "95.00") == 0) {
        return 1.959964;
    } else if (strcmp(ci, "99.00") == 0) {
        return 2.575829;
    } else if (strcmp(ci, "99.90") == 0) {
        return 3.290527;
    } else if (strcmp(ci, "99.99") == 0) {
        return 3.890592;
    }
    return 3.890592;
}

unsigned int samples_for_target_ci(double p, double error, double Z)
{
    return (Z*Z)*p*(1-p)/(error*error);
}
