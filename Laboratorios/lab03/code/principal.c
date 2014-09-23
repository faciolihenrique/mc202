/* Laborat�rio 03 - matrizes esparsas ligadas - Programa principal */
/* Adapta��o do exerc�cio originalmente preparado por Jorge Stolfi */

/* A libera��o total da mem�ria din�mica alocada por 'MALLOC' �   */
/* testada no fim utilizando a fun��o 'bapply'.     */

#include <stdio.h>
#include <string.h>
#include "matrizes.h" 
#include "balloc.h"

/* As matrizes s�o representadas externamente por letras mai�sculas: */
#define min_nome 'A'
#define max_nome 'D'

/* Internamente, elas s�o representadas por inteiros em "[0..num_nomes-1]": */
#define num_nomes (max_nome - min_nome + 1)
typedef unsigned char num_matriz; /* [0..max_nome-min_nome] */

/*BALLOC*/
typedef struct Register_Tag {
  struct Register_Tag *next;  /**< next registered block */
  void *ptr;                  /**< pointer to the allocated block */
  char *who;                  /**< caller file name */
  int where;                  /**< caller line number */
  size_t size;                  /**< allocated block size */
} Register;

/**
 * Linked list head. Field 'where' will be used as a counter for
 * registered blocks.
 */
Register head = {NULL,NULL,0};

/*BALLOC*/

/* Nosso tipo booleanso */
typedef enum {false, true} Boolean;

/* Fun��o auxiliar que imprime dados sobre bloco de mem�ria n�o
   liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {

  printf("Faltou liberar o bloco alocado no arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
  
} /* bprint */

void le_nome(num_matriz *k)
  /* L� um nome de matriz, pulando brancos, e devolve o n�mero correspondente. */
  { 
    char c;
    scanf(" %c", &c);
    if ((c < min_nome) || (c > max_nome)) 
      { erro("nome de matriz invalido"); }
    (*k) = c - min_nome;
  }

int main()
  {
    char acao;
    num_matriz k, k1, k2, k3;
    int m, n, i, j;
    float x;
    matriz a[num_nomes];

    while (true)
      { 
        scanf("%c", &acao);
        printf("a��o: %c", acao);
        switch (acao)
          { 
            case 'r': 
              le_nome(&k); prox_linha();
              printf(" %c\n", min_nome+k);
              le_matriz(&a[k]);
              break;
            case 'z': 
              le_nome(&k); scanf("%d %d", &m, &n); prox_linha();
              printf(" %c %d %d\n", min_nome+k, m, n);
              inicializa(&a[k], m, n);
              break;
            case 'v': 
              le_nome(&k); scanf("%d %d", &i, &j); prox_linha();
              printf(" %c %d %d\n", min_nome+k, i, j);
              printf("  %c[%d,%d] = %8.2f\n", min_nome+k, i, j, valor(&(a[k]), i, j));
              break;
            case 'a':
              le_nome(&k); scanf("%d %d %f", &i, &j, &x); prox_linha();
              printf(" %c %2d %2d %8.2f\n", min_nome+k, i, j, x);
              atribui(&a[k], i, j, x);
              break;
            case 's':
              le_nome(&k1); le_nome(&k2); le_nome(&k3); prox_linha();
              printf(" %c %c %c\n", min_nome+k1, min_nome+k2, min_nome+k3);
              soma(&a[k1], &a[k2], &a[k3]);
              break;
            case 'm':
              le_nome(&k1); le_nome(&k2); le_nome(&k3); prox_linha();
              printf(" %c %c %c\n", min_nome+k1, min_nome+k2, min_nome+k3);
              multiplica(&a[k1], &a[k2], &a[k3]);
              break;
            case 't':
              le_nome(&k1); le_nome(&k2); prox_linha();
              printf(" %c %c\n", min_nome+k1, min_nome+k2);
              transpoe(&a[k1], &a[k2]);
              break;
            case 'w':
              le_nome(&k); prox_linha();
              printf(" %c\n", min_nome+k);
              imprime_matriz(&a[k]);
              break;
            case 'x':
              printf("\n");
	      bapply(bprint);
              printf("fim da execu��o.\n");
              exit(0);
              break;
            case '#':
              { int c;
                do 
                  { c = getchar(); putchar(c); } 
                while ((c != '\n') && (c != EOF));
              }
              break;
  	   case 'l':
	     le_nome(&k); prox_linha();
             printf(" %c\n", min_nome+k);
             libera(&a[k]);
             break;
            default:
              { erro("a��o inv�lida"); }
          } /* switch */
      } /* while */

   bapply(bprint);

   return 0;
  } /* main */


/*=================FUNCOES DE BALLOC================*/
/* Auxiliary */

void auxfree(Register **p) {

  Register *q = *p;
  *p = q->next;
  memset(q->ptr,0,q->size);
  free(q->ptr);
  free(q);
  head.where--;
  return;
  
} /* auxfree */

/* API implementation */

void *balloc(char *who, int where, size_t n) {

  void *p;
  Register *r = malloc(sizeof(Register));
  if (r==NULL)
    return NULL;
  p = malloc(n);
  if (p==NULL) {
    free(r);
    return NULL;
  }
  r->next = head.next;
  r->ptr = p;
  r->who = who;
  r->where = where;
  r->size = n;
  head.next = r;
  head.where++;
  return p;
  
} /* balloc */

