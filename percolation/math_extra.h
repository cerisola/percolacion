/*!
    @file math_extra.h
    @brief This file contains generic math functions not included in the
    standard library.

    @author Federico Cerisola
    @copyright MIT License.
*/

#ifndef MATH_EXTRA_H
#define MATH_EXTRA_H

/*! Create an exponentially spaced grid in a given interval with the maximum
    density centered at a given point.

    This function creates a discrete grid of \f$N\f$ points in the interval
    \f$(x_{min}, x_{max})\f$ with the maximum density of points centered around
    the position \f$x_{center}\f$. The distribution of points is given by the
    formula
    \f[
        x_n = \begin{cases}
                \frac{x_{center} - x_{min}}{e^{-h}-1}
                  \left(e^{-\frac{hn}{N/2}} - 1\right) + x_{min} & \mbox{if } n < N/2 \\
                \frac{x_{max} - x_{center}}{e^{h}-1}
                  \left(e^{\frac{h(n-N/2)}{N/2}} - 1\right) + x_{center} & \mbox{if } n > N/2
              \end{cases}
    \f]
    where \f$h\f$ is a user selectable parameter wich determines the points
    spacing.

    @param xmin initial value of the interval.
    @param xmax final value of the interval.
    @param xcenter where to center the maximum density of points.
    @param npoints the number of points in the grid.
    @param decay how fast the exponential deays (see parameter \f$h\f$ in
        formula above).

    @returns pointer to the grid.

    @warning xcenter must be strictly smaller than xmax and strictly grater than
        xmin.
*/
double * create_exponential_centered_grid(const double xmin, const double xmax,
                                          const double xcenter, const int npoints,
                                          const double decay);

#endif /* MATH_EXTRA_H */
