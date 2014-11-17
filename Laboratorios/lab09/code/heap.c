/*
  Implementa��o das fun��es de manipula��o de filas de prioridade
  (FP). Vide o arquivo heap.h com as especifica��es.
 */  

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "balloc.h"

typedef struct {
  int tamMax;
  int tam;
  funcCompara *comp;/* fun��o de compara��o */
  void *vetor[1];   /* tamanho alocado ser� 'tamMax' */
} RegHeap, *ImplHeap;


/* Fun��es auxiliares para manipula��o de FPs. */
void Sobe(ImplHeap h, int m) {

  /* COMPLETAR */
  
} /* Sobe */

void Desce(ImplHeap h, int m) {

  /* COMPLETAR */
  
} /* Desce */


Heap CriaHeapAux(int n, funcCompara *comp, void *elems[]) {
  /* Cria um heap vazio; se 'elems' n�o � nulo, preenche com os
     valores do vetor 'elems' e transforma num heap.
  */
  ImplHeap ih = MALLOC(sizeof(RegHeap)+(n-1)*sizeof(void *));

  /* COMPLETAR */
  
  return ih;
  
} /* CriaHeapAux */

Heap CriaHeap(int n, funcCompara *comp) {

  return CriaHeapAux(n,comp,NULL);

} /* CriaHeap */

Heap CriaInicializaHeap(int n, funcCompara *comp, void *elems[]) {

  return CriaHeapAux(n,comp,elems);

} /* CriaInicializaHeap */

int TamanhoHeap(Heap h) {

  /* COMPLETAR */
  
  return 0; /* provis�rio */
  
} /* TamanhoHeap */


void InsereHeap(Heap h, void *e) {

  ImplHeap ih = h;
  if (ih->tam==ih->tamMax) {
    printf("Estouro da FP\n");
    exit(0);
  }

  /* COMPLETAR */
 
} /* insereHeap */


void * RemoveHeap(Heap h) {

  ImplHeap ih = h;
  void *ret = NULL;
  if (ih->tam==0) {
    printf("FP vazia\n");
    exit(0);
  }

  /* COMPLETAR */

  return ret;
  
} /* removeHeap */

void LiberaHeap(Heap h) {

  /* COMPLETAR */

} /* liberaHeap */


void * Elemento(Heap h, int k) {

  ImplHeap ih = h;
  
  if ((k<0) || (k>=ih->tam))
    return NULL;
  return ih->vetor[k];

} /* Elemento */
