/* 
 * principal.c - Este programa testa o m�dulo 'heap.c', operando
 * sobre uma fila de prioridades (FP).
 *
 *  Comandos aceitos:
 *       i <ra> <nome> insere novo registro com ra e nome
 *       r             emove e devolve o registro da raiz da FP
 *       p             imprime e remove todos os dados contidos na FP 
 *                               em ordem natural da estrutura
 *       l             libera espa�o ocupado pela FP (mas n�o por seus elementos)
 *       n             imprime o n�mero de elementos da FP
 *       v             verifica a estrutura da FP                                     
 *       d             despeja a FP como uma �rvore (depura��o)
 *       h             imprime resumo dos comandos
 *       x ou q        encerra interpreta��o;
 *       #  coment�rio
 *
 */


#include <stdio.h>
#include <string.h>
#include "balloc.h"
#include "heap.h" 

typedef char * String;
typedef enum {false, true} Boolean;

#define TAM_MAX 100

typedef struct {
  int ra;
  String nome;
} Aluno;


/* ================================================== */
/* Fun��o que despeja a FP sob a forma de uma �rvore para ser usada na
   depura��o.
*/
void ImprimeArvore(Heap h, int k, int desl, int nivel, char aponta) {
  
  Aluno *ap = Elemento(h, k);
  
  if (ap!=NULL) {
    ImprimeArvore(h,2*k+2,desl,nivel+1,'/');
    printf("%*s",(nivel-1)*desl," ");
    if (nivel>1)
      printf("  %c",aponta);
    printf("%06d\n",ap->ra);
    ImprimeArvore(h,2*k+1,desl,nivel+1,'\\');
  }
} /* ImprimeArvore */



int comparaAlunos(void *a, void *b) {
  /* Compara os ra's dos alunos 'a' e 'b' */
  Aluno *aa = a;
  Aluno *bb = b;
  if (aa->ra>bb->ra)
    return -1;
  if (aa->ra<bb->ra)
    return +1;
  return 0;
 
} /* comparaAlunos */


void bprint(char *who, int where, void *ptr, size_t size) {
/* Fun��o auxiliar que imprime dados sobre bloco de mem�ria n�o
   liberado. */
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
    Aluno *ap;
    Heap heap;
    Boolean fim = false;
    int ra;
    int i, tam, fe, fd;
    char acao;

    heap = CriaHeap(TAM_MAX, comparaAlunos); 

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
          ap = MALLOC(sizeof(Aluno));
          *ap = aluno;
          InsereHeap(heap,ap);
	  break;
	
	case 'r':
	case 'R':
	  ImprimeComentario();
          ap = RemoveHeap(heap);
	  printf(" %06d %s\n", ap->ra, ap->nome);
          FREE(ap->nome);
          FREE(ap);
	  break;

	case 'p':
        case 'P':
	  ImprimeComentario();
          tam = TamanhoHeap(heap);
          for (i=0; i<tam; i++) {
	    ap = RemoveHeap(heap);
	    printf(" %06d %s\n", ap->ra, ap->nome);
	    FREE(ap->nome);
	    FREE(ap);
          }
	  break;
            
	case 'l':
	case 'L':
	  ImprimeComentario();
	  LiberaHeap(heap);
	  break;
	 
	case 'n':
	case 'N':
	  ImprimeComentario();
	  printf("N�mero de elementos: %d.\n", TamanhoHeap(heap));
	  break;

	case 'v':
        case 'V':
	  ImprimeComentario();
          tam = TamanhoHeap(heap);
          for (i=0; i<tam; i++) {
	    fe = 2*i+1;
            fd = fe+1;
            ra = ((Aluno *)Elemento(heap,i))->ra;
	    if (((fe<tam)&&(ra>((Aluno *)Elemento(heap,fe))->ra)) ||
		((fd<tam)&&(ra>((Aluno *)Elemento(heap,fd))->ra))) {
	      printf("Fila inv�lida\n");
	      break;
	    }
	  }
          printf("Fila v�lida\n");
	  break;

	case 'd':
        case 'D':
	  ImprimeComentario();
          if (TamanhoHeap(heap)==0)
	    printf("�rvore vazia\n");
          else
	    ImprimeArvore(heap,0,3,1,' ');
	  break;
	  
	case 'h':
	case 'H':
	  ImprimeComentario();
	  printf("\n");
	  printf("#             : coment�rio.\n");
	  printf("i <ra> <nome> : insere novo registro com ra e nome\n");                             
	  printf("r             : emove e devolve o registro da raiz da FP\n");
          printf("p             : imprime e remove todos os dados contidos na FP\n");               
	  printf("                        em ordem natural da estrutura\n");                             
	  printf("l             : libera espa�o ocupado pela FP (mas n�o por seus elementos)\n");          
	  printf("n             : imprime o n�mero de elementos da FP\n");                                 
	  printf("v             : verifica a estrutura da FP\n");                                          
          printf("d             : despeja a FP como uma �rvore (depura��o)\n");
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
