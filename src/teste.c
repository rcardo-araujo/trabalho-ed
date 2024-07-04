#include "../headers/includes.h"

TARVBP* catalogo2Arv(char *nomeArq, int t){
    TARVBP *a = TARVBP_cria(nomeArq, t);
    FILE *fp = fopen("catalogo.txt", "r");
    char selecao[40];
    int size;
    TJ *j;
    int i = 5;
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
    imprimeNo(a);
    TARVBP* p;
    for(int i = 0; i <= a->num_chaves; i++) {
        p = leNo(a->filhos[i], 2);
        imprimeNo(p);
        TARVBP_libera(p, 2);
    }
    a = TARVBP_retira(a, 1, 2);
    imprimeNo(a);
    for(int i = 0; i <= a->num_chaves; i++) {
        p = leNo(a->filhos[i], 2);
        imprimeNo(p);
        TARVBP_libera(p, 2);
    }
    TARVBP_libera(a, 2);

    return 0;
}
