#include "../headers/includes.h"

TARVBP* catalogo2Arv(char *nomeArq, int t){
    TARVBP *a = TARVBP_cria(nomeArq, t);
    FILE *fp = fopen("catalogo.txt", "r");
    char selecao[40];
    int size;
    TJ *j;
    int i = 6;
    while(i > 0){
        if(verificaSelecao(fp)){
            readLine(fp, selecao, &size, '\n');
        } else {
            j = leJogador(fp, selecao);
            a = TARVBP_insere(a, j, t);
            i--;
        }
    }
    return a;
}

int main(void){
    TARVBP *a = catalogo2Arv("root", 2);
    a = TARVBP_retira(a, 131, 2);
    a = TARVBP_retira(a, 152, 2);
    a = TARVBP_retira(a, 63, 2);
    a = TARVBP_retira(a, 216, 2);
    a = TARVBP_retira(a, 38, 2);
    imprimeNo(a);
    // char *p = (char *)malloc(sizeof(char)*40);
    TARVBP *b = TARVBP_busca(a, 1, 2);
    if(b) {
        imprimeNo(b);
        TARVBP_libera(b, 2);
    }
    TARVBP_libera(a, 2);
    return 0;
}