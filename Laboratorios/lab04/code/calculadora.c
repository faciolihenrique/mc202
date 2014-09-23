/* M�dulo de c�lculo de express�es p�s-fixas sobre uma base de dados     */
/* formada por polin�mios em uma vari�vel.                               */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "pilha.h"
#include "polinomios.h"
#include "balloc.h"
#include "boolean.h"

/* Mensagens de erro para este m�dulo.                                     */

#define MSG_ERRO_NOME_INVALIDO "nome inv�lido para a base de polin�mios."
#define MSG_ERRO_POLINOMIO_NAO_INICIALIZADO "tentativa de recuperar polin�mio n�o inicializado."
#define MSG_ERRO_FALTA_OPERANDO "n�mero insuficiente de operandos."
#define MSG_ERRO_FALTA_OPERADOR  "n�mero insuficiente de operandores."
#define MSG_ERRO_CARACTERE_INVALIDO "caractere inv�lido."

#define IMPRIME_ERRO(msg)  {printf("Erro: %s\n",msg); exit(0); }

#define TAM_BASE 5
Polinomio vetorPoli[TAM_BASE];

void InicializaBasePolinomios() {
/* Inicializa polin�mios com NULL, indicando que n�o h� polin�mios       */
/* v�lidos na base.                                                      */ 
  int i;
  for (i = 0; i < TAM_BASE; i++)
    vetorPoli[i] = NULL;
}

Polinomio RecuperaPolinomio(char x) {
/* Retorna o polin�mio de nome x.                                        */
  Polinomio poli;
  x = toupper(x);
  if (x >= 'A' && x < 'A' + TAM_BASE) 
    poli =  vetorPoli[x - 'A'];
  else {
    IMPRIME_ERRO(MSG_ERRO_NOME_INVALIDO);
    return NULL;
  }
  
  if (poli == NULL)
    IMPRIME_ERRO(MSG_ERRO_POLINOMIO_NAO_INICIALIZADO);

  return poli;
}

void ArmazenaPolinomio(char x, Polinomio p) {
/* Armazena o polin�mio p sob o nome x na base.                          */
  x = toupper(x);
  if (x >= 'A' && x < 'A' + TAM_BASE) 
    vetorPoli[x - 'A'] = p;
  else 
    IMPRIME_ERRO(MSG_ERRO_NOME_INVALIDO);
}

/*** C�lculo da express�o                                                 */

/* Defini��o dos elementos da pilha. Polin�mios tempor�rios devem ser     */
/* liberados ap�s terem sido utilizados. Polin�mios da base s� s�o        */
/* liberados quando o usu�rio invoca libera.                              */ 
typedef struct ElemPilha {
  Polinomio poli;
  Boolean temp; 
} ElemPilha;

ElemPilha* VerificaDesempilha (Pilha* pilha) {
/* Desempilha um elemento, enviando uma mensagem de erro caso a pilha      */
/* esteja vazia.                                                           */
  if (PilhaVazia(pilha)) {
    IMPRIME_ERRO(MSG_ERRO_FALTA_OPERANDO);
    return NULL;
  }
  return (ElemPilha*) Desempilha(pilha);
}

void EmpilhaOperando(Pilha* pilha, Polinomio poli, Boolean temp) {
/* Cria e empilha um n� do tipo ElemPilha.                                 */
  ElemPilha *elem = MALLOC (sizeof(ElemPilha));
  elem->poli = poli; 
  elem->temp = temp; 
  Empilha (pilha, elem);
}

 Boolean Operando(char c) {
/* Verifica se um caractere corresponde a um operando v�lido.              */
   return (c >= 'a' && c < 'a'+TAM_BASE) || (c >= 'A' && c < 'A'+TAM_BASE);
 }

Polinomio CalcExpr(char* expr) { 
/* Retorna o polin�mio referente � express�o dada.                       */
/* O polin�mio devolvido � sempre uma nova c�pia, mesmo que a            */
/* express�o seja uma vari�vel simples.                                  */

  /*----- COMPLETAR -----*/
  return NULL;        // resultado tempor�rio

}
