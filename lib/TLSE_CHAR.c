#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/TLSE_CHAR.h"

TLSECHAR* TLSECHAR_inicializa(void) {
    return NULL;
}

TLSECHAR* TLSECHAR_insere_aux(char* nome_pais) {
    TLSECHAR* novo = (TLSECHAR*)malloc(sizeof(TLSECHAR));
    strcpy(novo->nome_pais, nome_pais);
    novo->prox = NULL;
    return novo;
}

TLSECHAR* TLSECHAR_insere(TLSECHAR* l, char* nome_pais) {
    if(!l) return TLSECHAR_insere_aux(nome_pais);
    l->prox = TLSECHAR_insere(l->prox, nome_pais);
    return l;
}

TLSECHAR* TLSECHAR_libera(TLSECHAR* l) {
    if(l) {
        l->prox = TLSECHAR_libera(l->prox);
        free(l);
    }
    return NULL;
}

void TLSECHAR_imprime(TLSECHAR* l) {
    if(!l) return;
    printf("%s\n", l->nome_pais);
    TLSECHAR_imprime(l->prox);
}
