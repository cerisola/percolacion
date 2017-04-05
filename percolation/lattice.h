/*
    This file contains functions to create, populate and manage lattices.
*/

/* Allocate lattice in memory */
int * allocate_lattice(int rows, int columns);

/* Populate lattice with given probability */
void populate_lattice(double probability, int * lattice, int rows, int columns);
