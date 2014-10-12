/*
 * principal.c - Arquivo de teste para o m�dulo de transforma��o de
 * express�es em nota��o infixa para �rvores bin�rias e representa��es
 * pr�-fixa e p�s-fixa.
 */
#include <stdio.h>
#include <string.h>
#include "balloc.h"
#include "analisador.h"

/* Fun��o despejaArv para ser usada na depura��o */
#include "imprimearvore.h"
char cadeiainfo[2] = "*"; /* conter� a cadeia de um caractere */
char *vazia = "�rvore vazia\n";

ArvBin esq(ArvBin a, int d) {
  /* Sup�e a!=NULL */
  return a->esq;
}

ArvBin dir(ArvBin a, int d) {
  /* Sup�e a!=NULL */
  return a->dir;
}

char *info(ArvBin a, int d) {
  /* Sup�e a!=NULL */
  cadeiainfo[0] = a->info;
  return cadeiainfo;
}


void despejaArv(ArvBin a) {
/* Fun��o para depura��o: despeja a �rvore "deitada" */
  printf("\n�rvore despejada:\n");
  ImprimeArvore(a,(subarvfunc*)esq,(subarvfunc*)dir,(infofunc*)info,NULL,1,vazia);
  printf("\n");
}

/* Fun��o auxiliar que imprime dados sobre bloco de mem�ria n�o
   liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {

  printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
  
} /* bprint */


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
  int i;
  printf("Erro:   ");  /* Mostra posi��o do primeiro erro encontrado */
  for (i = 0; i < erro.posicao; i++)
    printf(" ");
  printf("^\n"); 
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
  char in[TAM_MAX_EXPR+2], res[TAM_MAX_EXPR+1];
  Erro erro;
  ArvBin arv;

  while (leExpr(in)>0) {
    erro = InArv(in,&arv);
    printf("Infixa: %s\n", in);
    if (erro.codigoErro == EXPR_VALIDA) {
      ArvPre(arv,res);
      /* para ser usado em depura��o: basta descomentar */
      /* despejaArv(arv); */
      printf("Prefixa: %s\n",res);
      ArvPos(arv,res);
      printf("Posfixa: %s\n\n",res);
    }
    else
      mostraErro(erro); 
    printf("\n");
    LiberaArv(arv);
  }
        
 /* Verifica se foram liberados todos os blocos alocados */
  bapply(bprint);

        
  printf("Processamento terminado\n");
  
  return 0;
  
} /* main */


