/* headers */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "lattice.h"
#include "clusters.h"
#include "io_helpers.h"

/* main body function */
int main(int argc, char ** argv)
{
    int L; /* square lattice size */
    double p; /* occupation probability of each lattice site */
    int *lattice; /* lattice array */
    unsigned int random_seed; /* random number generator seed */
    char percolated;
    int cluster_sizes_total_count; /* total number of different cluster sizes */
    int *cluster_sizes_counts; /* count of clusters of a given size (paied in cluster_sizes) */
    int *cluster_sizes; /* sizes of clusters */
    int *cluster_sizes_percolated; /* how many percolating clusters of each size there are */
    int filled_count; /* number of occupied nodes */
    int empty_count; /* number of empty nodes */

    /* read input arguments; if none provided fallback to default values */
    if (argc == 3 || argc == 4) {
        L = atoi(argv[1]);
        p = atof(argv[2]);
        if (argc == 4) {
            random_seed = atoi(argv[3]);
        } else {
            random_seed = (unsigned int)time(NULL);
        }
    } else {
        L = 10;
        p = 0.4;
        random_seed = (unsigned int)time(NULL);
    }

    /* allocate lattice */
    lattice = allocate_lattice(L, L, 0);

    /* populate lattice with given probability */
    populate_lattice(p, lattice, L, L, random_seed);

    /* print the generated lattice for visualization */
    print_lattice(lattice, L, L, 1);

    /* label clusters and print result */
    label_clusters(lattice, L, L);
    print_lattice(lattice, L, L, 1);

    /* perform statistics on cluster sizes */
    cluster_statistics(lattice, L, L, &cluster_sizes_total_count, &cluster_sizes,
                       &cluster_sizes_counts, &cluster_sizes_percolated,
                       &filled_count, &empty_count);
    printf("Occupied: %d | Free: %d\n", filled_count, empty_count);
    printf("Total # of cluster sizes: %d\n", cluster_sizes_total_count);
    print_lattice(cluster_sizes, 1, cluster_sizes_total_count, 1);
    print_lattice(cluster_sizes_counts, 1, cluster_sizes_total_count, 1);
    print_lattice(cluster_sizes_percolated, 1, cluster_sizes_total_count, 1);

    /* determine presence of a percolating cluster */
    percolated = has_percolating_cluster(lattice, L, L);
    printf("Lattice has percolating cluster: %s\n", percolated ? "true" : "false");

    /* free memory before leaving */
    free(lattice);

    return 0;
}
