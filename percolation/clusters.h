/*!
    @file clusters.h
    @brief This file contains functions for searching, labelling and analyzing
    clusters in a lattice.
*/

#ifndef CLUSTERS_H
#define CLUSTERS_H

/*!  Search for and label clusters in a lattice.

    This function implements the Hoshen-Kopelman algorithm [1] for labelling
    clusters in a lattice.

    [1]: Hoshen, J.; Kopelman, R. (15 October 1976)."Percolation and cluster
    distribution. I. Cluster multiple labeling technique and critical
    concentration algorithm". Phys. Rev. B. 14 (8): 3438–3445.
    doi:10.1103/PhysRevB.14.3438

    @param lattice pointer to the lattice to be analyzed.
    @param rows the number of rows in the lattice.
    @param columns the nubmer of columns in the lattice.
*/
void label_clusters(int * lattice, int rows, int columns);

/*! Determine whether a lattice has a percolating cluster.

    @param lattice pointer to lattice to be analyzed. The lattice must already
        have all clusters labeled.
    @param  rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @return A boolean indicating whether the lattice has a percolating cluster
        or not.

    @see label_clusters for a function that labels clusters in a lattice.
*/
char has_percolating_cluster(const int * lattice, int rows, int columns);

/*! Perform cluster sizes statistics.

    @param lattice pointer to lattice to be analyzed. The lattice must already
        have all clusters labeled.
    @param rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @param cluster_sizes_count pointer to integer where to store the total number
        of different cluster sizes present in the lattice.
    @param cluster_sizes pointer to array where to store the sizes of the clusters.
    @param sizes_counts pointer to array where to store the amount of clusters
        that have the size given by the matching position in the cluster_sizes
        array.
    @param filled_count pointer to integer where to store the total number of
        occupied nodes.
    @param empty_count pointer to integer where to store the total number of
        empty nodes.

    @warning cluster_sizes and cluster_sizes must be manually free'd by the user.

    @see label_clusters for a function that labels clusters in a lattice.
*/
void cluster_statistics(const int * lattice, int rows, int columns,
                        int * cluster_sizes_total_count, int ** cluster_sizes,
                        int ** cluster_sizes_counts, int ** cluster_sizes_percolated,
                        int * filled_count, int * empty_count);

#endif /* CLUSTERS_H */
