/* Copyright 2017 Federico Cerisola */
/* MIT License (see root directory) */
/* see header file for detailed documentation of each function */

#include "io_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <time.h>

void print_lattice(const int * lattice, int rows, int columns, char with_borders)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        if (with_borders) {
            for (j = 0; j < columns; j++) {
                printf("------");
            }
            printf("-\n");
        }
        for (j = 0; j < columns; j++) {
            if (with_borders) {
                putchar('|');
                putchar(' ');
            }
            if (lattice[i*columns + j] == 1) {
                printf(" x ");
            } else if (lattice[i*columns + j] > 1) {
                printf("%03d", lattice[i*columns + j]);
            } else {
                if (with_borders) {
                    putchar(' ');
                    putchar(' ');
                    putchar(' ');
                } else {
                    printf(" o ");
                }
            }
            if (with_borders) {
                putchar(' ');
                if (j == columns - 1) {
                    putchar('|');
                }
            } else {
                if (j < columns - 1) {
                    putchar(' ');
                }
            }
        }
        putchar('\n');
    }
    if (with_borders) {
        for (j = 0; j < columns; j++) {
            printf("------");
        }
        printf("-\n");
    } else {
        putchar('\n');
    }
}

/*! Format the file name with the given parameters
    @param path path to the folder where the data will be written.
    @param prefix file name prefix.
    @param rows the number of rows in the lattice.
    @param columns the number of columns in the lattice.
    @param seed the initial random number generator seed used to populate the
        lattice.
    @param other additional parameter to add to the file name.

    @returns pointer to array where the formatted file full path will be
        written.
*/
char * format_file_full_path(const char * path, const char * prefix, int rows,
                           int columns, unsigned int seed, const double other)
{
    size_t file_full_path_length;
    char * file_full_path;

    file_full_path_length = strlen(path) + strlen(prefix) + 160;
    file_full_path = (char *)malloc(file_full_path_length*sizeof(char));
    sprintf(file_full_path, "%s/%s_%dx%d_%u_%.*e.csv", path, prefix, rows, columns, seed, DBL_DIG-1, other);

    return file_full_path;
}

void write_lattice_to_file(const char * path, const int * lattice, int rows,
                           int columns, double probability, unsigned int seed)
{
    int i;
    int j;
    time_t current_time;
    char * file_full_path;
    FILE * file_handler;

    current_time = time(NULL);
    file_full_path = format_file_full_path(path, "lattice", rows, columns, seed, probability);

    file_handler = fopen(file_full_path, "w");
    fprintf(file_handler, ";rows:%d\n", rows);
    fprintf(file_handler, ";columns:%d\n", columns);
    fprintf(file_handler, ";seed:%u\n", seed);
    fprintf(file_handler, ";probability:%.*e\n", DBL_DIG-1, probability);
    fprintf(file_handler, ";date:%s", asctime(localtime(&current_time)));
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            fprintf(file_handler, "%d", lattice[i*columns + j]);
            if (j < columns - 1) {
                fputs(",", file_handler);
            }
        }
        fputs("\n", file_handler);
    }

    fclose(file_handler);
    free(file_full_path);
}

void write_cluster_statistics_to_file(const char * path,
                                      const int * cluster_sizes,
                                      const int * cluster_sizes_counts,
                                      const int * cluster_sizes_percolated,
                                      int cluster_sizes_total_count, int rows,
                                      int columns, double probability,
                                      unsigned int seed, int realizations,
                                      const char * other)
{
    int i;
    time_t current_time;
    char * file_full_path;
    FILE * file_handler;

    current_time = time(NULL);
    file_full_path = format_file_full_path(path, "clusters", rows, columns, seed, probability);

    file_handler = fopen(file_full_path, "w");
    fprintf(file_handler, ";rows:%d\n", rows);
    fprintf(file_handler, ";columns:%d\n", columns);
    fprintf(file_handler, ";seed:%u\n", seed);
    fprintf(file_handler, ";probability:%.*e\n", DBL_DIG-1, probability);
    fprintf(file_handler, ";realizations:%d\n", realizations);
    if (other) {
        fprintf(file_handler, "%s", other);
    }
    fprintf(file_handler, ";date:%s", asctime(localtime(&current_time)));
    for (i = 0; i < cluster_sizes_total_count; i++) {
        fprintf(file_handler, "%d,%d,%d\n", cluster_sizes[i], cluster_sizes_counts[i],
                cluster_sizes_percolated[i]);
    }

    fclose(file_handler);
    free(file_full_path);
}

