#ifndef OP_H
#define OP_H

#include "../headers/includes.h"

TARVBP *BuscaJogadorMaisNovo_1(TARVBP *arv, int t);
int TIJcmp(const void *p1, const void *p2);
TARVBP *BuscaJogadorMaisVelho_2(TARVBP *arv, int t);
TARVBP **BuscaJogadoresPorAno_7(TARVBP *arv, int t, char *ano, int *tam);
TARVBP **BuscaJogadoresPorMes_8(TARVBP *arv, int t, char *mes, int *tam);
TJ *maisNovosPorEquipe(TARVBP *arv, int t, char *pais);
TJ *maisVelhosPorEquipe(TARVBP *arv, int t, char *pais);
TJ *maisVelhosPorEquipe(TARVBP *arv, int t, char *pais);

TLSETJ* maisAtuaramEquipe(TARVBP* a, int t, char* pais); // [02]
TLSETJ* menosAtuaramEquipe(TARVBP* a, int t, char* pais); // [02]
TLSETJ* maisAtuaramCadaEquipe(TARVBP* a, int t); // [02]
TLSETJ* menosAtuaramCadaEquipe(TARVBP* a, int t); // [02]
TLSETJ* menosAtuaramTotal(TARVBP* a, int t); // [03]
TLSETJ* maisAtuaramTotal(TARVBP* a, int t); // [03]
TLSECHAR* maioresEquipes(int* qtd); // [04]
TLSECHAR* menoresEquipes(int* qtd); // [04]
TLSETJ* buscaAllForaOrigemEquipe(TARVBP* a, int t, char* nome_pais); // [05]
TLSETJ* buscaAllForaOrigem(TARVBP* a, int t); // [05]
TLSETJ* buscaAllNaOrigemEquipe(TARVBP* a, int t, char* nome_pais); //[06]
TLSETJ* buscaAllNaOrigem(TARVBP* a, int t); // [06]
TLSECHAR* maioresEquipesForaOrigem(TARVBP* a, int t, int* qtd); // [09]
TLSECHAR* maioresEquipesNaOrigem(TARVBP* a, int t, int* qtd); // [10]
TLSETJ* buscaAllJogadoresEquipe(TARVBP* a, int t, char* nome_pais); // [13]
TJ* buscaCapitaoEquipe(TARVBP* a, int t, char* nome_pais); // [14]
TLSETJ* buscaAllCapitaes(TARVBP* a, int t); // [14]
TARVBP* retiraCapitaoEquipe(TARVBP* a, int t, char* nome_pais); // [14]
TARVBP* retiraAllCapitaes(TARVBP* a, int t); // [14]
TARVBP* retiraAllEquipeAtuaPais(TARVBP* a, int t, char* nome_equipe, char* nome_pais); // [16]
TARVBP* retiraAllNaOrigem(TARVBP* a, int t, char* nome_pais); // [17]
TARVBP* retiraAllForaOrigem(TARVBP* a, int t, char* nome_pais); // [18]
TARVBP* retiraAllEquipe(TARVBP* a, int t, char* nome_pais); // [19]
TARVBP *retiraIds(TARVBP *arv, int t, int *vet, int n); // [20]

#endif
