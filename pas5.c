#include "pas5.h"

Heap* citire_heap_pas5(const char* fisier_trasee, const char* fisier_lorzi, const char* fisier_ca)
{
    FILE* f = fopen(fisier_trasee, "r");
    if (!f)
    {
        printf("Eroare la deschiderea fisierului de trasee(pas5)!\n");
        exit(1);
    }

    Coada* lorzi = creare_coada();
    Coada* ca = creare_coada();
    Heap* heap = malloc(sizeof(Heap));
    heap->vector_trasee = citire_trasee(f);
    fclose(f);

    citire_din_fisier_arbore(lorzi, fisier_lorzi);
    citire_din_fisier_arbore(ca, fisier_ca);
    heap->lorzi = lorzi;
    heap->ca = ca;
    heap->primii8 = extrage_cei_opt(lorzi, ca);
    return heap;
}

void heapifup_pas_cu_pas(Heap* heap)
{
    for (int i = 0; i < 8; i++) 
    {
        int pas = 0;
        for (int j = 0; j < 4; j++) pas += heap->vector_trasee[i][j];
        Node* nod = heap->primii8[i];
        nod->experienta += pas;
        heapifup(heap, i);
    }
}