void write_critical_point_bisection_search_results(const char * path,
                                                   double * critical_points,
                                                   int number_trials, int precision,
                                                   int rows, int columns,
                                                   double start_probability,
                                                   unsigned int seed)
{
    int i;
    time_t current_time;
    char * file_full_path;
    FILE * file_handler;

    current_time = time(NULL);
    file_full_path = format_file_full_path(path, "critical_bisection_search", rows, columns, seed, number_trials);

    file_handler = fopen(file_full_path, "w");
    fprintf(file_handler, ";rows:%d\n", rows);
    fprintf(file_handler, ";columns:%d\n", columns);
    fprintf(file_handler, ";seed:%u\n", seed);
    fprintf(file_handler, ";pini:%.*e\n", DBL_DIG-1, start_probability);
    fprintf(file_handler, ";ntrials:%d\n", number_trials);
    fprintf(file_handler, ";precision:%d\n", precision);
    fprintf(file_handler, ";date:%s", asctime(localtime(&current_time)));
    for (i = 0; i < number_trials; i++) {
        fprintf(file_handler, "%.*e\n", DBL_DIG-1, critical_points[i]);
    }

    fclose(file_handler);
    free(file_full_path);
}

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
                                                        double decay)
{
    char * other;

    other = (char *)malloc(140*sizeof(char));
    sprintf(other, ";source:probability_sweep\n;grid_npoints:%d\n;grid_center:%.*e\n;grid_decay:%.*e\n",
            grid_points, DBL_DIG-1, probability_center, DBL_DIG-1, decay);

    write_cluster_statistics_to_file(path, cluster_sizes, cluster_sizes_counts,
                                     cluster_sizes_percolated, cluster_sizes_total_count,
                                     rows, columns, probability, seed, realizations,
                                     other);
    free(other);
}

void write_probability_sweep_percolation_probability(const char * path,
                                                     const double * probability_grid,
                                                     const int * percolation_counts,
                                                     int grid_npoints,
                                                     double probability_center,
                                                     double decay,
                                                     int * realizations,
                                                     int rows, int columns,
                                                     unsigned int seed)
{
    int i;
    time_t current_time;
    char * file_full_path;
    FILE * file_handler;

    current_time = time(NULL);
    file_full_path = format_file_full_path(path, "percolation_probability", rows, columns, seed, grid_npoints);

    file_handler = fopen(file_full_path, "w");
    fprintf(file_handler, ";rows:%d\n", rows);
    fprintf(file_handler, ";columns:%d\n", columns);
    fprintf(file_handler, ";seed:%u\n", seed);
    fprintf(file_handler, ";grid_npoints:%d\n", grid_npoints);
    fprintf(file_handler, ";grid_center:%.*e\n", DBL_DIG-1, probability_center);
    fprintf(file_handler, ";grid_decay:%.*e\n", DBL_DIG-1, decay);
    fprintf(file_handler, ";date:%s", asctime(localtime(&current_time)));
    for (i = 0; i < grid_npoints; i++) {
        fprintf(file_handler, "%.*e,%d,%d,%.*e\n", DBL_DIG-1, probability_grid[i],
                percolation_counts[i], realizations[i],
                DBL_DIG-1, ((double)percolation_counts[i])/realizations[i]);
    }

    fclose(file_handler);
    free(file_full_path);
}

void write_mass_windowing_results(const char * path, const int * window_sizes,
                                  const unsigned long * mass, int window_sizes_count,
                                  double probability, int nrealizations,
                                  int rows, int columns, unsigned int seed)
{
    int i;
    time_t current_time;
    char * file_full_path;
    FILE * file_handler;

    current_time = time(NULL);
    file_full_path = format_file_full_path(path, "mass_windowing", rows, columns, seed, probability);

    file_handler = fopen(file_full_path, "w");
    fprintf(file_handler, ";rows:%d\n", rows);
    fprintf(file_handler, ";columns:%d\n", columns);
    fprintf(file_handler, ";probability:%.*e\n", DBL_DIG-1, probability);
    fprintf(file_handler, ";nrealizations:%d\n", nrealizations);
    fprintf(file_handler, ";seed:%u\n", seed);
    fprintf(file_handler, ";date:%s", asctime(localtime(&current_time)));
    for (i = 0; i < window_sizes_count; i++) {
        fprintf(file_handler, "%d,%lu,%.*e\n", window_sizes[i], mass[i],
                DBL_DIG-1, ((double)mass[i])/nrealizations);
    }

    fclose(file_handler);
    free(file_full_path);
}
