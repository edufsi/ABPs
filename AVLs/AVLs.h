#include <stdbool.h>

struct NoAVL{
    struct NoAVL *esq;
    struct NoAVL *dir;
    struct NoAVL *pai;
    int valor;
    int FB;
};

typedef struct NoAVL AVL;

AVL* irmao_AVL(AVL *arvore);
AVL* rotacao_dupla_direita (AVL* p, int *num_rotacoes);
AVL* rotacao_dupla_esquerda (AVL *p, int *num_rotacoes);
int insereAVL(AVL **arvore, int valor, int *num_rotacoes);
void destruir_AVL(AVL **arvore);
AVL* consulta_AVL(AVL *a, int valor, int *num_comp);
int altura_AVL(AVL* arvore);
AVL* caso_rotacao_esquerda(AVL* no, bool *avl_arrumada, int *num_rotacoes);
AVL* caso_rotacao_direita(AVL* no, bool *avl_arrumada, int *num_rotacoes);
AVL* rotacao_esquerda(AVL *no, int *num_rotacoes);
AVL* rotacao_direita(AVL *no, int *num_rotacoes);
void PreEsquerda_AVL(AVL *arvore);
