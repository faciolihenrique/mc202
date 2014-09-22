/* Este programa testa o módulo 'polinomios.c'. São declaradas 4  */
/* variáveis globais do tipo 'Polinomio' (elementos do vetor 'v'),*/
/* e o programa interpreta as ações dadas no arquivo de entrada.  */

/* A liberação total da memória dinâmica alocada por 'MALLOC' é   */
/*      testada no fim utilizando a função 'bapply'.     */


#include <stdio.h>
#include <string.h>
#include "polinomios.h" 
#include "balloc.h"

typedef struct Register_Tag {
    struct Register_Tag *next;  /**< next registered block */
    void *ptr;                  /**< pointer to the allocated block */
    char *who;                  /**< caller file name */
    int where;                  /**< caller line number */
    size_t size;                  /**< allocated block size */
} Register;

Register head = {NULL,NULL,0};

/* Função auxiliar que imprime dados sobre bloco de memória não
   liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {

  printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
  
} /* bprint */


void ImprimeComentario() {
  char c;
  int res;
  do { 
    res = scanf("%c", &c); 
    if (res!=EOF)
      printf("%c",c);
  } while ((res!=EOF) && (c!='\n'));
}

int main() {

  char acao;
  Polinomio v[4];
  int k, m, n;
  int e;
  float c;
  Boolean fim = false;
    
  /* --------------------------------------------------------------------------- */

  do { 
    scanf("%c", &acao);
    printf("Ação: %c", acao);
    switch (acao)
      { 
          
      case '#':
	ImprimeComentario();
	break;
            
      case 'c':
      case 'C':
	scanf("%d",&k);
	printf("%2d",k);
	ImprimeComentario();
	v[k-1] = CriaPolinomioNulo();
	break;
            
      case 'l':
      case 'L':
	scanf("%d",&k);
	printf("%2d",k);
	ImprimeComentario();
	LiberaPolinomio(v[k-1]);
	break;
            
      case 'n':
      case 'N':
	scanf("%d",&k);
	printf("%2d",k);
	ImprimeComentario();
	if (PolinomioNulo(v[k-1]))
	  printf("Polinomio %d é nulo\n",k);
	else 
	  printf("Polinomio %d não é nulo\n",k);
	break;
            
      case 't':
      case 'T':
	scanf("%d%d%f",&k,&e,&c);
	printf("%2d%3d%5.1f",k,e,c);
	ImprimeComentario();
	InsereTermo(v[k-1],e,c);
	break;
            
      case 'i':
      case 'I':
	scanf("%d",&k);
	printf("%2d",k);
	ImprimeComentario();
	printf("----> ");
	ImprimePolinomio(v[k-1]);
	break;
            
      case 's':
      case 'S':
	scanf("%d%d%d",&k,&m,&n);
	printf("%2d%2d%2d",k,m,n);
	ImprimeComentario();
	v[k-1] = SomaPolinomios(v[m-1],v[n-1]);
	break;
            
      case 'r':
      case 'R':
	scanf("%d%d%d%f",&k,&m,&e,&c);
	printf("%2d%2d%3d%5.1f",k,m,e,c);
	ImprimeComentario();
	v[k-1] = MultTermo(v[m-1],e,c);
	break;
            
      case 'm':
      case 'M':
	scanf("%d%d%d",&k,&m,&n);
	printf("%2d%2d%2d",k,m,n);
	ImprimeComentario();
	v[k-1] = MultPolinomios(v[m-1],v[n-1]);
	break;
            
      case 'h':
      case 'H':
	ImprimeComentario();
	printf("\n");
	printf("#         : comentário\n");
	printf("c k       : v[k] := 0\n");
	printf("l k       : Libera v[k]\n");
	printf("n k       : testa se  v[k]=0\n");
	printf("t k e c   : acrescenta termo (e,c) a v[k]\n");
	printf("i k       : imprime v[k]\n");
	printf("s k m n   : v[k] := v[m]+v[n]\n");
	printf("r k m e c : v[k] := v[m]*(e,c)\n");
	printf("m k m n   : v[k] := v[m]*v[n]\n");
	printf("x         : término\n");
	printf("q         : término\n");
	printf("h         : imprime resumo\n");
	fim = true;
	break;
            
      case 'x':
      case 'X':
      case 'q':
      case 'Q':
	ImprimeComentario();
	fim = true;
	break;
            
      }  /* switch */

  } while (!fim);
      
  /* Verifica se foram liberados todos os blocos alocados */
  bapply(bprint);
   
  printf("Processamento terminado\n");

  return 0;
  
} /* main */


/*------------------BALLOC.C*?--------------------------*/
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

/*-#-#-#-#-#-3-#-#-3-#-#----------POLINOMIOS.C----------#-#3-3-#-#-#-#--#-#---------*/

/*-----------------------  Função auxiliar  ----------------------------*/

void InsereTermoAux(Polinomio p, int e, float c) {
    /* Insere o termo '(e,c)' após o nó apontado por 'p'.               */
    Polinomio new = MALLOC(sizeof(Termo));
    
    new->expo = e;
    new->coef = c;
    new->prox = p->prox;
    p->prox = new;
    
} /* InsereTermoAux */


/*---------------- Implementação das funções da interface --------------*/


