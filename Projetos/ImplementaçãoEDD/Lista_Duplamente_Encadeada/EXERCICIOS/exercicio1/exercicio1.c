/*
Implementar uma função inserirNoFinal para incluir um item no final da lista. Para isso,
utilize um apontador cauda que já está disponível. Observe que tendo este apontador, a
inserção é rápida e fácil, já que o novo item será colocado após o último e será a nova
cauda da lista.
*/


#include <stdio.h>
#include <stdlib.h>

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

// Função para inserir um item no final da lista duplamente encadeada
void inserirNoFinal(LISTA *lista, ITEM item) {
    NO *novoNo = (NO *)malloc(sizeof(NO));
    if (novoNo == NULL) {
        perror("Erro ao alocar memória para o novo nó");
        exit(EXIT_FAILURE);
    }

    novoNo->item = item;
    novoNo->ant = lista->cauda; // O nó anterior do novo nó aponta para a antiga cauda
    novoNo->prox = NULL; // O próximo nó do novo nó é nulo

    if (lista->cauda == NULL) {
        lista->cabeca = novoNo; // Se a lista está vazia, o novo nó será tanto a cabeça quanto a cauda
    } else {
        lista->cauda->prox = novoNo; // O próximo nó da antiga cauda aponta para o novo nó
    }

    lista->cauda = novoNo; // Atualiza a cauda da lista
    lista->tamanho++;
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
    printf("\n");
    printf("Tamanho da lista: %d\n", minhaLista->tamanho);

    ITEM itemFinal;
    printf("Digite o valor a ser inserido no final da lista: ");
    scanf("%d", &itemFinal);
    inserirNoFinal(minhaLista, itemFinal);
    imprimirLista(minhaLista);
    printf("Tamanho da lista: %d\n", minhaLista->tamanho);
    printf("\n");

    liberarLista(minhaLista);
    return 0;
}
