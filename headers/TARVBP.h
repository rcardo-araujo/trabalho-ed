#ifndef TARVBP_H
#define TARVBP_H

#include "TJ.h"

typedef struct arvbp {
    char *nome_arq;
    int folha;
    int num_chaves;
    int *chaves;
    TJ **reg;
    char **filhos;
    char *prox;
} TARVBP;

void escreveNo(char* nome_arq, TARVBP* no);
TARVBP *leNo(char* nome_arq, int t);
void imprimeNo(TARVBP* a);

TARVBP* TARVBP_cria(char* nome_arq, int t);
TARVBP* TARVBP_busca(TARVBP* a, int id, int t);
TARVBP* TARVBP_insere(TARVBP* a, TJ* elem, int t);
TARVBP* TARVBP_retira(TARVBP* a, int id, int t);
void TARVBP_libera(TARVBP* a, int t);

#endif
