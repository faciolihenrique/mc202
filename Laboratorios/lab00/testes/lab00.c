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
    strcpy(nameFileIn, argv[1]);
    
    return 0;
}

void contagem_arquivo(char nameFileIn[]){
    char aux;
    int line = 0,character = 0;
    
    /*Abertura do arquivo texto em modo read*/
    FILE *txtFileIn;
    txtFileIn = fopen(nameFileIn,"r");
    while(fscanf(txtFileIn , "%c" , &aux) != EOF){
        if(aux == '\n'){
            line++;
        }else{
            character++;
        }
    }
    
    printf("%d caracteres\n%d linhas", line, character);
    
}
