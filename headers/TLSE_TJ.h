#ifndef TLSE_TJ_H
#define TLSE_TJ_H

#include "TJ.h"

typedef struct lse_tj {
    TJ* jogador;
    struct lse_tj* prox;
} TLSETJ;

TLSETJ* TLSETJ_inicializa(void);
TLSETJ* TLSETJ_insere(TLSETJ* l, TJ* elem);
TLSETJ* TLSETJ_libera(TLSETJ* l);
void TLSETJ_imprime(TLSETJ* l);

#endif
