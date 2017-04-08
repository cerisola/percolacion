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

    @param path path to folder were the lattice will be written. If the file
        exists it will be overwritten.
    @param lattice pointer to lattice to be written.
    @param rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @param seed the random generator seed used to generate the lattice.
*/
void write_lattice_to_file(const char * path, const int * lattice, int rows,
                           int columns, int seed);
