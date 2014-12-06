/*
 * huffman.h - Interface para o m�dulo de compress�o de textos
 *             utilizando o algoritmo de Huffman.
 */

#include <string.h>

typedef enum {false, true} Boolean;

Boolean ConstroiHuffman(char txt[],int n);
/* A partir do texto 'texto' de 'n' caracteres, constr�i a �rvore de
   Huffman para compress�o deste texto e a guarda numa vari�vel local
   do m�dulo 'huffman.c'.  Numa outra vari�vel local guarda um vetor
   de apontadores para as folhas da �rvore. Devolve 'true' se a
   constru��o teve sucesso; 'false' caso contr�rio. */

void ImprimeHuffman();
/* Imprime a �rvore de Huffman num formato leg�vel. Fun��o auxiliar
   para os testes pelo programa principal */ 
   
void LiberaHuffman();
/* Libera a mem�ria din�mica ocupada pelas estruturas criadas por
   'ConstroiHuffman'. */

Boolean Comprime(char *txt, int n,
		 char *bits, int *numBits, int numBitsMax);
/* Comprime os 'n' caracteres do texto 'txt' usando as estruturas j�
   constru�das, e deixa o resultado como uma seq��ncia de pseudo-bits
   (ou bits verdadeiros) na �rea apontada por 'bits'. Devolve em
   'numBits' o n�mero total de bits gerado. Em caso de sucesso devolve
   'true'; se houver mais de 'numBitsMax' bits, devolve 'false'. */

Boolean Descomprime(char *txt, int *n,
		    char *bits, int numBits, int numMaxCars);
/* Descomprime a cadeia de pseudo-bits (ou bits verdadeiros) na �rea
   apontada por 'bits', de comprimento 'numBits' seguindo a �rvore de
   Huffman j� constru�da.  Em caso de sucesso devolve 'true'; se
   aparecer uma codifica��o incompat�vel com a �rvore, ou se houver
   mais caracteres que 'tamMaxTxt' devolve 'false'.*/
