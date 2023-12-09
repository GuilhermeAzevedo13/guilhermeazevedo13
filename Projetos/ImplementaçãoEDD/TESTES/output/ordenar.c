#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

typedef int ITEM;

typedef struct {
    ITEM itens[MAX];
    int tamanho;
} LISTA;

int tamanho(LISTA *l) {
    return l->tamanho;
}

bool inserir(ITEM item, LISTA *l) {
    if (tamanho(l) == MAX) {
        return false; // Lista Cheia
    } else {
        l->itens[l->tamanho++] = item;
    }
    return true;
}

void inserirLISTA(LISTA *l) {
    printf("=> TESTE DE INSERIR\n");
    int quantidade, i;
    printf("Quantos itens deseja guardar na lista? ");
    scanf("%d", &quantidade);

    ITEM item;
    for (i = 0; i < quantidade; i++) {
        printf("Digite o valor para a posicao [%d]: ", i);
        scanf("%d", &item);
        inserir(item, l);
    }
}

void exibirItem(ITEM i){
    printf("%d", i);
}

void exibirLista(LISTA *l){
    int i;
    printf("[");
    for(i = 0; i < tamanho(l);){
        exibirItem(l->itens[i++]);
        if (i < tamanho(l)){
            printf(",");
        }
    }
    printf("]");
}

// Imprimir na tela o status da lista
void imprimirStatus(LISTA *l){
    printf("Tamanho = %d\n", tamanho(l));
    exibirLista(l);
    printf("\n");
}

void inverterLista(LISTA *l, int tamanho) {
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio < fim) {
        // Troca os elementos entre as posições inicio e fim
        int temp = l->itens[inicio];
        l->itens[inicio] = l->itens[fim];
        l->itens[fim] = temp;

        // Move os índices para a próxima posição e a anterior, respectivamente
        inicio++;
        fim--;
    }
}


void ordenaLista(LISTA *l){
    
    int maior = (l->itens[0]);
    int menor = (l->itens[0]);

    int i;
    for (i = 1; i < tamanho(l); i++){
        if ((l -> itens[i]) > maior){
            maior = (l->itens[i]);
        }
        if ((l -> itens[i]) < menor){
            menor = (l->itens[i]);
        }
    }

    for (i = 0; i < tamanho(l); i++){
        if ((l -> itens[i]) < maior){

        }
    }

    printf("\n");
    printf("Maior: %d\n", maior);
    printf("Menor: %d\n", menor);
}


int main(void) {
    LISTA l;
    l.tamanho = 0; // Inicializa o tamanho da lista como 0
    inserirLISTA(&l);
    imprimirStatus(&l);
    inverterLista(&l);
    ordenaLista(&l);
    imprimirStatus(&l);
    getchar();
    return 0;
}
