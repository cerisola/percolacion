/*!
    @file io_helpers.h
    @brief This file contains helper functions for printing lattices.

    @author Federico Cerisola
    @copyright MIT License.
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
    @param realizations the number of different lattice realizations that were
        taken to aggregate the cluster statistics.
    @param other additional information that should be writter to the output
        file header (optional, pass NULL if none is needed).
*/
void write_cluster_statistics_to_file(const char * path,
                                      const int * cluster_sizes,
                                      const int * cluster_sizes_counts,
                                      const int * cluster_sizes_percolated,
                                      int cluster_sizes_total_count, int rows,
                                      int columns, double probability,
                                      unsigned int seed, int realizations,
                                      const char * other);

/*! Write critical point search via bisection results to file.

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
void write_critical_point_bisection_search_results(const char * path,
                                                   double * critical_points,
                                                   int number_trials, int precision,
                                                   int rows, int columns,
                                                   double start_probability,
                                                   unsigned int seed);

/*! Write cluster statistics generated during a probability sweep to file.

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
    @param seed the random number generator seed used at the beginning of the
        probability sweep.
    @param realizations the number of different lattice realizations that were
        taken to aggregate the cluster statistics.
    @param grid_points the number of points in the probability grid.
    @param probability_center center of the probability grid.
    @param decay exponential decay coefficient of the probability grid.
*/
void write_probability_sweep_cluster_statistics_to_file(const char * path,
                                                        const int * cluster_sizes,
                                                        const int * cluster_sizes_counts,
                                                        const int * cluster_sizes_percolated,
                                                        int cluster_sizes_total_count,
                                                        int rows, int columns,
                                                        double probability,
                                                        unsigned int seed,
                                                        int realizations,
                                                        int grid_points,
                                                        double probability_center,
                                                        double decay);

/*! Write the percolation probability obtained during a probability sweep to a file.

    @param path path to the folder where the data will be written. If the file
        exists it will be overwritten.
    @param probability_grid the population probabilities tested.
    @param percolation_counts how many times each probability produced a
        percolating cluster.
    @param grid_npoints the number of points in the probability grid.
    @param probability_center the central probability of the exponential grid.
    @param decay the exponential decay coefficient of the grid.
    @param realizations how many times each probability was tested.
    @param rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @param seed the random number generator seed used at the beginning of the
        probability sweep.
*/
void write_probability_sweep_percolation_probability(const char * path,
                                                     const double * probability_grid,
                                                     const int * percolation_counts,
                                                     int grid_npoints,
                                                     double probability_center,
                                                     double decay,
                                                     int * realizations,
                                                     int rows, int columns,
                                                     unsigned int seed);


/*! Write the percolating cluster mass for given window sizes to a file.

    @param path path to the folder where the data will be written. If the file
        exists it will be overwritten.
    @param window_sizes sizes of the windows tested.
    @param mass accumulated mass of the percolating cluster of each window size.
    @param window_sizes_count the total number of different window sizes tested.
    @param probability the population probabilities used.
    @param nrealizations how many times each window size was tested.
    @param rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @param seed the random number generator seed used at the beginning of the
        probability sweep.
*/
void write_mass_windowing_results(const char * path, const int * window_sizes,
                                  const int * mass, int window_sizes_count,
                                  double probability, int nrealizations,
                                  int rows, int columns, unsigned int seed);
#endif /* IO_HELPERS_H */
