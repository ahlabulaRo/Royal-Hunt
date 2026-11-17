#ifndef PAS4_H
#define PAS4_H
#include "pas3.h"

int** citire_trasee(FILE* f);
Node** extrage_cei_opt(Coada* q1 , Coada* q2);
void afiseaza_primii8(Node** primii8);
void asignare_trasee(Heap* heap);
void heapifup(Heap* heap , int idx);
void afiseaza_heap_in_fisier(Heap* heap, const char* nume_fisier);
Heap* creare_heap_din_fisiere(const char* fisier_trasee, const char* fisier_lorzi, const char* fisier_ca);
void eliberare_trasee(int** v_trasee);

#endif