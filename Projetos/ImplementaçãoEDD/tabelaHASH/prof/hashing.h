#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef HASHING
#define HASHING

#define MAX 10

typedef int TIPOCHAVE;

typedef enum {NuncaUsada, Desocupada, Ocupada} SITUACAO;

typedef struct {
  TIPOCHAVE chave;
  char valor[100];
} ITEM;

typedef struct {
  ITEM item;
  SITUACAO situacao;
} ITEM_TAB_HASH;

typedef struct{
  ITEM_TAB_HASH itens[MAX];
  int tamanho;
} TABELAHASH;


/*
   Compara o x com o y, retornando:
     1 caso x > y
     0 caso x = y
    -1 caso x < y
*/
char compare(TIPOCHAVE x, TIPOCHAVE y);

// Retorna true se x = y e false caso contrario
bool igual(TIPOCHAVE x, TIPOCHAVE y);

/*
  Objetivo: Inicializa a tabela hash passada, fazendo com que a
            situacao de todas as posicoes da tabela sejam marcadas
            como nunca usadas (NuncaUsada)
*/
void inicializar(TABELAHASH *t);

/*
  Objetivo: Retorna a posicao da tabela correspondente ao valor 
            da chave passada. 
            Usa a funcao de resto da divisao: Chave % MAX
*/
int hash(TIPOCHAVE chave);

/*
  Objetivo: Retorna a proxima posicao a ser analisada na presenca de
            colisoes, baseada na posicao passada
*/
int proximaPosicao(int pos);

// Retornar o tamanho da tabela hash (quantidade de ocupados)
int tamanho(TABELAHASH *t);

// Retorna true se a tabela hash esta cheia (Tamanho = MAX)
bool cheia(TABELAHASH *t);

// Retorna true se a tabela hash esta vazia (Tamanho = 0)
bool vazia(TABELAHASH *t);

/*
  Objetivo: Insere na tabela t, o dado contido no parametro item. 
            Se ja existir alguma chave igual na tabela, retorna false
            para indicar que nao foi possivel inserir. 
            Caso contrario, coloca o dado na primeira posicao disponivel
            (Desocupada ou NuncaUsada) e retorna true.
*/
bool inserir(ITEM item, TABELAHASH *t);

/*
  Objetivo: Procura pela chave passada. Se existir, o parametro
            pos contem a posicao e a funcao retorna true.
            Caso contrario, apenas retorna false.
*/
bool encontrarPos(TIPOCHAVE chave, int *pos, TABELAHASH *t);


/*
  Objetivo: Se a tabela contem algum elemento com a chave especificada,
            coloca o item correspondente no parametro item e retorna true.
            Caso contrario, apenas retorna false
*/
bool obter(TIPOCHAVE chave, ITEM *item, TABELAHASH *t);

/*
  Objetivo: Se a tabela contem algum elemento com a chave especificada,
            coloca o item contido no parametro item na posicao correta
            da tabela e retorna true. Caso contrario, apenas retorna false.
*/
bool alterar(ITEM item, TABELAHASH *t);

/*
  Objetivo: Remove o item contido na tabela que possui a chave passada.
            Se existir, retorna true e a posicao do array e marcada como
            Desocupada. Caso contrario, apenas retorna false
*/
bool remover(TIPOCHAVE chave, TABELAHASH *t);

// Exibicao da tabela hash
void exibirTab(TABELAHASH *t);

// Limpeza da tabela hash
void limpar(TABELAHASH *t);

#endif // LISTA_SEQ_ESTATICA