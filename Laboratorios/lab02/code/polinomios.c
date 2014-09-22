/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli		    *
 * RA : 157986				        *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        * 
 * * * * * * * * * * * * * * * * * */

/* Este m�dulo implementa opera��es sobre polin�mios em uma vari�vel.   */
/* Cada polin�mio � representado por uma lista ligada circular, com n�   */
/* cabe�a. Os n�s da lista representam os termos n�o nulos do polin�mio */
/* em ordem crescente dos seus expoentes. O n� cabe�a tem expoente '-1'.*/

#include "polinomios.h"
#include "balloc.h"
#include <stdio.h>

/*-----------------------  Fun��o auxiliar  ----------------------------*/

void InsereTermoAux(Polinomio p, int e, float c) {
    /* Insere o termo '(e,c)' ap�s o n� apontado por 'p'.               */
    Polinomio new = MALLOC(sizeof(Termo));
    
    new->expo = e;
    new->coef = c;
    new->prox = p->prox;
    p->prox = new;
    
} /* InsereTermoAux */


/*---------------- Implementa��o das fun��es da interface --------------*/


void ImprimePolinomio(Polinomio p) {
    /* Imprime, em ordem crescente dos expoentes, os termos do              */
    /* n�o nulos do 'p'. No caso do polin�mio identicamente nulo,           */
    /* imprime as palavras "Polin�mio nulo".                                */
    
    if (p==NULL) {
        printf("Polin�mio inv�lido\n");
        return;
    }
    
    if (p->prox==p) {
        printf("Polin�mio nulo\n");
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
    /* Devolve um novo polin�mio identicamente nulo(apenas com no cabeca)  */
    Polinomio q = MALLOC(sizeof(Termo));
    
    /*Um polinomio nulo s� possui o n� cabe�a apontando para ele mesmo*/
    q->expo = -1;
    q->prox = q;
    
    return q;
} /* CriaPolinomioNulo */



void LiberaPolinomio(Polinomio p) {
    /* Libera toda a mem�ria din�mica ocupada por um polin�mio.             */
    
    /*Inicia no seguinte ao no cabeca, que eh passado como argumento*/
    Polinomio next = p->prox, aux;
    
    /*Desaloca cada termo do polinomio ate chegar no n� cabeca*/
    while(next != p){
        aux = next->prox;
        FREE(next);
        next = aux;
    }
    
    /*Desaloca o no cabeca*/
    FREE(p);
    
}/* LiberaPolinomio */

Boolean PolinomioNulo(Polinomio p) {
    /* Verifica se o polin�mio 'p' � identicamente nulo.                    */
    
    /*Um polinomio identicamente nulo se o no cabeca aponta para ele mesmo */
    if(p->prox == p){
        return true;
    }
    
    return false;
    
} /* PolinomioNulo */


void InsereTermo(Polinomio p, int e, float c) {
    /* Insere no polinomio 'p' o termo '(e,c)', de maneira a manter os      */
    /* termos ordenados. Sup�e que n�o existe ainda em 'p' um termo com     */
    /* expoente 'e', e que 'c' n�o � zero.                                  */
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
    /* Devolve a soma dos polin�mios 'a' e 'b'. N�o altera os polin�mios    */
    /* dados. Termos nulos n�o s�o inseridos no resultados.                 */
    Polinomio soma, aux_a = a->prox, aux_b= b->prox;
    
    /*Inicializa um polinomio nulo*/
    soma = CriaPolinomioNulo();
    
    /*Realiza a operacao de somar enquanto os dois polinomios nao forem */
    /*iguais ao n� cace�a*/;
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
    /* Devolve o polin�mio 'p' multiplicado pelo termo '(e,c)'. Sup�e       */
    /* que 'c' n�o � nulo. N�o altera o polin�mio dado.                     */
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
    /* Devolve o produto dos polin�mios 'a' e 'b'. N�o altera os polin�mios */
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
