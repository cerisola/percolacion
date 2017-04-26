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
    double center_of_mass_x, center_of_mass_y;
    int mass;
    int * window;
    int center;
    int * percolating_cluster_mass;
    int * window_size;
    int window_sizes_count;
    int output_interval;
    int l;
    int i, j, n;

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
    //output_interval = N / 10;
    output_interval = 1;

    srand_pcg(random_seed);

    /* allocate lattice */
    lattice = allocate_lattice(L, L, 0);

    window_sizes_count = 0;
    window_size = (int *)malloc(((L-2)/2)*sizeof(int));
    percolating_cluster_mass = (int *)malloc(((L-2)/2)*sizeof(int));
    for (l = 2; l <= L; l += 2) {
        window_size[l/2] = l;
        percolating_cluster_mass[l/2] = 0;
        window_sizes_count++;
    }

    /* calculate percolating cluster mass per window size */
    for (n = 0; n < N; n++) {
        percolating_cluster_idx = -1;
        while (percolating_cluster_idx < 0) {
            populate_lattice(probability, lattice, L, L, 0);
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
            if (!percolating_cluster_idx) continue;
            mass = 0;
            center_of_mass_x = 0;
            center_of_mass_y = 0;
            for (i = 0; i < L; i++) {
                for (j = 0; j < L; j++) {
                    if (lattice[i*L + j] == lattice[percolating_cluster_idx]) {
                        center_of_mass_x += i;
                        center_of_mass_y += j;
                        mass += 1;
                    }
                }
            }
            center_of_mass_x = center_of_mass_x / mass;
            center_of_mass_y = center_of_mass_y / mass;
            //printf("center of mass: %f\n", center_of_mass);
            if (center_of_mass_x < (L - 2.0)/2.0 - 2 || center_of_mass_y < (L - 2.0)/2.0 - 2
                || center_of_mass_x > (L + 2.0)/2.0 + 2 || center_of_mass_y > (L + 2.0)/2.0 + 2) {
                    percolating_cluster_idx = -1;
            }
        }
        for (l = 2; l <= L; l += 2) {
            window = allocate_lattice(l, l, 0);
            center = (int)((L - l)/2.0);
            for (i = 0; i < l; i++) {
                for (j = 0; j < l; j++) {
                    window[i*l + j] = lattice[center*(L+1) + j + L*i];
                }
            }
            window_size[l/2] = l;
            for (i = 0; i < l*l; i++) {
                if (window[i] == lattice[percolating_cluster_idx]) {
                    percolating_cluster_mass[l/2] += 1;
                }
            }
            /*
            printf("lattice:\n");
            print_lattice(lattice, L, L, 1);
            printf("window: %dx%d @ %d\nstart at %d\n", l, l, center, center*(L+1));
            print_lattice(window, l, l, 1);
            */
            free(window);
            printf("finished with lattice %d out of %d\n", l, L);
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
