/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * Tarefa 08 - 2sem 2014           *
 * * * * * * * * * * * * * * * * * */

/*
 * Arquivo base.c: implementa??o das fun??es de manipula??o da base.
 */

#include <stdio.h>
#include "base.h"
#include "balloc.h"

#include "imprimearvore.h"

typedef struct AuxNoArv {
    Aluno info;                  /* registros de informa??o */
    struct AuxNoArv *esq,*dir;   /* sub?rvores */
    short int bal;               /* fator de balanceamento */
 }NoArv, * ImplBase;

/* ============================================================ */

/* Fun??o ImprimeBase para produzir a representa??o gr?fica */
/* Pode ajudar na depura??o */

char cadeiainfo[7] = "0000000"; /* conter? os digitos do RA */
char *vazia = "?rvore vazia\n";

ImplBase esq(ImplBase a, int d) {
    /* Sup?e a != NULL */
    return a->esq;
}

ImplBase dir(ImplBase a, int d) {
    /* Sup?e a != NULL */
    return a->dir;
}

char *info(ImplBase a, int d) {
    /* Sup?e a != NULL */
    sprintf(cadeiainfo,"%6d", (a->info).ra);
    /* cadeiainfo[0] = (a->info)->ra;*/
    return cadeiainfo;
}

void ImprimeBase(Base *p) {
/* Imprime a base sob a forma de uma ?rvore 'deitada'. */
    ImplBase q = (ImplBase)(*p);
    printf("\n");
    ImprimeArvore(q,(subarvfunc*)esq,(subarvfunc*)dir,(infofunc*)info,NULL,1,vazia);
    printf("\n");
}

/* ======================Funcoes de Rotacao==================== */
/*Funcoes que rotacionam os n?s conforme o nescessario. As funcoes
RR e LL s?o iguais apenas invertidas, assim como a LR com a RL
*/
void RotacaoLL(ImplBase *no){

    ImplBase filho = (*no)->esq, aux = *no;

    *no = filho;
    aux->esq = filho->dir;
    filho->dir = aux;

    /*Balanceamento*/
    aux->bal = 0;
}

void RotacaoLR(ImplBase *no){
    ImplBase filho = (*no)->esq, neto = filho->dir, aux = *no;

    *no = neto;
    filho->dir = neto->esq;
    aux->esq = neto->dir;
    neto->dir = aux;
    neto->esq = filho;

    /*Balanceamento dos nos*/
    if(neto->bal == 0){
        filho->bal = 0;
        aux->bal = 0;
    }
    else if(neto->bal == 1){
        filho->bal = -1;
        aux->bal = 0;
    }
    else if(neto->bal == -1){
        filho->bal = 0;
        aux->bal = 1;
    }

    neto->bal = 0;

}

void RotacaoRR(ImplBase *no){
    ImplBase filho = (*no)->dir, aux = *no;

    aux->dir = filho->esq;
    filho->esq = aux;
    *no = filho;

    /*Balanceamento*/
    aux->bal = 0;
}

void RotacaoRL(ImplBase *no){
    ImplBase filho = (*no)->dir, neto = filho->esq, aux = *no;

    *no = neto;
    aux->dir = neto->esq;
    filho->esq = neto->dir;
    neto->esq = aux;
    neto->dir = filho;

    /*Balanceamento dos nós*/

    if(neto->bal == 0){
        filho->bal = 0;
        aux->bal = 0;
    }
    else if(neto->bal == -1){
        filho->bal = 1;
        aux->bal = 0;
    }
    else if(neto->bal == 1){
        filho->bal = 0;
        aux->bal = -1;
    }

    neto->bal = 0;
}

/* ============================================================ */


Base CriaBase(){
/* Devolve apontador para uma base vazia */
    return NULL;
}

Base SubEsq(Base *p){
/* Devolve a sub?rvore esquerda da base 'p' se n?o for vazia; caso
contr?rio devolve NULL. */

    /*Faz o Castindg de base para ImplBase*/
    ImplBase aux = (ImplBase) *p;

    if (*p == NULL){
        return NULL;
    }

    return (Base) aux->esq;
}


Base SubDir(Base *p){
/* Devolve a sub?rvore direita da base 'p' se n?o for vazia; caso
   contr?rio devolve NULL. */
    /*Faz o Castindg de base para ImplBase*/
    ImplBase aux = (ImplBase) *p;

    if (*p == NULL){
        return NULL;
    }

    return (Base) aux->dir;

}


int FatorBal(Base *p){
/* Devolve o fator de balanceamento da raiz da base: altura da
   sub?rvore direita menos a altura da sub?rvore esquerda; devolve
   zero se a ?rvore ? vazia. */

    ImplBase arv = (Base) *p;

    return arv->bal;
}

