/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli		    *
 * RA : 157986				        *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        * 
 * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include "matrizes.h"
#include "balloc.h"

void erro(char *msg){ 
    printf("\n*** %s\n", msg); 
    exit(1);
}  

void remove_elem(matriz *a, ap_elemento r){
    /* Fun��o auxiliar: elimina um elemento "r" da matriz "a". */
    
    /*Para se excluir um elemento, deve-se passar os ponteiros
      que ele aponta para seus vizinhos, entao:*/
    
    /*Para remover o elemento da coluna em que se encontra*/
    r->ab->ac = r->ac;
    r->ac->ab = r->ab;
    /*Para remover o elemento da linha em que se encontra*/
    r->dir->esq = r->esq;
    r->esq->dir = r->dir;
    
    FREE(r);
    a->nelems--;
  }

void prox_linha(void){ 
    char c;
    do {
        scanf("%c", &c);
    } while ((c != '\n') && (c != EOF));
}

void inicializa(matriz *a, int m, int n){
    ap_elemento r, t;
    int i, j;
    
    if ((m < 1) || (m > LCMAX)){
        erro("inicializa: n�mero de linhas inv�lido");
    }
    if ((n < 1) || (n > LCMAX)){
        erro("inicializa: n�mero de colunas inv�lido");
    }
    a->nlins = m;
    a->ncols = n;
    a->nelems = 0;
    a->clin = (ap_elemento *)MALLOC((m+1)*sizeof(ap_elemento));
    a->ccol = (ap_elemento *)MALLOC((n+1)*sizeof(ap_elemento));
    
    /* Cria a cabe�a das cabe�as "r". */
    r = (ap_elemento)MALLOC(sizeof(elemento));
    if (r == NULL) { erro("inicializa: mem�ria esgotada"); }
    r->lin = m;
    r->col = n;
    r->val = 0;
    r->esq = r; r->dir = r;
    r->ac = r; r->ab = r;
    a->clin[m] = r;
    a->ccol[n] = r;
    
    /* Cria cabe�as das linhas: */
    for (i = 0; i < m; i++)
      { t = (ap_elemento)MALLOC(sizeof(elemento));
        if (t == NULL) { erro("inicializa: mem�ria esgotada"); }
        t->lin = i;
        t->col = n;
        t->val = 0;
        t->esq = t; t->dir = t;
        /* Insere logo acima da super-cabe�a: */
        t->ac = r->ac; t->ab = r;
        t->ab->ac = t;
        t->ac->ab = t;
        a->clin[i] = t;
      }
    
    /* Cria cabe�as das colunas: */
    for(i = 0; i < n; i++){
        t = (ap_elemento)MALLOC(sizeof(elemento));
        if (t == NULL) { erro("inicializa: mem�ria esgotada"); }
        t->lin = m;
        t->col = i;
        t->val = 0;
        t->ac = t;
        t->ab = t;
        
        /*Insere ao lado esquerdo da super-cabeca*/
        t->esq = r->esq;
        t->dir = r;
        t->dir->esq = t;
        t->esq->dir = t;
        a->ccol[i] = t;
    }
}

void libera(matriz *a) {
    /* Libera toda a mem�ria din�mica ocupada por uma matriz */
    int i;
    ap_elemento elemento, aux;
    
    /*Desaloca linha por linha a matriz*/
    for(i = 0; i <=  a->nlins; i++){
        elemento= a->clin[i]->esq;
        
        while( elemento != (a->clin[i]) ){
            aux = elemento->esq;
            remove_elem(a, elemento);
            elemento = aux;
        }
        FREE(a->clin[i]);
    }
    
    FREE(a->clin);
    FREE(a->ccol);
    FREE(a);
    
}

void encontra(matriz *a, int i, int j, ap_elemento *ppl, ap_elemento *ppc){ 
     /* Fun��o auxiliar: se o elemento "a[i,j]" existe,
    devolve seu endere�o em "*ppl" e "*ppc".  Caso contr�rio,
    devolve nessas vari�veis os endere�os dos seus sucessores
    imediatos na linha e coluna (possivelmente as respectivas
    cabe�as). */
    ap_elemento pl, pc;
    
    
    if ((i < 0) || (i >= a->nlins)) {
        erro("encontra: linha inv�lida");
    }
    if ((j < 0) || (j >= a->ncols)) {
        erro("encontra: coluna inv�lida");
    }
    
    /* Procura elemento "pl" na linha "i": */
    pl = a->clin[i]; 
    
    pl = pl->dir; while (pl->col < j) { pl = pl->dir; }
    if (pl->col == j){
        pc = pl;
    }else{ /* Procura elemento "pc" na coluna "j": */
        pc = a->ccol[j];
        pc = pc->ab; while (pc->lin < i) { pc =  pc->ab; }
        /* Consist�ncia: */
        if (pc == pl) {
             erro("encontra: apontadores pirados");
        }
    }
    
    if ((pl->lin != i) || (pl->col < j)){
        erro("encontra: pl inconsistente");
    }
    if ((pc->col != j) || (pc->lin < i)){
        erro("encontra: pc inconsistente");
    }
    
    (*ppl) = pl; (*ppc) = pc;
} 

