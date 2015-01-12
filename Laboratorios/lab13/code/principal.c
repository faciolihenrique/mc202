/*
  principal.c - Este programa testa a implementa��o do algoritmo de
  Dijkstra.  Os seus dados s�o fornecidos no seguinte formato:
  
    n             (n�mero de v�rtices)
    u0  v0  p0    (aresta 0)
    u1  v1  p1    (aresta 1)
    ...
    -1  -1  -1    (sentinela indica fim das arestas)
    r0            (raiz 0)
    r1            (raiz 1)
    ...
    -1            (sentinela indica fim das raizes para c�lculo)           
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "balloc.h"
#include "dijkstra.h"

#define TAM_MAX 100

/* Fun��o auxiliar que imprime dados sobre bloco de mem�ria n�o
   liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {
    printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
} /* bprint */


void DadosErrados() {
  printf("Erro na leitura dos dados ou dados inv�lidos\n");
  exit(0);
} /* DadosErrados */ 

int main() {
  
  Grafo g;
  int n;
  int u, v, p, r;
  int *dist;
  int achou;
  
  /* N�mero de v�rtices */
  if ((scanf("%d",&n)!=1) || (n<0) || (n>TAM_MAX))
    DadosErrados();
  
  g = CriaGrafoVazio(n);
  if ((dist=MALLOC(sizeof(int)*n))==NULL) {
    printf("Mem�ria esgotada\n");
    return 0;
  }

  /* Leitura de arestas */
  while (1) {
    if (scanf("%d %d %d",&u,&v,&p)!=3)
      DadosErrados();
    if (u==-1)
      break;
    if (AcrescentaAresta(g,u,v,p)!=CERTO)
      DadosErrados();
  } /* break */
  ImprimeGrafo(g);
  
  /* Aplica��o do algoritmo de Dijkstra */
  while (1) {
    if (scanf("%d",&r)!=1)
      DadosErrados();
    if (r==-1)
      break;
    if ((r<0) || (r>=n))
      DadosErrados();
    printf("Caminhos m�nimos a partir do v�rtice %d:\n",r);
    Dijkstra(g,r,dist);
    achou = 0;
    for (v=0; v<n; v++) {
      if ((v!=r) && (dist[v]!=INT_MAX)) {
	printf("%3d:  %d\n",v,dist[v]);
        achou++;
      }
    }
    if (achou==0)
      printf("  nenhum\n");
  } /* break */

  LiberaGrafo(g);
  
  FREE(dist);
  
  bapply(bprint);

  printf("Processamento terminado\n");

  return 0;

} /* main */
