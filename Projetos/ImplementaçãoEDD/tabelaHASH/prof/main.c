#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Hashing.h"

//////////////////////////////////////////////////////////////

void lerItens(TABELAHASH *t)
{
    printf("Digite a quantidade de itens que deseja ler: ");
    int n;
    scanf("%d", &n);
    
    printf("\nDigite a chave e o valor separados por um espaco:\n");
    // insere os valores n pares chave,valor
    ITEM item;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &item.chave);
        scanf("%s", item.valor);
        inserir(item, t);
    }
}

void imprimirTab(TABELAHASH *t)
{
    printf("\nTamanho = %d\n", tamanho(t));
    exibirTab(t);
    printf("\n");
}


void pesquisarValor(TABELAHASH *t)
{
    printf("\nDigite a chave do item que deseja procurar: ");
    TIPOCHAVE chave;
    ITEM item;
    scanf("%d", &chave);
    if (obter(chave, &item, t))
       printf("Achou o item com chave %d: %s\n", item.chave, item.valor);
    else
       printf("Nao achou o item com chave %d\n", chave);

}

void alterarValor(TABELAHASH *t)
{
    ITEM item;
    printf("\nDigite a chave do item que deseja alterar: ");
    scanf("%d", &item.chave);
    printf("Digite o valor do item que deseja alterar: ");
    scanf("%s", item.valor);
 
    if (alterar(item, t))
       printf("Alterou o item com chave %d: %s\n", item.chave, item.valor);
    else
       printf("Nao alterou o item com chave %d\n", item.chave);

}

void removerValor(TABELAHASH *t)
{
    TIPOCHAVE chave;
    printf("\nDigite a chave do item que deseja remover: ");
    scanf("%d", &chave);
 
    if (remover(chave, t))
       printf("Removeu o item com chave %d\n", chave);
    else
       printf("Nao removeu o item com chave %d\n", chave);

}

//////////////////////////////////////////////////////////////

int main() 
{
   TABELAHASH t;
  
   inicializar(&t);
   lerItens(&t);
   imprimirTab(&t);

   alterarValor(&t);
   pesquisarValor(&t);
   imprimirTab(&t);

   removerValor(&t);
   pesquisarValor(&t);
   imprimirTab(&t);

   lerItens(&t);
   imprimirTab(&t);

   getchar();
   return 0;
}