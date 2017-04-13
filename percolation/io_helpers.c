#include "io_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

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
    size_t path_length;
    size_t prefix_length;
    size_t file_full_path_length;
    char * file_full_path;
    char * file_name_prefix_string;
    char * rows_string;
    char * columns_string;
    char * seed_string;

    prefix_length = strlen(prefix);
    file_name_prefix_string = (char *)malloc((prefix_length + 12)*sizeof(char));
    sprintf(file_name_prefix_string, "/%s_", prefix);

    rows_string = (char *)malloc(12*sizeof(char));
    sprintf(rows_string, "%d", rows);

    columns_string = (char *)malloc(12*sizeof(char));
    sprintf(columns_string, "%d", columns);

    seed_string = (char *)malloc(12*sizeof(char));
    sprintf(seed_string, "%d", seed);

    path_length = strlen(path);
    file_full_path_length  = path_length + strlen(file_name_prefix_string) + 70;
    file_full_path = (char *)malloc(file_full_path_length*sizeof(char));
    strcpy(file_full_path, path);
    strcat(file_full_path, file_name_prefix_string);
    strcat(file_full_path, rows_string);
    strcat(file_full_path, "x");
    strcat(file_full_path, columns_string);
    strcat(file_full_path, "_");
    strcat(file_full_path, seed_string);
    strcat(file_full_path, ".csv");

    free(file_name_prefix_string);
    free(rows_string);
    free(columns_string);
    free(seed_string);

    return file_full_path;
}

void write_lattice_to_file(const char * path, const int * lattice, int rows,
                           int columns, double probability, int seed)
{
    int i;
    int j;
    char * file_full_path;
    FILE * file_handler;

    file_full_path = format_file_full_path(path, "lattice", rows, columns, seed);

    file_handler = fopen(file_full_path, "w");
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
    char * file_full_path;
    FILE * file_handler;

    file_full_path = format_file_full_path(path, "clusters", rows, columns, seed);

    file_handler = fopen(file_full_path, "w");
    fprintf(file_handler, "percolated:%d\n", percolated);
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
    char * file_full_path;
    FILE * file_handler;

    file_full_path = format_file_full_path(path, "critical_search", rows, columns, seed);

    file_handler = fopen(file_full_path, "w");
    fprintf(file_handler, ";rows:%d\n", rows);
    fprintf(file_handler, ";columns:%d\n", columns);
    fprintf(file_handler, ";seed:%d\n", seed);
    fprintf(file_handler, ";pini:%.*e\n", DBL_DIG-1, start_probability);
    fprintf(file_handler, ";ntrials:%d\n", number_trials);
    fprintf(file_handler, ";precision:%d\n", precision);
    for (i = 0; i < number_trials; i++) {
        fprintf(file_handler, "%.*e\n", DBL_DIG-1, critical_points[i]);
    }

    fclose(file_handler);
    free(file_full_path);
}
