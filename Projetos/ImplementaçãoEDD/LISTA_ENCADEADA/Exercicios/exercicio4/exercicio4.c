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
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if (lista == NULL) {
        perror("Erro ao alocar memoria para a lista");
        exit(EXIT_FAILURE);
    }
    lista->cabeca = NULL;
    lista->tamanho = 0;
    return lista;
}

void inserirItemOrdenado(LISTA *lista, ITEM item) {
    NO *novoNo = (NO *)malloc(sizeof(NO));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o no");
        exit(EXIT_FAILURE);
    }
    novoNo->item = item;

    if (lista->cabeca == NULL || item < lista->cabeca->item) {
        novoNo->prox = lista->cabeca;
        lista->cabeca = novoNo;
    } else {
        NO *atual = lista->cabeca;
        while (atual->prox != NULL && item > atual->prox->item) {
            atual = atual->prox;
        }
        novoNo->prox = atual->prox;
        atual->prox = novoNo;
    }

    lista->tamanho++;
}

void removerPorPosicao(LISTA *lista, int posicao) {
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posicao invalida!\n");
        return;
    }

    NO *anterior = NULL;
    NO *atual = lista->cabeca;
    int i;
    for (i = 0; i < posicao; i++) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) {
        lista->cabeca = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    lista->tamanho--;
}

int buscarNaLista(LISTA *lista, ITEM valor) {
    NO *atual = lista->cabeca;
    int posicao = 0;
    while (atual != NULL && atual->item <= valor) {
        if (atual->item == valor) {
            printf("Valor encontrado na posicao %d.\n", posicao);
            return 1; // Encontrou o valor na lista
        }
        atual = atual->prox;
        posicao++;
    }
    return 0; // Valor nao encontrado
}

void imprimirLista(LISTA *lista) {
    NO *atual = lista->cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->item);
        atual = atual->prox;
    }
    printf("NULL\n");
}

void liberarLista(LISTA *lista) {
    NO *atual = lista->cabeca;
    while (atual != NULL) {
        NO *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

void inverter(LISTA *l) {
    NO *anterior = NULL;
    NO *atual = l->cabeca;
    NO *proximo = NULL;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    l->cabeca = anterior;
}

int main() {
    LISTA *lista = criarLista();
    int opcao, item, posicaoRemover, valorBusca;
    char continuar;

    do {
        system("cls"); // Limpar a tela

        printf("Menu:\n");
        printf("1. Inserir item\n");
        printf("2. Remover por posicao\n");
        printf("3. Buscar valor na lista\n");
        printf("4. Imprimir lista\n");
        printf("5. Inverter lista\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                do {
                    printf("Digite o item a ser inserido: ");
                    scanf("%d", &item);
                    inserirItemOrdenado(lista, item);
                    printf("Deseja continuar inserindo? (S/N): ");
                    scanf(" %c", &continuar);
                } while (continuar == 'S' || continuar == 's');
                break;
            case 2:
                printf("Digite a posicao a partir da qual deseja remover (0 a %d): ", lista->tamanho - 1);
                scanf("%d", &posicaoRemover);
                if (posicaoRemover <= (lista->tamanho - 1) && posicaoRemover >= 0) {
                    removerPorPosicao(lista, posicaoRemover);
                } else {
                    printf("Valor da posicao maior que %d\n", lista->tamanho - 1);
                    getchar(); // Limpar o buffer do teclado
                }
                break;

            case 3:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valorBusca);
                if (buscarNaLista(lista, valorBusca)) {
                    // Valor encontrado na busca, nada mais a fazer aqui
                } else {
                    printf("Valor nao encontrado na lista.\n");
                }
                printf("Pressione Enter para continuar...");
                getchar(); // Limpar o buffer do teclado
                getchar(); // Aguardar a tecla Enter
                break;
            case 4:
                printf("Lista encadeada: ");
                imprimirLista(lista);
                printf("Pressione Enter para continuar...");
                getchar(); // Limpar o buffer do teclado
                getchar(); // Aguardar a tecla Enter
                break;
            case 5:
                inverter(lista);
                printf("Lista invertida com sucesso.\n");
                imprimirLista(lista);
                printf("Pressione Enter para continuar...");
                //getchar(); // Limpar o buffer do teclado
                break;
            case 6:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);

    liberarLista(lista);

    return 0;
}
