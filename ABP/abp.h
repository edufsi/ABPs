#include <stdio.h>


struct T_Nodo_ABP{
    struct T_Nodo_ABP *dir;
    struct T_Nodo_ABP *esq;
    int valor;
};

typedef struct T_Nodo_ABP ABP;


int insere_ABP(ABP **arvore, int valor);
void destruir_ABP(ABP **arvore);
ABP* consulta_ABP(ABP *a, int valor, int *num_comp);
int altura_ABP(ABP* arvore);
void PreEsquerdaABP(ABP *arvore);
