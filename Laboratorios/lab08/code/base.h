/* 
 *  Arquivo base.h: defini��o de tipos e cabe�alhos das fun��es de
 *  manipula��o da base.
 *
 * A base de dados � sempre passada por refer�ncia a fim de
 * uniformizar o tratamento; em alguns casos isto n�o seria
 * necess�rio.
 */

typedef enum {false, true} Boolean;

typedef char * String;

typedef void * Base;  /* tipo efetivo escondido */


typedef struct {
  int ra;
  String nome;
  } Aluno;
  
/* Tipo da fun��o a ser passado para a fun��o de percurso: o argumento
   aponta para o campo de informa��o (aluno). */
typedef void TipoVisita(Aluno *aluno);


Base CriaBase();
/* Devolve apontador para uma base vazia */

Base SubEsq(Base *p);
/* Devolve a sub�rvore esquerda da base 'p' se n�o for vazia; caso
   contr�rio devolve NULL. */

Base SubDir(Base *p);
/* Devolve a sub�rvore direita da base 'p' se n�o for vazia; caso
   contr�rio devolve NULL. */

int FatorBal(Base *p);
/* Devolve o fator de balanceamento da raiz da base: altura da
   sub�rvore direita menos a altura da sub�rvore esquerda; devolve
   zero se a �rvore � vazia. */

Boolean InsereBase(Base *p, Aluno a);
/* Insere o registro 'a' na base 'p' se n�o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contr�rio devolve 'false' */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a);
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'. 'a' conter� 
   os dados do aluno, se encontrado. */
   
int AlturaBase(Base *p);
/* Devolve a altura da base 'p'. */

int NumeroNosBase(Base *p);
/* Devolve o n�mero de n�s da base 'p'. */

void PercorreBase(Base *p, TipoVisita Visita);
/* Executa um percurso inordem na base, invocando a fun��o Visita
   para todos os elementos. */

void LiberaBase(Base *p);
/* Libera todos os n�s da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */

Boolean RemoveBase(Base *p, int ra);
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. 

   A IMPLEMENTA��O DESTA FUN��O � OPCIONAL. 

*/

void ImprimeBase(Base *p);
  /* Imprime a base sob a forma de uma �rvore 'deitada'. */
