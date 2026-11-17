#include "pas1.h"

Coada* creare_coada()
{
    Coada* q = (Coada*)malloc(sizeof(Coada));
    if(!q)
    {
        printf("Eroare la alocarea cozii in functia creare_coada!\n");
        exit(1);
    }
    q->front = q->rear = NULL;
    return q;
}

Node* creare_nod(char* nume , float experienta , int varsta , enum statut_social ss)
{
    Node* nod_nou = (Node*)malloc(sizeof(Node));
    if(!nod_nou)
    {
        printf("Eroare la alocarea nodului nou in functia creare_nod!\n");
        exit(1);
    }

    nod_nou->nume = (char*)malloc(strlen(nume)+1);
    if(!nod_nou->nume)
    {
        printf("Eroare la alocarea numelui in functia creare_nod!\n");
        free(nod_nou);
        exit(1);
    }

    strcpy(nod_nou->nume , nume);
    nod_nou->experienta = experienta;
    nod_nou->varsta = varsta;
    nod_nou->ss = ss;
    nod_nou->next = NULL;
    nod_nou->prev = NULL;
    return nod_nou;
}

void adauga_in_coada(Coada* q , char* nume , float experienta , int varsta , enum statut_social ss)
{
    Node* nod_nou = creare_nod(nume , experienta , varsta , ss);
    if(!nod_nou) exit(1);
    if(q->rear == NULL) q->front = q->rear = nod_nou;
    else
    {
        q->rear->prev = nod_nou;
        nod_nou->next = q->rear;
        q->rear = nod_nou;
    }
}

void afiseaza_coada(Coada* q)
{
    Node* temp = q->front;
    while(temp != NULL)
    {
        printf("Nume: %10s\t Experienta: %.2f\t Varsta: %d\t" , temp->nume , temp->experienta , temp->varsta);
        switch(temp->ss)
        {
            case 1:
                printf("Statut social: LORD\n");
                break;
            case 2:
                printf("Statut social: CAVALER\n");
                break;
            case 3:
                printf("Statut social: AVENTURIER\n");
                break;
            default:
                printf("Statut social: Necunoscut\n");
                break;
        }
        temp = temp->prev;
    }
}

enum statut_social string_la_statut_social(char* statut_str)
{
    if (strcmp(statut_str, "lord") == 0)
    {
        return LORD;
    }
    else if (strcmp(statut_str, "cavaler") == 0)
    {
        return CAVALER;
    }
    else if (strcmp(statut_str, "aventurier") == 0)
    {
        return AVENTURIER;
    }
    return -1;
}

void citire_din_fisier(Coada* q, const char* nume_fisier)
{
    FILE* fisier = fopen(nume_fisier, "r");
    if (!fisier)
    {
        printf("Eroare la deschiderea fisierului!\n");
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

        curent = strtok(NULL, " ;\n");
        if (!curent) 
        {
            printf("Eroare varsta!\n");
        }
        varsta = atoi(curent);

        for(int i=0;i<strlen(statut);i++)
        {
            statut[i] = tolower(statut[i]);
        }
        enum statut_social ss = string_la_statut_social(statut);

        if (ss != -1)
        {
            adauga_in_coada(q, nume, experienta, varsta, ss);
        }

        else
        {
            printf("Eroare la statut social(citire din fisier)!\n");
            exit(1);
        }
    }

    fclose(fisier);
}

void afisare_in_fisier(Coada* q , const char* nume_fisier)
{
    FILE* fisier = fopen(nume_fisier , "w");
    if (!fisier)
    {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }
    fprintf(fisier , "Nume Experienta Varsta Statut_social\n");

    Node* temp = q->front;
    while(temp != NULL)
    {
        char noul_nume[50];
        strcpy(noul_nume , temp->nume);
        for(int i=0;i<strlen(noul_nume);i++)
        {
            if(noul_nume[i] == ' ')
            {
                noul_nume[i] = '-';
            }
            if(i == 0 || noul_nume[i-1] ==  '-')
            {
                noul_nume[i] = toupper(noul_nume[i]);
            }
            else
            {
                noul_nume[i] = tolower(noul_nume[i]);
            }
        }
        fprintf(fisier , "%s %.2f %d " , noul_nume , temp->experienta , temp->varsta);
        switch(temp->ss)
        {
            case 1:
                fprintf(fisier , "LORD\n");
                break;
            case 2:
                fprintf(fisier , "CAVALER\n");
                break;
            case 3:
                fprintf(fisier , "AVENTURIER\n");
                break;
            default:
                fprintf(fisier , "Necunoscut\n");
                break;
        }
        temp = temp->prev;
    }
    fclose(fisier);
}

void elibereaza_coada(Coada* q)
{
    Node* temp;
    while(q->front != NULL)
    {
        temp = q->front;
        q->front = q->front->prev;
        free(temp->nume);
        free(temp);
    }
    free(q);
    q = NULL;
}


