#ifndef OP_H
#define OP_H

#include "../headers/includes.h"

TARVBP *BuscaJogadorMaisNovo_1(TARVBP *arv, int t);
int TIJcmp(const void *p1, const void *p2);
TARVBP *BuscaJogadorMaisVelho_2(TARVBP *arv, int t);
TARVBP **BuscaJogadoresPorAno_7(TARVBP *arv, int t, char *ano, int *tam);
TARVBP **BuscaJogadoresPorMes_8(TARVBP *arv, int t, char *mes, int *tam);

#endif