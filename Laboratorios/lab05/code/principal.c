/*
  Disciplina: MC202
  Tarefa 05 
  Segundo semestre de 2014
*/

/*
 * principal.c - Arquivo de teste para o m�dulo de transforma��o de
 * express�es na nota��o infixa para p�s-fixa.
 */
#include <stdio.h>
#include <string.h>

#include "analisador.h"


/* Mensagens de erro para os c�digos previstos em analisador.h */
char *msg_erro[] = {
  "Express�o v�lida.",
  "Operando esperado nesta posi��o.",
  "Operador esperado nesta posi��o.",  
  "Fecha par�ntese esperado nesta posi��o.",
  "Caractere inv�lido nesta posi��o.",
  "Cadeia de brancos."
};


void mostraErro(Erro erro) {
/* Imprime uma mensagem de erro. N�o encerra a execu��o do programa.    */
  printf("Erro:   %*s^\n",erro.posicao,""); /* Mostra posi��o do primeiro erro encontrado */
  printf("        %s\n\n", msg_erro[erro.codigoErro]);
} /* mostraErro */


int leExpr(char *in) {
/* Tenta ler uma express�o da entrada, desprezando linhas maiores do */
/* que TAM_MAX_EXPR, linhas vazias e linhas de coment�rio. Retorna o */
/* n�mero de caracteres lidos.                                       */
  int m;
  char ch;
  
  for (;;) {
    if (fgets(in,TAM_MAX_EXPR+2,stdin)==NULL) /* fim de arquivo */
      return 0;
    m = strlen(in);
    if (in[0]=='#')  { /* coment�rio */
      printf("%s",in);
    } else if (in[m-1]!='\n') { /* '\n' n�o coube */
      printf("Infixa: %s",in);
      do {
	ch=getc(stdin);
        putc(ch,stdout);
      } while (ch!='\n');    /* resto da entrada */
      printf("Erro:   Cadeia de entrada muito longa.\n\n");
    } else if (m>1) {        /* cadeia n�o vazia */
      in[m-1] = '\0';             /* elimina '\n' */
      return m-1;
    }
  }
  
} /* LeExpr */


int main() {
  char in[TAM_MAX_EXPR+2], pos[TAM_MAX_EXPR+1];
  Erro erro;

  while (leExpr(in)>0) {
      erro = InPos(in, pos);
      printf("Infixa: %s\n", in);
      if (erro.codigoErro == EXPR_VALIDA) {
	printf("Posfixa: %s\n\n", pos);
      }
      else
	mostraErro(erro); 
  }
        
  printf("Processamento terminado\n");
  
  return 0;
  
} /* main */


