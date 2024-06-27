#include <stdlib.h>
#include <stdio.h>
#include "TARVBM.h"

int main(void){
    int x[] = {1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 68, 39, 62, 7, 55, 43, 16, 67, 34, 35};
    TARVBM *a =TARVBM_cria(2);
    for(int i=0; i<20; i++){
        a = TARVBM_insere(a, x[i], 2);
    }

    TARVBM_imprime(a);
    printf("\n");
    return 0;
}