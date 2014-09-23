/* Implementa��o de pilhas. Os elementos empilhados s�o do tipo void*.     */

#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

/* Mensagens de erro para este m�dulo.                                     */
#define MSG_ERRO_PILHA_CHEIA "n�mero m�ximo de elementos na pilha excedido."
#define MSG_ERRO_PILHA_VAZIA "tentativa de desempilhar elemento de pilha vazia."

#define IMPRIME_ERRO(msg)  {printf("%s\n",msg); exit(0); }


void CriaPilha (Pilha* p) {
/* Inicializa uma pilha.                                                   */
  /*----- COMPLETAR -----*/
}

Boolean PilhaVazia (Pilha* p) {
/* Verifica se a pilha est� vazia.                                         */
  /*----- COMPLETAR -----*/
  return false; /*-- PROVIS�RIO --*/
}

void Empilha (Pilha* p, void *elem) {
/* Empilha um elemento na pilha.                                           */
  /*----- COMPLETAR -----*/
}

void* Desempilha (Pilha* p) {
/* Desempilha um elemento da pilha.                                        */ 
  /*----- COMPLETAR -----*/
  return NULL; /*-- PROVIS�RIO --*/
}

