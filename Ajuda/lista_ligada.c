/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli		    *
 * RA : 157986				        *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *    
 * LISTA LIGADA                    *
 * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

typedef struct No_st{
    int numero;
    struct No *prox;
}No;
/*Função do tipo apontador para lista, i.e., o tipo de função tem de ser igual ao tipo que retorna*/
No * cria_lista();

int main(){


    return 0;
}

No * cria_lista(){
    No * novo,*aux;
 
    novo = (No *) malloc( sizeof( No ));   /*Aloca memória do tamanho de uma célula*/
 
    if(novo == NULL) exit(0);    /* Se não alocar memória significa que não há memoria disponível, logo deve sair*/
 
 
    novo->prox = NULL;         /*Como esta deve ser a primeira função a ser executada, esta célula vazia aponta para NULL*/
 
    aux= novo; /*Para retornar o aux com o endereço da célula vazia, deve ser corrigido o valor do mesmo*/
 
 
    return (aux); /*Retorna o aux*/
}