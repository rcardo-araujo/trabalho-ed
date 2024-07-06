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

int TABSELE_tam();
int indSelecao(FILE* ftab, char* nome_pais);
int existeSelecao(FILE* ftab, char* nome_pais);
int existeJogador(FILE* ftab, TJ* jogador);
void TABSELE_inicializa(void);
TSELE* TABSELE_criaReg(char* nome_pais);
void TABSELE_adicionaJogador(TJ* jogador);
void TABSELE_removeJogador(TJ* jogador);
void TABSELE_imprimeTabela(void);

static const char* TAB_SELECOES = "tabelas/tab_selecoes.bin";
static const int TAM = (sizeof(TSELE)) * 11;

#endif
