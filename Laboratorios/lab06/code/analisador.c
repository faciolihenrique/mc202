/*
  Autor:         COMPLETAR!
  RA:            COMPLETAR!
  Disciplina:    MC202
  Turma:         COMPLETAR!
  
  Tarefa 06 
  Segundo semestre de 2014

*/

/* 
 * analisador.c: M�dulo de transforma��o de express�es em �rvores
 * bin�rias e seus percursos.
 */

#include "analisador.h"
#include <stdlib.h>
#include <ctype.h>
#include "balloc.h"

/* Vari�veis globais a este m�dulo */

char *in;  /* Cadeia e �ndice para express�o infixa (entrada). */
int indIn;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */

Erro geral;

/* Macro para desprezar espa�os em branco na cadeia de entrada. */
/* Para evitar chamadas desnecess�rias a esta macro, adotou-se  */
/* seguinte conve��o. A macro � invocada uma vez imediatamente  */
/* antes da primeira chamada � fun��o Expressao e imediatamente */
/* ap�s todo o incremento de indIn.                             */
#define DESPREZA_ESPACOS() while (in[indIn] == ' ') indIn++


/* Prot�tipos das fun��es mutuamente recursivas. */
/* O resultado � devolvido atrav�s da vari�vel 'arv'. */
Erro Expressao(ArvBin *arv);
Erro Termo(ArvBin *arv);
Erro Fator(ArvBin *arv);
Erro Primario(ArvBin *arv);

/* Fun��o auxiliar -- declarada mais adiante */
Erro montaErro(int codigo, int pos);

/*Funcoes auxiliares criadas por mim*/
void VerificaCaractere();
void avancaCaractere();
void imprimeSaida(char saida, ArvBin *arv);

/*************************************************************/
/*                 Fun��o   principal                        */
/*************************************************************/

Erro InArv(char *infixa, ArvBin *arv) {
/* Transforma a nota��o infixa em �rvore bin�ria.  Em caso de erro,
   devolve o c�digo e a posi��o na cadeia de entrada onde o erro foi
   encontrado.  */

    
    return resCorreto;  /***** PROVIS�RIO ******/

}

/*************************************************************/
/*           Fun��es de implementa��o do analisador          */
/*************************************************************/

Erro montaErro(int codigo, int posicao){
    /* Devolve estrutura com c�digo de erro e posi��o */
    Erro res;

    /*Caso ja tenha algum erro anterior, ele prevalece*/
    if (geral.posicao == -1){
        res.posicao = posicao;
        res.codigoErro = codigo;
        return res;
    }

    return geral;

}/* montaErro */


Erro Expressao(ArvBin *arv) {
/* Processa uma express�o da cadeia de entrada.  */
    char operador = in[indIn];
    char unario = 0;

    VerificaCaractere();

    /*Operador Unario*/
    if(operador == '-'){
        unario = '~';
        avancaCaractere();
    }else if(operador == '+'){
        unario = '&';
        avancaCaractere();
    }

    Termo(arv);

    if(unario){
        imprimeSaida(unario,arv);
    }

    operador = in[indIn];
    while((operador == '+') || (operador == '-')){
        avancaCaractere();
        Termo(arv);
        imprimeSaida(operador,arv);
        operador = in[indIn];
    }

    return resCorreto;
  
} /* Expressao */


Erro Termo(ArvBin *arv) {
    /* Processa um termo da cadeia de entrada.  */
    char operador;

    Fator(arv);

    operador = in[indIn];
    while((operador == '*') || (operador == '/')){
        avancaCaractere();
        Fator(arv);
        imprimeSaida(operador,arv);
        operador = in[indIn];
    }

    return resCorreto;
} /* Termo */


Erro Fator(ArvBin *arv) {
    /* Processa um fator da cadeia de entrada.  */

    Primario(arv);

    if((in[indIn]) == '^'){
        avancaCaractere();
        Fator(arv);
        imprimeSaida('^',arv);
    }

    return resCorreto;

} /* Fator */


