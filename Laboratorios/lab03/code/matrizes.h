/* Laborat�rio 03 - matrizes esparsas ligadas - interface. */
/* Adapta��o do exerc�cio originalmente preparado por Jorge Stolfi */

#define LCMAX 10000  /* N�mero m�ximo de linhas e de colunas. */

    /* As linhas e colunas da matriz esparsa s�o numeradas "0 .. nlins-1" e
      "0 .. ncols-1", respectivamente.

      Os elementos n�o nulos de cada linha "i" formam uma lista
      circular com cabe�a, duplamente ligada pelos campos "dir"
      e "esq". A cabe�a da linha, "clin[i]", fica na
      extremidade direita da mesma, e tem "clin[i]->col = ncols".

      Analogamente, os elementos de cada coluna "j" formam uma lista
      circular com cabe�a, duplamente ligada pelos campos "ab" e
      "ac". A cabe�a da coluna, "ccol[j]", fica na extremidade
      inferior da mesma, com "ccol[j]->lin = nlins".

      As cabe�as de todas as linhas s�o ligadas entre si pelos
      campos "ab" e "ac", e as cabe�as das colunas s�o
      ligadas pelos campos "dir" e "esq". As duas listas de
      cabe�as compartilham um �nico n� *super-cabe�a* "clin[nlins] =
      ccol[ncols]", no canto inferior direito da matriz
      (com "lin = nlins" e "col = ncols"). */

/* Representa��o ligada de matrizes esparsas: */
typedef struct elemento *ap_elemento;

typedef struct elemento
  { int lin, col;          /* �ndices na matriz original. */ 
    float val;             /* Valor do elemento. */
    ap_elemento dir;       /* Pr�x. elem. na mesma linha, ou cabe�a da linha. */
    ap_elemento esq;       /* Elem. ant. na mesma linha, ou cabe�a da linha. */
    ap_elemento ab;        /* Pr�x. elem. na mesma coluna, ou cabe�a da coluna. */
    ap_elemento ac;        /* Elem. ant. na mesma coluna, ou cabe�a da coluna. */
  } elemento;

typedef struct 
  { int nlins, ncols;      /* Dimens�es da matriz original. */  
    int nelems;            /* N�mero de elementos n�o nulos. */
    ap_elemento *clin;     /* "clin[i]" = cabe�a da linha "i". */
    ap_elemento *ccol;     /* "ccol[j]" = cabe�a da coluna "j". */
  } matriz;


/* Os procedimentos abaixo devem interromper o programa com 
  uma mensagem de erro quando os argumentos fornecidos n�o
  satisfazem as condi��es especificadas. Veja o procedimento 
  "erro" mais abaixo. */

void inicializa(matriz *a, int m, int n);
  /* Inicializa "a" com uma matriz nula de "m" linhas e "n" colunas. */

void libera(matriz *a);
  /* Libera toda a mem�ria din�mica ocupada por uma matriz */

float valor(matriz *a, int i, int j);
  /* Retorna o valor do elemento da matriz "a" com �ndices "[i,j]"
    (que devem estar nos respectivos intervalos de validade).  */

void atribui(matriz *a, int i, int j, float v);
  /* Armazena o valor "v" na matriz "a", com �ndices "[i,j]"
    (que devem estar nos respectivos intervalos de validade). */

void soma(matriz *a, matriz *b, matriz *s);
  /* Coloca em "s" a soma das matrizes "a" e "b",
    que devem ter as mesmas dimens�es (linhas e colunas).  */

void multiplica(matriz *a, matriz *b, matriz *p);
  /* Retorna na matriz "p" o produto das matrizes "a" e "b".
     O n�mero de colunas de "a" deve ser igual ao n�mero de linhas de "b". */

void transpoe(matriz *a, matriz *t);
  /* Coloca em "t" a transposta da matriz "a". */

void le_matriz(matriz *a);
  /* L� uma matriz e coloca-a em "a". A pr�xima linha  do arquivo
    de entrada deve conter tr�s inteiros "nlins", "ncols", "nelems" 
    (n�mero de linhas, de colunas, e de elementos n�o nulos da matriz).
    Em seguida devem vir "nelems" linhas do arquivo, cada qual contendo
    os �ndices "lin" e "col" e o valor "val" de um elemento n�o nulo da
    matriz. */

void imprime_matriz(matriz *a);
  /* Imprime os elementos da matriz "a", no formato esperado
    por "le_matriz". */

void erro(char *msg);
  /* Fun��o auxiliar: imprime "msg" e termina o programa. */

void prox_linha(void);
  /* Fun��o auxiliar: pula caracteres at� o pr�ximo fim-de-linha. */

