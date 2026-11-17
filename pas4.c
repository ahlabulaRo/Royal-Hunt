#include "pas4.h"

int** citire_trasee(FILE* f)
{
    int** v_trasee = (int**)malloc(sizeof(int*) * 8);
    if(!v_trasee)
    {
        printf("Eroare la alocare vector de trasee(citire_trasee -> pas4)\n");
        exit(1);
    }
    char linie[100];

    for(int i=0;i<8;i++)
    {
        if(!fgets(linie , sizeof(linie) , f))
        {
            printf("Eroare la citirea liniei!(pas4)\n");
            exit(1);
        }
        v_trasee[i] = (int*)malloc(sizeof(int) * 4);

        sscanf(linie , "%*s %d %d %d %d" , &v_trasee[i][0] , &v_trasee[i][1] , &v_trasee[i][2] , &v_trasee[i][3]);
    }
    return v_trasee;
}

Node** extrage_cei_opt(Coada* q1 , Coada* q2)
{
    Node** vector_primii8 = (Node**)malloc(sizeof(Node*) * 8);

    Node* temp1 = q1->front;
    Node* temp2 = q2->front;
    int c1=0,c2=0,idx_comun=0;

    while(c1<4 || c2<4)
    {
            if(c1<4 && temp1)
            {
                vector_primii8[idx_comun++] = temp1;
                temp1->id = idx_comun;
                temp1 = temp1->prev;
                c1++;
            }

            if(c2<4 && temp2)
            {
                vector_primii8[idx_comun++] = temp2;
                temp2->id = idx_comun;
                temp2 = temp2->prev;
                c2++;
            }
    }
    return vector_primii8;
}

void afiseaza_primii8(Node** primii8)
{
    for (int i = 0; i < 8; i++) {
        if (primii8[i]) {
            printf("Nod %d:\n", i + 1);
            printf("  Traseu: %d %d %d %d\n" , primii8[i]->traseu[0] , primii8[i]->traseu[1] , primii8[i]->traseu[2] , primii8[i]->traseu[3]);
            printf("  Nume: %s\n", primii8[i]->nume);
            printf("  Varsta: %d\n", primii8[i]->varsta);
            printf("  Experienta: %.2f\n", primii8[i]->experienta);

            switch (primii8[i]->ss) {
                case LORD: printf("  Statut: LORD\n"); break;
                case CAVALER: printf("  Statut: CAVALER\n"); break;
                case AVENTURIER: printf("  Statut: AVENTURIER\n"); break;
                default: printf("  Statut: NECUNOSCUT\n"); break;
            }
        } else {
            printf("Nod %d: NULL\n", i + 1);
        }
    }
}

void asignare_trasee(Heap* heap)
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<4;j++)
        {
            heap->primii8[i]->traseu[j] = heap->vector_trasee[i][j];
        }
    }
}

void heapifup(Heap* heap , int idx)
{
    while(idx>0)
    {
        int parent = (idx-1)/2;

        if(heap->primii8[idx]->experienta > heap->primii8[parent]->experienta)
        {
            Node* swap = heap->primii8[idx];
            heap->primii8[idx] = heap->primii8[parent];
            heap->primii8[parent] = swap;

            int* traseu_swap = heap->vector_trasee[idx];
            heap->vector_trasee[idx] = heap->vector_trasee[parent];
            heap->vector_trasee[parent] = traseu_swap;

            idx = parent;
        }
        else break;
    }
}

void afiseaza_heap_in_fisier(Heap* heap, const char* nume_fisier)
{
    FILE* f = fopen(nume_fisier, "w");
    if (!f)
    {
        printf("Eroare la deschiderea fisierului de iesire(pas4)");
        return;
    }

    fprintf(f, "Nume_Traseu - Nume_Participant (Experienta_participant)\n");

    for (int i = 0; i < 8 ; i++) {
        Node* prototip = heap->primii8[i];
        fprintf(f, "T%d - %s (%.2f)\n", prototip->id, prototip->nume, prototip->experienta);
    }

    fclose(f);
}

Heap* creare_heap_din_fisiere(const char* fisier_trasee, const char* fisier_lorzi, const char* fisier_ca) 
{
    FILE* f = fopen(fisier_trasee, "r");
    if (!f) 
    {
        printf("Eroare la deschiderea fisierului de trasee(pas4)!\n");
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
    asignare_trasee(heap);
    for (int i = 0; i < 8; i++) 
    {
        heapifup(heap, i);
    }
    return heap;
}


void eliberare_trasee(int** v_trasee)
{
    for(int i=0;i<8;i++)
    {
        free(v_trasee[i]);
    }
    free(v_trasee);
}

