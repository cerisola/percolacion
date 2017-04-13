/*!
    @file lattice.h
    @brief This file contains functions to create, populate and manage lattices.
*/

#ifndef LATTICE_H
#define LATTICE_H

/*! Allocate lattice in memory.

    @param rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @param initialize boolean indicating whether the lattice should also be
        initialized after allocating.
    @return A pointer to the allocated lattice.
    @note The lattice is allocated using row-major ordering.
    @warning The allocated lattice must be manually free'd by the user.
*/
int * allocate_lattice(int rows, int columns, int initialize);

/*! Populate lattice with given probability.

    @param probability the probability of each site to be occupied.
    @param lattice a pointer to the lattice to be populated.
    @param rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @param seed the seed used to initialize the random number generator. If
        seed = 0, the random number generator is not initialized.
*/
void populate_lattice(double probability, int * lattice, int rows, int columns,
                      unsigned int seed);

#endif /* LATTICE_H */
