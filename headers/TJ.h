#ifndef TJ_H
#define TJ_H

typedef struct jogador{
    int id;
    int num;
    char pos[3];
    char nome[30];
    int capitao;
    char data_nasc[11];
    int num_part;
    int num_gols;
    char pais_time[21];
    char time[24];
    char pais[12];
} TJ;

TJ* leJogador(FILE* fp, char* selecao);
int capitao(char* nome);
void imprimeJogador(TJ* j);
int verificaSelecao(FILE* fp);

#endif
