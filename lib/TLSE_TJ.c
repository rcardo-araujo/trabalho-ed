#include <stdio.h>
#include <stdlib.h>
#include "../headers/TJ.h"
#include "../headers/TLSE_TJ.h"

TLSETJ* TLSETJ_inicializa(void) {
    return NULL;
}

TLSETJ* TLSETJ_insere_aux(TJ* elem) {
    TLSETJ* novo = (TLSETJ*)malloc(sizeof(TLSETJ));
    novo->jogador = elem;
    novo->prox = NULL;
    return novo;
}

TLSETJ* TLSETJ_insere(TLSETJ* l, TJ* elem) {
    if(!l) return TLSETJ_insere_aux(elem);
    l->prox = TLSETJ_insere(l->prox, elem);
    return l;
}

TLSETJ* TLSETJ_libera(TLSETJ* l) {
    if(l) {
        l->prox = TLSETJ_libera(l->prox);
        free(l);
    }
    return NULL;
}

void TLSETJ_imprime(TLSETJ* l) {
    if(!l) return;
    imprimeJogador(l->jogador);
    TLSETJ_imprime(l->prox);
}
