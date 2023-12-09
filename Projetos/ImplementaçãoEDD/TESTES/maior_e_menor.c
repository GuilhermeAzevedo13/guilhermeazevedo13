#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *lista = NULL, i;
    lista = (int *)malloc(5 * sizeof(int));

    for (i = 0; i < 5; i++) {
        scanf("%d", &lista[i]);
    }

    printf("[");
    for (i = 0; i < 5; i++) {
        printf("%d", lista[i]);
        if (i < 4) {
            printf(",");
        }
    }
    printf("]");

    int maior = lista[0]; // Inicializa o maior com o primeiro elemento da lista
    int menor = lista[0]; // Inicializa o menor com o primeiro elemento da lista

    for (i = 1; i < 5; i++) { // Começa do índice 1, pois já consideramos o índice 0 na inicialização
        if (lista[i] > maior) {
            maior = lista[i];
        }
        if (lista[i] < menor) {
            menor = lista[i];
        }
    }

    printf("\n");
    printf("Maior: %d\n", maior);
    printf("Menor: %d\n", menor);

    free(lista);

    return 0;
}
