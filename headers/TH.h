#ifndef TH_H
#define TH_H
 
#include <stdio.h>
#include <stdlib.h>

typedef struct idadeJogador{
	int id;
	char data[11];
	int prox;
	int status;
}TIJ;

int TH_hash(char *data);
void TH_inicializa(char *arq, char *dados);
TIJ **TH_busca_mes_ano(char *tabHash, char *dados,  char *data, int *tam);
int TH_retira(char *tabHash, char *arq, char *data);
void TH_insere(char *tabHash, char *arq, char *data, int id);
void TH_imprime (char *nome_hash, char *nome_dados);

#endif