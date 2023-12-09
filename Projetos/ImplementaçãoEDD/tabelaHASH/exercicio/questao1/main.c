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
    printf("\nDigite a chave do item que deseja alterar: ");
    TIPOCHAVE chave;
    ITEM item;
    scanf("%d", &chave);
    printf("Digite o valor do item que deseja alterar: ");
    scanf("%s", item.valor);
 
    if (alterar(item, t))
       printf("Alterou o item com chave %d: %s\n", item.chave, item.valor);
    else
       printf("Nao alterou o item com chave %d\n", chave);
}

void removerValor(TABELAHASH *t)
{
    printf("\nDigite a chave do item que deseja remover: ");
    TIPOCHAVE chave;
    scanf("%d", &chave);
 
    if (remover(chave, t))
       printf("Removeu o item com chave %d\n", chave);
    else
       printf("Nao removeu o item com chave %d\n", chave);
}


int main() 
{
   TABELAHASH t;
  
   inicializar(&t, 10);
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

   rehash(&t, 20);
   imprimirTab(&t);

   getchar();
   return 0;
}