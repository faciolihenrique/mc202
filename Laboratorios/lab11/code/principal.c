/* 
   Programa principal para teste do Lab 11.
*/

#include <stdio.h>
#include <string.h>
#include "base.h"

#define ComprMaxNome 100

String buf;     /* Vari�vel global para evitar aloca��o repetida */

/* Fun��o auxiliar que imprime dados sobre bloco de mem�ria n�o
   liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {
    printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
} /* bprint */


Boolean LeAluno(FILE * arq, Aluno *a) {
/* Devolve 'false' no fim do arquivo */
/* Notar como � lida uma cadeia de caracteres terminando no fim da
   linha. A nota��o '[^\n]' significa qualquer caractere diferente de
   '\n'. */

  if (fscanf(arq,"%d %[^\n]\n",&((*a).ra), buf)==EOF)
    return false;    /* fim de arquivo */
    
  (*a).nome = MALLOC(strlen(buf)+1);
  strcpy((*a).nome,buf);
  return true;
}

int main(int argc, char * argv[]) {
/* Os argumentos s�o os nomes dos dois arquivos que
   cont�m, respectivamente, os dados para inser��o e
   as operacoes.  A sa�da � para o arquivo 'stdout'. */

  Aluno a;
  int ra;
  char op;
  Base p; 
  FILE * dados;
  FILE * operacoes;
  

  if (argc!=3) {                          /* verifica o n�mero de
					     argumentos */
    printf("Faltam ou sobram nomes dos arquivos\n");
    return 1;
  }
  
  dados = fopen(argv[1],"r");
  operacoes = fopen(argv[2],"r");
  
  if ((dados==NULL) || (operacoes==NULL)) {
    printf("Problmas na abertura dos arquivos\n");
    return 1;
  }
  
  buf = MALLOC(ComprMaxNome);
  p = CriaBase();
  
  printf("Carga inicial dos dados:\n");
  
  while (LeAluno(dados,&a)) {
    if (!InsereBase(p,&a)) {
        printf("RA=%06d repetido\n",a.ra);
        FREE(a.nome);
    }
  }
  
  printf("\nOpera��es:\n");
  while (fscanf(operacoes,"%c",&op)!=EOF) {
    switch (op) {
      case 'i':  
        LeAluno(operacoes,&a);              /* ignora o resultado
					       booleano */
        printf("Insere: %06d %s\n",a.ra,a.nome);
        if (!InsereBase(p,&a)) {
          printf("RA=%06d repetido\n",a.ra);
          FREE(a.nome);
	}
        break;
      case 'r': 
        fscanf(operacoes,"%d\n",&ra);
        printf("Remove: %06d\n",ra);
        if (!RemoveBase(p,ra))
          printf("RA inexistente: %06d\n",ra);
        break;
      case 'c': 
        fscanf(operacoes,"%d\n",&ra);
        printf("Consulta: %06d\n",ra);
        if (ConsultaBase(p,ra,&a))
          printf("%06d  %s\n",a.ra, a.nome);
        else
          printf("RA inexistente: %06d\n",ra);
        break;
      case 'w': 
        fscanf(operacoes,"\n");
        printf("\nImprime base: %d registro(s):\n",NumeroRegsBase(p));
        ImprimeBase(p);
        printf("\n");
        break;
      default:
        fscanf(operacoes,"\n");
        printf("Opera��o inv�lida: %c\n",op);
        break;
    }
  }

  LiberaBase(p);
  FREE(buf);
  
  fclose(dados);
  fclose(operacoes);
    
  bapply(bprint);
   
  printf("\nProcessamento terminado\n");
  return 0;

}
