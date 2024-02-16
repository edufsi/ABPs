#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RubroNegras.h"

int altura_RN(RubroNegra *arvore){
    if(arvore == NULL)
        return 0;

    int altura_dir, altura_esq;

    altura_dir = altura_RN(arvore->dir);
    altura_esq = altura_RN(arvore->esq);

    if(altura_dir > altura_esq)
        return 1 + altura_dir;
    else
        return 1 + altura_esq;
}

void PreEsquerda(RubroNegra *arvore){
    if(arvore == NULL) return;
    printf("%d,%s\n", arvore->cor, arvore->alimento);
    PreEsquerda(arvore->esq);
    PreEsquerda(arvore->dir);
}

RubroNegra* consulta_RN(RubroNegra *a, int valor, int *num_comp){
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



int insereRN(RubroNegra **arvore, int valor, int *num_rotacoes) {
    RubroNegra* pai = NULL;
    RubroNegra* nodo_inserido = (RubroNegra*) malloc(sizeof(RubroNegra));
    RubroNegra* aux = *arvore;
    RubroNegra *nodo_tio, *nodo_avo;


    if(nodo_inserido == NULL) return;

    nodo_inserido->valor = valor;
    nodo_inserido->dir = NULL;
    nodo_inserido->esq = NULL;
    nodo_inserido->cor = vermelho;

    // Anda na arvore ate encontrar a posicao do pai do nodo
    while(aux != NULL){
        pai = aux;
        if (valor < aux->valor)
            aux = aux->esq;
        else if(valor > aux->valor)
            aux = aux->dir;
        else
            return -1;
    }

    nodo_inserido->pai = pai;


    // Primeiro caso: o novo nodo eh o primeiro da arvore, ou seja, nao tem um pai
    if(nodo_inserido->pai == NULL){

		nodo_inserido->cor = preto;
        *arvore = nodo_inserido;
        return 0;
    }

    // Se o novo nodo nao eh o primeiro a ser inserido na arvore, ele eh filho de um nodo. Encontra a posicao que o nodo deve ser inserido:
    if(valor < nodo_inserido->pai->valor)
        nodo_inserido->pai->esq = nodo_inserido;
    else if(valor > nodo_inserido->pai->valor)
        nodo_inserido->pai->dir = nodo_inserido;
    else 
        return -1;


    // A partir daqui, todos os campos do nodo inserido já foram preenchidos. Assim, o procedimento a seguir não difere 
    // da chamada recursiva da função a partir do caso 3
    caso2(nodo_inserido, arvore, num_rotacoes);

    if((*arvore)->pai != NULL)
        *arvore = nodo_inserido->pai;

    return 0;
    
}


// Primeiro caso: o novo nodo eh o primeiro da arvore, ou seja, nao tem um pai
void caso1(RubroNegra* nodo_inserido, RubroNegra** arvore, int *num_rotacoes){
    if(nodo_inserido->pai == NULL){
		nodo_inserido->cor = preto;
        *arvore = nodo_inserido;
        return;
    }

    caso2(nodo_inserido, arvore, num_rotacoes);
}

// Segundo caso: o pai do nodo inserido eh preto. Neste caso, a arvore continua sempre valida
void caso2(RubroNegra* nodo_inserido, RubroNegra** arvore, int *num_rotacoes){
    if(nodo_inserido->pai->cor == preto)
        return;

// A partir daqui garantidamente existe um avo, pois o pai eh garantidamente vermelho

    caso3(nodo_inserido, arvore, num_rotacoes);
}


// Terceiro caso: o pai e o tio sao vermelhos. Neste caso, tornamos ambos pretos e o avo vermelho. Mas se o avo for a raiz, ele nao
// pode ser pintado de vermelho, tendo de continuar preto
void caso3(RubroNegra* nodo_inserido, RubroNegra** arvore, int *num_rotacoes){
    RubroNegra *nodo_tio, *nodo_avo;

    nodo_tio = tio(nodo_inserido);


    if(nodo_tio != NULL && nodo_tio->cor == vermelho){
        nodo_inserido->pai->cor = preto;
        nodo_tio->cor = preto;
        nodo_avo = avo(nodo_inserido); 
        nodo_avo->cor = vermelho;

        caso1(nodo_avo, arvore, num_rotacoes);
        return;
    } 

    caso4(nodo_inserido, arvore, num_rotacoes); 
}


// Quarto caso: o pai eh vermelho mas o tio eh preto E o novo nodo eh um filho em uma direcao e seu pai eh um filho em outra direcao
// Neste caso, uma rotacao deve ser feita e ainda assim deve-se fazer o quinto caso - uma outra rotacao
void caso4(RubroNegra* nodo_inserido, RubroNegra** arvore, int *num_rotacoes){
    RubroNegra *nodo_avo;
    nodo_avo = avo(nodo_inserido);

    if(nodo_inserido == nodo_inserido->pai->dir && nodo_inserido->pai == nodo_avo->esq){
        nodo_inserido = rotacaoEsquerda(nodo_inserido->pai, num_rotacoes); // apos a rotacao, o nodo inserido se tornara pai de seu antigo pai

        nodo_inserido->pai->esq = nodo_inserido;
      // portanto, consideraremos entao que o nodo inserido a partir de agora eh o antigo pai do nodo original
        nodo_inserido = nodo_inserido->esq;
        *num_rotacoes -= 1;
    }
    else if(nodo_inserido == nodo_inserido->pai->esq && nodo_inserido->pai == nodo_avo->dir){
            nodo_inserido = rotacaoDireita(nodo_inserido->pai, num_rotacoes);  
            nodo_inserido->pai->dir = nodo_inserido;
            nodo_inserido = nodo_inserido->dir;

            *num_rotacoes -= 1;
    }

    caso5(nodo_inserido, arvore, num_rotacoes); 
}


// Quinto caso: o pai eh vermelho mas o tio eh preto E o novo nodo eh filho na mesma direcao que seu pai eh filho
// Neste caso, uma rotacao deve ser feita, alem da troca das cores do pai do nodo inserido com seu avo
void caso5(RubroNegra* nodo_inserido, RubroNegra** arvore, int *num_rotacoes){
    RubroNegra *nodo_avo = avo(nodo_inserido);
    nodo_avo = avo(nodo_inserido);

    nodo_inserido->pai->cor = preto;
    nodo_avo->cor = vermelho; // o avo era preto, uma vez que se ele fosse vermelho nao poderia ter um filho vermelho

    if(nodo_inserido == nodo_inserido->pai->esq){
        
        nodo_avo = rotacaoDireita(nodo_avo, num_rotacoes);
        


        if(nodo_avo->pai != NULL){
            if(nodo_avo->dir == nodo_avo->pai->esq)
                nodo_avo->pai->esq = nodo_avo;
            else if(nodo_avo->dir == nodo_avo->pai->dir)
                nodo_avo->pai->dir = nodo_avo;
        }
    }
    else{
        nodo_avo = rotacaoEsquerda(nodo_avo, num_rotacoes);
        if(nodo_avo->pai != NULL){
            if(nodo_avo->esq == nodo_avo->pai->esq)
                nodo_avo->pai->esq = nodo_avo;
            else if(nodo_avo->esq == nodo_avo->pai->dir)
                nodo_avo->pai->dir = nodo_avo;
        }     
    }

    if((*arvore)->pai != NULL)       
        *arvore = nodo_inserido->pai;
}


RubroNegra* avo(RubroNegra *arvore) {
    if ((arvore != NULL) && (arvore->pai != NULL))
            return (arvore->pai)->pai;
    else
        return NULL;
}

RubroNegra* tio(RubroNegra *arvore) {
    RubroNegra *nAvo = avo(arvore);
    if (nAvo == NULL) return NULL;

    if (arvore->pai == nAvo->esq)
        return nAvo->dir;
    else
        return nAvo->esq;

}

RubroNegra* rotacaoDireita(RubroNegra *no, int *num_rotacoes) {
    RubroNegra *aux = no;
    no = aux->esq;
    aux->esq = no->dir;
    no->dir = aux;
    no->pai = aux->pai;

    if(aux->esq != NULL)
        (aux->esq)->pai = aux;

    aux->pai = no;
    *num_rotacoes += 1; 

    return no;
}

RubroNegra* rotacaoEsquerda(RubroNegra *no, int *num_rotacoes) {
    RubroNegra *aux = no;

    no = aux->dir;
    aux->dir = no->esq;
    no->esq = aux;

    no->pai = aux->pai;
    if (aux->dir != NULL)
        (aux->dir)->pai = aux;

    aux->pai = no;
    *num_rotacoes += 1; 

    return no;

}

RubroNegra *irmao(RubroNegra *pai, RubroNegra *noAtual){
    if(pai == NULL) return NULL;

    if(strcmp(pai->dir->alimento, noAtual->alimento) == 0)
        return pai->esq;
    else
        return pai->dir;
}

int filhoEsquerdo(RubroNegra *arvore){
    if(arvore->pai->esq == arvore)
        return 1;
    else
        return 0;
}


void destruir_RN(RubroNegra** arvore){
    if(*arvore == NULL)
        return;

    destruir_RN(&((*arvore)->dir));
    destruir_RN(&((*arvore)->esq));
    free(*arvore);
    
    *arvore = NULL;
}
