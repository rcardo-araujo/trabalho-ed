/**
 * @file TJ.h
 * @brief Cabeçalho do tipo jogador @c TJ
 */

#ifndef TJ_H
#define TJ_H

typedef struct jogador{
    int id;             /**< o identificador único do jogador */
    int num;            /**< o número da camisa que ele usa em sua respectiva seleção */
    char pos[3];        /**< a posição que ele joga (GK - Goleiro, DF – Defensor, MF – Meio-campo e FW – Atacante) */
    char nome[30]; 
    int capitao;     /**< o nome do jogador */
    char data_nasc[11]; /**< a sua data de nascimento */
    int num_part;       /**< o número de partidas pela seleção */
    int num_gols;       /**< o número de gols pela respectiva seleção */
    char pais_time[21]; /**< o país do seu time atual */
    char time[24];      /**< o nome do time atual em que o jogador atua */
    char pais[12];      /**< nome do país */
} TJ;

TJ* leJogador(FILE* fp, char* selecao);
int capitao(char* nome);
void imprimeJogador(TJ* j);
int verificaSelecao(FILE* fp);

#endif
