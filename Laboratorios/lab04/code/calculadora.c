/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli		    *
 * RA : 157986				        *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        * 
 * * * * * * * * * * * * * * * * * */

/* M�dulo de c�lculo de express�es p�s-fixas sobre uma base de dados     */
/* formada por polin�mios em uma vari�vel.                               */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "pilha.h"
#include "polinomios.h"
#include "balloc.h"
#include "boolean.h"

/* Mensagens de erro para este m�dulo.                                     */

#define MSG_ERRO_NOME_INVALIDO "nome inv�lido para a base de polin�mios."
#define MSG_ERRO_POLINOMIO_NAO_INICIALIZADO "tentativa de recuperar polin�mio n�o inicializado."
#define MSG_ERRO_FALTA_OPERANDO "n�mero insuficiente de operandos."
#define MSG_ERRO_FALTA_OPERADOR  "n�mero insuficiente de operandores."
#define MSG_ERRO_CARACTERE_INVALIDO "caractere inv�lido."

#define IMPRIME_ERRO(msg)  {printf("Erro: %s\n",msg); exit(0); }

#define TAM_BASE 5

Polinomio vetorPoli[TAM_BASE];

void InicializaBasePolinomios() {
/* Inicializa polin�mios com NULL, indicando que n�o h� polin�mios       */
/* v�lidos na base.                                                      */ 
  int i;
  for (i = 0; i < TAM_BASE; i++)
    vetorPoli[i] = NULL;
}

Polinomio RecuperaPolinomio(char x) {
/* Retorna o polin�mio de nome x.                                        */
  Polinomio poli;
  x = toupper(x);
  if (x >= 'A' && x < 'A' + TAM_BASE) 
    poli =  vetorPoli[x - 'A'];
  else {
    IMPRIME_ERRO(MSG_ERRO_NOME_INVALIDO);
    return NULL;
  }
  
  if (poli == NULL)
    IMPRIME_ERRO(MSG_ERRO_POLINOMIO_NAO_INICIALIZADO);

  return poli;
}

void ArmazenaPolinomio(char x, Polinomio p) {
/* Armazena o polin�mio p sob o nome x na base.                          */
  x = toupper(x);
  if (x >= 'A' && x < 'A' + TAM_BASE) 
    vetorPoli[x - 'A'] = p;
  else 
    IMPRIME_ERRO(MSG_ERRO_NOME_INVALIDO);
}

/*** C�lculo da express�o                                                 */

/* Defini��o dos elementos da pilha. Polin�mios tempor�rios devem ser     */
/* liberados ap�s terem sido utilizados. Polin�mios da base s� s�o        */
/* liberados quando o usu�rio invoca libera.                              */ 
typedef struct ElemPilha {
  Polinomio poli;
  Boolean temp; 
} ElemPilha;


ElemPilha* VerificaDesempilha(Pilha* pilha) {
/* Desempilha um elemento, enviando uma mensagem de erro caso a pilha      */
/* esteja vazia.                                                           */
  if (PilhaVazia(pilha)) {
    IMPRIME_ERRO(MSG_ERRO_FALTA_OPERANDO);
    return NULL;
  }
  return (ElemPilha*) Desempilha(pilha);
}

void EmpilhaOperando(Pilha* pilha, Polinomio poli, Boolean temp) {
/* Cria e empilha um n� do tipo ElemPilha.                                 */
  ElemPilha *elem = MALLOC (sizeof(ElemPilha));
  elem->poli = poli; 
  elem->temp = temp; 
  Empilha (pilha, elem);
}

Boolean Operando(char c) {
/* Verifica se um caractere corresponde a um operando v�lido.              */
   return (c >= 'a' && c < 'a'+TAM_BASE) || (c >= 'A' && c < 'A'+TAM_BASE); 
}

