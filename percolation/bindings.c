#include "lattice.h"
#include "clusters.h"
#include "io_helpers.h"

void llenar(int * red, int n, float prob)
{
    populate_lattice(prob, red, n, n, 0);
}

int hoshen(int * red, int n)
{
    label_clusters(red, n, n);
    return 0;
}

int percola(int * red, int n)
{
    return has_percolating_cluster(red, n, n);
}

int actualizar(int * red, int * clase, int s, int frag)
{
    if (s) {
        *red = s;
    } else {
        clase[frag] = frag;
        *red = frag;
        frag = frag + 1;
    }
    return frag;
}

void etiqueta_falsa(int * red, int * clase, int s1, int s2)
{
    while (clase[s1] < 0) {
        s1 = -clase[s1];
    }

    while (clase[s2] < 0) {
        s2 = -clase[s2];
    }

    if (s1 < s2) {
        clase[s2] = -s1;
        *red = s1;
    } else if (s2 < s1) {
        clase[s1] = -s2;
        *red = s2;
    } else {
        *red = s1;
    }
}

void corregir_etiqueta(int * red, int * clase, int n)
{
    int s;
    int i;
    for (i = 0; i < n*n; i++) {
        s = red[i];
        while (clase[s] < 0) {
            s = -clase[s];
        }
        red[i] = s;
    }
}
