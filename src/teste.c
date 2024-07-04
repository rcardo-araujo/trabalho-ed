#include "../headers/includes.h"

TARVBP* catalogo2Arv(char *nomeArq, int t){
    TARVBP *a = TARVBP_cria(nomeArq, t);
    FILE *fp = fopen("catalogo.txt", "r");
    char selecao[40];
    int size;
    TJ *j;
    int i = 4;
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

int main(void) {
    TARVBP* a = catalogo2Arv("root", 2);
    imprimeNo(b);
    imprimeNo(a);
    // a = TARVBP_retira(a, 1, 2);

    printf("\n## Apos remocao:\n");
    imprimeNo(a);

    return 0;
}
