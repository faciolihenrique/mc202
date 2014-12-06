/*
 * Este programa testa as fun��es de um m�dulo de compress�o
 * descompress�o conforme especificado no arquivo 'huffman.h'.
 * 
 */

#include <stdio.h>
#include "balloc.h"
#include "huffman.h"

#define TamMaxTexto 2500        /* em caracteres */
#define TamMaxComprimido 16000  /* em bits       */

void bprint(char *who, int where, void *ptr, size_t size) {
/* Fun��o auxiliar que imprime dados sobre bloco de mem�ria n�o
   liberado. */
  printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
} /* bprint */


Boolean LeTexto(char *txt, int *n) {
/* L� o arquivo de entrada na �rea apontada por 'txt' e coloca em '*n'
   o n�mero de caracteres lidos. Devolve 'true' em caso de sucesso;
   devolve 'false' se o comprimento do arquivo for maior do que
   'TamMaxTexto'.  */

  int resScanf;

  *n = 0;
  while((resScanf = scanf("%c", txt)) != EOF && *n < TamMaxTexto) {
    txt++;
    (*n)++;
  }

  return resScanf == EOF;

} /* LeCadeia */

void Escreve(char *s, int n) {
/* Escreve 'n' caracteres da cadeia 's' */

  int i;

  for (i = 0; i<n; i++) {
    printf("%c",*s);
    s++;
  }
  printf("\n");
  
} /* Escreve */

#define TamMaxLinha 30

void EscreveBits(char *s, int nBits) {
/* Escreve 'nBits' da cadeia 's' */

  int i;
  char byte;

  for (i = 0; i<nBits; i++) {
    if (i % TamMaxLinha == 0) 
      printf("\n");
    if (i % 8 == 0) {
      byte = *s; 
      s++;
    }
    else
      byte = byte << 1;
    if (byte & 0x80)
      printf("1");
    else
      printf("0");
  }
  printf("\n");
} /* EscreveBits */


void EscreveBitsSimulados(char *s, int nBits) {
/* Escreve 'nBits' da cadeia 's' (pseudo-bits) */
  int i;

  for (i = 0; i<nBits; i++) {
    if (i % TamMaxLinha == 0) 
      printf("\n");
    printf("%c", s[i]);
  }
  printf("\n");
} /* EscreveBitsSimulados */

int main() {

  char txt[TamMaxTexto];
  char auxTxt[TamMaxTexto];
  char bits[TamMaxComprimido];

  int tamTxt, tamAuxTxt, numBits;

  /* L� o texto de entrada */
  if (!LeTexto(txt, &tamTxt)) {
    printf("Problemas com o arquivo de entrada\n");
    return 0;
  }

  printf("\nTexto original:\n");
  printf("--------------------------------------------------\n");
  Escreve(txt,tamTxt);
  printf("--------------------------------------------------\n");
  
  /* Inicializa estruturas */
  if(ConstroiHuffman(txt, tamTxt)) {
    printf("\n�rvore de Huffman:\n\n");
    ImprimeHuffman();
  } else {
    printf("\nN�o foi poss�vel construir a �rvore\n");
    return 0;
  }
    
  if (!Comprime(txt, tamTxt, bits, &numBits, TamMaxComprimido)) {
    printf("Problemas na compress�o\n");
    return 0;
  }

  printf("\nTexto comprimido:\n");
 #ifdef PSEUDO_BITS
    EscreveBitsSimulados(bits, numBits);
  #else
    EscreveBits(bits, numBits);
#endif    
  printf("\n");

  if (!Descomprime(auxTxt,&tamAuxTxt,bits,numBits,TamMaxTexto)) {
    printf("Problemas na descompress�o\n");
    return 1;
  }
  printf("\nTexto descomprimido:\n");
  printf("--------------------------------------------------\n");
    Escreve(auxTxt, tamAuxTxt);
  printf("--------------------------------------------------\n");
  

  if (tamTxt == tamAuxTxt &&
      strncmp(txt,auxTxt,tamTxt)==0) 
    printf("\nTextos id�nticos\n");
  else {
    printf("\nTextos diferentes\n");
    return 0;
  }

  printf("\nTexto original: %d bytes\n", tamTxt);
  printf("Cadeia comprimida: %d bits (%d bytes)\n",  numBits,
	 numBits % 8 == 0 ? numBits/8 : numBits/8 + 1);
  printf("M�dia: %2.1f bits/caractere\n",
	(float)numBits/(float)tamTxt);

  LiberaHuffman();

  /* Finaliza��o */

  int bch = bcheck();
  /* Verifica libera��o correta de mem�ria din�mica */
  if (bch!=0) {
    printf("\n%d blocos de mem�ria din�mica n�o foram liberados:\n",bch);
    bapply(bprint);
  } else{
    printf("\nA mem�ria din�mica foi totalmente liberada\n" );
  }
  
  printf("\nProcessamento terminado\n");
  return 0;

}