int bfree(void *ptr) {
  
  Register **p;
  if (ptr==NULL)
    return 1;      // attempt to free a NULL pointer
  for (p=&(head.next); (((*p)!=NULL)&&(((*p)->ptr)!=ptr)); p=&((*p)->next)) {
    // advance through the list
  }
  if ((*p)==NULL)  // attempt to free an unregistered pointer 
    return 2;
  auxfree(p);
  return 0;        // OK

} /* bfree */

int bnextfree(char **who, int *where) {

  Register *p = head.next;
  if (p==NULL)
    return 1;
  *who = p->who;
  *where = p->where;
  auxfree(&(head.next));
  return 0;
  
} /* bnextfree */

void bfreeall() {

  while (head.next!=NULL)
    auxfree(&(head.next));
  
} /* bfreeall */

int bcheck() {

  return head.where;
  
} /* bcheck */

void bapply(bfunc *bf) {

  Register *p;
  for (p=head.next;p!=NULL;p=p->next)
    bf(p->who,p->where,p->ptr,p->size);

} /* bapply */

/*=================FIM BALLOC===================*/

/*==================MATRIZES====================*/
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
 

/*Faz com que o elemto na posicao i, j seja realocado para a posicao
  j, i*/
void transpoe(matriz *a, matriz *t){ 
    int i;
    ap_elemento aux;
    
    inicializa(t, a->ncols, a->nlins);
    
    for(i = 0; i < a->nlins; i++){
        
        aux = a->clin[i]->dir;
        
        while(aux != a->clin[i]){
            atribui(t, aux->col, aux->lin, aux->val);
            aux = aux->dir;
        }
    }
    
}

void soma(matriz *a, matriz *b, matriz *s){
    int i, j; float v;
    
    ap_elemento aux_a, aux_b;
    
    /* Verifica se possuem mesmas dimens�es: */
    if ((a->nlins != b->nlins) || (a->ncols != b->ncols))
      erro("soma: matrizes com tamanhos diferentes");
    /* Inicializa matriz "s" com mesmas dimensoes de "a" e "b": */
    inicializa(s, a->nlins, a->ncols);
    
    /*Vai linha por linha vendo se os elementos estao nas duas matrizes,
      se estiver, soma as duas, se estiver em uma, e nao na outra, o valor
      eh repassado*/
    for(i = 0; i < a->nlins; i++){
        aux_a = a->clin[i]->dir;
        aux_b = b->clin[i]->dir;
        
        while(aux_a != a->clin[i] || aux_b != b->clin[i]){
            /*Caso em que as posicoes sao as mesmas*/
            if(aux_a->col == aux_b->col){
                v = aux_a->val + aux_b->val;
                if(v){
                    atribui(s, aux_a->lin, aux_a->col, v);
                }/*Se a soma n�o da 0*/
                aux_a = aux_a->dir;
                aux_b = aux_b->dir;
            }
            /*Caso em que 'b' possui uma coluna que 'a' n�o*/
            else if(aux_a->col > aux_b->col || aux_a == a->clin[i]){
                atribui(s, aux_b->lin, aux_b->col, aux_b->val);
                aux_b = aux_b->dir;
            }
            /*Caso em que 'a' possui uma coluna e 'b' nao*/
            else if(aux_b->col > aux_a->col || aux_b == b->clin[i]){
                atribui(s, aux_a->lin, aux_a->col, aux_a->val);
                aux_a = aux_a->dir;
            }
            
        }
    }
    
}

void multiplica(matriz *a, matriz *b, matriz *p){
    int i, j;
    float valor;
    ap_elemento aux_a, aux_b;
    
    if ((a->ncols) != (b->nlins)) {
        erro("multiplica: tamanhos invalidos");
    }
    
    
    inicializa(p, a->nlins, b->ncols);
    
    /*Para caso uma das matrizes seja nula, a matriz retornada sera nula*/
    if(!(a->nelems) || !(b->nelems)){
        return;
    }
    
    /*Faz-se um loop para percorrer todas as linha da matriz a e todas as
      colunas da matriz b, para cada lina e cada coluna percorre-nas para 
      ver se haver� alguma valor na multiplicacao, ou ser� 0.*/
    for(j = 0; j < b->ncols; j++){
        for(i = 0; i < a->nlins; i++){
            aux_a = a->clin[i]->dir;
            aux_b = b->ccol[j]->ab;
            valor = 0;
            
            /*Loop para percorrer a coluna apontada por b e 
             a linha apontada por a*/
            while(aux_a != a->clin[i] && aux_b != b->ccol[j]){
                /*Caso em que h� a multiplicacao por um numero
                  diferente de 0*/
                if(aux_a->col == aux_b->lin){
                    valor = valor + (aux_a->val * aux_b->val);
                    aux_b = aux_b->ab;
                    aux_a = aux_a->dir;
                }
                /*Caso do elemento na linha a for 0*/
                else if(aux_a->col > aux_b->lin || aux_a == a->clin[i]){
                    aux_b = aux_b->ab;
                }
                /*Caso o elemento na coluna b for 0*/
                else if(aux_b->lin > aux_a->col || aux_b == b->ccol[j]){
                    aux_a = aux_a->dir;
                }
            }
            
            /*Se a soma da multiplicacao n�o deu algum valor 0*/
            if(valor){
                atribui(p, i, j, valor);
            }
            
        }
    }
}
