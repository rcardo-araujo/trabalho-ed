#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct arvbp {
    int folha;
    int num_chaves;
    int *chaves;
    TJ *reg;
    char** filhos;
    char *prox;
} TARVBP;

char *readLine(FILE *fp, int *size){
    char *string = (char *) malloc(sizeof(char)*40);
    int i = 0, x;
    char c;
    while(i < 40){
        x = fread(&c, sizeof(char), 1, fp);
        if(x != 1) {
            size = -1;
            return string;
        }
        if(c == '\n'){
            string[i] = '\0';
            break;
        }
        string[i] = c;
        i++;
    }
    (*size) = i;
    return string;
}

void escreveNo(FILE *fp, TARVBP *no, int t){
    fwrite(&no->folha, sizeof(int), 1, fp);
    fwrite(&no->num_chaves, sizeof(int), 1, fp);

    for(int i; i< no->num_chaves; i++){
        if(no->folha) fwrite(&no->reg[i], sizeof(TJ), 1, fp);
        else {
            fwrite(&no->chaves[i], sizeof(int), 1, fp);
        }
            
    }
    if(!no->folha){
        for(int i; i < no->num_chaves+1; i++){
            fwrite(&no->filhos[i], sizeof(char), strlen(no->filhos[i]), fp);
            fwrite("\n", sizeof(char), 1, fp);
        }
    }
    if(no->prox) fwrite(no->prox, sizeof(char), strlen(no->prox), fp);
}

TARVBP leNo(FILE *fp, int t){
    if(!fp) return NULL;
    TARVBP *no = (TARVBP *) malloc(sizeof(TARVBP));
    no->filhos = (char *) malloc(sizeof(char *)*2*t);
    fread(&no->folha, sizeof(int), 1, fp);
    if(no->folha) {
        no->reg = (TJ *) malloc(sizeof(TJ *)*2*t-1);
        no->chaves = NULL;
    }
    else {
        no->chaves = (int *) malloc(sizeof(int)*2*t-1);
        no->reg = NULL;
    }
    fread(&no->num_chaves, sizeof(int), 1, fp);
    for(int i = 0; i < no->num_chaves; i++){
        if(!no->folha) fread(&no->chaves[i], sizeof(int), 1, fp);
        else fread(&no->reg[i], sizeof(TJ), 1, fp);
    }
    int size;
    char c[40];
    for(int j = 0; j < no->num_chaves+1; j++){
        c = readLine(fp, size);
        no->filhos[j] = (char *) malloc(sizeof(char)*size);
        strcpy(no->filhos[j], c);
    }
    c = readLine(fp, size);
    if(size < 0){
        no->prox = NULL;
    } else{
        no->prox = (char *) malloc(sizeof(char)*size);
        strcpy(no->prox, c);
    }
    return no;
}

TARVBP *TARVBP_busca(TARVBP *a, int elem, int t){
    if(!a) return NULL;
    if(!no->folha){
        int i = 0;
        while(a->chaves[i] < elem && i < a->num_chaves){
            i++;
        }
        TARVBP *fiho = leNo(fopen(a->filhos[i], "rb"), t);
        return TARVBP_busca(filho, elem, t);
    }
    while(a->regs[i].id < elem && i < a->num_chaves){
        i++
    }
    if(i < a->num_chaves && a->regs[i].id == elem) return a;
    return NULL;
}