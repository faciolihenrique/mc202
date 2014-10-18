/* * * * * * * * * * * * * * * * * *
 * Henrique Noronha Facioli		    *
 * RA : 157986				        *
 * henrique.facioli@gmail.com      *
 * henrique.facioli@ic.unicamp.br  *
 * github : henriquefacioli        * 
 * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>

int main(){
    int x = 0, i , j , k , n = 10;
    for (i=1; i<=n; i++){
        for (j=1; j<=i; j++){
            for(k=1; k<=j; k++){
                x++;
            }
        }
    }
    
    printf("Oi", x);
    
    return 0;
}
