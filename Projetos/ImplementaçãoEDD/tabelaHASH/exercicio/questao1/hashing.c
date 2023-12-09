#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Hashing.h"


char compare(TIPOCHAVE x, TIPOCHAVE y)
{
    return x > y ? 1 : (x < y ? -1 : 0);
}

bool igual(TIPOCHAVE x, TIPOCHAVE y)
{
    return compare(x, y) == 0;
}


void inicializar(TABELAHASH *t, int capacidade)
{
    t->tamanho = 0;
    t->capacidade = capacidade;

    // Aloca dinamicamente o vetor de itens
    t->itens = (ITEM_TAB_HASH *) malloc(capacidade * sizeof(ITEM_TAB_HASH));
    for (int i = 0; i < capacidade; i++)
        t->itens[i].situacao = NuncaUsada;
}


int hash(TIPOCHAVE chave)
{
   return chave % t->capacidade;
}


int proximaPosicao(int pos)
{
   return (pos + 1) % t->capacidade;
}


int tamanho(TABELAHASH *t)
{
   return t->tamanho;
}


bool cheia(TABELAHASH *t)
{
   return tamanho(t) == t->capacidade;
}


bool vazia(TABELAHASH *t)
{
   return tamanho(t) == 0;
}


bool inserir(ITEM item, TABELAHASH *t)
{
   // Se a tabela estiver cheia, não insere
   if (cheia(t))
      return false;

   // Procura uma posição vazia para inserir o item
   int pos = hash(item.chave);
   int cont = 0;
   while (t->itens[pos].situacao != NuncaUsada)
   {
      // Se encontrar uma chave igual, não insere
      if (igual(t->itens[pos].item.chave, item.chave))
         return false;

      // Procura a próxima posição
      pos = proximaPosicao(pos);
      cont++;

      // Se percorrer a tabela inteira, não insere
      if (cont == t->capacidade)
         return false;
   }

   // Insere o item na posição encontrada
   t->itens[pos].item = item;
   t->itens[pos].situacao = Ocupada;
   t->tamanho++;

   return true;
}


bool encontrarPos(TIPOCHAVE chave, int *pos, TABELAHASH *t)
{
   // Procura a posição do item com a chave informada
   *pos = hash(chave);
   int cont = 0;
   while (t->itens[*pos].situacao != NuncaUsada)
   {
      // Se encontrar a chave, retorna true
      if (igual(t->itens[*pos].item.chave, chave))
         return true;

      // Procura a próxima posição
      *pos = proximaPosicao(*pos);
      cont++;

      // Se percorrer a tabela inteira, não encontra
      if (cont == t->capacidade)
         return false;
   }

   // Não encontra o item
   return false;
}


bool obter(TIPOCHAVE chave, ITEM *item, TABELAHASH *t)
{
   // Procura a posição do item com a chave informada
   int pos;
   if (!encontrarPos(chave, &pos, t))
      return false;

   // Copia o item para o parametro item
   *item = t->itens[pos].item;
   return true;
}


bool alterar(ITEM item, TABELAHASH *t)
{
   // Procura a posição do item com a chave informada
   int pos;
   if (!encontrarPos(item.chave, &pos, t))
      return false;

   // Altera o item na posição encontrada
   t->itens[pos].item = item;
   return true;
}

bool remover(TIPOCHAVE chave, TABELAHASH *t)
{
   // Procura a posição do item com a chave informada
   int pos;
   if (!encontrarPos(chave, &pos, t))
      return false;

   // Marca a posição como desocupada
   t->itens[pos].situacao = Desocupada;
   t->tamanho--;

   return true;
}


void exibirTab(TABELAHASH *t)
{
   printf("Posicao | Situacao/Item\n");
   for (int i = 0; i < t->capacidade; i++)
   {
      printf("[%d] | ", i);
      if (t->itens[i].situacao == Ocupada)
         printf("(%d,%s)\n", t->itens[i].item.chave, t->itens[i].item.valor);
      else if (t->itens[i].situacao == NuncaUsada)
         printf("(NU)\n");
      else
         printf("(D)\n");
   }
}


void limpar(TABELAHASH *t)
{
   for (int i = 0; i < t->capacidade; i++)
      t->itens[i].situacao = NuncaUsada;

   t->tamanho = 0;
}


void rehash(TABELAHASH *t, int novaCapacidade)
{
   // Aloca um novo vetor de itens
   ITEM_TAB_HASH *novosItens = (ITEM_TAB_HASH *) malloc(novaCapacidade * sizeof(ITEM_TAB_HASH));
   for (int i = 0; i < novaCapacidade; i++);
      novosItens[i].situacao = NuncaUsada;

   // Copia os itens antigos para o novo vetor
   for (int i = 0; i < t->capacidade; i++)
   {
      if (t->itens[i].situacao == Ocupada)
      {
         int novaPos = hash(t->itens[i].item.chave);
         while (novosItens[novaPos].situacao != NuncaUsada)
            novaPos = proximaPosicao(novaPos);

         novosItens[novaPos] = t->itens[i];
      }
   }

   // Libera o vetor antigo
   free(t->itens);

   // Atualiza os dados da tabela hash
   t->itens = novosItens;
   t->capacidade = novaCapacidade;
}