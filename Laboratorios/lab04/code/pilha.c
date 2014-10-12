/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli		    *
 * RA : 157986				        *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        * 
 * * * * * * * * * * * * * * * * * */

/* Implementação de pilhas. Os elementos empilhados são do tipo void*.     */

#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

/* Mensagens de erro para este módulo.                                     */
#define MSG_ERRO_PILHA_CHEIA "número máximo de elementos na pilha excedido."
#define MSG_ERRO_PILHA_VAZIA "tentativa de desempilhar elemento de pilha vazia."

#define IMPRIME_ERRO(msg)  {printf("%s\n",msg); exit(0); }

void CriaPilha (Pilha* p) {
    /*Quando se cria uma pilha, ela não contem nenhum elemento, entao assume
      que o valor do topo é -1*/
    p->topo = -1;
    
}

Boolean PilhaVazia (Pilha* p) {
/* Verifica se a pilha está vazia.                                         */
    if (p->topo == -1){
        return true;
    }else{
        return false;        
    }
}

void Empilha (Pilha* p, void *elem) {
/* Empilha um elemento na pilha.                                           */

    /*Verifica se a pilha ja esta lotada*/
    if(p->topo == (MAX_ELEM_PILHA - 1)){
        IMPRIME_ERRO(MSG_ERRO_PILHA_CHEIA);
    }
    
    /*Adiciona o elemento ao topo da pilha*/
    p->topo++;
    p->vetor[p->topo] = elem;
    
}

void* Desempilha (Pilha* p) {
/* Desempilha um elemento da pilha.                                        */ 
    
    /*Verifica se ja esvaziou toda a pilha*/
    if(p->topo == -1){
        IMPRIME_ERRO(MSG_ERRO_PILHA_VAZIA);
    }
    
    /*Retorna o valor do topo da pilha e remove 1 do contador de elementos*/
    p->topo--;
    return p->vetor[(p->topo + 1)];
}

