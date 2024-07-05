#ifndef TABSELE_H
#define TABSELE_H

#include "TJ.h"

static const char* tab_selecoes = "tabelas/tab_selecoes.bin";

typedef struct selecao {
    char nome[12];
    int tem_capitao;
    int id_capitao;
    int num_jogadores;
    int jogadores[30];
} TSELE;

int indSelecao(FILE* ftab, char* nome_pais);
int existeSelecao(FILE* ftab, char* nome);
int existeJogador(FILE* ftab, TJ* jogador);
void TABSELE_inicializa(void);
TSELE* TABSELE_criaReg(char* nome_pais);
void TABSELE_adicionaJogador(TJ* jogador);
void TABSELE_removeJogador(TJ* jogador);
void TABSELE_imprimeTabela(void);

#endif
