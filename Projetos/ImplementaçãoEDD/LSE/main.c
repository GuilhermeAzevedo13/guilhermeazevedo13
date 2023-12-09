#include <stdio.h>
#include "funcoes_LSE.h"

// Imprimir na tela o status da lista
void imprimirStatus(LISTA *l){
    printf("Tamanho = %d\n", tamanho(l));
    exibirLista(l);
    printf("\n");
}

// Testar a inserção de Valores na lista
void testarInserir(LISTA *l){
    printf("=> TESTE DE INSERIR\n");
    int quantidade, i;
    printf("Quantos itens deseja guardar na lista? ");
    scanf("%d", &quantidade);

    ITEM item;
    for(i = 0; i < quantidade; i++){
        printf("Digite o valor para a posicao [%d]: ", i);
        scanf("%d", &item);
        inserir(item, l);
    }

    imprimirStatus(l);
}

// Testar a insercao de valores na lista escolhendo a posicao
void testarInserirNaPos(LISTA *l){
    printf("=> TESTE INSERIR NA POSICAO\n");
    int quantidade, i;
    printf("Quantos itens deseja inserir na lista? ");
    scanf("%d", &quantidade);

    ITEM item;
    for(i = 0; i < quantidade; i++){
        printf("Digite a posicao da Insercao de (0 a %d): ", tamanho(l));
        int p;
        scanf("%d", &p);

        printf("Digite o valor para a posicao [%d]: ", p);
        scanf("%d", &item);
        if (inserirNaPos(item, p, l)){
            printf("Insercao bem sucedida!!!");
        }else{
            printf("Erro na Insercao!!!");
        }
        imprimirStatus(l);
    }
}

// Testa a busca de valores na Lista
void TestarBuscar(LISTA *l){
    // Testa a busca por um valor existente
    printf("=> TESTE DE BUSCA\n");
    printf("Digite o valor que deseja Buscar: ");
    ITEM item;
    scanf("%d", &item);
    int pos = buscar(item, l);
    if (pos >= 0){
        printf("Achou na posicao: %d\n", pos);
    }else{
        printf("Nao achou o item na lista\n");
    }

    // Testa a busca por uma posicao existente
    printf("Digite a posicao que deseja acessar (ou -1 para sair)");
    int p;
    scanf("%d", &p);
    while (p != -1){

        item = enesimo(p, l);
        printf("Achou na posicao [%d] o valor: %d\n", p, item);
        // Leitura da proxima posicao a ser acessada
        printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
        scanf("%d", &p);
    }
}

// Testa a busca de valores na lista
void testarBuscar(LISTA *l)
{
    // Testa a busca por um valor existente
    printf("=> Teste de Busca\n");
    printf("Digite o valor que deseja buscar: ");
    ITEM item;
    scanf("%d", &item);
    int pos = buscar(item, l);
    if (pos >= 0)
        printf("Achou na posicao: %d\n", pos);
    else
        printf("Nao achou o item na lista\n");

    // Testa a busca por uma posicao existente
    printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
    int p;
    scanf("%d", &p);
    while (p != -1)
    {
        item = enesimo(p, l);
        printf("Achou na posicao[%d] o valor: %d\n", p, item);
        // Leitura da proxima posicao a ser acessada
        printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
        scanf("%d", &p);
    }

}

// Testa a alteracao de um valor numa posicao
void testarAlterar(LISTA *l){
    printf("=> TEESTE ALTERACAO\n");
    int p;
    printf("Digite a posicao que deseja ALTERAR (ou -1 para sair): ");
    scanf("%d", &p);
    while (p != -1){
        // Leitura do novo valor
        printf("Digite o NOVO valor para a posicao [%d]: ", p);
        ITEM item;
        scanf("%d", &item);
        if(alterar(item, p, l)){
            printf("Alterou com sucesso\n");
        }else{
            printf("Erro na Alteracao!!!");
        }
        imprimirStatus(l);

        // Leitura da proxima posicao a ser acessada
        printf("Digite a posicao que deseja ALTERAR (ou -1 para sair): ");
        scanf("%d", &p);
    }
}

void imprimirMenu() {
    printf("MENU INTERATIVO\n");
    printf("1. Testar Inserir\n");
    printf("2. Testar Inserir na Posicao\n");
    printf("3. Testar Buscar\n");
    printf("4. Testar Alterar\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    LISTA l;

    inicializar(&l);
    testarInserir(&l);
    testarInserirNaPos(&l);
    testarBuscar(&l);
    testarAlterar(&l);
    destruir(&l);
    imprimirStatus(&l);

    getchar();
    return 0;
}