float valor(matriz *a, int i, int j){
    ap_elemento pl, pc;
    encontra(a, i, j, &pl, &pc); 
    if (pl != pc){
        return 0;
    }
    else{
        return pl->val;
    }
}
 
void insere_elem(matriz *a, int i, int j, float v, ap_elemento pl, ap_elemento pc){
    /* Fun��o auxiliar: insere um elemento de valor "v" e �ndices "[i,j]",
     dadas as posi��es dos sucessores do elemento "a*[i,j]" na linha e 
     coluna, respectivamente (possivelmente cabe�as).  Sup�e que o 
     elemento n�o est� na matriz, e que "v != 0". */
    
    ap_elemento r;
    
    /*Ve se os casos estao dentro do esperado*/
    if (v == 0){
        erro("insere: elemento nulo"); 
    }
    if (pl->col < j) {
        erro("insere: pl inconsistente");
    }
    if (pc->lin < i) {
        erro("insere: pc inconsistente");
    }
    
    r = (ap_elemento)MALLOC(sizeof(elemento));
    r->lin = i;
    r->col = j;
    r->val = v;
    
    /* Insere o elemento nas listas da linha e da coluna: */
    /*Inserindo na coluna*/
    
    r->ab = pc;
    r->ac = pc->ac;
    r->ac->ab = r;
    pc->ac = r;
    
    /*Inserindo na linha*/
    r->dir = pl;
    r->esq = pl->esq;
    r->esq->dir = r;
    pl->esq = r;
    
    a->nelems++;
}   

void atribui(matriz *a, int i, int j, float v){
    ap_elemento pl, pc;
    encontra(a, i, j, &pl, &pc); 
    if (pl != pc)
      { /* Elemento n�o existe; se "v" n�o � nulo, precisa encaixar: */
        if (v != 0.0) { insere_elem(a, i, j, v, pl, pc); }
      }
    else
      { /* Elemento existe; se "v" � nulo, precisa remover, sen�o alterar: */
        if (v != 0.0) { pl->val = v; } else { remove_elem(a, pl); }
      }
}

void le_matriz(matriz *a){
    int m, n, d;
    int i, j; float v;
    int ip, jp; /* �ndices do elemento anterior. */
    int k;

    scanf("%d %d %d", &m, &n, &d); prox_linha();
    inicializa(a, m, n);
    ip = -1; jp = n-1;
    for (k = 0; k < d; k++)
      { scanf("%d %d %f", &i, &j, &v); prox_linha();
        if (v != 0) { insere_elem(a, i, j, v, a->clin[i], a->ccol[j]); }
      }
}

void imprime_matriz(matriz *a){
    int i;
    printf("%d %d %d\n", a->nlins, a->ncols, a->nelems);
    for (i = 0; i < a->nlins; i++)
      { elemento *p = a->clin[i]->dir;
        while (p->col < a->ncols) 
          { printf("  %2d %2d %8.2f\n", p->lin, p->col, p->val);
            p = p->dir;
          }
      }
}
 
void transpoe(matriz *a, matriz *t){ 
    int i;
    inicializa(t, a->ncols, a->nlins);
    erro("!!!COMPLETAR");
}

void soma(matriz *a, matriz *b, matriz *s){
    int i, j; float v;
    
    ap_elemento aux_a, aux+b;
    
    /* Verifica se possuem mesmas dimens�es: */
    if ((a->nlins != b->nlins) || (a->ncols != b->ncols))
      erro("soma: matrizes com tamanhos diferentes");
    /* Inicializa matriz "s" com mesmas dimensoes de "a" e "b": */
    inicializa(s, a->nlins, a->ncols);
    
    /*Vai linha por linha vendo se os elementos estao nas duas matrizes,
      se estiver, soma as duas, se estiver em uma, e nao na outra, o valor
      eh repassado*/
    
    for(i = 0; i <= a->nlins; i++){
        aux_a = a->clin[i]->dir;
        aux_b = b->clin[i]->dir;
        
        while(aux_a != a->clin[i] || aux_b != b->clin[i]){
            if(aux_a->col == aux_b->col){
                atribui(s, aux_a->lin, aux_a->col, (aux_a->val + aux_b->val);
            }
            
        }
        
        
        
    }
    
    
}

void multiplica(matriz *a, matriz *b, matriz *p){
    int i, j;
    if ((a->ncols) != (b->nlins)) { erro("multiplica: tamanhos invalidos"); }
    inicializa(p, a->nlins, b->ncols);
    erro("!!!COMPLETAR");
}