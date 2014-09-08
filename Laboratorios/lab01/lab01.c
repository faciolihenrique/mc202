/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli		    *
 * RA : 157986				        *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        * 
 * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

#define TAM 20

/*Funcao que faz a leitura dos dados de entrada e checa se sao validos*/
int leitura_entrada(int *tamanho, int matriz[TAM][TAM]);
/*Procura os pontos de sela*/
void ponto_de_sela(int tamanho, int matriz[TAM][TAM]);
/*Impressao do texto nescessario*/
void impressao(int opcao);



int main(){
    int tamanho, matriz[TAM][TAM];
    int opcao; 
    
    opcao = leitura_entrada(&tamanho, matriz);
    impressao(opcao);
    
    if(opcao != -1){
        ponto_de_sela(tamanho, matriz);
    }

    return 0;
}

/*Esta funcao faz a leitura dos numeros iniciais fornecidos,
  capturando o tamanho da matriz e os seus elementos, fazen-
  do a checagem se sao dados validos ou nao.
  Nao serao validos quando o tamanho da matriz for menor que
  1, maior que 20 ou, os dados da matriz forem imcompletos.
  Caso haja uma invalidez, a funcao retorna -1, caso contra-
  rio, 1.
 */
int leitura_entrada(int* tamanho, int matriz[TAM][TAM]){
    int i, j;
    char c;
    /*Faz a leitura do tamanho da matriz*/
    scanf("%d", tamanho);

    /*Checa se o tamanho informado é valido*/
    if(*tamanho < 1 || *tamanho > 20){
        return -1;
    }
    else{
        while((c=getchar()) != '\n');
        /*Leitura da matriz e busca do menor elemtento*/
        for(i = 0; i < *tamanho; i++){
            for(j = 0; j < *tamanho; j++){
                if(scanf("%d", &matriz[i][j]) == -1){
                    return -1;
                }
            }
            while((c=getchar()) != '\n');
        }
    }
    
    return 1;
}

/*Esta funcao procura um ponto de sela na matriz de entra-
  da, primeiramente, fazendo a busca do menor termo de uma
  linha i e armazena a coluna em que ele se encontra no ve
  tor linha, para no caso de que haja mais de 1 numero i-
  gual ele possa armazenar todos. Em seguida, ele varre as
  colunas armazenadas no vetor linha e ve se o elemento da
  da linha i, na coluna j, e' o menor da coluna j, se sim, 
  faz a impressao definida, se nao, percorre a proxima co-
  luna. Caso ele percorra todas as posicoes da matriz e nao
  encontre nenhum ponto de cela ele imprime nenhum.
*/
  
void ponto_de_sela(int tamanho, int matriz[TAM][TAM]){
    int i, j, k;
    int menor, maior, repeticao;
    int fail, ocorre = 0;
    int linha[TAM];
    
    for(i = 0; i < tamanho ; i++){
        repeticao = 0;
        menor = matriz[i][0];
        linha[repeticao] = 0;
        for(j = 1; j < tamanho ; j++){
            if(menor > matriz[i][j]){
                menor = matriz[i][j];
                repeticao = 0;
                linha[repeticao] = j;
            }else if(menor == matriz[i][j]){
                repeticao++;
                linha[repeticao] = j;
            }
        }
        
        /*Depois que achou os menores da linha, procura o maior da culuna*/
        for(j = 0; j <= repeticao ; j++){
            maior = matriz[i][(linha[j])];
            fail = 0;
            for(k = 0; k < tamanho && !fail; k++){
                if(maior < matriz[k][(linha[j])]){
                    fail = 1;
                }
            }
            if(!fail){
                ocorre = 1;
                printf("%4d%4d%4d\n", i, linha[j], matriz[i][linha[j]]);
            }
        }
    }
    if(!ocorre){
        printf("nenhum\n");
    }
}

/*Esta funcao*/

void impressao(int opcao){
    if(opcao == -1){
        printf("Dados inválidos\n");
    }else{
        printf("Os pontos de sela da matriz são:\n");
    }
}

