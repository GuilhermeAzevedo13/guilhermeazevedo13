#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int ITEM;

typedef struct estrutura {
    ITEM item;
    struct estrutura *prox;
} NO;

typedef struct {
    NO *cabeca;
    NO *ultimo;
    int tamanho;
} LISTA;

void inicializar(LISTA *l) {
    l->cabeca = NULL;
    l->tamanho = 0;
}

NO *criarNo(ITEM item, NO *prox) {
    NO *pNovo = (NO *)malloc(sizeof(NO));
    if (pNovo == NULL) {
        printf("Nao foi possivel alocar memoria para pNovo\n");
        exit(EXIT_FAILURE);
    }
    pNovo->item = item;
    pNovo->prox = prox;
    return pNovo;
}

bool inserir(ITEM item, LISTA *l) {
    l->cabeca = criarNo(item, l->cabeca);
    l->tamanho++;
    return true;
}

void imprimirItem(ITEM i) {
    printf("%d", i);
}

void imprimirLista(LISTA *l) {
    printf("[");
    NO *p = l->cabeca;
    while (p) {
        imprimirItem(p->item);
        if (p->prox) {
            printf(",");
        }
        p = p->prox;
    }
    printf("]\n");
}

void testarInserir(LISTA *l) {
    printf("=> Teste de Inserir\n");
    int qtd;
    printf("Quantos itens deseja guardar na lista? ");
    scanf("%d", &qtd);

    ITEM item;
    int i;
    for (i = 1; i <= qtd; i++) {
        printf("Digite o valor %d/%d: ", i, qtd);
        scanf("%d", &item);
        inserir(item, l);
    }
}

void destruir(LISTA *l) {
    NO *atual = l->cabeca;
    while (atual) {
        NO *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    l->cabeca = NULL;
    l->tamanho = 0;
}

bool inserirNoFinal(ITEM item, LISTA *l) {
    NO *novoNo = criarNo(item, NULL);
    if (l->ultimo == NULL) {
        l->cabeca = novoNo;
        l->ultimo = novoNo;
    } else {
        l->ultimo->prox = novoNo;
        l->ultimo = novoNo;
    }
    l->tamanho++;
    return true;
}

LISTA *clonar(LISTA *l) {
    //LISTA *l2 = (LISTA *)malloc(sizeof(LISTA));
    if (l == NULL) {
        printf("Erro ao alocar memoria para a nova lista\n");
        exit(EXIT_FAILURE);
    }

    //inicializar(l2); // Inicializa a nova lista

    NO *p = l->cabeca;
    while (p != NULL) {
        inserirNoFinal(p->item, l); // Insere copia do item na nova lista
        p = p->prox;
    }


    return l;
}



int main() {
    LISTA l;

    inicializar(&l);
    testarInserir(&l);
    imprimirLista(&l);

    LISTA *novaLista = clonar(&l);
    printf("Lista clonada: ");
    imprimirLista(novaLista);

    destruir(&l);
    destruir(novaLista);

    return 0;
}
