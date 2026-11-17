#ifndef PAS2_H
#define PAS2_H

#include "pas1.h"

Node* creaza_nod_arbore(char* num , float exp , int var , enum statut_social ss);
Node* adauga_in_arbore_dupa_experienta(Node* root , char* num , float exp , int var , enum statut_social ss);
void citire_din_fisier_arbore(Coada* q , const char* nume_fisier);
void creaza_arbori_din_coada(Coada* q, Node** arbore_lorzi, Node** arbore_cavaleri_aventurieri);
void afiseaza_arbore_inordine(Node* root, FILE* f);
void salvare_arbori_in_fisiere(Coada* q, const char* fisier_lorzi, const char* fisier_cavaleri_aventurieri);
void elibereaza_arbore(Node* root);

#endif