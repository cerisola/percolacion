#include "io_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void write_lattice_to_file(const char * path, const int * lattice, int rows,
                           int columns, int seed)
{
    int i;
    int j;
    size_t path_length;
    size_t file_full_path_length;
    char * file_full_path;
    char * rows_string;
    char * columns_string;
    char * seed_string;
    FILE * file_handler;

    rows_string = (char *)malloc(12*sizeof(char));
    sprintf(rows_string, "%d", rows);

    columns_string = (char *)malloc(12*sizeof(char));
    sprintf(columns_string, "%d", columns);

    seed_string = (char *)malloc(12*sizeof(char));
    sprintf(seed_string, "%d", seed);

    path_length = strlen(path);
    file_full_path_length  = path_length + 70;
    file_full_path = (char *)malloc(file_full_path_length*sizeof(char));
    strcpy(file_full_path, path);
    strcat(file_full_path, "/lattice_");
    strcat(file_full_path, rows_string);
    strcat(file_full_path, "x");
    strcat(file_full_path, columns_string);
    strcat(file_full_path, "_");
    strcat(file_full_path, seed_string);
    strcat(file_full_path, ".csv");

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
    free(rows_string);
    free(columns_string);
    free(seed_string);
    free(file_full_path);
}

void write_cluster_statistics_to_file(const char * path,
                                      const int * cluster_sizes,
                                      const int * cluster_sizes_counts,
                                      int cluster_sizes_total_count,
                                      int rows, int columns, int seed)
{
    int i;
    size_t path_length;
    size_t file_full_path_length;
    char * file_full_path;
    char * rows_string;
    char * columns_string;
    char * seed_string;
    FILE * file_handler;

    rows_string = (char *)malloc(12*sizeof(char));
    sprintf(rows_string, "%d", rows);

    columns_string = (char *)malloc(12*sizeof(char));
    sprintf(columns_string, "%d", columns);

    seed_string = (char *)malloc(12*sizeof(char));
    sprintf(seed_string, "%d", seed);

    path_length = strlen(path);
    file_full_path_length  = path_length + 70;
    file_full_path = (char *)malloc(file_full_path_length*sizeof(char));
    strcpy(file_full_path, path);
    strcat(file_full_path, "/clusters_");
    strcat(file_full_path, rows_string);
    strcat(file_full_path, "x");
    strcat(file_full_path, columns_string);
    strcat(file_full_path, "_");
    strcat(file_full_path, seed_string);
    strcat(file_full_path, ".csv");

    file_handler = fopen(file_full_path, "w");
    for (i = 0; i < cluster_sizes_total_count; i++) {
        fprintf(file_handler, "%d,%d\n", cluster_sizes[i], cluster_sizes_counts[i]);
    }

    fclose(file_handler);
    free(rows_string);
    free(columns_string);
    free(seed_string);
    free(file_full_path);
}
