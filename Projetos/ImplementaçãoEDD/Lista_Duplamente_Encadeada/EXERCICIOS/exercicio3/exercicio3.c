/*
Implementar uma função inverter para colocar os itens da lista passada na ordem
inversa. Para implementação da função faça apenas o ajuste dos apontadores da lista,
deixando as variáveis dinâmicas alocadas nas mesmas áreas de memória. A função deve
ter a assinatura abaixo:

void inverter(LISTA *l);
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

// Função para inverter a ordem dos itens na lista
void inverter(LISTA *l) {
    NO *atual = l->cabeca;
    NO *anterior = NULL;

    while (atual != NULL) {
        NO *proximo = atual->prox;
        atual->prox = anterior;
        atual->ant = proximo;

        anterior = atual;
        atual = proximo;
    }

    NO *temp = l->cabeca;
    l->cabeca = l->cauda;
    l->cauda = temp;
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

int main(void){

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

    inverter(minhaLista);
    printf("Lista Invertida: ");
    imprimirLista(minhaLista);


    return 0;
}