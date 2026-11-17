#ifndef PAS7_H
#define PAS7_H

#include<stdio.h>
#include<stdlib.h>

#define N 11

typedef struct Node_Graph
{
    int vv;
    struct Node_Graph* next;
}Node_Graph;

typedef struct
{
    int V, E;
    Node_Graph** A;
}Graph;

Graph* creare_din_fisier(const char* nume_fisier , int vector_intrare[] , int vector_iesire[]);
void dfs(Graph* g, int nod, int traseu[], int lungime, int* vector_iesire, int* vector_intrare , FILE* nume_fisier);
void genereaza_trasee(Graph* g, int* vector_intrare, int* vector_iesire , FILE* nume_fisier);
void sorteaza_lista(Node_Graph** head);
void eliberare_graf(Graph* graf);

#endif 