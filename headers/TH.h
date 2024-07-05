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
TIJ* TH_busca(char *tabHash, char *dados, int n, char *data);
int TH_retira(char *tabHash, char *arq, char *data);
void TH_insere(char *tabHash, char *arq, char *data, int id);
void TH_imprime (char *nome_hash, char *nome_dados);

#endif