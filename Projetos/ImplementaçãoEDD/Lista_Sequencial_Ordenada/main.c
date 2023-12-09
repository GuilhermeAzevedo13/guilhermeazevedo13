#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "ListaSeqOrd.h"

// Imprime na tela o status da lista
void imprimirStatus(LISTA *l){
    printf("Tamanho = %d\n", tamanho(l));
	exibirLista(l);
	printf("\n");
}

// Testa a insercao de valores na lista
void testarInserir(LISTA *l){
    printf("=> Teste de Inserir\n");
    int qtd;
    printf("Quantos itens deseja guardar na lista? ");
    scanf("%d", &qtd);

    ITEM item;
    int i;
    for (i = 1; i <= qtd; i++){
        printf("Digite o valor %d/%d: ", i, qtd);
        scanf("%d", &item);
        inserir(item, l);
	}

	imprimirStatus(l);
}


// Testa a insercao de valores na lista escolhendo a posicao
void testarInserirVarios(LISTA *l){ 
    
    printf("=> Teste de InserirVarios\n");
    int qtd;
    printf("Quantos itens aleatorios deseja inserir na lista? ");
    scanf("%d", &qtd);

	ITEM item;
    int sucessos = 0;
    int erros = 0;

    // Inicia a contagem de tempo
    time_t inicio = time(NULL);
    int i;
	for (i = 0; i < qtd; i++){
        item = rand();
        if (inserir(item, l)){
            sucessos += 1;
        }else{
            erros += 1;
        }
	}
    // Finaliza a contagem de tempo
    time_t fim = time(NULL);
    // Calcula o tempo decorrido
    double tempo_gasto = (double)(fim - inicio);
    // Tempo medio por insercao
    double tempo_medio = 1000.0  * tempo_gasto / qtd;

    printf("Insercoes com sucesso: %d\n", sucessos);
    printf("Insercoes com erro: %d\n", erros);
    printf("Tempo total das insercoes %f segundos\n", tempo_gasto);
    printf("Tempo medio por insercao %f milisegundos\n", tempo_medio);
}



// Testa a busca de valores na lista
void testarBuscar(LISTA *l){
    // Testa a busca por um valor existente
    printf("=> Teste de Busca\n");

    // Preenchendo a lista com valores crescentes
    int TOTAL = 100;
    limpar(l);
    printf("=> Limpando a lista\n");

    // Preenchendo a lista com os valores de TOTAL ate 1
    int i;
    for (i = TOTAL; i > 0; i--){
        if (!inserir(i, l))
            printf("Algum erro duranta a insercao do valor %d\n", i);
        else
           printf("Inserido o valor %d\n", i);
    }
       
    printf("=> Preenchida a lista com valores de 1 a %d\n", TOTAL);
        
    printf("Digite o valor que deseja buscar: ");
    ITEM item;
    scanf("%d", &item);
    int pos = buscar(item, l); 
    if (pos >= 0){
        printf("Achou na posicao: %d\n", pos);
    }else{
        printf("Nao achou o item na lista\n");
    }

    // Testa a busca por uma posicao existente
    printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
    int p;
    scanf("%d", &p);
    while (p != -1){
        ITEM item = enesimo(p, l);
        printf("Achou na posicao[%d] o valor: %d\n", p, item);
        // Leitura da proxima posicao a ser acessada
        printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
        scanf("%d", &p);
    }

}


int main(void){
    
    
	LISTA l;
	
	inicializar(&l);
    printf("\nA main rodou");
    /*
    testarInserir(&l);
    testarInserirVarios(&l);
    testarBuscar(&l); 
    limpar(&l);
    imprimirStatus(&l);
    destruir(&l);
    */
    getchar();
	return 0;
}