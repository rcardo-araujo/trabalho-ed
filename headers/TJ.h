#ifndef TJ_H
#define TJ_H

#include <stdio.h>

typedef struct jogador{
    int id;
    int num;
    char pos[3];
    char nome[30];
    char data_nasc[11];
    int num_part;
    int num_gols;
    char pais_time[21];
    char time[24];
    char pais[12];
} TJ;

TJ* leJogador(FILE* fp, char* selecao);
void imprimeJogador(TJ* j);
int verificaSelecao(FILE* fp);

#endif
