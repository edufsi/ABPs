#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "AVLs.h"

void PreEsquerda_AVL(AVL *arvore){

    if(arvore == NULL) return;
    printf("%d, %s\n", arvore->FB, arvore->alimento);

    PreEsquerda_AVL(arvore->esq);
    PreEsquerda_AVL(arvore->dir);
}



AVL* consulta_AVL(AVL *a, int valor, int *num_comp){
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


void destruir_AVL(AVL** arvore){
    if(*arvore == NULL)
        return;

    destruir_AVL(&((*arvore)->dir));
    destruir_AVL(&((*arvore)->esq));
    free(*arvore);
    
    *arvore = NULL;
}

int altura_AVL(AVL* arvore){
    int altura_direita, altura_esquerda;
    if(arvore == NULL)
        return 0;

    altura_direita = altura_AVL(arvore->dir);
    altura_esquerda = altura_AVL(arvore->esq);

    if(altura_direita > altura_esquerda)
        return 1 + altura_direita;
    else
        return 1 + altura_esquerda;
    
}



int insereAVL(AVL  **arvore, int valor, int *num_rotacoes){
    AVL* pai = NULL;
    AVL* nodo_inserido = (AVL*) malloc(sizeof(AVL));
    AVL* aux = *arvore;
    bool avl_arrumada;

    if(nodo_inserido == NULL) return;

    nodo_inserido->valor = valor;
    nodo_inserido->dir = NULL;
    nodo_inserido->esq = NULL;
    nodo_inserido->FB = 0;

    // Anda na arvore ate encontrar a posicao do pai do nodo
    while(aux != NULL){
        pai = aux;
        if(valor < a->valor)
            aux = aux->esq;

        else if(valor > a->valor)
            aux = aux->dir;

        else
            return -1;

    }

    nodo_inserido->pai = pai;

    

    // Se o nodo nao tem pai, ele eh o primeiro a ser inserido na arvore
    if(nodo_inserido->pai == NULL){
        *arvore = nodo_inserido;
        return 0;
    }


    if(valor < nodo_inserido->pai->valor)
        nodo_inserido->pai->esq = nodo_inserido;
    
    else if(valor > nodo_inserido->pai valor)
        nodo_inserido->pai->dir = nodo_inserido;
    else
        return -1;





    avl_arrumada = false;


    while(!avl_arrumada && nodo_inserido->pai != NULL){

        if(nodo_inserido == nodo_inserido->pai->dir){
            
            switch(nodo_inserido->pai->FB){
            case 0:
                nodo_inserido->pai->FB = -1;
                break;
            case 1:
                nodo_inserido->pai->FB = 0;
                avl_arrumada = true;
                break;
            case -1:
                nodo_inserido = caso_rotacao_esquerda(nodo_inserido->pai, &avl_arrumada, num_rotacoes);
                break;

            }
        }
        else{
            switch(nodo_inserido->pai->FB){
            case 0:
                nodo_inserido->pai->FB = 1;
                break;
            case -1:
                nodo_inserido->pai->FB = 0;
                avl_arrumada = true;
                break;
            case 1:
                nodo_inserido = caso_rotacao_direita(nodo_inserido->pai, &avl_arrumada, num_rotacoes);
                break;

            }
        }

        nodo_inserido = nodo_inserido->pai;

    }      

    while((*arvore)->pai != NULL)
        *arvore = (*arvore)->pai;

    return 0;

}



AVL* irmao_AVL(AVL *arvore) {
    if(arvore->pai == NULL)
        return NULL;
    
    if (arvore == arvore->pai->dir)
        return arvore->pai->esq;
    else
        return arvore->pai->dir;
}


AVL* caso_rotacao_direita(AVL* no, bool *avl_arrumada, int *num_rotacoes){
    AVL* filho = no->esq;
    if(filho->FB == 1)
        no = rotacao_direita(no, num_rotacoes);
    else{
        no = rotacao_dupla_direita(no, num_rotacoes);
    }
    no->FB = 0;
    *avl_arrumada = true;
    return no;
}

AVL* rotacao_dupla_direita (AVL* p, int *num_rotacoes){
    AVL *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    
    if(u->dir != NULL)
        u->dir->pai = u;

    v->esq = u;
    p->esq = v->dir;

    if(p->esq != NULL)
        p->esq->pai = p;

    v->dir = p;

    if (v->FB == 1) 
        p->FB = -1;
    else 
        p->FB = 0;
    if (v->FB == -1) 
        u->FB = 1;
    else 
        u->FB = 0;
    
    v->pai = p->pai;
    p->pai = v;
    u->pai = v;

    p = v;

    *num_rotacoes += 1;

    if(p->pai == NULL)
        return p;

    if(p->dir == p->pai->esq)
        p->pai->esq = p;
    
        
    else if(p->dir == p->pai->dir)
        p->pai->dir = p;
    

    return p;
} 

AVL* rotacao_dupla_esquerda (AVL *p, int *num_rotacoes){
    AVL *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;

    if(z->esq != NULL)
        z->esq->pai = z;

    y->dir = z;
    p->dir = y->esq;

    if(p->dir != NULL)
        p->dir->pai = p;

    y->esq = p;

    if (y->FB == -1) 
        p->FB = 1;
    else 
        p->FB = 0;
    if (y->FB == 1) 
        z->FB = -1;
    else 
        z->FB = 0;


    y->pai = p->pai;
    z->pai = y;
    p->pai = y;

    p = y;

    *num_rotacoes += 1;

    if(p->pai == NULL)
        return p;

    if(p->esq == p->pai->esq)
        p->pai->esq = p;
    
    else if(p->esq == p->pai->dir)
        p->pai->dir = p;
    
    

    return p;
}

AVL* caso_rotacao_esquerda(AVL* no, bool *avl_arrumada, int *num_rotacoes){
    AVL* filho = no->dir;

    if(filho->FB == -1)
        no = rotacao_esquerda(no, num_rotacoes);
    else{
        no = rotacao_dupla_esquerda(no, num_rotacoes);
    }

    
    no->FB = 0;
    *avl_arrumada = true;

    return no;
}

AVL* rotacao_esquerda(AVL *no, int *num_rotacoes){
    AVL *aux;
    int aux_troca;

    aux = no->dir;
    
    no->dir = aux->esq;
    aux->esq = no;

    no->FB = 0;
    aux->pai = no->pai;
    no->pai = aux;

    if(no->dir != NULL)
        no->dir->pai = no;
    
    no = aux;

    *num_rotacoes += 1;

    if(no->pai == NULL)
        return no;
    

    if(no->esq == no->pai->esq)
        no->pai->esq = no;
    else if(no->esq == no->pai->dir)
        no->pai->dir = no;
        
    return no;
} 


AVL* rotacao_direita(AVL *no, int *num_rotacoes){
    AVL *aux;
    int aux_troca;

    aux = no->esq;

    no->esq = aux->dir;
    aux->dir = no;
    no->FB = 0;
    aux->pai = no->pai;
    no->pai = aux;
    
    if(no->esq != NULL)
        no->esq->pai = no;

    no = aux;

    *num_rotacoes += 1;
    if(no->pai == NULL)
        return no;

    if(no->dir == no->pai->esq)
        no->pai->esq = no;
    else if(no->dir == no->pai->dir)
        no->pai->dir = no;



    return no;
}


