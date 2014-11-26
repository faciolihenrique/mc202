/* * * * * * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli                *
 * RA : 157986                             *
 * henrique.facioli@gmail.com              *
 * henrique.facioli@students.ic.unicamp.br *
 * github : henriquefacioli                *
 * Tarefa 10 - 2sem 2014                   *
 * * * * * * * * * * * * * * * * * * * * * */

/* Arquivo trie.c:

   Implementação de árvores digitais (ADs) através de um tipo
   abstrato de dados usando apontadores "void *".

   Todas as definições estão no arquivo "trie.h".

*/

#include <stdio.h>

#include "trie.h"
#include "balloc.h"

typedef struct RegTrie * ImplTrie;

typedef struct RegTrie {
    Boolean fim;                 /* término de uma cadeia */
    ImplTrie subarv[TAM_ALFABETO]; /* vetor de subárvores */
} RegTrie;



/* ------------------------------------------------------------ */
/*          Sugestões de algumas funções auxiliares             */
/* ------------------------------------------------------------ */

ImplTrie criaInicializaNo() {
    /* Devolve um nó com a marca de fim de cadeia verdadeira e todas as
    subárvores vazias; usada para criar a AD inicial e durante a
    inserção.
    */

    ImplTrie p = MALLOC(sizeof(RegTrie));
    if (p==NULL) {
        printf("Memória esgotada\n");
        exit(0);
    }
    p->fim = false;
    for (int k=0; k<TAM_ALFABETO; k++)
      p->subarv[k] = NULL;
    return p;
}


Boolean livre(ImplTrie t) {
    /* Devolve verdadeiro se o nó 't' não é final e é uma folha; usada
    durante a remoção.
    */
    if(t->fim == true){
        return false;
    }
    return true;

}


void percorreAux(ImplTrie t, funcVisita *v, char *buf, int m) {
    /* Percorre a AD em ordem lexicográfica; constroi as cadeias em 'buf'
    e aplica a função 'v' quando termina uma cadeia, colocando no fim o
    caractere '\0'; 'm' é o índice do próximo caractere em 'buf'.
    */


}


/* ------------------------------------------------------------ */
/*                      Fim das sugestões                       */
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

    while(*s != '\0'){
        if(tree->subarv[*s-'a'] == NULL){
            ImplTrie aux = criaInicializaNo();
            tree->subarv[*s-'a'] = aux;
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
  Funções usadas somente para verificação; conceitualmente
  não fazem parte da implementação.
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
            aux = numNosAD(ih->subarv[i]);
            if(aux > cont){
                cont = aux;
            }
        }
    }

    return cont + 1;
}
