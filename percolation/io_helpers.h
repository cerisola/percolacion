/*!
    @file io_helpers.h
    @brief This file contains helper functions for printing lattices.
*/

/*! Print lattice to the standard output.

    @param lattice pointer to the lattice to be printed.
    @param rows the number of rows in the lattice.
    @param columns the number of columnn in the lattice.
    @param with_borders boolean to determine whether to print the lattice with
        borders around each cell.
*/
void print_lattice(const int * lattice, int rows, int columns, int with_borders);

/*! Write lattice to file.

    @param path path to the folder were the lattice will be written. If the file
        exists it will be overwritten.
    @param lattice pointer to lattice to be written.
    @param rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @param probability the probability used to populate the lattice.
    @param seed the random generator seed used to generate the lattice.
*/
void write_lattice_to_file(const char * path, const int * lattice, int rows,
                           int columns, double probability, int seed);

/*! Write cluster statistics to file.

    @param path path to the folder where the data will be written. If the file
        exists it will be overwritten.
    @param cluster_sizes pointer to array with the different values of cluster
        sizes.
    @param cluster_sizes_counts pointer to array with the count of clusters that
        have a given size (given by the respective element of the cluster_sizes
        parameter).
    @param cluster_sizes_total_count total amount of different cluster sizes.
    @param percolated boolean indicating whether the lattice has a percolating
        cluster.
    @param rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @param probability the probability used to populate the lattice.
    @param seed the random number generator seed used to generate the lattice.
*/
void write_cluster_statistics_to_file(const char * path,
                                      const int * cluster_sizes,
                                      const int * cluster_sizes_counts,
                                      int cluster_sizes_total_count,
                                      int percolated, int rows, int columns,
                                      double probability, int seed);
