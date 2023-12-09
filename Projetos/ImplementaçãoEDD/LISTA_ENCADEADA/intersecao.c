#include <stdio.h>
#include <stdlib.h>

typedef int ITEM;

typedef struct estrutura {
    ITEM item;
    struct estrutura *prox;
} NO;

typedef struct {
    NO *cabeca;
    int tamanho;
} LISTA;

LISTA* criarLista() {
    LISTA* lista = (LISTA*)malloc(sizeof(LISTA));
    if (lista != NULL) {
        lista->cabeca = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

void inserir(LISTA *lista, ITEM item) {
    NO *novoNo = (NO *)malloc(sizeof(NO));
    if (novoNo == NULL) {
        perror("Erro ao alocar memória para o novo nó");
        exit(EXIT_FAILURE);
    }

    novoNo->item = item;
    novoNo->prox = lista->cabeca;
    lista->cabeca = novoNo;
    lista->tamanho++;
}

LISTA *intersecao(LISTA *lista1, LISTA *lista2) {
    LISTA *intersecaoLista = criarLista();
    
    NO *atual1 = lista1->cabeca;
    while (atual1 != NULL) {
        NO *atual2 = lista2->cabeca;
        while (atual2 != NULL) {
            if (atual1->item == atual2->item) {
                inserir(intersecaoLista, atual1->item);
                break;
            }
            atual2 = atual2->prox;
        }
        atual1 = atual1->prox;
    }

    return intersecaoLista;
}

void imprimirLista(LISTA *lista) {
    NO *atual = lista->cabeca;
    while (atual != NULL) {
        printf("%d ", atual->item);
        atual = atual->prox;
    }
    printf("\n");
}

void liberarLista(LISTA *lista) {
    NO *atual = lista->cabeca;
    while (atual != NULL) {
        NO *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

int main(void){

    LISTA *lista1 = criarLista();
    LISTA *lista2 = criarLista();

    printf("Insira valores na lista 1 (digite -1 para encerrar):\n");
    ITEM valor = 0;
    do{
        printf("Digite um valor: ");
        scanf("%d", &valor);
        if (valor != -1){
            inserir(lista1, valor);
        }
    }while (valor != -1);

    printf("Lista 1: ");
    imprimirLista(lista1);
    printf("Tamanho da lista: %d\n", lista1->tamanho);
    printf("\n");

    printf("Insira valores na lista 2 (digite -1 para encerrar):\n");
    valor = 0;
    do{
        printf("Digite um valor: ");
        scanf("%d", &valor);
        if (valor != -1){
            inserir(lista2, valor);
        }
    }while (valor != -1);

    printf("Lista 2: ");
    imprimirLista(lista2);
    printf("Tamanho da lista: %d\n", lista2->tamanho);
    printf("\n");

    LISTA *intersecaoLista = intersecao(lista1, lista2);
    printf("Intersecao: ");
    imprimirLista(intersecaoLista);


    liberarLista(lista1);
    liberarLista(lista2);
    liberarLista(intersecaoLista);

    return 0;
}