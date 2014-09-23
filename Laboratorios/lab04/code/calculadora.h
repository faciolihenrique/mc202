/* Interface para o m�dulo de c�lculo de express�es p�s-fixas sobre       */
/* uma base de dados formada por polin�mios em uma vari�vel.              */

#ifndef _CalcExpr_DEFINED
#define _CalcExpr_DEFINED

#include "polinomios.h"

#define MAX_EXPR 100 /* Tamanho m�ximo de uma express�o */

void InicializaBasePolinomios();
/* Inicializa polin�mios com NULL, indicando que n�o h� polin�nios       */
/* v�lidos na base.                                                      */ 

Polinomio RecuperaPolinomio(char x);
/* Retorna o polin�mio de nome x.                                        */

void ArmazenaPolinomio(char x, Polinomio p);
/* Armazena o polin�mio p sob o nome x na base.                          */


Polinomio CalcExpr(char* expr);
/* Retorna o polin�mio referente � express�o dada.                       */
/* O polin�mio devolvido � sempre uma nova c�pia, mesmo que a            */
/* express�o seja uma vari�vel simples.                                  */

#endif
