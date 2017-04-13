#include "io_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <time.h>

void print_lattice(const int * lattice, int rows, int columns, int with_borders)
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

    @returns pointer to array where the formatted file full path will be
        written.
*/
char * format_file_full_path(const char * path, const char * prefix, int rows,
                           int columns, int seed)
{
    size_t file_full_path_length;
    char * file_full_path;

    file_full_path_length = strlen(path) + strlen(prefix) + 120;
    file_full_path = (char *)malloc(file_full_path_length*sizeof(char));
    sprintf(file_full_path, "%s/%s_%dx%d_%d.csv", path, prefix, rows, columns, seed);

    return file_full_path;
}

void write_lattice_to_file(const char * path, const int * lattice, int rows,
                           int columns, double probability, int seed)
{
    int i;
    int j;
    time_t current_time;
    char * file_full_path;
    FILE * file_handler;

    current_time = time(NULL);
    file_full_path = format_file_full_path(path, "lattice", rows, columns, seed);

    file_handler = fopen(file_full_path, "w");
    fprintf(file_handler, ";rows:%d\n", rows);
    fprintf(file_handler, ";columns:%d\n", columns);
    fprintf(file_handler, ";seed:%d\n", seed);
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
                                      int cluster_sizes_total_count,
                                      int percolated,  int rows, int columns,
                                      double probability, int seed)
{
    int i;
    time_t current_time;
    char * file_full_path;
    FILE * file_handler;

    current_time = time(NULL);
    file_full_path = format_file_full_path(path, "clusters", rows, columns, seed);

    file_handler = fopen(file_full_path, "w");
    fprintf(file_handler, ";rows:%d\n", rows);
    fprintf(file_handler, ";columns:%d\n", columns);
    fprintf(file_handler, ";seed:%d\n", seed);
    fprintf(file_handler, ";probability:%.*e\n", DBL_DIG-1, probability);
    fprintf(file_handler, ";percolated:%d\n", percolated);
    fprintf(file_handler, ";date:%s", asctime(localtime(&current_time)));
    for (i = 0; i < cluster_sizes_total_count; i++) {
        fprintf(file_handler, "%d,%d\n", cluster_sizes[i], cluster_sizes_counts[i]);
    }

    fclose(file_handler);
    free(file_full_path);
}

void write_critical_point_search_results(const char * path,
                                         double * critical_points,
                                         int number_trials, int precision,
                                         int rows, int columns,
                                         double start_probability, int seed)
{
    int i;
    time_t current_time;
    char * file_full_path;
    FILE * file_handler;

    current_time = time(NULL);
    file_full_path = format_file_full_path(path, "critical_search", rows, columns, seed);

    file_handler = fopen(file_full_path, "w");
    fprintf(file_handler, ";rows:%d\n", rows);
    fprintf(file_handler, ";columns:%d\n", columns);
    fprintf(file_handler, ";seed:%d\n", seed);
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
