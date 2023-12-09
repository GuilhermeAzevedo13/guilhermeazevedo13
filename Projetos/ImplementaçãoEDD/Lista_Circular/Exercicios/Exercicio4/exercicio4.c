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

int inserirOrdenado(LISTA *lista, ITEM valor){
    NO *novo = (NO *)malloc(sizeof(NO));
    if (novo == NULL)
        return 0;

    novo->item = valor;

    if (lista->cabeca == NULL){
        novo->prox = novo;
        lista->cabeca = novo;
    }
    else if (valor < lista->cabeca->item){
        NO *aux = lista->cabeca;
        while (aux->prox != lista->cabeca)
            aux = aux->prox;

        novo->prox = lista->cabeca;
        aux->prox = novo;
        lista->cabeca = novo;
    }else{
        NO *ant = lista->cabeca;
        NO *atual = lista->cabeca->prox;

        while (atual != lista->cabeca && valor > atual->item){
            ant = atual;
            atual = atual->prox;
        }

        novo->prox = atual;
        ant->prox = novo;
    }

    lista->tamanho++;
    return 1;
}

NO *buscarNaPosicao(LISTA *lista, int posicao)
{
    if (lista->cabeca == NULL || posicao < 0 || posicao >= lista->tamanho)
        return NULL;

    NO *atual = lista->cabeca;
    int i;
    for (i = 0; i < posicao; i++){
        atual = atual->prox;
    }

    return atual;
}

int inserirNaPosicao(LISTA *lista, ITEM valor, int posicao)
{
    if (posicao < 0 || posicao > lista->tamanho)
        return 0;

    NO *novo = (NO *)malloc(sizeof(NO));
    if (novo == NULL)
        return 0;

    novo->item = valor;

    if (lista->cabeca == NULL){
        novo->prox = novo;
        lista->cabeca = novo;
    }
    else if (posicao == 0){
        NO *aux = lista->cabeca;
        while (aux->prox != lista->cabeca){
            aux = aux->prox;
        }
        novo->prox = lista->cabeca;
        aux->prox = novo;
        lista->cabeca = novo;
    }else{
        NO *atual = buscarNaPosicao(lista, posicao - 1);
        novo->prox = atual->prox;
        atual->prox = novo;
    }

    lista->tamanho++;
    return 1;
}

int removerNaPosicao(LISTA *lista, int posicao)
{
    if (posicao < 0 || posicao >= lista->tamanho)
        return 0;

    if (lista->cabeca == NULL)
        return 0;

    if (posicao == 0)
    {
        NO *aux = lista->cabeca;
        while (aux->prox != lista->cabeca)
            aux = aux->prox;

        NO *removido = lista->cabeca;
        aux->prox = lista->cabeca->prox;
        lista->cabeca = lista->cabeca->prox;
        free(removido);
    }
    else
    {
        NO *anterior = buscarNaPosicao(lista, posicao - 1);
        NO *removido = anterior->prox;
        anterior->prox = removido->prox;
        free(removido);
    }

    lista->tamanho--;
    return 1;
}

void imprimirLista(LISTA *lista)
{
    if (lista->cabeca == NULL)
    {
        printf("A lista esta vazia.\n");
        return;
    }

    NO *atual = lista->cabeca;

    do
    {
        printf("%d ", atual->item);
        atual = atual->prox;
    } while (atual != lista->cabeca);

    printf("\n");
}

void inverter(LISTA *l) {
    NO *anterior = NULL;
    NO *atual = l->cabeca;
    NO *proximo = NULL;

    do {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    } while (atual != l->cabeca);

    l->cabeca = anterior;
}



int main(){
    LISTA minhaLista;

    inicializarLista(&minhaLista);

    printf("Insira valores na lista circular (digite -1 para encerrar):\n");
    ITEM valor;
    do{
        printf("Digite um valor: ");
        scanf("%d", &valor);
        if (valor != -1){
            inserirOrdenado(&minhaLista, valor);
        }
    }while (valor != -1);

    printf("Lista ordenada circular: ");
    imprimirLista(&minhaLista);

    int posicao;
    printf("Digite a posicao para buscar: ");
    scanf("%d", &posicao);

    NO *noEncontrado = buscarNaPosicao(&minhaLista, posicao);
    if (noEncontrado != NULL){
        printf("Valor na posicao %d: %d\n", posicao, noEncontrado->item);
    }else{
        printf("Posicao invalida.\n");
    }

    printf("Digite a posicao para inserir: ");
    scanf("%d", &posicao);
    printf("Digite o valor para inserir: ");
    scanf("%d", &valor);
    if (inserirNaPosicao(&minhaLista, valor, posicao)){
        printf("Valor inserido com sucesso.\n");
        imprimirLista(&minhaLista);
        printf("Novo Tamanho da lista: %d\n", minhaLista.tamanho);
    }else{
        printf("Insercao invalida.\n");
    }

    int posicaoRemover;
    printf("Digite a posicao para remover: ");
    scanf("%d", &posicaoRemover);

    if (removerNaPosicao(&minhaLista, posicaoRemover))
    {
        printf("Valor removido com sucesso.\n");
        printf("Lista ordenada circular apos a remocao: \n");
        imprimirLista(&minhaLista);
        printf("Novo Tamanho da lista: %d\n", minhaLista.tamanho);
    }
    else
    {
        printf("Remocao invalida.\n");
    }

    inverter(&minhaLista);
    printf("Lista invertida com sucesso.\n");
    imprimirLista(&minhaLista);
    printf("Pressione Enter para continuar...");

    return 0;
}
