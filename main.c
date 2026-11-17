#include "pas6.h"
#include "pas7.h"

int main()
{
    ///pas1
    Coada* q = creare_coada();
    citire_din_fisier(q, "./Pas_1/candidati.csv");
    afisare_in_fisier(q, "./Pas_1/test_1.csv");
    elibereaza_coada(q);

    ///pas2
    Coada* p = creare_coada();
    citire_din_fisier_arbore(p , "./Pas_1/test_1.csv");
    salvare_arbori_in_fisiere(p , "./Pas_2/test_2_lorzi.csv" , "./Pas_2/test_2_cavaleri_aventurieri.csv");
    elibereaza_coada(p);

    ///pas3
    Coada* coadaContestatii = creare_coada();
    Coada* coadaLista = creare_coada();
    citire_din_fisier_pas3(coadaContestatii, "./Pas_3/contestatii.csv");
    citire_din_fisier_arbore(coadaLista, "./Pas_2/test_2_lorzi.csv");
    sterge_elemente_comune(coadaLista , coadaContestatii);
    salvare_arbori_in_fisiere(coadaLista , "./Pas_3/test_3_lorzi.csv" , "./Pas_3/test_3_ca.csv");
    elibereaza_coada(coadaLista);
    elibereaza_coada(coadaContestatii);

    ///pas4 + pas5
    Heap* heap = creare_heap_din_fisiere("./Pas_4/trasee.csv" , "./Pas_3/test_3_lorzi.csv" , "./Pas_2/test_2_cavaleri_aventurieri.csv");
    afiseaza_heap_in_fisier(heap, "./Pas_4/test_4.csv");
    Heap* alt_heap = citire_heap_pas5("./Pas_4/trasee.csv" , "./Pas_3/test_3_lorzi.csv" , "./Pas_2/test_2_cavaleri_aventurieri.csv");
    heapifup_pas_cu_pas(heap);
    afiseaza_heap_in_fisier(heap , "./Pas_5/test_5.csv");
    free(heap->primii8);
    free(alt_heap->primii8);
    eliberare_trasee(heap->vector_trasee);
    eliberare_trasee(alt_heap->vector_trasee);
    elibereaza_coada(heap->lorzi);
    elibereaza_coada(heap->ca);
    elibereaza_coada(alt_heap->lorzi);
    elibereaza_coada(alt_heap->ca);
    free(heap);
    free(alt_heap);

    ///pas6
    Heap* h = creare_heap_din_fisiere("./Pas_4/trasee.csv" , "./Pas_3/test_3_lorzi.csv" , "./Pas_2/test_2_cavaleri_aventurieri.csv");
    actualizare_experienta(h);
    afisare_pas6(h , "./Pas_6/test_6.csv");
    free(h->primii8);
    eliberare_trasee(h->vector_trasee);
    elibereaza_coada(h->lorzi);
    elibereaza_coada(h->ca);
    free(h);

    ///pas7
    int intrare[N], iesire[N];
    Graph* graf = creare_din_fisier("./Pas_7/drumuri.csv", intrare, iesire);
    if(graf == NULL) return 1;
    FILE* fout = fopen("./Pas_7/test_7.csv", "w");
    if(!fout)
    {
        printf("Eroare la scrierea in fisierul de iesire!\n");
        return 1;
    }

    genereaza_trasee(graf, intrare, iesire, fout);
    eliberare_graf(graf);
    fclose(fout);
    return 0;
}
