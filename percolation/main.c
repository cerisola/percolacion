/* headers */
#include <stdlib.h>
#include <time.h>

#include "lattice.h"
#include "clusters.h"
#include "io_helpers.h"

/* main body function */
int main(int argc, char ** argv)
{
    int L; /* square lattice size */
    double p; /* occupation probability of each lattice site */
    int *lattice; /* lattice array */

    /* read input arguments; if none provided fallback to default values */
    if (argc == 3) {
        L = atoi(argv[1]);
        p = atof(argv[2]);
    } else {
        L = 10;
        p = 0.4;
    }

    /* initialize random number generator seed */
    srand(time(NULL));

    /* allocate lattice */
    lattice = allocate_lattice(L, L);

    /* populate lattice with given probability */
    populate_lattice(p, lattice, L, L);

    /* print the generated lattice for visualization */
    print_lattice(lattice, L, L, 1);

    /* label clusters and print result */
    label_clusters(lattice, L, L);
    print_lattice(lattice, L, L, 1);

    /* free memory before leaving */
    free(lattice);

    return 0;
}