Erro Primario(ArvBin *arv) {
    /* Processa um fator prim�rio da cadeia de entrada.  */
    char corrente = in[indIn];

    switch(corrente){
            /* Caso seja um parenteses, tera uma expressao dentro dele */
        case '(':
            avancaCaractere();

            Expressao(arv);

            /* Verifica o fechamento do parenteses */
            if(in[indIn] == ')'){
                avancaCaractere();
            }else{
                geral = montaErro(FECHA_PARENTESE_ESPERADO, indIn);
            }
            break;
            /* Caso seja um operador nao esperado */
        case ')':
        case '/':
        case '*':
        case '+':
        case '-':
        case '\0':
            geral = montaErro(OPERANDO_ESPERADO, indIn);
            break;
            /* Caso seja uma variavel(a, b, c, ... ,z) */
        default:
            imprimeSaida(in[indIn],arv);
            avancaCaractere();
            break;
    }
    
    return resCorreto;
} /* Primario */

/* Percursos */

void ArvPre(ArvBin arv, char *pre) {
 /* Produz a representa��o pr�-fixa a partir da �rvore. */
 
  /***** COMPLETAR!  *****/

  *pre = '\0';   /***** PROVIS�RIO ******/

}

void ArvPos(ArvBin arv, char *pos) {
/* Produz a representa��o p�s-fixa a partir da �rvore. */
  /***** COMPLETAR!  *****/

  *pos = '\0';   /***** PROVIS�RIO ******/  

}


void LiberaArv(ArvBin arv) {
/* Libera o espa�o ocupado pela �rvore. */

  /***** COMPLETAR!  *****/


}

/****************************************************************************/
/*Fun��es de implementadas por mim para auxiliar no entendimento do programa*/
/****************************************************************************/

/*Verifica se o caractere de entrada � valido, se nao for modifica 'geral'*/
void VerificaCaractere(){
    char car = in[indIn];

    if ((car >= 'a' && car <= 'z') || car == '+' || car == '-' || car == '*' || car == '/' ||
        car == '^' || car == '(' || car == ')' || car == '\0') {
        return;
    }else{
        geral = montaErro(CARACTERE_INVALIDO, indIn);
    }
}/*Verifica Caractere*/

/* Funcao para avancar um caractere e pular os espacoes em branco */
void avancaCaractere(){
    /* Avanca um caractere */
    indIn++;

    /* Caso o caractere seja espaco */
    while(in[indIn] == ' '){
        indIn++;
    }

    VerificaCaractere();
}/*Avanca Caractere*/

/* Funcao para adicionar o caractere nescessario na arvore */
/* A funcao pega o n� cabeca e checa ambos os lados, primeiro o
   direito e depois o esquerdo, verificando se estao vazios. Se sim
   o valor lido � atribuido a aux, e o lado vazio aponta para aux.
   Se ja estiver ambos os lados ocupados, a arvore aumenta um nivel
*/
void imprimeSaida(char saida, ArvBin *arv){
    ArvBin *aux1;
    aux1 = MALLOC(sizeof(NoArvBin));
    
    /*Caso o operador de entrada seja um un�rio, o n� nao tem 
      o lado esquerdo*/
    if(saida == '&' || saida == '~'){
        (*arv)->info = saida;
        (*arv)->esq = (*arv);
        aux1->dir = (*arv);
        arv = &aux1;
    } 
    
    /*Se nao for um unario, entao faz a entrada*/   
    if((*arv)->dir == NULL){
        aux1->info = saida;
        (*arv)->dir = aux1;
    }else if((*arv)->esq == NULL){
        aux1->info = saida;
        (*arv)->esq = aux1;
    }else{
        (*arv)->info = saida;
        aux1->dir = (*arv);
        arv = &aux1;
    }
}/*Imprime Saida na Arvore*/
