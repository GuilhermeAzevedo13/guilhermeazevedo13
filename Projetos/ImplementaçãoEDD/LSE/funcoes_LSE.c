//
// Created by Mano Gui on 14/07/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes_LSE.h"

void inverterLista(LISTA *l, int tamanho){
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

void exibirListaReversa(LISTA *l){
    int i=0,j=0;

}

char compare(ITEM x, ITEM y){
    if (x > y){
        return 1;
    }else if (x < y){
        return -1;
    }else{
        return 0;
    }
}

bool igual(ITEM x, ITEM y){
    return compare(x,y) == 0;
}

void inicializar(LISTA *l){
    l -> tamanho = 0;
}

int tamanho(LISTA *l){
    return l->tamanho;
}

bool cheia(LISTA *l){
    return tamanho(l) == MAX;
}

bool vazia(LISTA *l){
    return tamanho(l) == 0;
}

/*
    * if (tamanho(l) == MAX): Verifica se o tamanho da lista (l) é igual a um valor máximo predefinido (MAX).
    Isso é usado para verificar se a lista está cheia.

    * return false;: Se a lista estiver cheia, ou seja, o tamanho da lista for igual a MAX, a função retorna
    false para indicar que a inserção não foi bem-sucedida devido à lista cheia.

    * l -> itens[l -> tamanho++] = item;: Se a lista não estiver cheia, o item é adicionado à lista. Isso é
    feito atribuindo o valor do item ao próximo espaço disponível na lista (l -> itens[l -> tamanho]), e em
    seguida, incrementando o tamanho da lista (l -> tamanho++).

    * return true;: Após a inserção bem-sucedida do item na lista, a função retorna true para indicar que a
    operação foi concluída com sucesso.

    * Portanto, a função inserir verifica se a lista está cheia e insere o item na lista, retornando true se
    a inserção for bem-sucedida ou false se a lista estiver cheia.
 */

bool inserir(ITEM item, LISTA *l){
    if (tamanho(l) == MAX){
        return false; // Lista Cheia
    }else{
        l -> itens[l -> tamanho ++] = item;
    }
    return true;
}

int buscar(ITEM item, LISTA *l){

    int pos;
    for(pos = 0; pos < tamanho(l); pos++){
        if (igual(item, l -> itens[pos])){
            return pos; // achou
        }
    }
    return -1; // nao achou
}

ITEM enesimo(int n, LISTA *l){
    if (n >= 0 && n < tamanho(l)){
        return (l -> itens[n]);
    }else{
        exit(EXIT_FAILURE);
    }
}

bool alterar(ITEM item, int pos, LISTA *l){
    if (pos >= 0 && pos < tamanho(l)){
        l -> itens[pos] = item;
        return true;
    }
    return false;
}

bool inserirNaPos(ITEM item, int i, LISTA *l){
    // A posição tem que estar entre 0 e MAX-1 e até o tamnho atual
    if ((tamanho(l) >= MAX) || (i < 0) || (i > tamanho(l))){
        return false; // Lista cheia ou indice invalido
    }

    // Se for inserido no meio, é necessário abrir espaço para o item
    int j;
    for (j = tamanho(l); j > i; j--){
        l -> itens[j] = l -> itens[j-1];
    }
    // Coloca o item em um espaço vago e ajusta o tamanho
    l -> itens[i] = item;
    return true;
}

bool remover(ITEM item, LISTA *l){
    int i, j;
    for(i = 0; i < tamanho(l); i++) {
        if (igual(item, l->itens[i])) {
            for (j = i; j < l->tamanho - 1; j++) {
                l->itens[j] = l->itens[j + 1];
            }
            l->tamanho--;
            return true; // Achou
        }
    }
    return false; // Nao Achou
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

void limpar(LISTA *l){
    l->tamanho = 0;
}

void destruir(LISTA *l){
    limpar(l);
}
