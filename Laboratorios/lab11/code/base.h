/*
   Arquivo 'base.h':
   Laborat�rio: 11
*/

#include "balloc.h"

#define MaxHash 11

typedef char * String;

typedef enum {false, true} Boolean;

typedef void * Base;  /* tipo efetivo escondido */

typedef struct {
  int ra;
  String nome;
  } Aluno;
  
Base CriaBase();
/* Devolve apontador para uma base vazia com tabela inicializada */

Boolean InsereBase(Base p, Aluno *a);
/* Insere o registro 'a' na base 'p' se n�o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contr�rio devolve 'false' */
   
Boolean RemoveBase(Base p, int ra);
/* Remove da base 'p' o aluno com 'ra' dado; devolve 'true'
   se ele existiu e 'false' caso contr�rio. */

Boolean ConsultaBase(Base p, int ra, Aluno *a);
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'.  'a' conter� 
   os dados do aluno, se encontrado. */
   
int NumeroRegsBase(Base p);
/* Devolve o n�mero de registros (alunos) na base 'p'. */

void ImprimeBase(Base p);
/* Imprime, os registros contidos na base 'p', um por linha.  A ordem
   de impress�o segue a ordem das entradas da tabela, e para cada
   entrada, a ordem da lista ligada.  Cada linha come�a com o �ndice
   correspondente na tabela de espalhamento. Deve ser usado o formato
   "(%3d) %06d %s\n". */
   
void LiberaBase(Base p);
/* Libera toda a mem�ria utilizada pela base 'p', bem como
   todas as cadeias que guardam os nomes. */
