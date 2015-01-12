/* * * * * * * * * * * * * * * * * * * * * *
* Henrique Noronha Facioli                *
* RA : 157986                             *
* henrique.facioli@gmail.com              *
* henrique.facioli@students.ic.unicamp.br *
* github : henriquefacioli                *
* Tarefa 11 - 2sem 2014                   *
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

/*Algoritimo para liberar uma lista ligada*/
void libera_lista(Lista a){
    Lista aux1 = a->prox, aux2;
    /*Caminha com duas variaveis uma seguida da outra, liberando a segunda
      e avançando, até que se chegue ao ó cabeça*/
    /*Como o nome é alocado dinamicamente, precisa libera-lo*/
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
    /*Funcao que cria uma base, inicializando o vetor de lista circular com nós
    cabeças com o valor -1 nelas*/
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
    /*Funcao que insere o aluno a na base p*/

    /*Casting*/
    ImplBase z = (ImplBase) p;
    /*Posicao do vetor de lista que deve ser colocado o aluno*/
    int posicao = Espalha(a->ra);
    Lista no, previous, novo_no;
    /*Faz com que previous comece no nó cabeça e nó no seguinte a ele*/
    no = z->tabela[posicao]->prox;
    previous = z->tabela[posicao];

    /*Procura o lugar do aluno dentro da lista, avançando com duas variaveis,
      uma seguida da outra*/
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

    /*Aumenta o numero de registros dentro da base*/
    z->numregs++;
    return true;
}


Boolean RemoveBase(Base p, int ra{
    /*Funcao que remove o aluno com o ra da lista*/

    /*Casting*/
    ImplBase z = (ImplBase) p;
    /*Posicao do vetor de lista que deve ser colocado o aluno*/
    int posicao = Espalha(ra);
    Lista no , previous;
    /*Assim como no insere*/
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

    /*Se nao encontrou, o aluno nao existe, e retorna false*/
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
    /*Funcao que imprime todos os registros da base*/
    /*Casting*/
    ImplBase z = (ImplBase) p;
    Lista no;

    /*Percorre o vetor de lista, imprimindo a lista*/
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
