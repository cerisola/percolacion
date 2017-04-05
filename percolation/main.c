/* headers */
#include <stdlib.h>
#include <time.h>

#include "lattice.h"
#include "io_helpers.h"

/* main body function */
int main()
{
    int L; /* square lattice size */
    double p; /* occupation probability of each lattice site */
    int *lattice; /* lattice array */

    /* initialize random number generator seed */
    srand(time(NULL));

    /* allocate lattice */
    L = 10;
    lattice = allocate_lattice(L, L);

    /* populate lattice with given probability */
    p = 0.4;
    populate_lattice(p, lattice, L, L);

    /* print the generated lattice for visualization */
    print_lattice(lattice, L, L, 1);

    /* free memory before leaving */
    free(lattice);

    return 0;
}
