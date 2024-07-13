#include "../headers/includes.h"

TARVBP* catalogo2Arv(char *nomeArq, int t){
    TARVBP *a = TARVBP_cria(nomeArq, t);
    FILE *fp = fopen("catalogo.txt", "r");
    char selecao[40];
    int size;
    TJ *j;
    int i = 284;
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
    TARVBP *b = TARVBP_busca(a, 1, 2);
    imprimeNo(a);
    char *p = (char *)malloc(sizeof(char)*40);
    imprimeNo(b);
    p = strcpy(p, b->prox);
    while(strcmp(p, "\0")){
        TARVBP *c = leNo(p, 2);
        imprimeNo(c);
        p = strcpy(p, c->prox);
        TARVBP_libera(c, 2);
    }
    TARVBP_libera(b, 2);
    TARVBP_libera(a, 2);
    free(p);

    int testeee = 2;
    int aaihf = 6;
    float trfgff = 12345.03482;

    return 0;
}