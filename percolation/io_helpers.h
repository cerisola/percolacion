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