void ImprimePolinomio(Polinomio p) {
    /* Imprime, em ordem crescente dos expoentes, os termos do              */
    /* não nulos do 'p'. No caso do polinômio identicamente nulo,           */
    /* imprime as palavras "Polinômio nulo".                                */
    
    if (p==NULL) {
        printf("Polinômio inválido\n");
        return;
    }
    
    if (p->prox==p) {
        printf("Polinômio nulo\n");
        return;
    }
    
    p = p->prox;
    while (p->expo!=-1) {
        printf("(%2d,%5.1f) ",p->expo,p->coef);
        p = p->prox;
    }
    printf("\n");
    
} /* ImprimePolinomio */


Polinomio CriaPolinomioNulo() {
    /* Devolve um novo polinômio identicamente nulo(apenas com no cabeca)  */
    Polinomio q = MALLOC(sizeof(Termo));
    
    /*Um polinomio nulo só possui o nó cabeça apontando para ele mesmo*/
    q->expo = -1;
    q->prox = q;
    
    return q;
} /* CriaPolinomioNulo */



void LiberaPolinomio(Polinomio p) {
    /* Libera toda a memória dinâmica ocupada por um polinômio.             */
    
    /*Inicia no seguinte ao no cabeca, que eh passado como argumento*/
    Polinomio next = p->prox, aux;
    
    /*Desaloca cada termo do polinomio ate chegar no nó cabeca*/
    while(next != p){
        aux = next->prox;
        FREE(next);
        next = aux;
    }
    
    /*Desaloca o no cabeca*/
    FREE(p);
    
}/* LiberaPolinomio */

Boolean PolinomioNulo(Polinomio p) {
    /* Verifica se o polinômio 'p' é identicamente nulo.                    */
    
    /*Um polinomio identicamente nulo se o no cabeca aponta para ele mesmo */
    if(p->prox == p){
        return true;
    }
    
    return false;
    
} /* PolinomioNulo */


void InsereTermo(Polinomio p, int e, float c) {
    /* Insere no polinomio 'p' o termo '(e,c)', de maneira a manter os      */
    /* termos ordenados. Supõe que não existe ainda em 'p' um termo com     */
    /* expoente 'e', e que 'c' não é zero.                                  */
    Polinomio currently = p, next = p->prox;
    
    /*Busca a posicao para adicionar p, entre currently e next*/
    while(((next->expo) < e) && (next->expo != -1)){
        currently = next;
        next = next->prox;
    }
    
    /*Insere o termo desejado*/
    InsereTermoAux(currently, e, c);
    
    
} /* InsereTermo */


Polinomio SomaPolinomios(Polinomio a, Polinomio b) {
    /* Devolve a soma dos polinômios 'a' e 'b'. Não altera os polinômios    */
    /* dados. Termos nulos não são inseridos no resultados.                 */
    Polinomio soma, aux_a = a->prox, aux_b= b->prox;
    
    /*Inicializa um polinomio nulo*/
    soma = CriaPolinomioNulo();
    
    /*Realiza a operacao de somar enquanto os dois polinomios nao forem */
    /*iguais ao nó caceça*/;
    while(aux_a != a || aux_b != b){
        
        if(aux_a->expo == aux_b->expo){
            /*Insercao do elemento caso haja a soma e nao seja nula*/
            if(aux_a->coef + aux_b->coef){
                InsereTermo(soma, aux_a->expo, (aux_a->coef + aux_b->coef) );
            }
            aux_a = aux_a->prox;
            aux_b = aux_b->prox;
        }else if(aux_a->expo > aux_b->expo || aux_a->expo == -1){
            /*Caso o polinomio a ja tenha encerrado ou o coeficiente dele for maior*/
            InsereTermo(soma, aux_b->expo, aux_b->coef);
            aux_b = aux_b->prox;
        }else if(aux_b->expo > aux_a->expo || aux_b->expo == -1){
            /*Caso o polinomio b ja tenha encerrado ou o coeficiente dele foir maior*/
            InsereTermo(soma, aux_a->expo, aux_a->coef);
            aux_a = aux_a->prox;
        }
    }
    
    return soma;
} /* SomaPolinomios */


Polinomio MultTermo(Polinomio p, int e, float c) {
    /* Devolve o polinômio 'p' multiplicado pelo termo '(e,c)'. Supõe       */
    /* que 'c' não é nulo. Não altera o polinômio dado.                     */
    Polinomio multiplicado, aux = p->prox;
    
    multiplicado = CriaPolinomioNulo();
    
    while(aux != p){
        /*Na multiplicaca, soma-se os expoentes dos termos multi
          plicados e multiplica os seus coeficientes
         */
        InsereTermo(multiplicado, (aux->expo + e), (aux->coef * c) );
        aux = aux->prox;
    }
    
    return multiplicado;

} /* MultTermo */


Polinomio MultPolinomios(Polinomio a, Polinomio b) {
    /* Devolve o produto dos polinômios 'a' e 'b'. Não altera os polinômios */
    /* dados.                                                               */
    Polinomio produto, polinomio_aux, aux_b = b->prox, soma;
    produto = CriaPolinomioNulo();
    
    while(aux_b != b){
        /*Multiplica o termo que o aporntador aux_b esta, pelo polinomio a*/
        polinomio_aux = MultTermo(a, aux_b->expo, aux_b->coef);
        /*Faz a soma dos produtos previamente calculado com o atual*/
        soma = SomaPolinomios(produto, polinomio_aux);
        /*Libera os polinomios ja utilizados*/
        LiberaPolinomio(polinomio_aux);
        LiberaPolinomio(produto);
        
        produto = soma;
        
        /*Avanca o termo do polinomio b*/
        aux_b = aux_b->prox;
    }
    
    return produto;
} /* MultPolinomios */

