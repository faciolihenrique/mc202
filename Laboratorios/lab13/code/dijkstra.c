/*
  Autor:         COMPLETAR!
  RA:            COMPLETAR!
  Disciplina:    MC202
  Turmas:        E e F
  
  Tarefa: 13
  Segundo semestre de 2014

*/

/* A especifica��o das fun��es encontra-se no arquivo dijkstra.h */

#include <stdio.h>
#include <limits.h>

#include "dijkstra.h"
#include "balloc.h"

typedef enum {false, true} Boolean;

/* Aresta */
typedef struct aux {
  int dest;
  int peso;
  struct aux *prox;
} Aresta;

/* Implementa��o de grafo */
typedef struct {
  int tam;               /* n�mero de v�rtices */
  Aresta * vertices[1];  /* tamanho final ser� 'tam' */
} RegGrafo, *ImplGrafo;


Grafo CriaGrafoVazio(int n) {

  /* COMPLETAR */
  
  return NULL;  /* PROVIS�RIO */
  
} /* CriaGrafoVazio */

Erro AcrescentaAresta(Grafo g, int u, int v, int p) {

  /* COMPLETAR */
  
  return CERTO;   /* PROVIS�RIO */
  
} /* AcrescentaAresta */

void ImprimeGrafo(Grafo g) {
 
  ImplGrafo ig = g;
  int i, n;
  Aresta *v;
  
  n = ig->tam;
  printf("Grafo de %d v�rtices:\n",n);
  for (i=0; i<n; i++) {
    printf("%4d:",i);
    v = ig->vertices[i];
    while (v!=NULL) {
      printf("%4d (%d)",v->dest,v->peso);
      v = v->prox;
    }
    printf("\n");
  }
  
} /* ImprimeGrafo */

void Dijkstra(Grafo g, int r, int dist[]) {
  
  /* COMPLETAR */
  
} /* Dijkstra */


void LiberaGrafo(Grafo g) {
  
  /* COMPLETAR */
  
} /* LiberaGradfo */
