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

    /* for debugging purposes */
    /*
    print_lattice(lattice, rows, columns, 1);
    print_lattice(labels, 2, lattice_size/4, 1);
    */

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
