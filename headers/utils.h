#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

void readLine(FILE *fp, char *string, int *size, char splitter);
void criaData(char *destino, char *dia, char *mes, char *ano);
char *converteMes(char *str);

#endif
