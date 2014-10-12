/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli		    *
 * RA : 157986				        *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        * 
 * * * * * * * * * * * * * * * * * */

/* Módulo de cálculo de expressões pós-fixas sobre uma base de dados     */
/* formada por polinômios em uma variável.                               */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "pilha.h"
#include "polinomios.h"
#include "balloc.h"
#include "boolean.h"

/* Mensagens de erro para este módulo.                                     */

#define MSG_ERRO_NOME_INVALIDO "nome inválido para a base de polinômios."
#define MSG_ERRO_POLINOMIO_NAO_INICIALIZADO "tentativa de recuperar polinômio não inicializado."
#define MSG_ERRO_FALTA_OPERANDO "número insuficiente de operandos."
#define MSG_ERRO_FALTA_OPERADOR  "número insuficiente de operandores."
#define MSG_ERRO_CARACTERE_INVALIDO "caractere inválido."

#define IMPRIME_ERRO(msg)  {printf("Erro: %s\n",msg); exit(0); }

#define TAM_BASE 5

Polinomio vetorPoli[TAM_BASE];

void InicializaBasePolinomios() {
/* Inicializa polinômios com NULL, indicando que não há polinômios       */
/* válidos na base.                                                      */ 
  int i;
  for (i = 0; i < TAM_BASE; i++)
    vetorPoli[i] = NULL;
}

Polinomio RecuperaPolinomio(char x) {
/* Retorna o polinômio de nome x.                                        */
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
/* Armazena o polinômio p sob o nome x na base.                          */
  x = toupper(x);
  if (x >= 'A' && x < 'A' + TAM_BASE) 
    vetorPoli[x - 'A'] = p;
  else 
    IMPRIME_ERRO(MSG_ERRO_NOME_INVALIDO);
}

/*** Cálculo da expressão                                                 */

/* Definição dos elementos da pilha. Polinômios temporários devem ser     */
/* liberados após terem sido utilizados. Polinômios da base só são        */
/* liberados quando o usuário invoca libera.                              */ 
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
/* Cria e empilha um nó do tipo ElemPilha.                                 */
  ElemPilha *elem = MALLOC (sizeof(ElemPilha));
  elem->poli = poli; 
  elem->temp = temp; 
  Empilha (pilha, elem);
}

Boolean Operando(char c) {
/* Verifica se um caractere corresponde a um operando válido.              */
   return (c >= 'a' && c < 'a'+TAM_BASE) || (c >= 'A' && c < 'A'+TAM_BASE); 
}

Polinomio CalcExpr(char* expr) { 
/* Retorna o polinômio referente à expressão dada.                       */
/* O polinômio devolvido é sempre uma nova cópia, mesmo que a            */
/* expressão seja uma variável simples.                                  */
    Pilha operacao;
    ElemPilha *aux1, *aux2;
    Polinomio temp;
    
    CriaPilha(&operacao);
    printf("Comeca a CalcExpr\n");
    /*Faz a leitura da expressão dada, termo por termo, até chegar no final da linha*/
    while(*expr != '\0'){
        /*Caso a entrada seja um operador*/
        if(!Operando(*expr)){ 
            printf("Operando\n");
            /*Caso o operador seja binário*/
            if(*expr == '+' || *expr == '-' || *expr == '*'){
                /*Como é um operador, deve-se utilizar os dois elementos do topo da pilha*/
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
            /*Caso o operador seja unário*/
            else if(*expr == '~'){
                /*Como é um operador unario, só é nescessario usar o elemento do topo
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
            /*Se não entrou em nenhum dos outros casos, a entada é invalida*/
            else{
                IMPRIME_ERRO(MSG_ERRO_CARACTERE_INVALIDO);
            }
            
        }        
        /*Se a entrada  não for um operador, é um polinomio*/
        else{
            printf("Operador\n");
            /*Empilha o elemento apontado na pilha operacao*/
            EmpilhaOperando(&operacao, vetorPoli[*expr - 'A'], false);
        }
        
        /*Avança a leitura*/
        expr++;    
    }
    /*Depois de terminar de ler as operacoes retira o ultimo elemento e verifica se
      a pilha está vazia, se sim, é por que completou as operacoes corretamente, entao
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
