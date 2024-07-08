#include "../headers/includes.h"

int main(void) {
    TABSELE_inicializa();
    TARVBP *a = catalogo2Arv("root", 2);
    TABSELE_imprime();

    TJ* j = TARVBP_buscaJogador(a, 16, 2);
    imprimeJogador(j);
    TABSELE_alteraCapitao(j, 0);
    TABSELE_imprime();
    
    // a = menu(a, 2);

    free(j);
    
    TARVBP_libera(a, 2);

    return 0;
}