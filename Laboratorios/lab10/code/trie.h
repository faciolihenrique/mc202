/*    Last update: "trie.h: 2014-11-05 (Wed)  17:06:50 BRST (tk)" */

/* Arquivo trie.h:

   Define a implementa��o de �rvores digitais (ADs) atrav�s de um tipo
   abstrato de dados usando apontadores "void *".
   
   Sup�e que as cadeias inseridas consistem apenas das letras
   min�sculas 'a' a 'z', sem s�mbolos diacr�ticos.
   
*/

/* Limites */
/* ------- */

#define TAM_ALFABETO 26
#define TAM_MAX_CADEIA 50

/* Tipos */
/* ----- */

typedef enum {false, true} Boolean;
typedef void * Trie;
typedef void funcVisita(char *s);  /* usada pela fun��o percorreAD */


/* Fun��es */
/*-------- */

Trie CriaAD();
/* Devolve uma AD vazia. Sup�e uma implementa��o que n�o modifica mais
   o apontador para a raiz da AD. */


Boolean consultaAD(Trie t, char *s);
/* Verifica se a cadeia de caracteres 's' foi inserida na AD 't'. */


Boolean insereAD(Trie t, char *s);
/* Insere na AD 't' a cadeia de caracteres 's'.  Devolve o valor
   verdadeiro se houve inser��o; devolve o valor falso se a cadeia j�
   ocorre em 't'.  A cadeia 's' pode ser vazia (de comprimento zero).
*/


Boolean removeAD(Trie t, char *s);
/* Remove da AD 't' a cadeia de caracteres 's'. Devolve o valor
   verdadeiro se houve remo��o; devolve o valor falso se a cadeia n�o
   ocorre em '*t'.
*/


int numCadeiasAD(Trie t);
/* Devolve o n�mero de cadeias contidas na AD. */


void percorreAD(Trie t, funcVisita *v);
/* Visita, em ordem alfab�tica, as cadeias contidas na AD 't' e
   aplica, a cada cadeia, a fun��o 'v', sob a forma "v(s)", supondo
   que 's' � um apontador para a cadeia que deve terminar com o
   caractere nulo '\0'.
*/


void liberaAD(Trie t);
/* Libera a mem�ria din�mica alocada na constru��o da AD 't'. */

/* ------------------------------------------------------------
 Fun��es seguintes s�o usadas somente para verifica��o;
 conceitualmente n�o fazem parte da implementa��o.
*/

   
int numNosAD(Trie t);
/* Devolve o n�mero de n�s da AD. */


int alturaAD(Trie t);
/* Devolve a altura da AD. */
