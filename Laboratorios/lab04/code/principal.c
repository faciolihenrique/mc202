/* Lab 04 - Este programa testa os m�dulos 'polinomios.c', 'pilha.c' e   */
/* 'calculadora.c'. A libera��o total da mem�ria din�mica alocada por    */
/* 'MALLOC' � testada no fim utilizando a fun��o 'bapply'.               */

#include <stdio.h>
#include "calculadora.h"
#include "polinomios.h" 
#include "balloc.h"


/* Fun��o auxiliar que imprime dados sobre bloco de mem�ria n�o
   liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {

  printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
  
} /* bprint */

/* Fun��o auxiliar para ler os dados de entrada */
void ImprimeComentario() {
  char c;
  int res;
  do { 
    res = scanf("%c", &c); 
    if (res!=EOF)
      printf("%c",c);
  } while ((res!=EOF) && (c!='\n'));
  fflush(stdout);
}

int main() {

  char acao, nome;
  char expr[MAX_EXPR+1];
  int e;
  float c;
  Boolean fim = false;
    
  /* ---------------------------------------------------------------- */
    
  InicializaBasePolinomios();

  do { 
    scanf("%c", &acao);
    printf("A��o: %c", acao);
    switch (acao)
      { 
          
      case '#':
	ImprimeComentario();
	break;
            
      case 'l':
      case 'L':
	scanf(" %c",&nome);
	printf(" %c", nome);
	ImprimeComentario();
	LiberaPolinomio(RecuperaPolinomio(nome));
	break;
          
      case 'a':
      case 'A':
	scanf(" %c %d%f",&nome,&e,&c);
	printf(" %c %d %.1f",nome,e,c);
	ImprimeComentario();
	ArmazenaPolinomio(nome,CriaPolinomioNulo());
	InsereTermo(RecuperaPolinomio(nome),e,c);
	break;
            
      case 'i':
      case 'I':
	scanf(" %c",&nome);
	printf(" %c", nome);
	ImprimeComentario();
	printf("----> ");
	ImprimePolinomio(RecuperaPolinomio(nome));
	break;
            
      case 'r':
      case 'R':
	scanf(" %c %s",&nome, expr);
	printf(" %c %s", nome, expr);
	ImprimeComentario();
	ArmazenaPolinomio(nome, CalcExpr(expr));
	break;
            
      case 'h':
      case 'H':
	ImprimeComentario();
	printf("\n");
	printf("a X e c   : Atribui o termo (e,c) ao polin�mio X\n");
	printf("r X expr  : Atribui o resultado de expr a X\n");
	printf("l X       : Libera X\n");
	printf("i X       : Imprime X\n");
	printf("h         : Imprime resumo\n");
	printf("#         : Linha de coment�rio\n");
	printf("x         : t�rmino\n");
	printf("q         : t�rmino\n");
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
  } while (!fim);
      

  /* Verifica se foram liberados todos os blocos alocados */
  bapply(bprint);

   
  printf("Processamento terminado\n");

  return 0;
  
} /* main */
