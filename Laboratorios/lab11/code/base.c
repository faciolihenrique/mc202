
#include <stdio.h>
#include "base.h"

/* DECLARA��ES DE TIPOS */
/* -------------------- */

typedef struct RegLista *Lista;
typedef struct RegLista {
  Aluno aluno;
  Lista prox;
} RegLista;

typedef struct RegBase *ImplBase;
typedef struct RegBase {
  int numregs;
  Lista tabela[MaxHash];
} RegBase;

/* FUN��O DE ESPALHAMENTO */
/* ---------------------- */

int Espalha(int k) {
  return (k%MaxHash);
} /* Espalha */

/* FUN��ES AUXILIARES */
/* ------------------ */

/* COMPLETAR SE NECESS�RIO */


/* FUN��ES DA INTERFACE */
/* -------------------- */

/* COMPLETAR */
