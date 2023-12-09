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
#include <stdbool.h>

typedef int ITEM;

typedef struct estrutura {
    ITEM item;
    struct estrutura *ant;
    struct estrutura *prox;
} NO;

typedef struct {
    NO *cabeca;
    NO *cauda;
    int tamanho;
} LISTA;

// Função para criar uma nova lista vazia
LISTA* criarLista() {
    LISTA* lista = (LISTA*)malloc(sizeof(LISTA));
    if (lista != NULL) {
        lista->cabeca = NULL;
        lista->cauda = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

// Função para inserir um item na cabeça da lista duplamente encadeada
void inserir(LISTA *lista, ITEM item) {
    NO *novoNo = (NO *)malloc(sizeof(NO));
    if (novoNo == NULL) {
        perror("Erro ao alocar memória para o novo nó");
        exit(EXIT_FAILURE);
    }

    novoNo->item = item;

    if (lista->cabeca == NULL) {
        novoNo->ant = NULL;
        novoNo->prox = NULL;
        lista->cabeca = novoNo;
        lista->cauda = novoNo;
    } else {
        novoNo->ant = NULL;
        novoNo->prox = lista->cabeca;
        lista->cabeca->ant = novoNo;
        lista->cabeca = novoNo;
    }

    lista->tamanho++;
}


// Função para imprimir os elementos da lista
void imprimirLista(LISTA* lista) {
    NO* atual = lista->cabeca;
    while (atual != NULL) {
        printf("%d ", atual->item);
        atual = atual->prox;
    }
    printf("\n");
}

// Função para liberar a memória alocada pela lista
void liberarLista(LISTA* lista) {
    NO* atual = lista->cabeca;
    while (atual != NULL) {
        NO* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

bool removerDaPos(ITEM *item, int i, LISTA *l) {
    if (i < 0 || i >= l->tamanho) {
        return false; // Posição inválida
    }

    NO *atual = l->cabeca;

    // Percorre a lista até a posição i
    int pos;
    for (pos = 0; pos < i; pos++) {
        atual = atual->prox;
    }

    *item = atual->item; // Armazena o valor do item que será removido

    // Atualiza os ponteiros dos nós vizinhos
    if (atual->ant != NULL) {
        atual->ant->prox = atual->prox;
    } else {
        l->cabeca = atual->prox;
    }

    if (atual->prox != NULL) {
        atual->prox->ant = atual->ant;
    } else {
        l->cauda = atual->ant;
    }

    free(atual); // Libera a memória do nó removido
    l->tamanho--; // Atualiza o tamanho da lista

    return true;
}

int main(void) {

    LISTA* minhaLista = criarLista();

    printf("Insira valores na lista Duplamente Encadeada (digite -1 para encerrar):\n");
    ITEM valor;
    do {
        printf("Digite um valor: ");
        scanf("%d", &valor);
        if (valor != -1) {
            inserir(minhaLista, valor);
        }
    } while (valor != -1);

    printf("Lista Duplamente Encadeada: ");
    imprimirLista(minhaLista);
    printf("Tamanho da lista: %d\n", minhaLista->tamanho);

    int pos;
    printf("Digite a posicao a ser removida: ");
    scanf("%d", &pos);

    ITEM itemRemovido;
    if (removerDaPos(&itemRemovido, pos, minhaLista)) {
        printf("Item removido da posicao %d: %d\n", pos, itemRemovido);
        printf("Lista apos remoção: ");
        imprimirLista(minhaLista);
        printf("Tamanho da lista: %d\n", minhaLista->tamanho);
        printf("\n");
    } else {
        printf("Posicao invalida. Nenhum item foi removido.\n");
    }

    liberarLista(minhaLista);
    return 0;
}
