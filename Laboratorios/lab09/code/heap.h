/*
  Arquivo heap.h: define a interface para uma fila de prioridades (FP)
  de  elementos fornecidos atrav�s de apontadores.
  
  A implementa��o sup�e que deseja-se uma FP com elemento m�ximo na
  raiz; pode-se obter uma FP com o m�nimo, atrav�s de defini��o
  conveniente da fun��o de compara��o 'comp'.
*/ 

typedef void * Heap;  /* tipo efetivo escondido */
typedef int funcCompara(void *, void *); /* tipo da fun��o de compara��o, devolvendo <0, 0, >0 */

Heap CriaHeap(int n, funcCompara *comp);
/* Cria uma FP vazia com espa�o de at� 'n' elementos que ser�o
   apontadores; 'comp' ser� a fun��o de compara��o para estes elementos.
*/

Heap CriaInicializaHeap(int n, funcCompara *comp, void *elems[]);
/* Cria uma FP de 'n' elementos apontadores fornecidos no vetor 'elems'.
   'comp' ser� a fun��o de compara��o para estes elementos.
*/

int TamanhoHeap(Heap h);
/* Devolve o n�mero de elementos contidos na FP. */

void InsereHeap(Heap h, void *e);
/* Insere o elemento 'e' na FP 'h'. Interrompe a execu��o do programa
   se houver estouro da FP.
*/

void * RemoveHeap(Heap h);
/* Remove e devolve o elemento m�ximo (de acordo com a fun��o 'comp')
   da FP.  Interrompe a execu��o do programa se a FP est� vazia.
*/

void LiberaHeap(Heap h);
/* Libera toda a mem�ria din�mica ocupada pela FP 'h', mas n�o por
   seus elementos.
*/

/* ============================================================ */

void * Elemento(Heap h, int k);
/* Devolve o k-�simo elemento (0<=k<tamanho da FP) do vetor que
   representa a FP.  Devolve NULL se o valor de k n�o � v�lido.  Esta
   fun��o � usada apenas para verifica��o da estrutura da FP mas n�o faz
   parte da especifica��o da interface abstrata pois esta n�o imp�e a
   implementa��o usando um vetor.
 */
