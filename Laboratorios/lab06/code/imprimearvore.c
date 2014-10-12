
/*  Last update: "imprimearvore.c: 2012-09-06 (Thu)  11:30:22 BRT (tk)"  */

/*! @file imprimearvore.c
 *
 * @brief Impress�o de �rvores bin�rias
 *
 * <b>Hist�rico:</b> V. imprimearvore.h
 */

#include <stdio.h>
#include "imprimearvore.h" 

void ImprimeArvoreAux(void *arv, subarvfunc *esq, subarvfunc *dir, infofunc *info, libfunc *libera, int desl, int nivel, char apont) {
  /* Fun��o auxiliar para 'ImprimeArvore': recebe os mesmos argumentos
     al�m do valor de n�vel do n� na �rvore e o caractere a
     representar o apontador (normalmente '\' ou '/').
  */
  
  void *p = arv;
  
  if (p!=NULL) {
    
    char *inf;
    
    ImprimeArvoreAux(dir(p,nivel+1), esq, dir, info, libera, desl, nivel+1, '/');
    printf("%*s",(nivel-1)*desl," ");
    if (nivel>1)
      printf("  %c",apont);
    inf = info(p,nivel);
    printf("%-s\n",inf);
    if (libera!=NULL)
      libera(inf);
    ImprimeArvoreAux(esq(p,nivel+1), esq, dir, info, libera, desl, nivel+1, '\\');
  }
  
}  /* ImprimeArvoreAux */

void ImprimeArvore(void *arv, subarvfunc *esq, subarvfunc *dir, infofunc *info, libfunc *libera, int desl, char *vazia) {
/* Imprime uma �rvore bin�ria num formato leg�vel. 
   
   Argumentos:
   
     arv:    apontador para a raiz da �rvore
     esq:    fun��o que devolve apontador para o filho esquerdo
     dir:    fun��o que devolve apontador para o filho direito
     info:   fun��o que processa a informa��o do n� da �rvore e devolve
             a cadeia a ser impressa
     libera: fun��o que libera o bloco de mem�ria devolvido por 'info'
             (pode ser NULL se desnecess�rio)

     Em todas as fun��es que s�o argumentos, o argumento inteiro
     corresponde ao n�vel do n�; na chamada inicial este n�vel ter�
     valor 1.

 */
  
  if (arv==NULL) 
    printf("%s",vazia);
  else
    ImprimeArvoreAux(arv, esq, dir, info, libera, desl, 1,' ');

} /* ImprimeArvore */
