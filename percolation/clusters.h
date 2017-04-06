/*!
    @file clusters.h
    @brief This file contains functions for searching, labelling and analyzing
    clusters in a lattice.
*/

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
