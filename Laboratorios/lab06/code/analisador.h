/* 
 * analisador.h: Interface para o m�dulo de transforma��o de
 * express�es em �rvores bin�rias e seus percursos.
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

/* Estrutura para retorno de erro, indicando tipo do erro e posi��o */
/* na cadeia de entrada.                                            */
typedef struct erro {
  int posicao;
  int codigoErro;
} Erro;

/* Estrutura de �rvore para representar uma express�o. O campo 'info'
   cont�m uma vari�vel ou um operador. */
typedef struct NoArvBin {
  char info;
  struct NoArvBin *esq, *dir;
} NoArvBin, *ArvBin;


Erro InArv(char* infixa, ArvBin *arv);
/* Transforma a nota��o infixa em �rvore bin�ria.  Em caso de erro,
   devolve o c�digo e a posi��o na cadeia de entrada onde o erro foi
   encontrado.  */

void ArvPre(ArvBin arv, char *pre);
/* Produz a representa��o pr�-fixa a partir da �rvore. */

void ArvPos(ArvBin arv, char *pos);
/* Produz a representa��o p�s-fixa a partir da �rvore. */

void LiberaArv(ArvBin arv);
/* Libera o espa�o ocupado pela �rvore. */
