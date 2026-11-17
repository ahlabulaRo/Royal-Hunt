#include "pas6.h"

void actualizare_experienta(Heap* heap)
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<4;j++)
        {
            heap->primii8[i]->experienta += heap->primii8[i]->traseu[j];
        }
    }
}

int compara_experiente(const void* a, const void* b)
{
    Node *nodA = *(Node **)a;
    Node *nodB = *(Node **)b;
    if (nodA->experienta > nodB->experienta) return -1;
    else if (nodA->experienta < nodB->experienta) return 1;
    else return 0;
}

void afisare_pas6(Heap* heap, const char* nume_fisier)
{
    FILE* f = fopen(nume_fisier, "w");
    if (!f)
    {
        printf("Eroare la deschiderea fisierului de iesire(pas6)!\n");
        return;
    }

    qsort(heap->primii8 , 8 , sizeof(Node*) , compara_experiente);
    fprintf(f, "Nume Experienta_totala\n");

    for (int i = 0; i < 3 ; i++) 
    {
        Node* nod2 = heap->primii8[i];
        fprintf(f, "%s %.2f\n", nod2->nume, nod2->experienta);
    }

    fclose(f);
}