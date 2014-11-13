/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * Tarefa 07 - 2sem 2014           *
 * * * * * * * * * * * * * * * * * */
 
/*
 * Arquivo base.c: implementa��o das fun��es de manipula��o da base.
 */

#include <stdio.h>
#include "base.h"
#include "balloc.h"

typedef struct AuxNoArv {
    Aluno info;                   /* registros de informa��o */
    struct AuxNoArv *esq,*dir;   /* sub�rvores */
}NoArv, * ImplBase;


Base CriaBase() {
/* Devolve apontador para uma base vazia */
    return NULL;
}

Boolean InsereBase(Base *p, Aluno a) {
    ImplBase arv = (ImplBase) *p;

    if(*p == NULL){
        arv = MALLOC(sizeof(NoArv));
        arv->info = a;
        arv->esq = NULL;
        arv->dir = NULL;

        *p = (Base) arv;

        return true;
    }

    /*Caso ja exista o elemento que deseja inserir*/
    if(arv->info.ra == a.ra){
        return false;
    }

    /*Faz a busca na arvore at� encontrar a posi��o nescessaria */
    if(a.ra > arv->info.ra){
        /*Faz o casting de ImplBase para Base*/
        return InsereBase((Base*) &(arv->dir), a);
    }else{
        return InsereBase((Base*) &(arv->esq), a);
    }
} /* InsereBase */

Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'. 'a' conter�
   os dados do aluno, se encontrado. */
    ImplBase arv = (ImplBase) *p;

    /*Se a arvore estiver vazia*/
    if(*p == NULL){
        return false;
    }

    /*Caso seja igual*/
    if(ra == arv->info.ra) {
        *a = arv->info;
        return true;
    }

    /*Verifica os lados, e chama o lado a partir de uma busca binaria */
    if(ra > arv->info.ra){
        /*Faz o casting de ImplBase para Base dentro da propria funcao*/
        ConsultaBase( (Base*) &(arv->dir), ra, a);
    }
    ConsultaBase( (Base*) &(arv->esq), ra, a);

} /* ConsultaBase */

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. */
    ImplBase aux , arv = (ImplBase) *p;

    if(*p == NULL){
        return false;
    }
    /*Caso ache o valor desejado:
       Caso nao exista elemento maior que ele (lado direito), a arvore da esquerda
       somente subir um nivel, se n�o busca o menor elemento do lado direito e substitui
       o elmento desejado por ele*/
    if(arv->info.ra == ra){
        if(arv->dir == NULL){
            *p = (Base) arv->esq;
            FREE(arv->info.nome);
            FREE(arv);
        }else{
            aux = arv->dir;
            /*Busca o menor elemento do lado direito*/
            while(aux->esq != NULL){
                aux = aux->esq;
            }
            arv->info = aux->info;
            RemoveBase((Base) arv, aux->info.ra);
        }

        return true;
    }

    /*Faz a busca na arvore pelo elemento*/
    if(ra > arv->info.ra){
        /*Faz o casting de ImplBase para Base*/
        p = (Base) &(arv->dir);
        RemoveBase(p, ra);
    }else{
        /*Faz o casting de ImplBase para Base*/
        p = (Base) &(arv->esq);
        RemoveBase(p, ra);
    }
} /* RemoveBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */
    int i = 0 , j = 0;

    ImplBase arv = (ImplBase) *p;

    if(*p == NULL){
        return 0;
    }

    i = AlturaBase((Base*) &(arv->dir));
    j = AlturaBase((Base*) &(arv->esq));
    if(i < j){
        return j + 1;
    }
    return i + 1;
} /* AlturaBase */

int NumeroNosBase(Base *p) {
/*Devolve o numero de nos da base 'p'. */
    ImplBase arv = (ImplBase) *p;

    if(*p == NULL){
        return 0;
    }

    return (1 + NumeroNosBase((Base*) &(arv->esq)) + NumeroNosBase((Base*) &(arv->dir)));

} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
  /*Executa um percurso inordem na base, invocando a fun��o Visita
    para todos os elementos. */
    ImplBase arv = (ImplBase) *p;

    if(*p == NULL){
        return;
    }

    PercorreBase((Base) &(arv->esq), Visita);
    Visita(&(arv->info));
    PercorreBase((Base) &(arv->dir), Visita);

}  /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os n�s da base apontada por 'p', bem
   como todas as cadeias que guardam os nomes. */

   ImplBase arv = (ImplBase) *p;

   LiberaBase((Base*) &(arv->dir));
   LiberaBase((Base*) &(arv->esq));

   FREE(arv->info.nome);
   FREE(arv);

} /* LiberaBase */
