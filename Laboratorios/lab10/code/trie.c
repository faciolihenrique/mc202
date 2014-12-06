/* * * * * * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli                *
 * RA : 157986                             *
 * henrique.facioli@gmail.com              *
 * henrique.facioli@students.ic.unicamp.br *
 * github : henriquefacioli                *
 * Tarefa 10 - 2sem 2014                   *
 * * * * * * * * * * * * * * * * * * * * * */

/* Arquivo trie.c:

   Implementa��o de �rvores digitais (ADs) atrav�s de um tipo
   abstrato de dados usando apontadores "void *".

   Todas as defini��es est�o no arquivo "trie.h".

*/

#include <stdio.h>

#include "trie.h"
#include "balloc.h"

typedef struct RegTrie * ImplTrie;

typedef struct RegTrie {
    Boolean fim;                 /* t�rmino de uma cadeia */
    ImplTrie subarv[TAM_ALFABETO]; /* vetor de sub�rvores */
} RegTrie;



/* ------------------------------------------------------------ */
/*          Sugest�es de algumas fun��es auxiliares             */
/* ------------------------------------------------------------ */

ImplTrie criaInicializaNo() {
    /* Devolve um n� com a marca de fim de cadeia falso e todas as
    sub�rvores vazias; usada para criar a AD inicial e durante a
    inser��o.
    */

    ImplTrie p = MALLOC(sizeof(RegTrie));
    if (p==NULL) {
        printf("Mem�ria esgotada\n");
        exit(0);
    }
    p->fim = false;
    for (int k=0; k<TAM_ALFABETO; k++)
      p->subarv[k] = NULL;
    return p;
}


Boolean livre(ImplTrie t) {
    /* Devolve verdadeiro se o n� 't' n�o � final e � uma folha; usada
    durante a remo��o.
    */
    if(t->fim == true){
        return false;
    }
    return true;

}


void percorreAux(ImplTrie t, funcVisita *v, char *buf, int m) {
    /* Percorre a AD em ordem lexicogr�fica; constroi as cadeias em 'buf'
    e aplica a fun��o 'v' quando termina uma cadeia, colocando no fim o
    caractere '\0'; 'm' � o �ndice do pr�ximo caractere em 'buf'.
    */


}


/* ------------------------------------------------------------ */
/*                      Fim das sugest�es                       */
/* ------------------------------------------------------------ */


Trie CriaAD() {

  return criaInicializaNo();

}


Boolean consultaAD(Trie t, char *s) {

    ImplTrie tree = (ImplTrie) t;

    if(*s != '\0'){
        if(tree->subarv[*s-'a'] != NULL){
            return consultaAD((Trie) tree->subarv[*s-'a'], s+1);
        }
        return false;
    }

    return tree->fim;
}


Boolean insereAD(Trie t, char *s) {
    ImplTrie tree = (ImplTrie) t;

    /*Enquanto n�o chegar ao fim da string de insersao ele verifica
      se a letra ja esta no vetor, se nao estiver, cria o n� da letra.*/
    while(*s != '\0'){
        if(tree->subarv[*s-'a'] == NULL){
            tree->subarv[*s-'a'] = criaInicializaNo();
        }
        tree = tree->subarv[*s-'a'];
        s++;
    }

    /*Se a palavra ja existisse na cadeia*/
    if(tree->fim){
        return false;
    }

    tree->fim = true;
    return true;
}


int numCadeiasAD(Trie t) {
    int i, cont = 0;
    ImplTrie ih = t;

    for(i = 0; i < TAM_ALFABETO; i++){
        if(ih->subarv[i] != NULL){
            cont = cont + numCadeiasAD(ih->subarv[i]);
        }
    }

    if(ih->fim){
        cont++;
    }

    return cont;
}


Boolean removeAD(Trie t, char *s) {

    ImplTrie tree = (ImplTrie) t;
    int i;

    /*Se chegou ao fim do da cadeia s e o n� � o fim de uma cadeia da arvore
      */
    if(*s == '\0' && tree->fim == true){
        short int achou = 0;
        /*Verifica se o n� possui algum filho*/
        for(i = 0; i < TAM_ALFABETO; i++){
            if(tree->subarv[i] != NULL){
                achou++;
            }
        }

        if(achou){
            tree->fim = false;
        }else{
            FREE(tree);
        }

        return true;
    }

    /*Se o n� da letra existir*/
    if(tree->subarv[*s-'a'] != NULL){
        short int achou = 0;
        /*Verifica se o n� possui mais de um filho*/
        for(i = 0; i < TAM_ALFABETO; i++){
            if(tree->subarv[i] != NULL){
                achou++;
            }
        }

        /*Caso tenha um unico filho, sera o subarv[s-a]*/
        if(achou == 1){
            Boolean aux = removeAD((Trie) tree->subarv[*s-'a'], s+1);
            FREE(tree);
            return aux;
        }

        /*Caso n�o tenha um unico filho, n�o remove o n�*/
        return removeAD((Trie) tree->subarv[*s-'a'], s+1);
    }

    /*Caso tenha chegado ao fim da string e n�o tenha encontrado o fim ou a subarve
      � nula(nao tem a palavra na arvore), retorna falso*/
    return false;
}


void percorreAD(Trie t, funcVisita *v) {

  char buf[TAM_MAX_CADEIA];

  percorreAux((ImplTrie)t,v,buf,0);

}

void liberaAD(Trie t) {

    int i;
    ImplTrie ih = t;

    for(i = 0; i < TAM_ALFABETO; i++){
        if(ih->subarv[i] != NULL){
            liberaAD( (Trie) ih->subarv[i]);
            FREE(ih->subarv[i]);
        }
    }

    FREE(ih);

}


/*
  Fun��es usadas somente para verifica��o; conceitualmente
  n�o fazem parte da implementa��o.
*/

int numNosAD(Trie t) {

    int i, cont = 1;
    ImplTrie ih = t;

    for(i = 0; i < TAM_ALFABETO; i++){
        if(ih->subarv[i] != NULL){
            cont = cont + numNosAD(ih->subarv[i]);
        }
    }

    return cont;
}

int alturaAD(Trie t) {

    int i, cont = 0, aux;
    ImplTrie ih = t;

    for(i = 0; i < TAM_ALFABETO; i++){
        if(ih->subarv[i] != NULL){
            /*Guarda em aux o tamanho da arvore*/
            aux = numNosAD((Trie) ih->subarv[i]);

            if(aux > cont){
                cont = aux;
            }
        }
    }

    return cont + 1;
}
