#include "pas2.h"

Node* creaza_nod_arbore(char* num , float exp , int var , enum statut_social ss)
{
    Node* root = (Node*)malloc(sizeof(Node));
    if(!root)
    {
        printf("Eroare alocare nod arbore lorzi!\n");
        exit(1);
    }

    root->nume = (char*)malloc(strlen(num) + 1);
    if(!(root->nume))
    {
        printf("Eroare alocare nume nod arbore lorzi!\n");
        free(root);
        exit(1);
    }

    strcpy(root->nume, num);
    root->experienta = exp;
    root->varsta = var;
    root->ss = ss;
    root->stanga = root->dreapta = NULL;
    return root;
}

void citire_din_fisier_arbore(Coada* q, const char* nume_fisier)
{
    FILE* fisier = fopen(nume_fisier, "r");
    if (!fisier)
    {
        printf("Eroare la deschiderea fisierului(pas2)!\n");
        return;
    }

    char linie[200];

    if (fgets(linie, sizeof(linie), fisier) == NULL) 
    {
        printf("Fisierul este gol!\n");
        fclose(fisier);
        return;
    }

    while (fgets(linie, sizeof(linie), fisier) != NULL)
    {
        char* curent;
        char statut[50], nume[100];
        float experienta;
        int varsta;

        curent = strtok(linie, " \n");
        if (!curent)
        {
            printf("Eroare nume(pas2)!\n");
            exit(1);
        }
        strcpy(nume, curent);

        curent = strtok(NULL, " \n");
        if (!curent)
        {
            printf("Eroare experienta(pas2)!\n");
            exit(1);
        }
        experienta = atof(curent);

        curent = strtok(NULL, " \n");
        if (!curent)
        {
            printf("Eroare varsta(pas2)!\n");
            exit(1);
        }
        varsta = atoi(curent);

        curent = strtok(NULL, " \n");
        if (!curent)
        {
            printf("Eroare statut social(pas2)!\n");
            exit(1);
        }
        strcpy(statut, curent);

        for (int i = 0; i < strlen(statut); i++)
        {
            statut[i] = tolower(statut[i]);
        }
        enum statut_social ss = string_la_statut_social(statut);
        if (ss == -1)
        {
            printf("Eroare la statut social(citire din fisier) - pas 2!\n");
            exit(1);
        }
        else
        {
            adauga_in_coada(q, nume, experienta, varsta, ss);
        }
    }

    fclose(fisier);
}

Node* adauga_in_arbore_dupa_experienta(Node* root , char* num , float exp , int var , enum statut_social ss)
{
    if(root == NULL)
    {
        return creaza_nod_arbore(num , exp , var , ss);
    }

    Node* curent = root;

    while(curent != NULL)
    {
        if(exp > curent->experienta)
        {
            if(curent->stanga == NULL)
            {
                curent->stanga = creaza_nod_arbore(num , exp , var, ss);
                break;
            }
            curent = curent->stanga;
        }

        else if(exp < curent->experienta)
        {
            if(curent->dreapta == NULL)
            {
                curent->dreapta = creaza_nod_arbore(num , exp , var , ss);
                break;
            }
            curent = curent->dreapta;
        }

        else 
        {
            if(var < curent->varsta)
            {
                if(curent->stanga == NULL)
                {
                    curent->stanga = creaza_nod_arbore(num , exp , var , ss);
                    break;
                }
                    curent = curent->stanga;
            }

            else
            {
                if(curent->dreapta == NULL)
                {
                    curent->dreapta = creaza_nod_arbore(num , exp , var , ss);
                    break;
                }
                curent = curent->dreapta;
            }
        }
    }
    return root;
}

void creaza_arbori_din_coada(Coada* q, Node** arbore_lorzi, Node** arbore_cavaleri_aventurieri)
{
    Node* temp = q->front;
    while (temp != NULL)
    {
        if (temp->ss == LORD)
        {
            *arbore_lorzi = adauga_in_arbore_dupa_experienta(*arbore_lorzi, temp->nume, temp->experienta, temp->varsta, temp->ss);
        }
        else if (temp->ss == CAVALER || temp->ss == AVENTURIER)
        {
            *arbore_cavaleri_aventurieri = adauga_in_arbore_dupa_experienta(*arbore_cavaleri_aventurieri, temp->nume, temp->experienta, temp->varsta, temp->ss);
        }
        temp = temp->prev;
    }
}

void afiseaza_arbore_inordine(Node* root, FILE* f)
{
    if (root == NULL) return;

    afiseaza_arbore_inordine(root->stanga, f);

    fprintf(f, "%s %.2f %d ", root->nume, root->experienta, root->varsta);
    switch (root->ss)
    {
        case LORD:
            fprintf(f, "LORD\n");
            break;
        case CAVALER:
            fprintf(f, "CAVALER\n");
            break;
        case AVENTURIER:
            fprintf(f, "AVENTURIER\n");
            break;
        default:
            fprintf(f, "Necunoscut\n");
            break;
    }

    afiseaza_arbore_inordine(root->dreapta, f);
}

void salvare_arbori_in_fisiere(Coada* q, const char* fisier_lorzi, const char* fisier_cavaleri_aventurieri)
{
    Node* arbore_lorzi = NULL;
    Node* arbore_cavaleri = NULL;
    
    creaza_arbori_din_coada(q, &arbore_lorzi, &arbore_cavaleri);

    FILE* f_lorzi = fopen(fisier_lorzi, "w");
    if (!f_lorzi)
    {
        printf("Eroare la deschiderea fisierului pentru lorzi!\n");
        exit(1);
    }
    fprintf(f_lorzi, "Nume Experienta Varsta Statut_social\n");
    afiseaza_arbore_inordine(arbore_lorzi, f_lorzi);
    fclose(f_lorzi);

    FILE* f_cavaleri = fopen(fisier_cavaleri_aventurieri, "w");
    if (!f_cavaleri) {
        printf("Eroare la deschiderea fisierului pentru cavaleri/aventurieri!\n");
        exit(1);
    }
    fprintf(f_cavaleri, "Nume Experienta Varsta Statut_social\n");
    afiseaza_arbore_inordine(arbore_cavaleri, f_cavaleri);
    fclose(f_cavaleri);

    elibereaza_arbore(arbore_lorzi);
    elibereaza_arbore(arbore_cavaleri);
}

void elibereaza_arbore(Node* root)
{
    if (root == NULL) return;
    elibereaza_arbore(root->stanga);
    elibereaza_arbore(root->dreapta);
    free(root->nume);
    free(root);
}