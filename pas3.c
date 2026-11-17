#include "pas3.h"

void sterge_elemente_comune(Coada* c , Coada* d)
{
    Node* curent = c->front;
    Node* anterior = NULL;

    while(curent != NULL)
    {
        int gasit = 0;

        Node* temp = d->front;
        while(temp != NULL)
        {
            if(strcmp(curent->nume , temp->nume) == 0 && curent->experienta == temp->experienta && curent->varsta == temp->varsta)
            {
                gasit = 1;
                break;
            }
            temp = temp->prev;
        }

        if(gasit)
        {
            Node* nod_de_sters = curent;

            if(anterior == NULL)
            {
                c->front = curent->prev;
                if(c->front == NULL) c->rear == NULL;
            }
            else
            {
                anterior->prev = curent->prev;
                if(curent == c->rear) c->rear = anterior;
            }
         curent = curent->prev;
         free(nod_de_sters->nume);
         free(nod_de_sters);
        }
        else
        {
            anterior = curent;
            curent = curent->prev;
        }
    }
}

void citire_din_fisier_pas3(Coada* q, const char* nume_fisier)
{
    FILE* fisier = fopen(nume_fisier, "r");
    if (!fisier)
    {
        printf("Eroare la deschiderea fisierului(pas3)!\n");
        return;
    }

    char linie[100];
    fgets(linie, sizeof(linie), fisier);

    while (fgets(linie, sizeof(linie), fisier))
    {
        char* curent;
        char statut[50], nume[100];
        float experienta;
        int varsta;

        curent = strtok(linie, " ");
        if (!curent)
        {
            printf("Eroare statut social!\n");
        }
        strcpy(statut, curent);

        curent = strtok(NULL, ";\n");
        if (!curent)
        {
            printf("Eroare nume!\n");
        }
        strcpy(nume, curent);

        curent = strtok(NULL, ";\n");
        if (!curent)
        {
            printf("Eroare experienta!\n");
        }
        experienta = atof(curent);

        curent = strtok(NULL, ";\n");
        if (!curent)
        {
            printf("Eroare varsta!\n");
        }
        varsta = atoi(curent);

        for(int i=0;i<strlen(statut);i++)
        {
            statut[i] = tolower(statut[i]);
        }
        for(int i=0;i<strlen(nume);i++)
        {
            if(nume[i] == ' ')
            {
                nume[i] = '-';
            }
        }
        enum statut_social ss = string_la_statut_social(statut);

        if (ss != -1)
        {
            adauga_in_coada(q, nume, experienta, varsta, ss);
        }

        else
        {
            printf("Eroare la statut social(citire din fisier pas3)!\n");
            exit(1);
        }
    }

    fclose(fisier);
}