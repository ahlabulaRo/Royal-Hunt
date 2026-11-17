#ifndef PAS1_H
#define PAS1_H

//#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

enum statut_social{LORD=1 , CAVALER , AVENTURIER};

typedef struct Node 
{
    char* nume;
    float experienta;
    int varsta;
    enum statut_social ss;
    int traseu[4];
    int id;
    struct Node* next;
    struct Node* prev;
    struct Node* stanga;
    struct Node* dreapta;
}Node;

typedef struct
{
    Node* front;
    Node* rear;
}Coada;

typedef struct Heap
{
    Node** primii8;
    Coada* lorzi;
    Coada* ca;
    int** vector_trasee;
    int size, capacity;
}Heap;

Coada* creare_coada();
Node* creare_nod(char* nume , float experienta , int varsta , enum statut_social ss);
void adauga_in_coada(Coada* q , char* nume , float experienta , int varsta , enum statut_social ss);
void afiseaza_coada(Coada* q);
enum statut_social string_la_statut_social(char* statut_str);
void citire_din_fisier(Coada* q, const char* nume_fisier);
void afisare_in_fisier(Coada* q , const char* nume_fisier);
void elibereaza_coada(Coada* q);

#endif