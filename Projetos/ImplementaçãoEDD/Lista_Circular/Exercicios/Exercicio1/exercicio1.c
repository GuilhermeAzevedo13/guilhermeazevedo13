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

typedef struct estrutura{
    ITEM item;
    struct estrutura *prox;
} NO;

typedef struct{
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
        while (ultimo->prox != lista->cabeca){
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

void inserirNoFinal(ITEM item, LISTA *lista) {
    NO *novoNo = criarNo(item, lista->cabeca); // Cria um novo nó com o próximo apontando para a cabeça

    if (novoNo == NULL) {
        perror("Erro ao alocar memória para o novo nó");
        exit(EXIT_FAILURE);
    }

    if (lista->cabeca == NULL) { // Se a lista está vazia
        novoNo->prox = novoNo; // O próximo nó aponta para ele mesmo
        lista->cabeca = novoNo; // Atualiza a cabeça da lista
    } else {
        NO *ultimo = lista->cabeca;
        while (ultimo->prox != lista->cabeca) {
            ultimo = ultimo->prox;
        }
        novoNo->prox = lista->cabeca; // O próximo nó aponta para a antiga cabeça
        ultimo->prox = novoNo; // O último nó aponta para o novo nó
    }

    lista->tamanho++;
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
    printf("Tamanho da lista: %d\n", minhaLista.tamanho);
    printf("\n");

    ITEM itemFinal;
    printf("Digite o valor a ser inserido no final da lista: ");
    scanf("%d", &itemFinal);
    inserirNoFinal(itemFinal, &minhaLista);
    imprimirLista(&minhaLista);
    printf("\n");
    printf("Tamanho da lista: %d\n", minhaLista.tamanho);
    printf("\n");

    return 0;
}
