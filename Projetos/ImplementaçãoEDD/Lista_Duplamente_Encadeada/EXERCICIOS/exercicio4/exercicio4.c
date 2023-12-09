/*
Baseando-se nas funções disponíveis na Lista Encadeada, implemente uma Lista
Duplamente Encadeada Ordenada, isto é, que considera o valor dos itens como critério
para manter os valores na ordem crescente, sendo o menor valor na cabeça da lista.
Aproveite e otimize funções de busca e remoção para interromperem a operação quando
chegarem a um valor maior do que o que se deseja buscar ou remover.
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

void inserirItemOrdenado(LISTA *lista, ITEM item) {
    NO *novoNo = (NO*)malloc(sizeof(NO));
    if (novoNo == NULL) {
        perror("Erro ao alocar memoria para o novo no");
        exit(EXIT_FAILURE);
    }
    novoNo->item = item;
    novoNo->ant = NULL;
    novoNo->prox = NULL;

    if (lista->cabeca == NULL) {
        lista->cabeca = novoNo;
        lista->cauda = novoNo;
    } else if (item <= lista->cabeca->item) {
        novoNo->prox = lista->cabeca;
        lista->cabeca->ant = novoNo;
        lista->cabeca = novoNo;
    } else if (item >= lista->cauda->item) {
        novoNo->ant = lista->cauda;
        lista->cauda->prox = novoNo;
        lista->cauda = novoNo;
    } else {
        NO *atual = lista->cabeca;
        while (atual->prox != NULL && item > atual->prox->item) {
            atual = atual->prox;
        }
        novoNo->ant = atual;
        novoNo->prox = atual->prox;
        atual->prox->ant = novoNo;
        atual->prox = novoNo;
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

NO* buscarValor(LISTA *lista, ITEM valor) {
    NO *atual = lista->cabeca;

    while (atual != NULL && atual->item <= valor) {
        if (atual->item == valor) {
            return atual; // Valor encontrado
        }
        atual = atual->prox;
    }

    return NULL; // Valor não encontrado ou maior que o valor desejado
}

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

void inserirNaPosicao(LISTA *lista, ITEM item, int posicao) {
    if (posicao < 1 || posicao > lista->tamanho + 1) {
        printf("Posicao invalida.\n");
        return;
    }

    NO *novoNo = (NO *)malloc(sizeof(NO));
    if (novoNo == NULL) {
        perror("Erro ao alocar memoria para o novo no");
        exit(EXIT_FAILURE);
    }
    novoNo->item = item;

    if (posicao == 1) {
        novoNo->ant = NULL;
        novoNo->prox = lista->cabeca;
        if (lista->cabeca != NULL) {
            lista->cabeca->ant = novoNo;
        }
        lista->cabeca = novoNo;
    } else if (posicao == lista->tamanho + 1) {
        novoNo->ant = lista->cauda;
        novoNo->prox = NULL;
        lista->cauda->prox = novoNo;
        lista->cauda = novoNo;
    } else {
        NO *atual = lista->cabeca;
        int i;
        for (i = 1; i < posicao - 1; i++) {
            atual = atual->prox;
        }
        novoNo->ant = atual;
        novoNo->prox = atual->prox;
        atual->prox->ant = novoNo;
        atual->prox = novoNo;
    }

    lista->tamanho++;
}

LISTA* clonarLista(LISTA *original) {
    LISTA *novaLista = criarLista();
    NO *atual = original->cabeca;

    while (atual != NULL) {
        inserirItemOrdenado(novaLista, atual->item);
        atual = atual->prox;
    }

    return novaLista;
}

int main(void){

    LISTA *minhaLista = criarLista();
    int opcao = 0, valor = 0;

    ITEM valorInserir;
    int posicaoInserir;

    ITEM valorBusca;

    int pos;

    LISTA *copiaLista = clonarLista(minhaLista);

    do{
        system("cls");

        printf("Menu:\n");
        printf("1. Inserir item Ordenado\n");
        printf("2. Remover por posicao\n");
        printf("3. Buscar valor na lista\n");
        printf("4. Imprimir lista\n");
        printf("5. Inverter lista\n");
        printf("6. Inserir na Posicao\n");
        printf("7. Clonar a Lista\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                do {
                    printf("Digite um valor: ");
                    scanf("%d", &valor);
                    if (valor != -1) {
                        inserirItemOrdenado(minhaLista, valor);
                    }
                } while (valor != -1);

                printf("Lista Duplamente Encadeada: ");
                imprimirLista(minhaLista);
                printf("Tamanho da lista: %d\n", minhaLista->tamanho);
                system("pause");
                getchar();
                break;

            case 2:
                printf("Digite a posicao a ser removida: ");
                scanf("%d", &pos);

                ITEM itemRemovido;
                if (removerDaPos(&itemRemovido, pos, minhaLista)) {
                printf("Item removido da posicao %d: %d\n", pos, itemRemovido);
                printf("Lista apos remocao: ");
                imprimirLista(minhaLista);
                printf("Tamanho da lista: %d\n", minhaLista->tamanho);
                printf("\n");
                } else {
                printf("Posicao invalida. Nenhum item foi removido.\n");
                }
                system("pause");
                getchar();
                break;

            case 3:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valorBusca);

                NO *noEncontrado = buscarValor(minhaLista, valorBusca);
                if (noEncontrado != NULL) {
                    printf("Valor encontrado: %d\n", noEncontrado->item);
                } else {
                    printf("Valor nao encontrado ou maior que o valor desejado.\n");
                }
                system("pause");
                getchar();
                break;

            case 4:
                printf("Lista Duplamente Encadeada: ");
                imprimirLista(minhaLista);
                printf("Tamanho da lista: %d\n", minhaLista->tamanho);
                system("pause");
                getchar();
                break;

            case 5:
                inverter(minhaLista);
                printf("Lista Invertida: ");
                imprimirLista(minhaLista);
                system("pause");
                getchar();
                break;

            case 6:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valorInserir);
                printf("Digite a posicao de insercao (1 a %d): ", minhaLista->tamanho + 1);
                scanf("%d", &posicaoInserir);

                inserirNaPosicao(minhaLista, valorInserir, posicaoInserir);

                printf("Lista Atualizada: ");
                imprimirLista(minhaLista);
                break;

            case 7:
                copiaLista = clonarLista(minhaLista);
                printf("Lista original: ");
                imprimirLista(minhaLista);
                printf("Lista clonada: ");
                imprimirLista(copiaLista);
                system("pause");
                liberarLista(copiaLista);
                break;

            case 8:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");

        }

    }while(opcao != 8);

    liberarLista(minhaLista);

    return 0;
}