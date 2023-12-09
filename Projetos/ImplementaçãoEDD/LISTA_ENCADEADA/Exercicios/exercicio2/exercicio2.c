/*
Implementar uma função para remover o item de uma certa posição da lista. A função
deve checar se a posição é válida, ou seja, se é referente a uma posição existente na lista.
Caso a remoção seja bem-sucedida, a função retorna true e o parâmetro item contém o
valor que foi removido da lista. Caso contrário, a função retorna false e a lista não será
alterada. A função deve ter a assinatura abaixo:

bool removerDaPos(ITEM *item, int i, LISTA *l);
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

bool removerDaPos(ITEM *item, int i, LISTA *l) {
    if (i < 0 || i >= l->tamanho) {
        // A posição não é válida
        return false;
    }

    if (i == 0) {
        // Remoção na cabeça da lista
        NO *temp = l->cabeca;
        *item = temp->item;
        l->cabeca = temp->prox;
        free(temp);
    } else {
        // Remoção em outra posição
        NO *anterior = NULL;
        NO *atual = l->cabeca;
        int j;
        for (j = 0; j < i; j++) {
            anterior = atual;
            atual = atual->prox;
        }
        *item = atual->item;
        anterior->prox = atual->prox;
        free(atual);
    }

    l->tamanho--;
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

int main() {
    LISTA l;

    inicializar(&l);
    testarInserir(&l);
    imprimirLista(&l);

    int pos;
    printf("Digite a posicao a ser removida (0 a %d): ",l.tamanho-1);
    scanf("%d", &pos);

    ITEM itemRemovido;
    if (removerDaPos(&itemRemovido, pos, &l)) {
        printf("Item removido: %d\n", itemRemovido);
        printf("Lista apos a remocao: ");
        imprimirLista(&l);
    } else {
        printf("Posicao invalida ou lista vazia.\n");
    }

    destruir(&l);

    return 0;
}
