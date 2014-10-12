/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli		    *
 * RA : 157986				        *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        * 
 * * * * * * * * * * * * * * * * * */

/* Este módulo implementa operações sobre polinômios em uma variável.   */
/* Cada polinômio é representado por uma lista ligada circular, com nó   */
/* cabeça. Os nós da lista representam os termos não nulos do polinômio */
/* em ordem crescente dos seus expoentes. O nó cabeça tem expoente '-1'.*/

#include "polinomios.h"
#include "balloc.h"
#include <stdio.h>

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
    printf("Liberando Polinomio\n");
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
    while(((next->expo) < e) && (next != p)){
        currently = next;
        next = next->prox;
    }
    
    /*Insere o termo desejado*/
    InsereTermoAux(currently, e, c);
    
    
} /* InsereTermo */


Polinomio SomaPolinomios(Polinomio a, Polinomio b) {
    printf("Somando Polinomio\n");
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


/*Mesmo processo da soma, só que reazliando a operacao inversa*/
Polinomio SubPolinomios(Polinomio a, Polinomio b) {
    printf("Subtraindo polinomio\n");
/* Devolve a diferença entre o polinômio 'a' e o polinômio 'b'. Não      */
/* altera os polinômios dados. Termos nulos não são inseridos no         */
/* resultado.                                                            */
    Polinomio sub, aux_a = a->prox, aux_b= b->prox;
    
    /*Inicializa um polinomio nulo*/
    sub = CriaPolinomioNulo();
    
    /*Realiza a operacao de subtrair enquanto os dois polinomios nao forem */
    /*iguais ao nó caceça*/
    while(aux_a != a || aux_b != b){
        
        if(aux_a->expo == aux_b->expo){
            /*Insercao do elemento caso haja a subtracao e nao seja nula*/
            if(aux_a->coef - aux_b->coef){
                InsereTermo(sub, aux_a->expo, (aux_a->coef - aux_b->coef) );
            }
            aux_a = aux_a->prox;
            aux_b = aux_b->prox;
        }else if(aux_a->expo > aux_b->expo || aux_a->expo == -1){
            /*Caso o polinomio a ja tenha encerrado ou o coeficiente dele for maior*/
            InsereTermo(sub, aux_b->expo, -(aux_b->coef));
            aux_b = aux_b->prox;
        }else if(aux_b->expo > aux_a->expo || aux_b->expo == -1){
            /*Caso o polinomio b ja tenha encerrado ou o coeficiente dele foir maior*/
            InsereTermo(sub, aux_a->expo, aux_a->coef);
            aux_a = aux_a->prox;
        }
    }
    
    return sub;
} /* SubPolinomios */

Polinomio MultTermo(Polinomio p, int e, float c) {
    printf("Multiplicando Polinomio por termo\n");
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
    printf("Multiplicando Polinomios\n");
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

