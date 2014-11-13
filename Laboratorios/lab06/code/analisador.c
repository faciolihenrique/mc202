/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli        *
 * RA : 157986                     *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * Tarefa 06 - 2sem 2014           *
 * * * * * * * * * * * * * * * * * */

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

int indPre = 0;
int indPos = 0;

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
void imprimeSaida(char saida, ArvBin *arv , ArvBin esq, ArvBin dir);


/*************************************************************/
/*                 Fun��o   principal                        */
/*************************************************************/

Erro InArv(char *infixa, ArvBin *arv) {
/* Transforma a nota��o infixa em �rvore bin�ria.  Em caso de erro,
   devolve o c�digo e a posi��o na cadeia de entrada onde o erro foi
   encontrado.  */
    in = infixa;

    /*Zera todos os contadores e apontadores que ja podem ter sido usados em outra leitura*/
    indIn = 0;
    indPos = 0;
    indPre = 0;
    *arv = NULL;
    geral.posicao = -1;

    /* Caso a programa comece com um espaco, pula ate o caractere valido mais proximo */
    DESPREZA_ESPACOS();
    /* Caso pule todos os espacos e termine, a entrada eh branca */
    if (in[indIn] == '\0'){
        return montaErro(CADEIA_DE_BRANCOS, 0);
    }

    Expressao(arv);

    /* Se terminou de ler o programa e ainda possui algum caractere na entrada */
    if(in[indIn] != '\0'){
        geral = montaErro(OPERADOR_ESPERADO, indIn);
    }

    /* Caso o programa tenha apresentado algum erro */
    if (geral.posicao != -1) {
        return geral;
    }
    return resCorreto;

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

    /*Caso seja um unario, a arvore at� entao criada � alocada a direita*/
    if(unario){
        imprimeSaida(unario, arv, NULL, *arv);
    }

    /*Caso seja um operador, a arvore criada at� entao � alocada a esquerda,
      o operador � colocado na arvore, e � passado o endere�o da arv->dir para
      que o termo seja alocado neste posicao*/
    operador = in[indIn];
    while((operador == '+') || (operador == '-')){
        avancaCaractere();
        imprimeSaida(operador, arv, *arv, NULL);
        Termo(&((*arv)->dir));
        operador = in[indIn];
    }

    return resCorreto;

} /* Expressao */


Erro Termo(ArvBin *arv) {
    /* Processa um termo da cadeia de entrada.  */
    char operador;

    Fator(arv);

    /*Aloca a o operador na arvore, faz com que a arvore criada
      at� entao seja alocada a sua esquerda e passa o endereco
      da sua direita para receber um Fator*/
    operador = in[indIn];
    while((operador == '*') || (operador == '/')){
        avancaCaractere();
        imprimeSaida(operador, arv, *arv, NULL);
        Fator(&((*arv)->dir));
        operador = in[indIn];
    }

    return resCorreto;
} /* Termo */


Erro Fator(ArvBin *arv) {
    /* Processa um fator da cadeia de entrada.  */

    Primario(arv);\

    /*Aloca a o operador na arvore, faz com que a arvore criada
     at� entao seja alocada a sua esquerda e passa o endereco
     da sua direita para receber um outro fator*/
    if((in[indIn]) == '^'){
        avancaCaractere();
        imprimeSaida('^', arv, *arv, NULL);
        Fator(&((*arv)->dir));
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
            /*Como e'� um polinomio, ele vira uma folha, o lado direito e esquerdo NULL*/
            imprimeSaida(corrente, arv, NULL, NULL);
            avancaCaractere();
            break;
    }

    return resCorreto;
} /* Primario */

/************ Percursos ***********/
void ArvPre(ArvBin arv, char *pre) {
 /* Produz a representa��o pr�-fixa a partir da �rvore. */
    if(arv != NULL){
        /*Imprime o caractere na posicao indPre na string pre*/
        pre[indPre] = arv->info;
        indPre++;
        pre[indPre] = '\0';

        ArvPre(arv->esq, pre);
        ArvPre(arv->dir, pre);
    }
}

void ArvPos(ArvBin arv, char *pos) {
/* Produz a representa��o p�s-fixa a partir da �rvore. */
    if(arv != NULL){
        ArvPos(arv->esq, pos);
        ArvPos(arv->dir, pos);

        /*Imprime o caracte na posicao indPos na string pos*/
        pos[indPos] = arv->info;
        indPos++;
    }
    pos[indPos] = '\0';
}


void LiberaArv(ArvBin arv) {
/* Libera o espa�o ocupado pela �rvore. */
    /*S� desaloca se o apontador nao for nulo*/
    if(arv != NULL) {
        LiberaArv(arv->esq);
        LiberaArv(arv->dir);

        FREE(arv);
    }

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
/* Aloca um n� na arvore, com a informacao saida, e apontadores
   para o parametro passado (esq e dir).
 */
void imprimeSaida(char saida, ArvBin *arv , ArvBin esq, ArvBin dir){
    ArvBin aux1 = MALLOC(sizeof(NoArvBin));

    aux1->info = saida;
    aux1->dir = dir;
    aux1->esq = esq;

    /*Faz o apontador arv apontar para o novo n�*/
    *arv = aux1;
}/*Imprime Saida na Arvore*/