Boolean InsercaoAVL(ImplBase *p, Aluno a, Boolean *alt){
/*C?digo auxiliar que insere na arvore o elemento a, sendo que o
c?digo foi baseado no slide que o professor disponibilizou em aula
Criei-na para poder usar um boolean que indica se a altura da arvo
re foi criada*/
    Boolean aux;

    if(*p == NULL){
        /*Faz a alocaco*/
         (*p) = MALLOC(sizeof(NoArv));
         (*p)->info = a;
         (*p)->bal = 0;
         (*p)->esq = NULL;
         (*p)->dir = NULL;


         *alt = true;
         return true;
    }

    /*Ja esta na arvore*/
    if(a.ra == (*p)->info.ra){
        return false;
    }

    /*Descer a esquerda*/
    if(a.ra < (*p)->info.ra){
        aux = InsercaoAVL( &((*p)->esq), a, alt);
        /*Caso nao tenha ocorrido a inser??o*/
        if(!aux){
            return false;
        }

        /*Nao houve mudanca na altura*/
        if(!(*alt)){
            return true;
        }

        /*Verifica qual o caso da inserção*/
        switch((*p)->bal){
            /*Termina o balanceamento*/
            case 1:
                (*p)->bal = 0;
                *alt = false;
                break;
            /*Continua a propagar o balanceamento*/
            case 0:
                (*p)->bal = -1;
                break;
            case -1:
                /*Caso o filho da esquerda esteja com o balanceamento do lado
                  da esquerda menor, correcao LL*/
                if( ((*p)->esq)->bal == -1){
                    RotacaoLL(p);
                }
                /*Caso nao esteja balanceada para a esquerda, sera 0 ou 1,
                  caso LR*/
                else{
                    RotacaoLR(p);
                }

                (*p)->bal = 0;

                *alt = false;
                break;
        }
        return true;
    }
    /*Descer a direita*/
    else{
        aux = InsercaoAVL( &((*p)->dir), a, alt);
        /*Caso nao tenha ocorrido a inser??o*/
        if(!aux){
            return false;
        }

        /*Nao houve mudanca na altura*/
        if(!(*alt)){
            return true;
        }
        /*Verifica qual o caso da inserção*/
        switch((*p)->bal){
            /*Terminar o balanceamento*/
            case -1:
                (*p)->bal = 0;
                *alt = false;
                break;
            /*Continua a balancear a arvore*/
            case 0:
                (*p)->bal = 1;
                break;
            /*Faz a rotação de uma parte da arvora*/
            case 1:
                /*Caso o filho da esquerda esteja com o balanceamento do lado
                  da esquerda menor, correcao LL*/
                if( ((*p)->dir)->bal == 1){
                    RotacaoRR(p);
                }
                /*Caso nao esteja balanceada para a esquerda, sera direita,
                  caso, LR*/
                else{
                    RotacaoRL(p);
                }

                (*p)->bal = 0;
                *alt = false;
                break;
        }
    }

    return true;
}

Boolean InsereBase(Base *p, Aluno a){
/* Insere o registro 'a' na base 'p' se n?o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contrrio devolve 'false' */

    Boolean aux = false; /*Auxiliar para verificar o caso de inver??o*/

    ImplBase* arv = (ImplBase*) p;/*Faz o casting*/

    return InsercaoAVL(arv, a, &aux);

}

Boolean RemoveBase(Base *p, int ra){
/* Devolve 'true' se um registro com 'ra' p?de ser removido da
   base 'p';  caso contr?rio devolve 'false'. */
   return false;
}

Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr?rio devolve 'false'. 'a' conter?
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
        return ConsultaBase( (Base*) &(arv->dir), ra, a);
    }

    return ConsultaBase( (Base*) &(arv->esq), ra, a);

}/* ConsultaBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */
    int i = 0 , j = 0;

    ImplBase arv = (ImplBase) *p;

    if(*p == NULL){
        return 0;
    }

    /*Descobre o qual o maior lado da arvore*/
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


void PercorreBase(Base *p, TipoVisita Visita){
/* Executa um percurso inordem na base, invocando a fun?o Visita
   para todos os elementos. */
   ImplBase arv = (ImplBase) *p;

   if(*p == NULL){
       return;
   }

   PercorreBase((Base) &(arv->esq), Visita);
   Visita(&(arv->info));
   PercorreBase((Base) &(arv->dir), Visita);

}
void LiberaBase(Base *p) {
/* Libera todos os nos da base apontada por 'p', bem
   como todas as cadeias que guardam os nomes. */

   ImplBase arv = (ImplBase) *p;

   if(*p != NULL){

       LiberaBase((Base*) &(arv->dir));
       LiberaBase((Base*) &(arv->esq));

       FREE(arv->info.nome);
       FREE(arv);
   }

} /* LiberaBase */
