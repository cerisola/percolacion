#ifndef BINDINGS_H
#define BINDINGS_H

void llenar(int * red, int n, float prob);
int hoshen(int * red, int n);
int actualizar(int * red, int * clase, int s, int frag);
void etiqueta_falsa(int * red, int * clase, int s1, int s2);
void corregir_etiqueta(int * red, int * clase, int n);
int percola(int * red, int n);

#endif /* BINDINGS_H */
