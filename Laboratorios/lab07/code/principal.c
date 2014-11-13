/* 
 * principal.c - Este programa testa o m�dulo 'base.c', operando
 * sobre uma �rvore de busca bin�ria sem otimiza��es. 
 *
 *  Comandos aceitos:
 *       i <ra> <nome> insere novo n� com ra e nome
 *       c <ra>        consulta ra
 *       r <ra>        remove ra, caso exita
 *       n  verifica n�mero de n�s na �rvore
 *       a  verifica altura da �rvore
 *       p  executa um percurso inordem na base
 *       l  libera base
 *       h  imprime resumo
 *       #  coment�rio
 *
 * A libera��o total da mem�ria din�mica alocada por 'MALLOC' � 
 *      testada no fim utilizando a fun��o 'FINISH_MALLOC()'.     
 */


#include <stdio.h>
#include <string.h>
#include "balloc.h"
#include "base.h" 

/* Fun��o auxiliar que imprime dados sobre bloco de mem�ria n�o
   liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {

  printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
  
} /* bprint */


void ImprimeComentario() {
  char c;
  int res;
    do { 
      res = scanf("%c", &c); 
      if (res!=EOF)
	printf("%c",c);
    } while ((res!=EOF) && (c!='\n'));
}

void ImprimeAluno(Aluno *aluno) {
  printf("%06d %s\n", aluno->ra, aluno->nome);
}

/* L� um nome da entrada, com no m�ximo 100 caracteres. */

#define COMPR_MAX_NOME 100
String leNome() {
  String nome;
  char buffer[COMPR_MAX_NOME+1];
  char c;
  int i, res;

  i = 0;
  while (i < COMPR_MAX_NOME && (res = scanf("%c", &c)) != EOF && c != '\n')
    buffer[i++] = c;
  buffer[i] = '\0';
  /* Despreza o restante da linha caso o nome seja maior que COMPR_MAX_NOME */
  if (i == COMPR_MAX_NOME && !(res == EOF || c == '\n'))
    while (scanf("%c", &c) != EOF && c != '\n') ;
  nome = MALLOC(strlen(buffer)+1);
  strcpy(nome, buffer);
  return nome;
}

int main() {
    Aluno aluno;
    Base base;
    Boolean fim = false;
    int ra;
    char acao;

    base = CriaBase(); 

    do { 
      if (scanf("%c", &acao) ==  EOF)
	fim = true; 
      else {
	printf("A��o: %c", acao);
	switch (acao) { 
          
	case '#':
	  ImprimeComentario();
	  break;
          
	case 'i':
	case 'I':
	  scanf("%d ",&aluno.ra);
	  aluno.nome = leNome();
	  printf(" %06d %s\n", aluno.ra, aluno.nome);
	  if (!InsereBase(&base, aluno)) {
	    printf("Ra %06d j� estava presente na base de dados.\n", aluno.ra);
	    FREE(aluno.nome);
	  }
	  break;
	
	case 'c':
	case 'C':
	  scanf("%d",&ra);
	  printf(" %06d",ra);
	  ImprimeComentario();
	  if (ConsultaBase(&base, ra, &aluno))
	    printf("%06d %s \n", ra, aluno.nome);
	  else
	    printf("Ra %06d n�o encontrado na base de dados.\n", ra);
	  break;

	case 'r':
	case 'R':
	  scanf("%d",&ra);
	  printf(" %06d",ra);
	  ImprimeComentario();
	  if (RemoveBase(&base, ra))
	    printf("Ra %06d removido.\n", ra);
	  else
	    printf("Ra %06d n�o encontrado na base de dados.\n", ra);
	  break;
            

	case 'n':
	case 'N':
	  ImprimeComentario();
	  printf("N�mero de n�s na base de dados: %d.\n", NumeroNosBase(&base));
	  break;

	case 'a':
	case 'A':
	  ImprimeComentario();
	  printf("Altura da base de dados: %d.\n", AlturaBase(&base));
	  break;
            
	case 'l':
	case 'L':
	  ImprimeComentario();
	  LiberaBase(&base);
	  base = CriaBase();
	  break;

	case 'p':
	case 'P':
	  ImprimeComentario();
	  PercorreBase(&base,ImprimeAluno);
	  break;
            
	case 'h':
	case 'H':
	  ImprimeComentario();
	  printf("\n");
	  printf("#             : coment�rio.\n");
	  printf("i <ra> <nome> : insere ra e nome na base.\n");
	  printf("c <ra>        : consulta ra na base.\n");
	  printf("r <ra>        : remove ra da base.\n");
	  printf("l             : libera base.\n");
	  printf("p             : executa um percurso inordem na base.\n");
	  printf("n             : verifica n�mero de n�s na base.\n");
	  printf("a             : verifica altura da base.\n");
	  printf("h             : imprime resumo.\n");
	  printf("x             : t�rmino.\n");
	  printf("q             : t�rmino.\n");
	  fim = true;
	  break;
            
	case 'x':
	case 'X':
	case 'q':
	case 'Q':
	  ImprimeComentario();
	  fim = true;
	  break;
	}  /* switch */
      }
    } while (!fim);
      
    
  bapply(bprint);

  printf("Processamento terminado\n");
  
  return 0;
  
} /* main */
