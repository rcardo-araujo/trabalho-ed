#include "../headers/includes.h"

int main(void) {
    TABSELE_inicializa();
    TARVBP *a = catalogo2Arv("root", 2);
    TABSELE_imprime();
    
    a = menu(a, 2);

    TARVBP_libera(a, 2);

    return 0;
}