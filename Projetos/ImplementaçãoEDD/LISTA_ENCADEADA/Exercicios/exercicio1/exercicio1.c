/* 
Implementar uma função inserirNoFinal para incluir um item no final da lista. Para isso,
utilize um apontador que mantenha o endereço do último elemento da lista. Observe que
tendo este apontador, a inserção é rápida e fácil, já que o novo item será colocado após o
último e será o novo último da lista. Fique atento para a remoção do último valor de uma
lista. Neste caso, a remoção tem que ajustar o apontador último para o nó que
anteriormente era o penúltimo.
 */

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
    NO *ultimo; // Novo ponteiro para o último nó
    int tamanho;
} LISTA;

void inicializar(LISTA *l) {
    l->cabeca = NULL;
    l->ultimo = NULL; // Inicializa o ponteiro do último nó
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
    if (l->ultimo == NULL) {
        l->ultimo = l->cabeca;
    }
    l->tamanho++;
    return true;
}

bool inserirNoFinal(ITEM item, LISTA *l) {
    if (l->ultimo == NULL) {
        l->ultimo = criarNo(item, NULL);
        l->cabeca = l->ultimo;
    } else {
        l->ultimo->prox = criarNo(item, NULL);
        l->ultimo = l->ultimo->prox;
    }
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
    l->ultimo = NULL;
    l->tamanho = 0;
}

int main() {
    LISTA l;

    inicializar(&l);
    testarInserir(&l);
    imprimirLista(&l);

    ITEM itemFinal;
    printf("Digite o valor a ser inserido no final da lista: ");
    scanf("%d", &itemFinal);
    inserirNoFinal(itemFinal, &l);

    imprimirLista(&l);
    destruir(&l);

    return 0;
}

