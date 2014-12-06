/* 
 * huffman.c - Implementa��o do algoritmo de Huffman. 
 */

/* 
 * huffman.c - Implementa��o do algoritmo de Huffman. 
 *             Para fazer a implementa��o com bits verdadeiros,
 *             deixe abaixo a inclus�o do arquivo "bits.h"; caso
 *             contr�rio, do arquivo "pseudo_bits.h".
 *
 *             Opcionalmente, poder� ser usada uma implementa��o
 *             independente de fila de prioridade (heap) da tarefa
 *             08. Neste caso, dever� ser submetido tamb�m o arquivo
 *             "heap.c". Caso contr�rio, dever� ser eliminada ou
 *             comentada a linha abaixo que inclui "heap.h".
 */


/*#include "heap.h"*/  /* descomente se necess�rio */

/* Deixe descomentada uma das duas linhas */
/*#include "bits.h"*/
#include "pseudo_bits.h"


#include <string.h>
#include <stdio.h>
#include "huffman.h"
#include "balloc.h"
#include "imprimearvore.h"

/* --------------------------------------------------------- */
/*         Tipos                                             */
/* --------------------------------------------------------- */


typedef struct RegArvHuf *ArvHuf;

typedef enum TipoFilho { 
  FilhoEsq = 0, FilhoDir = 1, Indeterminado } TipoFilho;

typedef struct RegArvHuf {
  int peso;                      /* peso da �rvore */
  char letra;                    /* somente no caso de folha */
  TipoFilho tipoFilho;           /* indica a rela��o com o pai */
  ArvHuf esq,dir,pai;            /* sub�rvores e pai */
} RegArvHuf;



/* --------------------------------------------------------- */
/*         Vari�veis globais                                 */
/* --------------------------------------------------------- */


ArvHuf Arvore;   /*  As fun��es abaixo construir�o e utilizar�o a
		     �rvore que ser� apontada por esta vari�vel */


ArvHuf Folhas[256];   /* Apontadores para as folhas da �rvore 'Arvore' */



/* --------------------------------------------------------- */
/* Fun��es auxiliares para este m�dulo                       */
/* --------------------------------------------------------- */

ArvHuf CriaFolha(char letra, int peso) {
/* Cria uma folha da �rvore; devolve NULL se n�o h� mais mem�ria. */

  ArvHuf p = MALLOC(sizeof(RegArvHuf));
  if (p!=NULL) {
    p->esq = p->dir = NULL;
    p->letra = letra;
    p->peso = peso;
    p->tipoFilho = Indeterminado;
  }
  return p;

} /* CriaFolha */

ArvHuf CombinaArvs(ArvHuf esq, ArvHuf dir) {
/* Combina duas sub�rvores numa �nica �rvore cujo peso � a soma dos
   pesos das sub�rvores; devolve NULL se n�o h� mais mem�ria. */
  
  ArvHuf p=MALLOC(sizeof(RegArvHuf));
  if (p!=NULL) {
    p->esq = esq;
    p->dir = dir;
    p->peso = esq->peso+dir->peso;
    esq->pai = dir->pai = p;
    esq->tipoFilho = FilhoEsq;
    dir->tipoFilho = FilhoDir;
  }
  return p;

} /* CombinaArvs */


void LiberaArvoreAux(ArvHuf p){
/* Libera a mem�ria din�mica ocupada pela �rvore 'p'. */

  if (p!=NULL) {
    LiberaArvoreAux(p->esq);
    LiberaArvoreAux(p->dir);
    FREE(p);
  }
  
} /* LiberaArvoreAux */

Boolean AcrescentaChar(char *s, int *n, char c, int maxCars) {
/* Acresenta � seq��ncia de caracteres 's' o caractere 'c' e
   incrementa '*n'. Devolve 'false' se o n�mero de caracteres
   ultrapassou 'maxCars'.  */
   
  if ((*n)==maxCars)
    return false;
  s[*n] = c;
  (*n)++;
  return true;
  
} /* AcrescentaChar */



/* Fun��es auxiliares para implementa��o com pseudo-bits */
/* --------------------------------------------------------- */

