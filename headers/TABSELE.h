#ifndef TABSELE_H
#define TABSELE_H

#include "TJ.h"

typedef struct selecao {
    char nome_pais[12];
    int tem_capitao;
    int ind_capitao;
    int num_jogadores;
    int jogadores[27];
} TSELE;

int existeEquipe(char* nome_pais);
int existeJogador(FILE* ftab, TJ* jogador);
int TABSELE_indiceEquipe(char* nome_pais);
TSELE* TABSELE_criaReg(const char* nome_pais);
void TABSELE_inicializa(void);
void TABSELE_adicionaJogador(TJ* jogador);
void TABSELE_removeJogador(TJ* jogador);
void TABSELE_alteraCapitao(TJ* jogador, int novoCapitao);
void TABSELE_imprime(void);

extern const char* TAB_SELECOES;
extern const int TAM_TABSELE;

#endif
