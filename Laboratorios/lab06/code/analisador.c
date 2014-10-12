/*
  Autor:         COMPLETAR!
  RA:            COMPLETAR!
  Disciplina:    MC202
  Turma:         COMPLETAR!
  
  Tarefa 06 
  Segundo semestre de 2014

*/

/* 
 * analisador.c: M�dulo de transforma��o de express�es em �rvores
 * bin�rias e seus percursos.
 */

#include "analisador.h"
#include <stdlib.h>
#include <ctype.h>
#include "balloc.h"

/* Vari�veis globais a este m�dulo */

char *in;  /* Cadeia e �ndice para express�o infixa (entrada). */
int indIn;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */

/* Macro para desprezar espa�os em branco na cadeia de entrada. */
/* Para evitar chamadas desnecess�rias a esta macro, adotou-se  */
/* seguinte conve��o. A macro � invocada uma vez imediatamente  */
/* antes da primeira chamada � fun��o Expressao e imediatamente */
/* ap�s todo o incremento de indIn.                             */
#define DESPREZA_ESPACOS() while (in[indIn] == ' ') indIn++


/* Prot�tipos das fun��es mutuamente recursivas. */
/* O resultado � devolvido atrav�s da vari�vel 'arv'. */
Erro Expressao(ArvBin *arv);
Erro Termo(ArvBin *arv);
Erro Fator(ArvBin *arv);
Erro Primario(ArvBin *arv);

/* Fun��o auxiliar -- declarada mais adiante */
Erro montaErro(int codigo, int pos);


/*************************************************************/
/*                 Fun��o   principal                        */
/*************************************************************/

Erro InArv(char *infixa, ArvBin *arv) {
/* Transforma a nota��o infixa em �rvore bin�ria.  Em caso de erro,
   devolve o c�digo e a posi��o na cadeia de entrada onde o erro foi
   encontrado.  */

  /***** COMPLETAR!  *****/
  
  *arv = NULL;        /***** PROVIS�RIO ******/  
  return resCorreto;  /***** PROVIS�RIO ******/  

}

/*************************************************************/
/*           Fun��es de implementa��o do analisador          */
/*************************************************************/

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com c�digo de erro e posi��o */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVIS�RIO ******/  

} /* montaErro */


Erro Expressao(ArvBin *arv) {
/* Processa uma express�o da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVIS�RIO ******/  
  
} /* Expressao */


Erro Termo(ArvBin *arv) {
/* Processa um termo da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVIS�RIO ******/  

} /* Termo */


Erro Fator(ArvBin *arv) {
/* Processa um fator da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVIS�RIO ******/  

} /* Fator */


Erro Primario(ArvBin *arv) {
/* Processa um  prim�rio da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVIS�RIO ******/  

} /* Primario */

/* Percursos */

void ArvPre(ArvBin arv, char *pre) {
 /* Produz a representa��o pr�-fixa a partir da �rvore. */
 
  /***** COMPLETAR!  *****/

  *pre = '\0';   /***** PROVIS�RIO ******/

}

void ArvPos(ArvBin arv, char *pos) {
/* Produz a representa��o p�s-fixa a partir da �rvore. */
  /***** COMPLETAR!  *****/

  *pos = '\0';   /***** PROVIS�RIO ******/  

}


void LiberaArv(ArvBin arv) {
/* Libera o espa�o ocupado pela �rvore. */

  /***** COMPLETAR!  *****/


}

