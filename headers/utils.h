/**
 * @file utils.h
 * @brief Cabeçalho das funções de Utils
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "TARVBP.h"

void readLine(FILE *fp, char *string, int *size, char splitter);
void criaData(char *destino, char *dia, char *mes, char *ano);
char *converteMes(char *str);
void converteDia(char *str);
int datacmp(char *data1, char *data2);
TARVBP* catalogo2Arv(char *nomeArq, int t);
TARVBP* menu(TARVBP* a, int t);


#endif
