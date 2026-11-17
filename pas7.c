#include "pas7.h"

Graph* creare_din_fisier(const char* nume_fisier, int intrare[], int iesire[])
{
    FILE* f = fopen(nume_fisier, "r");
    if(!f)
    {
        printf("Eroare la deschiderea fisierului(pas7)!\n");
        return NULL;
    }

    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = N;
    g->E = 0;
    g->A = (Node_Graph**)malloc(g->V * sizeof(Node_Graph*));

    for(int i = 0; i < g->V; i++)
    {
        g->A[i] = (Node_Graph*)malloc(sizeof(Node_Graph));
        g->A[i]->vv = i;
        g->A[i]->next = NULL;
        intrare[i] = 0;
        iesire[i] = 0;
    }

    int intra, iese;
    while(fscanf(f, "%d %d", &intra, &iese) != EOF)
    {
        Node_Graph* nou = (Node_Graph*)malloc(sizeof(Node_Graph));
        nou->vv = iese;
        nou->next = g->A[intra]->next;
        g->A[intra]->next = nou;

        g->E++;
        iesire[intra]++;
        
        intrare[iese]++;
    }
    fclose(f);
    
    for (int i = 0; i < g->V; i++) sorteaza_lista(&g->A[i]->next);
    return g;
}

void dfs(Graph* g, int nod, int traseu[], int lungime, int* iesire, int* intrare, FILE* fout)
{
    traseu[lungime++] = nod;

    if(iesire[nod] == 0)
    {
        static int nr = 1;
        fprintf(fout, "T%d: ", nr++);
        for (int i = 0; i < lungime; i++) fprintf(fout, "%d ", traseu[i]);
        fprintf(fout, "\n");
        return;
    }

    Node_Graph* p = g->A[nod]->next;
    while(p)
    {
        dfs(g, p->vv, traseu, lungime, iesire, intrare, fout);
        p = p->next;
    }
}


void genereaza_trasee(Graph* g, int* intrare, int* iesire, FILE* fout)
{
    int traseu[100];
    for(int i = 0; i < g->V; i++)
    {
        if(intrare[i] == 0) dfs(g, i, traseu, 0, iesire, intrare, fout);
    }
}


void sorteaza_lista(Node_Graph** head)
{
    if(!*head || !(*head)->next) return;

    int schimba;
    Node_Graph *p1 , *p2 = NULL;

    do{
        schimba = 0;
        p1 = *head;

        while(p1->next != p2)
        {
            if (p1->vv > p1->next->vv)
            {
                int temp = p1->vv;
                p1->vv = p1->next->vv;
                p1->next->vv = temp;
                schimba = 1;
            }
            p1 = p1->next;
        }
        p2 = p1;
    }while(schimba);
}

void eliberare_graf(Graph* graf)
{
    for(int i = 0; i < graf->V; i++)
    {
        Node_Graph* p = graf->A[i];
        while(p)
        {
            Node_Graph* temp = p;
            p = p->next;
            free(temp);
        }
    }
    free(graf->A);
    free(graf);
}
