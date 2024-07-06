#include "../headers/includes.h"
#include <locale.h>

int main(void){
    setlocale(LC_ALL, "pt_BR.UTF-8");

    TABSELE_inicializa();
    TARVBP *a = catalogo2Arv("root", 2);
    
    a = menu(a, 2);
    
    TARVBP_libera(a, 2);

    return 0;
}