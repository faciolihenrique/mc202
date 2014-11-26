/* 
 * principal.c - Este programa testa o m�dulo 'trie.c' que
 * implementa �rvores digitais ADs)
 *
 *  Comandos aceitos:
 *       c     cria e devolve uma AD vazia
 *       i  s  insere a cadeia s na AD
 *       v  s  verifica se a cadeia s est� na AD
 *       r  s  remove a cadeia s da AD
 *       p     visita as cadeias da AD em ordem alfab�tica
 *       n     imprime o n�mero de n�s da AD
 *       a     imprime a altura da AD
 *       k     imprime o n�mero de cadeias na AD
 *       l     libera a mem�ria din�mica ocupada pela AD     
 *       h     imprime resumo
 *       x ou qencerra execu��o
 *       #  coment�rio
 *
 * A libera��o total da mem�ria din�mica alocada por 'MALLOC' � 
 *     testada no fim.
 */
 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "balloc.h"
#include "trie.h" 

char entrada[TAM_MAX_CADEIA+4];

/* Fun��o auxiliar que imprime dados sobre bloco de mem�ria n�o liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {
    printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
} /* bprint */


/* Fun��o que l� o c�digo da a��o e a cadeia que pode ser
   vazia. Imprime todas as linhas */
char *leLinha(char *acao) {
 
  char *p, *q;
  p = fgets(entrada, TAM_MAX_CADEIA+4, stdin);
  if (p==NULL) {
    printf("Erro de leitura\n");
    exit(0);
  }
  printf("%s", entrada);
  if (strlen(entrada)<2) { /* a��o, \n */
    printf("Entrada inv�lida\n");
    exit(0);
  }
  *acao = entrada[0];
  do {
    p++;
  } while(*p==' ');
  q = p;
  while (*q>='a' && *q<='z') 
    q++;
  *q = '\0';
  return p;

} /* leLinha */
  
void visita(char *s) {
  if (*s=='\0')
    printf("Cadeia vazia\n");
  else
    printf("%s\n",s);
}

int main() {

  Trie trie;
  Boolean fim = false;
  char *cadeia;
  char acao;
  
  do { 
    
    cadeia = leLinha(&acao);
    
    switch(acao) {

 	case 'c':
	case 'C':
	  trie = CriaAD();
          break;
        
	case '#':
        case ' ':
	  break;
	  
	case 'i':
	case 'I':
          if (!insereAD(trie,cadeia))
	    printf("A cadeia j� ocorre na �rvore\n");
	  break;
        
	case 'v':
	case 'V':
          if (consultaAD(trie,cadeia))
	    printf("A cadeia ocorre na �rvore\n");
	  else
	    printf("A cadeia n�o ocorre na �rvore\n");
	  break;        

	case 'r':
	case 'R':
          if (!removeAD(trie,cadeia))
	    printf("A cadeia n�o ocorre na �rvore\n");
	  break;
        
 	case 'p':
	case 'P':
	  percorreAD(trie,visita);
          break;
          
 	case 'n':
	case 'N':
	  printf("Nos: %d\n",numNosAD(trie));
          break;
          
 	case 'a':
	case 'A':
	  printf("Altura: %d\n",alturaAD(trie));
          break;
          
 	case 'k':
	case 'K':
	  printf("Cadeias: %d\n",numCadeiasAD(trie));
          break;
          
 	case 'l':
	case 'L':
	  liberaAD(trie);
          break;
          
	case 'h':
	case 'H':
	  printf("#     : coment�rio.\n");
          printf("c     : cria e devolve uma AD vazia\n");
	  printf("i  s  : insere a cadeia s na AD\n");
	  printf("v  s  : verifica se a cadeia s est� na AD\n");
	  printf("r  s  : remove a a cadeia s est� da AD\n");
	  printf("p     : visita as cadeias da AD em ordem alfab�tica\n");
	  printf("n     : imprime o n�mero de n�s da AD\n");
	  printf("a     : imprime a altura da AD\n");
          printf("k     : imprime o n�mero de cadeias da AD\n");
	  printf("l     : libera a mem�ria din�mica ocupada pela AD\n");
	  printf("h     : imprime resumo.\n");
	  printf("x     : t�rmino.\n");
	  printf("q     : t�rmino.\n");
	  break;
	
	case 'x':
	case 'X':
	case 'q':
	case 'Q':
	  fim = true;
	  break;
          
        default:
	  printf("Acao invalida\n");
          break;

	}  /* switch */

    } while (!fim);

  bapply(bprint);

  printf("Processamento terminado\n");
  
  return 0;
  
} /* main */
