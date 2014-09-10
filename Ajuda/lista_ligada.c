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
/*Fun��o do tipo apontador para lista, i.e., o tipo de fun��o tem de ser igual ao tipo que retorna*/
No * cria_lista();

int main(){


    return 0;
}

No * cria_lista(){
    No * novo,*aux;
 
    novo = (No *) malloc( sizeof( No ));   /*Aloca mem�ria do tamanho de uma c�lula*/
 
    if(novo == NULL) exit(0);    /* Se n�o alocar mem�ria significa que n�o h� memoria dispon�vel, logo deve sair*/
 
 
    novo->prox = NULL;         /*Como esta deve ser a primeira fun��o a ser executada, esta c�lula vazia aponta para NULL*/
 
    aux= novo; /*Para retornar o aux com o endere�o da c�lula vazia, deve ser corrigido o valor do mesmo*/
 
 
    return (aux); /*Retorna o aux*/
}