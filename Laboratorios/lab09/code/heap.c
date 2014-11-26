/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * Tarefa 09 - 2sem 2014           *
 * * * * * * * * * * * * * * * * * */

/*
  Implementação das funções de manipulação de filas de prioridade
  (FP). Vide o arquivo heap.h com as especificações.
 */

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "balloc.h"

typedef struct {
    int tamMax;
    int tam;
    funcCompara *comp; /* função de comparação */
    void *vetor[1];    /* tamanho alocado será 'tamMax' */
} RegHeap, *ImplHeap;

/*Funcoes baseadas no slide que o professor passou em aula*/

/* Funções auxiliares para manipulação de FPs. */
void Sobe(ImplHeap h, int m) {
    /*Pega a posicao do pai de m*/
    int i = (m - 1)/2;
    /*auxiliar que guada o valor do vetor m*/
    void *aux = h->vetor[m];

    /*Enquanto m nao for a raiz e enquanto o valor de arvore for menor que
      o valor que esta subindo*/
    while( (m > 0) && h->comp(h->vetor[i], aux) < 0){
        h->vetor[m] = h->vetor[i];
        m = i;
        i = (i-1)/2;
    }

    h->vetor[m] = aux;

} /* Sobe */

void Desce(ImplHeap h, int m) {
    /*Escolhe o filho esquerdo*/
    int i = (2*m + 1);
    /*Copia o valor desejado para uma variavel auxiliar*/
    void *aux = h->vetor[m];

    /*Verificar se o filho esquerdo existe, ou seja, enquanto nao estiver em uma
      folha*/
    while(i < h->tam){
        /*Verifica qual o filho é maior, direito ou esquerdo*/
        if(i < (h->tam - 1)  && h->comp(h->vetor[i] , h->vetor[i+1]) < 0){
            i++;
        }
        /*Verifica se aux é maior, se nao, sobe com o valor*/
        if( h->comp( aux, h->vetor[i] ) < 0){
            h->vetor[m] = h->vetor[i];
            m = i;
            i = 2*i + 1;
        }
        else{
            break;
        }
    }

    h->vetor[m] = aux;


} /* Desce */


Heap CriaHeapAux(int n, funcCompara *comp, void *elems[]) {
    /* Cria um heap vazio; se 'elems' não é nulo, preenche com os
    valores do vetor 'elems' e transforma num heap.
    */
    int i;
    ImplHeap ih = MALLOC(sizeof(RegHeap)+(n-1)*sizeof(void *));

    ih->tamMax = n;
    ih->tam = 0;
    ih->comp = comp;

    if(elems != NULL){
        /*Copia os valored de elems para o heap*/
        for(i = 0; i < n && elems[i] != NULL; i++){
            ih->vetor[i] = elems[i];
            (ih->tam)++;
        }
        /*Faz a organizacao do heap*/
        for(i = (ih->tam - 2)/2; i >= 0; i--){
            Desce(ih, i);
        }
    }

    return (Heap) ih;

} /* CriaHeapAux */

Heap CriaHeap(int n, funcCompara *comp) {

    return CriaHeapAux(n,comp,NULL);

} /* CriaHeap */

Heap CriaInicializaHeap(int n, funcCompara *comp, void *elems[]) {

    return CriaHeapAux(n,comp,elems);

} /* CriaInicializaHeap */

int TamanhoHeap(Heap h) {
    /*retorna o tamanho da heap*/

    ImplHeap ih = (ImplHeap) h;

    return ih->tam;

} /* TamanhoHeap */


void InsereHeap(Heap h, void *e) {

    ImplHeap ih = (ImplHeap) h;

    /*Caso esteja com o numero maximo de elementos*/
    if (ih->tam == ih->tamMax) {
        printf("Estouro da FP\n");
        exit(0);
    }

    /*Faz a inserçao do elemento na ultima posicao e chama a funcao subir
      que acha a posicao correta do elemento*/
    ih->vetor[ih->tam] = e;
    (ih->tam)++;
    Sobe(ih, (ih->tam)-1);

} /* insereHeap */


void * RemoveHeap(Heap h) {

    ImplHeap ih = (ImplHeap) h;
    void *ret = NULL;

    if (ih->tam == 0) {
        printf("FP vazia\n");
        exit(0);
    }

    ret = ih->vetor[0]; /*Salva em ret o maior valor do Heap*/

    /*Faz o ultimo elemento do vetor ser o primeiro e chama a funcao desce,
      que reorganiza o vetor corretamente*/
    (ih->tam)--;
    ih->vetor[0] = ih->vetor[(ih->tam)];
    Desce(ih, 0);

    return ret;

} /* removeHeap */

void LiberaHeap(Heap h) {

    ImplHeap ih = (ImplHeap) h;

    FREE(ih);
} /* liberaHeap */


void * Elemento(Heap h, int k) {

    ImplHeap ih = h;

    if ((k<0) || (k>=ih->tam))
        return NULL;
    return ih->vetor[k];

} /* Elemento */
