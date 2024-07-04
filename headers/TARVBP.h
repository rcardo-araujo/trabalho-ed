/**
 * @file TARVBP.h
 * @brief Arquivo cabeçalho da árvore B+
 */

#ifndef TARVBP_H
#define TARVBP_H

#include "TJ.h"

/**
 * @struct arvbp
 * @brief Representa um nó da árvore B+
 * @details Esta árvore é processada em arquivos binários
 */
typedef struct arvbp {
    char *nomeArq;  /**< Nome do arquivo que representa este nó */
    int folha;      /**< Variável booleana para dizer se o nó é uma folha (1) ou não (0) */
    int num_chaves; /**< Quantidade de chaves deste nó */
    int *chaves;    /**< Vetor de chaves */
    TJ **reg;       /**< Vetor de ponteiros para TJ */
    char **filhos;  /**< Vetor de strings (char *) representando os filhos deste nó (cada elemento é um nome de arquivo) */
    char *prox;     /**< String (char *) com o nome do arquivo para o próximo nó da lista encadeada */
}TARVBP;

void escreveNo(char* nome_arq, TARVBP* no);

TARVBP *leNo(char* nome_arq, int t);

void imprimeNo(TARVBP* a);

TARVBP* TARVBP_cria(char* nome_arq, int t);

TARVBP* TARVBP_busca(TARVBP* a, int elem, int t);

TARVBP* TARVBP_insere(TARVBP* a, TJ* elem, int t);

void TARVBP_libera(TARVBP* a, int t);

TARVBP *TARVBP_retira(TARVBP* a, int id, int t);

#endif
