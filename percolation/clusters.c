#include "clusters.h"
#include <stdlib.h>

void label_clusters(int * lattice, int rows, int columns)
{
    int i;
    int lattice_size;
    int next_label;
    int label_upper_row;
    int label_left_col;
    int current_label;
    int * labels;

    lattice_size = rows*columns;

    /* allocate and initialize auxilliary label storing array */
    labels = (int *) malloc((lattice_size/2)*sizeof(int));
    for (i = 0; i < lattice_size/2; i++) {
        labels[i] = i;
    }

    /* start labelling clusters from 2 */
    /* (0 and 1 are reserved for indicating free/occupied lattice sites) */
    next_label = 2;

    /* identify clusters and assign labels */
    /* treat first cell and first row separately */
    if (lattice[0] == 1) {
        lattice[0] = next_label;
        next_label++;
    }

    for (i = 1; i < columns; i++) {
        /* empty cells need no labeling */
        if (lattice[i] == 0) {
            continue;
        }

        /* get label of left column first neighbour */
        label_left_col = lattice[i - 1];

        /* left column neighbour is not occupied; assign new label */
        if (label_left_col == 0) {
            lattice[i] = next_label;
            next_label++;
            continue;
        }

        /* left column neighbour is occupied; copy its label */
        lattice[i] = label_left_col;
    }

    /* treat all other rows */
    for (i = columns; i < lattice_size; i++) {
        /* empty cells need no labeling */
        if (lattice[i] == 0) {
            continue;
        }

        /* get labels of first neighbours at upper row and left colum */
        label_upper_row = lattice[i - columns];
        label_left_col = (i % columns > 0) ? lattice[i - 1] : 0;

        /* no previously visited first neighbours are occupied; assign new label */
        if (label_upper_row == 0 && label_left_col == 0) {
            lattice[i] = next_label;
            next_label++;
            continue;
        }

        /* there is only one occupied fist neighbour; copy its label */
        if (label_upper_row * label_left_col == 0) {
            lattice[i] = label_upper_row > 0 ? label_upper_row : label_left_col;
            continue;
        }

        /* both first neighbours are occupied; handle possible conflict */
        /* first, get true labels of both neighbours */
        while (labels[label_upper_row] < 0) {
            label_upper_row = -labels[label_upper_row];
        }

        while (labels[label_left_col] < 0) {
            label_left_col = -labels[label_left_col];
        }

        /* find the smallest of the labels and assign it */
        /* also if needed correct the conflict in the labels assignments */
        if (label_upper_row < label_left_col) {
            lattice[i] = label_upper_row;
            labels[label_left_col] = -label_upper_row;
        } else if (label_left_col < label_upper_row) {
            lattice[i] = label_left_col;
            labels[label_upper_row] = -label_left_col;
        } else {
            lattice[i] = label_left_col;
        }
    }

    /* resolve temporary labels */
    for (i = 0; i < lattice_size; i++) {
        current_label = lattice[i];
        while (labels[current_label] < 0) {
            current_label = -labels[current_label];
        }
        labels[current_label] = current_label;
        lattice[i] = current_label;
    }

    /* free used memory */
    free(labels);
}

char has_percolating_cluster(const int * lattice, int rows, int columns)
{
    int i;
    int j;

    /* compare first and last row labels */
    for (i = 0; i < columns; i++) {
        if (lattice[i] == 0) {
            continue;
        }
        for (j = 0; j < columns; j++) {
            if (lattice[i] == lattice[rows*(columns-1) + j]) {
                return 1;
            }
        }
    }

    /* compare first and last column labels */
    for (i = 0; i < rows; i++) {
        if (lattice[i*columns] == 0) {
            continue;
        }
        for (j = 0; j < rows; j++) {
            if (lattice[i*columns] == lattice[j*columns + columns - 1]) {
                return 1;
            }
        }
    }

    /* if none of the above is true, then there is no percolating cluster */
    return 0;
}

void cluster_statistics(const int * lattice, int rows, int columns,
                        int * cluster_sizes_total_count, int ** cluster_sizes,
                        int ** cluster_sizes_counts, int * filled_count, int * empty_count)
{
    int i;
    int lattice_size;
    int cluster_labels_total_count; /* total number of different cluster labels */
    int * cluster_labels_indices; /* indices mapping each cluster label to a count value */
    int * cluster_labels_sizes; /* size of cluster for each label (via above index mapping */
    int * cluster_sizes_indices; /* indices mapping for each cluster size to a size value */

    /* assign each label their total node count; stored via an index mapping */
    lattice_size = rows*columns;
    cluster_labels_total_count = 0;
    cluster_labels_indices = (int *)malloc((lattice_size/2)*sizeof(int));
    cluster_labels_sizes = (int *)malloc((lattice_size/2)*sizeof(int));
    cluster_sizes_indices = (int *)malloc((lattice_size)*sizeof(int));
    for (i = 0; i < lattice_size/2; i++) {
        cluster_labels_indices[i] = -1;
        cluster_labels_sizes[i] = 0;
    }
    for (i = 0; i < lattice_size; i++) {
        /* use this loop to initialize this array for later use; this way we
           save ourselves an extra loop over the entire lattice */
        cluster_sizes_indices[i] = -1;

        /* actual cluster size counting */
        if (lattice[i] == 0) {
            continue;
        }

        if (cluster_labels_indices[lattice[i]] < 0) {
            cluster_labels_indices[lattice[i]] = cluster_labels_total_count;
            cluster_labels_total_count++;
        }
        cluster_labels_sizes[cluster_labels_indices[lattice[i]]] += 1;
    }

    free(cluster_labels_indices);

    /* get count of each cluster size */
    *cluster_sizes_total_count = 0;
    *cluster_sizes = (int *)malloc(cluster_labels_total_count*sizeof(int));
    *cluster_sizes_counts = (int *)malloc(cluster_labels_total_count*sizeof(int));
    for (i = 0; i < cluster_labels_total_count; i++) {
        (*cluster_sizes)[i] = 0;
        (*cluster_sizes_counts)[i] = 0;
    }
    for (i = 0; i < cluster_labels_total_count; i++) {
        if (cluster_sizes_indices[cluster_labels_sizes[i]] < 0) {
            cluster_sizes_indices[cluster_labels_sizes[i]] = *cluster_sizes_total_count;
            (*cluster_sizes_total_count) += 1;
        }
        (*cluster_sizes)[cluster_sizes_indices[cluster_labels_sizes[i]]] = cluster_labels_sizes[i];
        (*cluster_sizes_counts)[cluster_sizes_indices[cluster_labels_sizes[i]]] += 1;
    }

    free(cluster_labels_sizes);
    free(cluster_sizes_indices);

    *cluster_sizes = realloc(*cluster_sizes, (*cluster_sizes_total_count)*sizeof(int));
    *cluster_sizes_counts = realloc(*cluster_sizes_counts, (*cluster_sizes_total_count)*sizeof(int));

    /* calcualte auxilliary convenience values */
    *filled_count = 0;
    for (i = 0; i < *cluster_sizes_total_count; i++) {
        *filled_count += ((*cluster_sizes)[i])*((*cluster_sizes_counts)[i]);
    }
    *empty_count = lattice_size - *filled_count;
}
