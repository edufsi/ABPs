typedef enum{vermelho, preto} Cor;

struct TNoRN{
    struct TNoRN  *pai;
    struct TNoRN *esq;
    struct TNoRN *dir;
    Cor cor;
    int valor;
};

typedef struct TNoRN  RubroNegra;

void caso1(RubroNegra* nodo_inserido, RubroNegra** arvore, int *num_rotacoes);
void caso2(RubroNegra* nodo_inserido, RubroNegra** arvore, int *num_rotacoes);
void caso3(RubroNegra* nodo_inserido, RubroNegra** arvore, int *num_rotacoes);
void caso4(RubroNegra* nodo_inserido, RubroNegra** arvore, int *num_rotacoes);
void caso5(RubroNegra* nodo_inserido, RubroNegra** arvore, int *num_rotacoes);

RubroNegra* consulta_RN(RubroNegra *a, int valor, int *num_comp);

int insereRN(RubroNegra **arvore, int valor, int *num_rotacoes);

RubroNegra *avo(RubroNegra *arvore);

RubroNegra *tio(RubroNegra *arvore);

RubroNegra* rotacaoDireita(RubroNegra *no, int *num_rotacoes);

RubroNegra* rotacaoEsquerda(RubroNegra *no, int *num_rotacoes);

RubroNegra *irmao(RubroNegra *pai, RubroNegra *noAtual);

int filhoEsquerdo(RubroNegra *arvore);

void destruir_RN(RubroNegra **arvore);

int altura_RN(RubroNegra *arvore);

void PreEsquerda(RubroNegra *arvore);
