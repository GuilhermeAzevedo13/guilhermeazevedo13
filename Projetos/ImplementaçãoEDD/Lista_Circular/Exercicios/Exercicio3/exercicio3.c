/*
Implementar uma função clonar para criar uma lista nova contendo uma cópia dos itens
da lista passada como parâmetro. A função deve ter a assinatura abaixo:

LISTA * clonar(LISTA *l);
*/

#include <stdio.h>
#include <stdlib.h>

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

LISTA* clonar(LISTA* l) {
    LISTA* listaClonada = (LISTA*)malloc(sizeof(LISTA));
    NO* clonar = l->cabeca;
    
    if (clonar == NULL) {
        listaClonada->cabeca = NULL;
        listaClonada->tamanho = 0;
        return listaClonada;
    }
    
    NO* novoNo = criarNo(clonar->item, NULL);
    listaClonada->cabeca = novoNo;
    listaClonada->tamanho = 1;
    
    while (clonar->prox != l->cabeca) {
        clonar = clonar->prox;
        novoNo->prox = criarNo(clonar->item, NULL);
        novoNo = novoNo->prox;
        listaClonada->tamanho++;
    }
    
    novoNo->prox = listaClonada->cabeca;
    
    return listaClonada;
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

    clonar(&minhaLista);
    printf("Lista Circular Clonada: ");
    imprimirLista(&minhaLista);



    return 0;
}

