/*
  Disciplina: MC202
  Tarefa 05 
  Segundo semestre de 2014
*/

/* 
 * analisador.h: Interface para o m�dulo de transforma��o de express�es na
 * nota��o infixa para p�s-fixa.
 */

/* Tamanho m�ximo de uma express�o */
#define TAM_MAX_EXPR 100

/* C�digos de erro */

typedef enum{
  EXPR_VALIDA,
  OPERANDO_ESPERADO,
  OPERADOR_ESPERADO,
  FECHA_PARENTESE_ESPERADO,
  CARACTERE_INVALIDO,
  CADEIA_DE_BRANCOS
} CodigosErro;

/* Estrutura para retorno de erro, indicando o tipo do erro e a posi��o
   na cadeia de entrada.  */
typedef struct erro {
  int posicao; 
  int codigoErro; 
} Erro; 

Erro InPos(char* infixa, char* posfixa);
/* Transforma uma express�o da nota��o infixa para a p�s-fixa. Em caso
   de erro, devolve o c�digo e a posi��o na cadeia de entrada onde o
   erro foi encontrado.  */
