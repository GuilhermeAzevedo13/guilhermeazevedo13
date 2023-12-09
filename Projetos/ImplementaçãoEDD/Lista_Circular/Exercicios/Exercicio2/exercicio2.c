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

typedef struct estrutura
{
    ITEM item;
    struct estrutura *prox;
} NO;

typedef struct
{
    NO *cabeca;
    int tamanho;
} LISTA;

void inicializarLista(LISTA *lista){
    lista->cabeca = NULL;
    lista->tamanho = 0;
}

NO* criarNo(ITEM item, NO* prox){
    NO* novoNo = (NO*)malloc(sizeof(NO));
    if (novoNo)
    {
        novoNo->item = item;
        novoNo->prox = prox;
    }
    return novoNo;
}


// Função para criar uma nova lista circular vazia
LISTA *criarLista(){
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if (lista == NULL){
        printf("Erro ao criar a lista");
        exit(EXIT_FAILURE);
    }

    lista->cabeca = NULL;
    lista->tamanho = 0;
    return lista;
}

// Função para inserir um item na cabeça da lista circular
void inserir(LISTA *lista, ITEM item){
    NO *novoNo = (NO *)malloc(sizeof(NO));
    if (novoNo == NULL){
        perror("Erro ao alocar memória para o novo nó");
        exit(EXIT_FAILURE);
    }

    novoNo->item = item;

    if (lista->cabeca == NULL){
        novoNo->prox = novoNo; // Lista vazia, o próximo nó aponta para ele mesmo
    }else{
        NO *ultimo = lista->cabeca;
        while (ultimo->prox != lista->cabeca)
        {
            ultimo = ultimo->prox;
        }
        novoNo->prox = lista->cabeca; // O próximo nó aponta para a antiga cabeça
        ultimo->prox = novoNo; // O último nó aponta para o novo nó
    }

    lista->cabeca = novoNo; // Atualiza a cabeça da lista
    lista->tamanho++;
}


// Função para imprimir os elementos da lista circular
void imprimirLista(LISTA *lista){
    if (lista->cabeca == NULL){
        printf("A lista está vazia.\n");
        return;
    }

    NO *atual = lista->cabeca;
    do{
        printf("%d ", atual->item);
        atual = atual->prox;
    } while (atual != lista->cabeca);
    printf("\n");
}

bool removerDaPos(ITEM *item, int i, LISTA *l) {
    if (i < 0 || i >= l->tamanho) {
        return false; // Posição inválida
    }

    NO *anterior = NULL;
    NO *atual = l->cabeca;
    int pos;
    for (pos = 0; pos < i; pos++) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior != NULL) {
        anterior->prox = atual->prox;
    } else {
        NO *ultimo = l->cabeca;
        while (ultimo->prox != l->cabeca) {
            ultimo = ultimo->prox;
        }
        l->cabeca = atual->prox;
        ultimo->prox = l->cabeca;
    }

    *item = atual->item;
    free(atual);
    l->tamanho--;

    return true;
}

int main(void){

    LISTA minhaLista;

    inicializarLista(&minhaLista);

    printf("Insira valores na lista circular (digite -1 para encerrar):\n");
    ITEM valor;
    do{
        printf("Digite um valor: ");
        scanf("%d", &valor);
        if (valor != -1){
            inserir(&minhaLista, valor);
        }
    }while (valor != -1);

    printf("Lista Circular: ");
    imprimirLista(&minhaLista);
    printf("\n");

    int pos;
    printf("Digite a posicao para remover: ");
    scanf("%d", &pos);

    ITEM itemRemovido;
    if (removerDaPos(&itemRemovido, pos, &minhaLista)) {
        printf("Item removido: %d\n", itemRemovido);
        printf("Lista apos remocao: ");
        imprimirLista(&minhaLista);
    } else {
        printf("Posicao invalida!\n");
    }

    return 0;
}