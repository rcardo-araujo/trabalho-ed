#include "../headers/includes.h"

int main(void){
    TARVBP *a = catalogo2Arv("root", 2);
    a = TARVBP_retira(a, 1, 2);
    a = TARVBP_retira(a, 38, 2);
    a = TARVBP_retira(a, 216, 2);
    a = TARVBP_retira(a, 131, 2);
    a = TARVBP_retira(a, 152, 2);
    a = TARVBP_retira(a, 63, 2);
    a = TARVBP_retira(a, 14, 2);
    a = TARVBP_retira(a, 194, 2);
    a = TARVBP_retira(a, 267, 2);
    a = TARVBP_retira(a, 110, 2);
    a = TARVBP_retira(a, 149, 2);
    a = TARVBP_retira(a, 237, 2);
    a = TARVBP_retira(a, 10, 2);
    a = TARVBP_retira(a, 16, 2);
    a = TARVBP_retira(a, 151, 2);
    a = TARVBP_retira(a, 192, 2);
    a = TARVBP_retira(a, 3, 2);
    a = TARVBP_retira(a, 20, 2);
    a = TARVBP_retira(a, 119, 2);
    a = TARVBP_retira(a, 196, 2);
    a = TARVBP_retira(a, 168, 2);
    a = TARVBP_retira(a, 266, 2);
    a = TARVBP_retira(a, 242, 2);
    a = TARVBP_retira(a, 27, 2);
    a = TARVBP_retira(a, 187, 2);
    a = TARVBP_retira(a, 200, 2);
    imprimeNo(a);
    // char *p = (char *)malloc(sizeof(char)*40);
    TARVBP *b = TARVBP_busca(a, 16, 2);
    if(b) {
        imprimeNo(b);
        TARVBP_libera(b, 2);
    }
    TARVBP_imprime(a, 2);
    TARVBP_libera(a, 2);
    return 0;
}