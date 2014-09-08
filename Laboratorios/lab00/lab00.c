/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli		    *
 * RA : 157986				        *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        *
 * Laboratório Nº 00               *
 * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 50

void contagem_arquivo(char nameFileIn[]);

int main(int argc, char *argv[]){
    char nameFileIn[TAM_NOME];
    
    /*Copia o nome do arquivo de entrada para a variavel*/
    strcpy(nameFileIn, argv[0]);
    
    return 0;
}

void contagem_arquivo(char nameFileIn[]){
    char aux;
    int line = 1,character = 0;
    
    /*Abertura do arquivo texto em modo read*/
    FILE *txtFileIn;
    txtFileIn = fopen(nameFileIn,"r");
    
    /*Enquanto não chegar no final do arquivo, ele incrmenta o numero
     *de linha se encontrar alguma \n e o numero de caracteres se não
     */
    while(fscanf(txtFileIn,"%c", &aux) != EOF){
        if(aux == '\n'){
            line++;
        }else{
            character++;
        }
    }
    
    printf("Caracteres: %d\nLinhas: %d",character,line);
    
    fclose(txtFileIn);
}
