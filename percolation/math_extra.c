/* Copyright 2017 Federico Cerisola */
/* MIT License (see root directory) */
/* see header file for detailed documentation of each function */

#include <stdlib.h>
#include <math.h>

double * create_exponential_centered_grid(const double xmin, const double xmax,
                                          const double xcenter, const int npoints,
                                          const double decay, int round_digits)
{
    int n;
    double * grid;
    int M;
    double A_left;
    double A_right;
    double B_left;
    double B_right;

    grid = (double *)malloc(npoints*sizeof(double));
    M = round(npoints/2.0);

    B_left = decay/M; /* M - 1 would make the point xcenter appear twice in the grid */
    A_left = (xcenter - xmin)/(exp(-decay) - 1.0);

    B_right = decay/(npoints - M - 1);
    A_right = (xmax - xcenter)/(exp(decay) - 1.0);

    for (n = 0; n < npoints; n++) {
        if (n < M) {
            grid[n] = A_left*(exp(-B_left*n) - 1.0) + xmin;
        } else {
            grid[n] = A_right*(exp(B_right*(n-M)) - 1.0) + xcenter;
        }
    }

    if (round_digits) {
        for (n = 0; n < npoints; n++) {
            grid[n] = ((int)(grid[n]*((int)pow(10, round_digits))))/((double)pow(10, round_digits));
        }
    }

    return grid;
}
