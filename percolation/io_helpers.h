/*!
    @file io_helpers.h
    @brief This file contains helper functions for printing lattices.
*/

#ifndef IO_HELPERS_H
#define IO_HELPERS_H

/*! Print lattice to the standard output.

    @param lattice pointer to the lattice to be printed.
    @param rows the number of rows in the lattice.
    @param columns the number of columnn in the lattice.
    @param with_borders boolean to determine whether to print the lattice with
        borders around each cell.
*/
void print_lattice(const int * lattice, int rows, int columns, char with_borders);

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
                           int columns, double probability, unsigned int seed);

/*! Write cluster statistics to file.

    @param path path to the folder where the data will be written. If the file
        exists it will be overwritten.
    @param cluster_sizes pointer to array with the different values of cluster
        sizes.
    @param cluster_sizes_counts array with the count of clusters that have a
        given size (given by the respective element of the cluster_sizes
        parameter).
    @param cluster_sizes_percolated array indicating how many percolating
        clusters there are of a given size (given by the respective element of
        the cluster_sizes parameter).
    @param cluster_sizes_total_count total amount of different cluster sizes.
    @param rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @param probability the probability used to populate the lattice.
    @param seed the random number generator seed used to generate the lattice.
    @param other additional information that should be writter to the output
        file header (optional, pass NULL if none is needed).
*/
void write_cluster_statistics_to_file(const char * path,
                                      const int * cluster_sizes,
                                      const int * cluster_sizes_counts,
                                      const int * cluster_sizes_percolated,
                                      int cluster_sizes_total_count, int rows,
                                      int columns, double probability,
                                      unsigned int seed, const char * other);

/*! Write critical point search results to file.

    @param path path to the folder where the data will be written. If the file
        exists it will be overwritten.
    @param critical_points array with the different estimated values of the
        critical point.
    @param number_trials number of total trials performed to estimate the
        critical point.
    @param precision the smallest step taken when searching for the critical
        point is given by \f$1/2^{\mathrm{precision}}\f$.
    @param rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @param start_probability the inital probability used to search for the
        critical point.
    @param seed the initial random number generator seed used to populate the
        lattice.
*/
void write_critical_point_search_results(const char * path,
                                         double * critical_points,
                                         int number_trials, int precision,
                                         int rows, int columns,
                                         double start_probability,
                                         unsigned int seed);

#endif /* IO_HELPERS_H */
