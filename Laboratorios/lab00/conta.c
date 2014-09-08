/* Programa: conta.c                                   */
/* Autor: Fulano de Tal                   RA000000     */
/* Disciplina: MC102                      Turma A      */
/* Data: 24/jan/2001                                   */

#include <stdio.h>

int main() {

  int cars=0, linhas=0;
  int c;
  
  while ((c=getchar())!=EOF)
    if (c=='\n')
      linhas++;
    else
      cars++;

  printf("Caracteres: %d\n",cars);
  printf("Linhas:     %d\n",linhas);
  
  return 0;
  
}
