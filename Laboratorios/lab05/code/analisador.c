/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli		   *
 * RA : 157986				       *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * Tarefa 05                       *
 * * * * * * * * * * * * * * * * * */

/* 
 * analisador.c: M�dulo de transforma��o de express�es na nota��o
 * infixa para p�s-fixa.
 */

#include "analisador.h"
#include <ctype.h>

/* Vari�veis globais a este m�dulo */

char *in;  /* Cadeia e �ndice para express�o infixa (entrada). */
int indIn;

char *pos; /* Cadeia e �ndice para express�o p�sfixa (sa�da). */
int indPos;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */

Erro geral; /*Para armazenar erro do programa*/


/* Prot�tipos das fun��es mutuamente recursivas */
Erro Expressao();
Erro Termo();
Erro Fator();
Erro Primario();

/* Fun��o auxiliar */
Erro montaErro(int codigo, int pos);

/*Funcoes auxiliares criadas por mim*/
void VerificaCaractere();
void avancaCaractere();
void imprimeSaida(char saida);

/*************************************************************/
/*                 Fun��o   principal                        */
/*************************************************************/

Erro InPos(char *infixa, char *posfixa) {
/* Transforma uma express�o da nota��o infixa para a p�s-fixa. Em caso
   de erro, devolve o c�digo e a posi��o na cadeia de entrada onde o
   erro foi encontrado.
 */
    in = &infixa[0];
    pos = &posfixa[0];
    indPos = indIn = 0;

    /* Zera a variavel global de erro */
    geral.posicao = -1;

    /* Caso a programa comece com um espaco, pula ate o caractere valido mais proximo */
    while(in[indIn] == ' '){
        indIn++;
    }
    /* Caso pule todos os espacos e termine, a entrada eh branca */
    if (in[indIn] == '\0'){
        return montaErro(CADEIA_DE_BRANCOS, 0);
    }

    Expressao();

    /* Termina de montar a string da posfixa */
    pos[indPos] = '\0';

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

/* Pela definicao:
   e = t1 (+) t2 (+) t3 ... (+) tn
   sendo t algum Termo
 */
Erro Expressao() {
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

    Termo();

    if(unario){
        imprimeSaida(unario);
    }

    operador = in[indIn];
    while((operador == '+') || (operador == '-')){
        avancaCaractere();
        Termo();
        imprimeSaida(operador);
        operador = in[indIn];
    }
  
  return resCorreto;

} /* Expressao */


/* Pela definicao:
   T = f1 (x) f2 (x) f3 ... (x) fn
   Sendo f um fator
 */
Erro Termo() {
/* Processa um termo da cadeia de entrada.  */
    char operador;

    Fator();

    operador = in[indIn];
    while((operador == '*') || (operador == '/')){
        avancaCaractere();
        Fator();
        imprimeSaida(operador);
        operador = in[indIn];
    }
    
    return resCorreto;
} /* Termo */


/* Pela definicao :
   f = p ^ f
   sendo p um primario e f um fator
 */
Erro Fator() {
/* Processa um fator da cadeia de entrada.  */
    
    Primario();
    
    if((in[indIn]) == '^'){
        avancaCaractere();
        Fator();
        imprimeSaida('^');
    }
    
    return resCorreto;  

} /* Fator */

/*A funcao primaria possui duas possibilidades :
  p = x ou p = (e), ou seja, uma expressao entre
  parenteses ou uma vari�vel
*/
Erro Primario() {
/* Processa um fator prim�rio da cadeia de entrada.  */
    char corrente = in[indIn];
    
    switch(corrente){
        /* Caso seja um parenteses, tera uma expressao dentro dele */
        case '(':
            avancaCaractere();

            Expressao();

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
            imprimeSaida(in[indIn]);
            avancaCaractere();
            break;
    }
  
  return resCorreto;
} /* Primario */

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

/* Funcao para adicionar o caractere nescessario no vetor apontado por pos */
void imprimeSaida(char saida){
    pos[indPos] = saida;
    indPos++;
}/*Imprime Saida*/
