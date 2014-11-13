/*
 *  Arquivo base.h: defini��o de tipos e cabe�alhos das fun��es de
 *  manipula��o da base.
 */

/* #include "balloc.h" */

typedef char * String;
typedef enum {false, true} Boolean;
typedef void * Base;  /* tipo efetivo escondido */

typedef struct {
    int ra;
    String nome;
}Aluno;

Base CriaBase();
/* Devolve apontador para uma base vazia */

Boolean InsereBase(Base *p, Aluno a);
/* Insere o registro 'a' na base 'p' se n�o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contr�rio devolve 'false' */

Boolean ConsultaBase(Base *p, int ra, Aluno *a);
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'. 'a' conter�
   os dados do aluno, se encontrado. */

Boolean RemoveBase(Base *p, int ra);
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. */

int AlturaBase(Base *p);
/* Devolve a altura da base 'p'. */

int NumeroNosBase(Base *p);
/* Devolve o n�mero de n�s da base 'p'. */

void PercorreBase(Base *p, void (*Visita)(Aluno*));
/* Executa um percurso inordem na base, invocando a fun��o Visita
   para todos os elementos. */

void LiberaBase(Base *p);
/* Libera todos os n�s da base apontada por 'p', bem
   como todas as cadeias que guardam os nomes. */
