/* * * * * * * * * * * * * * * * * * * * * *
* Henrique Noronha Facioli                *
* RA : 157986                             *
* henrique.facioli@gmail.com              *
* henrique.facioli@students.ic.unicamp.br *
* github : henriquefacioli                *
* Tarefa 10 - 2sem 2014                   *
* * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include "base.h"

/* DECLARAÇÕES DE TIPOS */
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

/* FUNÇÃO DE ESPALHAMENTO */
/* ---------------------- */

int Espalha(int k) {
  return (k%MaxHash);
} /* Espalha */

/* FUNÇÕES AUXILIARES */
/* ------------------ */

/*Algoritimo recursivo para liberar todos os nós da lista*/
void libera_lista(Lista a){
    Lista aux1 = a->prox, aux2;
    while(aux1->aluno.ra != -1){
        aux2 = aux1->prox;
        FREE(aux1->aluno.nome);
        FREE(aux1);
        aux1 = aux2;
    }

    FREE(a);
}


/* FUNÇÕES DA INTERFACE */
/* -------------------- */
Base CriaBase(){
    ImplBase aux = MALLOC(sizeof(RegBase));
    aux->numregs = 0;

    /*Inicializa o vetor de lista circular com o no cabeça*/
    for(int i = 0; i < MaxHash; i++){
        aux->tabela[i] = MALLOC(sizeof(RegLista));
        aux->tabela[i]->aluno.ra = -1;
        aux->tabela[i]->prox = aux->tabela[i];
    }

    return (Base) aux;
}

Boolean InsereBase(Base p, Aluno *a){
    /*Casting*/
    ImplBase z = (ImplBase) p;
    /*Posicao do vetor de lista que deve ser colocado o aluno*/
    int posicao = Espalha(a->ra);
    Lista no, previous, novo_no;

    no = z->tabela[posicao]->prox;
    previous = z->tabela[posicao];

    /*Procura o lugar do aluno dentro da lista*/
    while( (a->ra > no->aluno.ra) && (no->aluno.ra != -1)){
        previous = no;
        no = no->prox;
    }

    /*Caso ja exista o aluno*/
    if(a->ra == no->aluno.ra){
        return false;
    }

    /*Caso seja uma insercao no meio da lista*/
    novo_no = MALLOC(sizeof(RegLista));
    novo_no->aluno = *a;
    novo_no->prox = previous->prox;
    previous->prox = novo_no;


    z->numregs++;
    return true;
}


Boolean RemoveBase(Base p, int ra){
    /*Casting*/
    ImplBase z = (ImplBase) p;
    /*Posicao do vetor de lista que deve ser colocado o aluno*/
    int posicao = Espalha(ra);
    Lista no , previous;

    no = z->tabela[posicao]->prox;
    previous = z->tabela[posicao];

    /*Procura o nó com o usuario desejado*/
    while((no->aluno.ra != -1) && (ra > no->aluno.ra)){
        previous = no;
        no = no->prox;
    }

    /*Se encontrou o aluno, o anterior dele aponta para o posterior dele e ele é
    liberado*/
    if(no->aluno.ra != -1 && ra == no->aluno.ra){
        previous->prox = no->prox;
        FREE(no->aluno.nome);
        FREE(no);

        z->numregs--;
        return true;
    }

    return false;
}

Boolean ConsultaBase(Base p, int ra, Aluno *a){
    /*Casting*/
    ImplBase z = (ImplBase) p;
    Lista auxiliar;


    /*Posicao do vetor de lista que deve ser colocado o aluno*/
    int posicao = Espalha(ra);
    auxiliar = z->tabela[posicao]->prox;

    while(auxiliar->aluno.ra != -1){
        if(ra == auxiliar->aluno.ra){
            *a = auxiliar->aluno;
            return true;
        }
        auxiliar = auxiliar->prox;
    }

    return false;
}

int NumeroRegsBase(Base p){
    /*Casting*/
    ImplBase z = (ImplBase) p;

    return z->numregs;
}

void ImprimeBase(Base p){
    /*Casting*/
    ImplBase z = (ImplBase) p;
    Lista no;

    for(int i = 0; i < MaxHash; i++){
        no = (z->tabela[i])->prox;
        while(no->aluno.ra != -1){
            printf("(%3d) %06d %s\n",i, no->aluno.ra, no->aluno.nome);
            no = no->prox;
        }
    }

}

void LiberaBase(Base p){
    /*Casting*/
    ImplBase z = (ImplBase) p;

    for(int i = 0; i < MaxHash; i++){
        libera_lista(z->tabela[i]);
    }

    FREE(p);
}