Boolean AcrescentaBit(char *bits, int *numBits, short int b, int maxBits) {
/* Acrescenta � seq��ncia de pseudo-bits 'bits' o bit indicado por 'b';
   incrementa 'numbits'. Devolve 'false' se o n�mero de bits
   ultrapassou 'maxBits'. */
  return AcrescentaChar(bits, numBits, (char)(b+'0'), maxBits);
} /* AcrescentaBit */

short int IBit(char *bits, int i) {
  /* Retorna o i-�simo bit da cadeia apontada por 'bits' */
  return bits[i] - '0';
}

                     
                     
/* --------------------------------------------------------- */
/* Fun��es da interface                                      */
/* --------------------------------------------------------- */
                      
Boolean ConstroiHuffman(char txt[], int n) {
/* A partir do texto 'texto' de 'n' caracteres, constr�i a �rvore de
   Huffman para compress�o deste texto e a guarda numa vari�vel local
   do m�dulo 'huffman.c'.  Numa outra vari�vel local guarda um vetor
   de apontadores para as folhas da �rvore. Devolve 'true' se a
   constru��o teve sucesso; 'false' caso contr�rio. */

  ArvHuf floresta[256];
  int freq[256], i;
  Heap heap;      /* Depende da implementa��o de heap */
  
  /* Inicializa vari�veis */
  for (i=0; i<256; i++) {
    freq[i] = 0;
    Folhas[i] = NULL;
  }

  /* Conta a freq��ncia dos caracteres */
  for (i=0; i<n; i++) {
    freq[(unsigned char) txt[i]]++;
  }

/*--------------------------*/
/*       COMPLETAR !!       */
/*--------------------------*/

  return true;   /* PROVIS�RIO */
  
} /* ConstroiHuffman */

void LiberaHuffman() {
/* Libera a mem�ria din�mica ocupada pelas estruturas criadas por
   'ConstroiHuffman'. */

/*--------------------------*/
/*       COMPLETAR !!       */
/*--------------------------*/

} /* LiberaHuffman */


Boolean Comprime(char *txt, int n,
		 char *bits, int *numBits, int numBitsMax) {
/* Comprime os 'n' caracteres do texto 'txt' usando as estruturas j�
   constru�das, e deixa o resultado como uma seq��ncia de pseudo-bits
   (ou bits verdadeiros) na �rea apontada por 'bits'. Devolve em
   'numBits' o n�mero total de bits gerado. Em caso de sucesso devolve
   'true'; se houver mais de 'numBitsMax' bits, devolve 'false'. */

/*--------------------------*/
/*       COMPLETAR !!       */
/*--------------------------*/

  return true;   /* PROVIS�RIO */
  
} /* Comprime */

   
Boolean Descomprime(char *txt, int *n,
		    char *bits, int numBits, int tamMaxTxt) {
/* Descomprime a cadeia de pseudo-bits (ou bits verdadeiros) na �rea
   apontada por 'bits', de comprimento 'numBits' seguindo a �rvore de
   Huffman j� constru�da.  Em caso de sucesso devolve 'true'; se
   aparecer uma codifica��o incompat�vel com a �rvore, ou se houver
   mais caracteres que 'tamMaxTxt' devolve 'false'.*/

/*--------------------------*/
/*       COMPLETAR !!       */
/*--------------------------*/

  return true;   /* PROVIS�RIO */
   
} /* Descomprime */

/* --------------------------------------------------------- */
/* Fun��es auxiliares para os testes pelo programa principal */
/* N�o modifique estas declara��es                           */
/* --------------------------------------------------------- */

#define DESLOCA 5

char buf[10];  /* O buffer de impress�o ser� fixo de at� 9 caracteres e \0 */

ArvHuf esq(ArvHuf p, int nivel) { return p->esq; }
ArvHuf dir(ArvHuf p, int nivel) { return p->dir; }

char *info(ArvHuf p, int nivel) { 
  if ((p->esq==NULL)&&(p->dir==NULL))  /* folha */
    sprintf(buf,"%4d:%c",p->peso,p->letra);
  else  /* n� interno */
    sprintf(buf,"%4d",p->peso);
  return buf;
}

void ImprimeHuffman() {
/* Imprime a �rvore de Huffman num formato leg�vel */

  ImprimeArvore(Arvore,(subarvfunc*)esq,(subarvfunc*)dir,(infofunc*)info,NULL,DESLOCA,"�rvore vazia");
  

} /* ImprimeArvore */










