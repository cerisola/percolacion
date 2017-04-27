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

/* main body function */
int main(int argc, char ** argv)
{
    int L; /* square lattice size */
    int * lattice; /* lattice array */
    unsigned int random_seed; /* random number generator seed */
    int N; /* number of repetitions */
    double probability; /* occupation probability */
    int percolating_cluster_idx;
    int * window;
    int center;
    int * percolating_cluster_mass;
    int * window_size;
    int window_sizes_count;
    int concentration;
    int output_interval;
    int l;
    int i, j, k, n;

    /* read input arguments; if none provided fallback to default values */
    if (argc < 4) {
        printf("usage: L nrepetitions probability (seed)\n");
        return 1;
    }
    L = atoi(argv[1]);
    N = atoi(argv[2]);
    probability = atof(argv[3]);
    if (argc == 5) {
        random_seed = atoi(argv[4]);
    } else {
        random_seed = (unsigned int)time(NULL);
    }

    /* initialize remaining variables */
    output_interval = N / 10;

    srand_pcg(random_seed);

    /* allocate lattice */
    lattice = allocate_lattice(L, L, 0);

    window_sizes_count = (int)ceil((L-1)/2.0);
    window_size = (int *)malloc(window_sizes_count*sizeof(int));
    percolating_cluster_mass = (int *)malloc(window_sizes_count*sizeof(int));
    for (i = 0; i < window_sizes_count; i++) {
        window_size[i] = (i + 1)*2;
        percolating_cluster_mass[i] = 0;
    }

    /* calculate percolating cluster mass per window size */
    for (n = 0; n < N; n++) {
        percolating_cluster_idx = -1;
        while (percolating_cluster_idx < 0) {
            populate_lattice(probability, lattice, L, L, 0);
            concentration = 0;
            for (i = 0; i < L*L; i++) {
                concentration += lattice[i];
            }
            if (((double)concentration)/(L*L) < probability*0.9995 ||
                ((double)concentration)/(L*L) > probability*1.0005) {
                continue;
            }
            label_clusters(lattice, L, L);
            for (i = 0; i < L; i++) {
                for (j = 0; j < L; j++) {
                    if (lattice[i] && lattice[i] == lattice[(L-1)*L + j]) {
                        percolating_cluster_idx = i;
                        break;
                    }
                    if (lattice[i*L] && lattice[i*L] == lattice[j*L + L - 1]) {
                        percolating_cluster_idx = i*L;
                        break;
                    }
                }
                if (percolating_cluster_idx) break;
            }
            if (percolating_cluster_idx < 0) continue;
            if (lattice[(int)(L/2.0)*L + (int)(L/2.0)] != lattice[percolating_cluster_idx]) {
                percolating_cluster_idx = -1;
            }
        }
        for (k = 0; k < window_sizes_count; k++) {
            l = window_size[k];
            window = allocate_lattice(l, l, 0);
            center = (int)round((L - l)/2.0);
            for (i = 0; i < l; i++) {
                for (j = 0; j < l; j++) {
                    window[i*l + j] = lattice[center*(L+1) + j + L*i];
                }
            }
            for (i = 0; i < l*l; i++) {
                if (window[i] == lattice[percolating_cluster_idx]) {
                    percolating_cluster_mass[k] += 1;
                }
            }
            free(window);
        }
        /* print progress to stdout */
        if ((n+1) % output_interval == 0) {
            printf("finished with round %d out of %d\n", n+1, N);
        }
    }

    write_mass_windowing_results("print/data", window_size, percolating_cluster_mass,
        window_sizes_count, probability, N, L, L, random_seed);

    free(lattice);
    free(window_size);
    free(percolating_cluster_mass);

    return 0;
}
