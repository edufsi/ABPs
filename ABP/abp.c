#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.h"


int insere_ABP(ABP** arvore, int valor){
    ABP *ant_arvore = NULL;
    ABP *raiz_original = *arvore;
    ABP *novo_nodo =  (ABP*) malloc(sizeof(ABP));

    novo_nodo->valor = valor;
    novo_nodo->esq = NULL;
    novo_nodo->dir = NULL;

    while(*arvore != NULL){
        ant_arvore = *arvore;

        if(valor < (*arvore)->valor)
            *arvore = (*arvore)->esq;
        else if(valor > (*arvore)->valor)
            *arvore = (*arvore)->dir;
        else
            return -1;
  
    }

    if(ant_arvore == NULL){
        *arvore = novo_nodo;
        return 0;
    }
        
    
    if(valor < ant_arvore->valor)
        ant_arvore->esq = novo_nodo;
    else if(valor > ant_arvore->valor)
        ant_arvore->dir = novo_nodo;
    else
        return -1;

    *arvore = raiz_original;
    return 0;
    
}

ABP* consulta_ABP(ABP *a, int valor, int *num_comp){
    while (a!=NULL){

        *num_comp += 1;

        if (valor == a->valor){
            return a;
        }
        
        else{
            if (valor < a->valor)
                a = a->esq;
            else
                a = a->dir;
            }
    }
 
    return NULL;
} 


void destruir_ABP(ABP **arvore){
    if(*arvore == NULL)
        return;
    destruir_ABP(&((*arvore)->dir));
    destruir_ABP(&((*arvore)->esq));
    free(*arvore);
    *arvore = NULL;
}



int altura_ABP(ABP* arvore){
    int altura_direita, altura_esquerda;
    if(arvore == NULL)
        return 0;

    altura_direita = altura_ABP(arvore->dir);
    altura_esquerda = altura_ABP(arvore->esq);

    if(altura_direita > altura_esquerda)
        return 1 + altura_direita;
    else
        return 1 + altura_esquerda;
    
}

void PreEsquerdaABP(ABP *arvore){
    if(arvore == NULL) return;
    printf("%s\n", arvore->alimento);
    PreEsquerdaABP(arvore->esq);
    PreEsquerdaABP(arvore->dir);

}

