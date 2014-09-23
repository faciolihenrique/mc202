/* Interface para a implementa��o de pilhas. Os elementos empilhados s�o  */
/* do tipo void*.                                                         */

#ifndef _Pilha_DEFINED
#define _Pilha_DEFINED

#include "balloc.h"
#include "boolean.h"

/* N�mero m�ximo de elementos na pilha */
#define MAX_ELEM_PILHA 100 

typedef struct Pilha {
  int topo;
  void* vetor[MAX_ELEM_PILHA];
} Pilha;

void CriaPilha (Pilha* p);
/* Inicializa uma pilha.                                                   */

Boolean PilhaVazia (Pilha* p);
/* Verifica se a pilha est� vazia.                                         */

void Empilha(Pilha* p, void* elem);
/* Empilha um elemento.                                                    */

void* Desempilha (Pilha* p);
/* Desempilha um elemento.                                                 */ 

#endif
