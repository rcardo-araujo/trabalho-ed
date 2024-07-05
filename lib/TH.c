#include "../headers/includes.h"
#include <string.h>

#define TAM 360

int TH_hash(char *data){
	char mes[3], ano[5];
    for(int i=0; i < 2; i++){
        mes[i] = data[i+3];
    }
    mes[2] = '\0';

    for(int i=0; i < 4; i++){
        ano[i] = data[i+6];
    }
    ano[4] = '\0';

	return (atoi(mes)-1) + ((atoi(ano)-1983) * 12);
}

void TH_inicializa(char *arq, char *dados){
	FILE *fp = fopen(dados, "wb");
	if(!fp) exit(1);
	fclose(fp);
	fp = fopen(arq, "wb");
	if(!fp) exit(1);
	int i, elem = -1;
	for(i = 0; i < TAM; i++)fwrite(&elem, sizeof(int), 1, fp);
	fclose(fp);
}

TIJ* TH_aloca(int id, char *data){
	TIJ *novo = (TIJ *) malloc(sizeof(TIJ));
	novo->id = id;
	strcpy(novo->data, data);
	novo->prox = -1;
	novo->status = 1;
	return novo;
}

TIJ* TH_busca(char *tabHash, char *dados, int n, char *data){
	FILE *fp = fopen(tabHash, "rb");
	if(!fp)exit(1);
	int pos, h = TH_hash(data);
	fseek(fp, h*sizeof(int), SEEK_SET);
	fread(&pos, sizeof(int), 1, fp);
	fclose(fp);
	if(pos == -1)return NULL;
	fp = fopen(dados,"rb");
	if(!fp) exit(1);
	fseek(fp, pos, SEEK_SET);
	TIJ aux;
	fread(&aux, sizeof(TIJ), 1, fp);

	TIJ *j = TH_aloca(aux.id, aux.data);
	j->prox = aux.prox;
	fclose(fp);

	return j;
}

int TH_retira(char *tabHash, char *arq, char *data){
	FILE *fp = fopen(tabHash, "rb");
	if(!fp) exit(1);
	int pos, h = TH_hash(data);
	fseek(fp, h*sizeof(int), SEEK_SET);
	fread(&pos, sizeof(int), 1, fp);
	fclose(fp);
	if(pos == -1)return -1;
	int id = -1;
	fp = fopen(arq,"rb+");
	if(!fp)exit(1);
	TIJ aux;
	while(1){
		fseek(fp, pos, SEEK_SET);
		fread(&aux, sizeof(TIJ), 1, fp);
		if((!strcmp(aux.data, data)) && (aux.status)){
			id = aux.id;
			aux.status = 0;
			fseek(fp, pos, SEEK_SET);
			fwrite(&aux, sizeof(TIJ), 1, fp);
			fclose(fp);
			return id;
		}
		if(aux.prox == -1){
			fclose(fp);
			return id;
		}
		pos = aux.prox;
	}
}

void TH_insere(char *tabHash, char *arq, char *data, int id){
  	FILE *fph = fopen(tabHash, "rb+");
  	if(!fph) exit(1);
  	int pos, h = TH_hash(data);
  	fseek(fph, h*sizeof(int), SEEK_SET);
  	fread(&pos, sizeof(int), 1, fph);
  	int ant, prim_pos_livre;
  	ant = prim_pos_livre = -1;
  	FILE *fp = fopen(arq,"rb+");
  	if(!fp){
  	  	fclose(fph);
  	  	exit(1);
  	}
  	TIJ aux;
  	while(pos != -1){
  	  	fseek(fp, pos, SEEK_SET);
  	  	fread(&aux, sizeof(TIJ), 1, fp);
  	  	if(aux.id == id){
  	  	  	strcpy(aux.data, data);
  	  	  	aux.status = 1;
  	  	  	fseek(fp, pos, SEEK_SET);
  	  	  	fwrite(&aux, sizeof(TIJ), 1, fp);
  	  	  	fclose(fp);
  	  	  	fclose(fph);
  	  	  	return;
  	  	}
  	  	if((!aux.status) && (prim_pos_livre == -1))prim_pos_livre=pos;
  	  	ant = pos;
  	  	pos = aux.prox;
  	}
  	if(prim_pos_livre == -1){
  	  	aux.id = id;
  	  	strcpy(aux.data, data);
  	  	aux.prox = -1;
  	  	aux.status = 1;
  	  	fseek(fp, 0L, SEEK_END);
  	  	pos = ftell(fp);
  	  	fwrite(&aux, sizeof(TIJ), 1, fp);
  	  	if(ant != -1){
  	  	  	fseek(fp, ant, SEEK_SET);
  	  	  	fread(&aux, sizeof(TIJ), 1, fp);
  	  	  	aux.prox = pos;
  	  	  	fseek(fp, ant, SEEK_SET);
  	  	  	fwrite(&aux, sizeof(TIJ), 1, fp);
  	  	}
  	  	else{
  	    	fseek(fph, h*sizeof(int), SEEK_SET);
  	    	fwrite(&pos, sizeof(int), 1, fph);
  	  	}
  	  fclose(fp);
  	  fclose(fph);
  	  return;
  	}
  	fseek(fp, prim_pos_livre, SEEK_SET);
  	fread(&aux, sizeof(TIJ), 1, fp);
  	aux.id = id;
  	strcpy(aux.data, data);
  	aux.status = 1;
  	fseek(fp, prim_pos_livre, SEEK_SET);
  	fwrite(&aux, sizeof(TIJ), 1, fp);
  	fclose(fp);
  	fclose(fph);
  	return;
}

void TH_imprime (char *nome_hash, char *nome_dados){
	FILE *fp = fopen(nome_hash, "rb");
	if(!fp) exit(1);
	int vet[TAM];
	fread(&vet, sizeof(int), TAM, fp);
	fclose(fp);

	fp = fopen(nome_dados, "rb");
	if(!fp) exit(1);
	int i, pos;
	for(i = 0; i < TAM; i++){
		int p = vet[i];
		if(p != -1) printf("%d:\n", i);
		TIJ x;
		while(p != -1){
			fseek(fp, p, SEEK_SET);
			pos = ftell (fp);
			fread(&x, sizeof(TIJ), 1, fp);
			printf("$%d: id: %d\tdata: %s\tstatus: %d\tprox_end: $%d\n", pos, x.id, x.data, x.status, x.prox);
			p = x.prox;
		}
	}
	fclose(fp);
}