Polinomio CalcExpr(char* expr) { 
/* Retorna o polin�mio referente � express�o dada.                       */
/* O polin�mio devolvido � sempre uma nova c�pia, mesmo que a            */
/* express�o seja uma vari�vel simples.                                  */
    Pilha operacao;
    ElemPilha *aux1, *aux2;
    Polinomio temp;
    
    CriaPilha(&operacao);
    printf("Comeca a CalcExpr\n");
    /*Faz a leitura da express�o dada, termo por termo, at� chegar no final da linha*/
    while(*expr != '\0'){
        /*Caso a entrada seja um operador*/
        if(!Operando(*expr)){ 
            printf("Operando\n");
            /*Caso o operador seja bin�rio*/
            if(*expr == '+' || *expr == '-' || *expr == '*'){
                /*Como � um operador, deve-se utilizar os dois elementos do topo da pilha*/
                aux1 = VerificaDesempilha(&operacao);
                aux2 = VerificaDesempilha(&operacao);
                
                
                /*Caso tente desempilhar mas a pilha ja esta vazia, entao falta operandos*/
                if(aux1 == NULL || aux2 == NULL){
                    IMPRIME_ERRO(MSG_ERRO_FALTA_OPERANDO);
                }
                
                /*Faz a operacao entre os dois elementos desempilhados*/
                if(*expr == '+'){
                    printf("Soma\n");
                    temp = SomaPolinomios(aux2->poli, aux1->poli);
                }
                else if(*expr == '-'){
                    printf("Sub\n");
                    temp = SubPolinomios(aux2->poli, aux1->poli);
                }
                else if(*expr == '*'){
                    printf("Multi\n");
                    temp = MultPolinomios(aux2->poli, aux1->poli);
                }
                
                /*Empilha o elemento resultante das operacoes*/
                EmpilhaOperando(&operacao, temp, true);
                
                
                /*Libera os elementos da pilha utilizados*/
                if(aux1->temp == true){
                    LiberaPolinomio(aux1->poli);
                }
                if(aux2->temp == true){
                    LiberaPolinomio(aux2->poli);
                }
                
                FREE(aux1);
                FREE(aux2);
            }
            /*Caso o operador seja un�rio*/
            else if(*expr == '~'){
                /*Como � um operador unario, s� � nescessario usar o elemento do topo
                  da pilha*/
                aux1 = VerificaDesempilha(&operacao);
                
                temp = MultTermo(aux1->poli, 0, -1.0);
                EmpilhaOperando(&operacao, temp, true);
                
                /*Desaloca a memoria nescessaria*/
                if(aux1->temp == true){
                    LiberaPolinomio(aux1->poli);
                }
                
                FREE(aux1);
            }
            /*Se n�o entrou em nenhum dos outros casos, a entada � invalida*/
            else{
                IMPRIME_ERRO(MSG_ERRO_CARACTERE_INVALIDO);
            }
            
        }        
        /*Se a entrada  n�o for um operador, � um polinomio*/
        else{
            printf("Operador\n");
            /*Empilha o elemento apontado na pilha operacao*/
            EmpilhaOperando(&operacao, vetorPoli[*expr - 'A'], false);
        }
        
        /*Avan�a a leitura*/
        expr++;    
    }
    /*Depois de terminar de ler as operacoes retira o ultimo elemento e verifica se
      a pilha est� vazia, se sim, � por que completou as operacoes corretamente, entao
      retorna esse polinomio
    */
    aux1 = VerificaDesempilha(&operacao);
    
    if(PilhaVazia(&operacao)){
        temp = aux1->poli;
        /*Cria um novo polinomio para poder ser retornado caso o elemento retornado seja 
          uma das 5 bases*/
        if(aux1->temp == false){
            temp = MultTermo(aux1->poli, 0, 1.0);
        }
        
        /*Desaloca o ultima elemento da pilha*/
        FREE(aux1);

        return temp;
    }else{
        /*Se a pilha ainda conter algum elemento*/
        IMPRIME_ERRO(MSG_ERRO_FALTA_OPERADOR);
    }
}
