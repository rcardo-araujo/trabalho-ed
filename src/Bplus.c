#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

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

TJ *leJogador(FILE *fp, char *selecao){
    TJ *j = (TJ *) malloc(sizeof(TJ));
    printf("a selecao: %s\n", selecao);
    strcpy(j->pais, selecao);
    printf("%s\n", j->pais);
    char c;
    char placeholder[40];
    char dia[3], mes[10], *ano = (char *)malloc(sizeof(char)*5);
    char datanasc[12];
    fscanf(fp, "%d", &j->id);
    fscanf(fp, "%c", &c);
    fscanf(fp, "%d", &j->num);
    fscanf(fp, "%c", &c);
    fscanf(fp, "%3[^/]", j->pos);
    fscanf(fp, "%c", &c);
    fscanf(fp, "%30[^/]", j->nome);
    fscanf(fp, "%c", &c);
    fscanf(fp, "%s", dia);
    fscanf(fp, "%s", mes);
    fscanf(fp, "%s", ano);
    char *mes_digitos = (char *)malloc(sizeof(char)*4);
    mes_digitos = strcpy(mes_digitos, converteMes(mes));
    criaData(datanasc, dia, mes_digitos, ano);
    free(mes_digitos);
    free(ano);
    strcpy(j->data_nasc, datanasc);
    fscanf(fp, "%11[^/]", placeholder);
    fscanf(fp, "%c", &c);
    fscanf(fp, "%d", &j->num_part);
    fscanf(fp, "%c", &c);
    fscanf(fp, "%d", &j->num_gols);
    fscanf(fp, "%c", &c);
    fscanf(fp, "%21[^/]", j->pais_time);
    fscanf(fp, "%c", &c);
    fscanf(fp, "%24[^\n]", j->time);
    fscanf(fp, "%c", &c);
    return j;
}

int verificaSelecao(FILE *fp){
    char c;
    fread(&c, sizeof(char), 1, fp);
    fseek(fp, -1*sizeof(char), SEEK_CUR);
    if(c >= 48 && c <= 57){
        return 0;
    }
    return 1;
}

typedef struct arvbp {
    int folha;
    int num_chaves;
    int *chaves;
    TJ **reg;
    char** filhos;
    char *prox;
} TARVBP;


void escreveNo(char *nomeF, TARVBP *no, int t){
    FILE *fp = fopen(nomeF, "wb");
    if(!fp) exit(1);
    fwrite(&no->folha, sizeof(int), 1, fp);
    fwrite(&no->num_chaves, sizeof(int), 1, fp);
    for(int i = 0; i < no->num_chaves; i++){
        if(no->folha) {
            fwrite(no->reg[i], sizeof(TJ), 1, fp);
        }
        else {
            fwrite(&no->chaves[i], sizeof(int), 1, fp);
        }       
    }
    if(!no->folha){
        for(int i; i < no->num_chaves+1; i++){
            fwrite(no->filhos[i], sizeof(char), strlen(no->filhos[i]), fp);
            fwrite("\n", sizeof(char), 1, fp);
        }
    }
    if(no->prox) fwrite(no->prox, sizeof(char), strlen(no->prox), fp);
    fclose(fp);
}

TARVBP *leNo(char *nomeF, int t){
    FILE *fp = fopen(nomeF, "rb");
    if(!fp) return NULL;
    TARVBP *no = (TARVBP *) malloc(sizeof(TARVBP));
    no->filhos = (char **) malloc(sizeof(char *)*2*t);
    fread(&no->folha, sizeof(int), 1, fp);
    if(no->folha) {
        no->reg = (TJ **) malloc(sizeof(TJ *)*2*t-1);
        no->chaves = NULL;
    }
    else {
        no->chaves = (int *) malloc(sizeof(int)*2*t-1);
        no->reg = NULL;
    }
    fread(&no->num_chaves, sizeof(int), 1, fp);

    if(!no->folha) fread(no->chaves, sizeof(int), no->num_chaves, fp);
    else {
        for(int i = 0; i < no->num_chaves; i++){
            no->reg[i] = (TJ *) malloc(sizeof(TJ));
            fread(no->reg[i], sizeof(TJ), 1, fp);
        }
    }
    int size;
    char c[40];
    for(int j = 0; j < no->num_chaves+1; j++){
        readLine(fp, c, &size, '\n');
        no->filhos[j] = (char *) malloc(sizeof(char)*size);
        strcpy(no->filhos[j], c);
    }
    readLine(fp, c, &size, '\n');
    if(size < 0){
        no->prox = NULL;
    } else{
        no->prox = (char *) malloc(sizeof(char)*size);
        strcpy(no->prox, c);
    }
    fclose(fp);
    return no;
}

TARVBP *TARVBP_busca(TARVBP *a, int elem, int t){
    if(!a) return NULL;
    if(!a->folha){
        int i = 0;
        while(a->chaves[i] < elem && i < a->num_chaves){
            i++;
        }
        TARVBP *filho = leNo(a->filhos[i], t);
        return TARVBP_busca(filho, elem, t);
    }
    int i = 0;
    while(a->reg[i]->id < elem && i < a->num_chaves){
        i++;
    }
    if(i < a->num_chaves && a->reg[i]->id == elem) return a;
    return NULL;
}

void imprimeJogador(TJ *j){
    printf("id: %d\nnum: %d \npos: %s\nnome: %s\nnasc: %s\nnum_part: %d\nnum_gols: %d\npais_time: %s\ntime: %s\npais: %s\n",
    j->id, j->num, j->pos, j->nome, j->data_nasc, j->num_part, j->num_gols, j->pais_time, j->time, j->pais);
}

void imprimeNo(TARVBP *a){
    if(a->folha){
        /*for(int i=0; i<a->num_chaves; i++){
            imprimeJogador(a->reg[i]);
        }*/
    } else {
        for(int i=0; i < a->num_chaves; i++){
            printf("chave %d: %d\n", i, a->chaves[i]);
        }
    }
    for(int i=0; i < a->num_chaves+1; i++){
        printf("filho %d: %s\n", i, a->filhos[i]);
    }
}

int main(void){
    /* TARVBP *a = (TARVBP *) malloc(sizeof(TARVBP));
    a->folha = 0;
    a->num_chaves = 2;
    a->chaves = (int *) malloc(sizeof(int)*3);
    a->chaves[0] = a->chaves[1] = a->chaves[2] = 1;
    a->filhos = (char **) malloc(sizeof(char *)*4);
    a->filhos[0] = "f0.bin";
    a->filhos[1] = "f1.bin";
    a->filhos[2] = "f2.bin";
    a->prox = NULL;
    imprimeNo(a);
    escreveNo("r1.bin", a, 2);
    TARVBP *b = leNo("r1.bin", 2);
    imprimeNo(b); 

    free(b->chaves);
    free(b->filhos);
    free(b);
    free(a->chaves);
    free(a->filhos);
    free(a); */
    FILE *fp = fopen("EURO.txt", "r");
    int i;
    char *str = (char *)malloc(sizeof(char)*40);
    TJ *j;
    if(verificaSelecao(fp)){
        readLine(fp, str, &i, '\n');
        j = leJogador(fp, str);
    }
    fclose(fp);
    imprimeJogador(j);
    free(j);
    free(str);
    return 0;
}