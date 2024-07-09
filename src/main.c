#include "../headers/includes.h"

int main(int argc, char** argv) {
    if(argc != 3) {
        printf("\nQuantidade de arugumentos inválida!\n");
        exit(1);
    }
    // Inicialização
    int t;
    if(sscanf(argv[1], "%d", &t) != 1) {
        printf("\nTipo de argumento para 't' inválido!\n");
        exit(1);
    }
    TARVBP* a = catalogo2Arv(argv[2], t);
    
    // Chamada do menu
    a = menu(a, t);

    TARVBP_libera(a, 2);

    return 0;
}
