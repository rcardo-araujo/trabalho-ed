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
    TJ **reg;
    char** filhos;
    char *prox;
} TARVBP;

void readLine(FILE *fp, char *string, int *size){
    int i = 0, x;
    char c;
    while(i < 40){
        x = fread(&c, sizeof(char), 1, fp);
        if(x != 1) {
            (*size) = -1;
        }
        if(c == '\n'){
            string[i] = '\0';
            break;
        }
        string[i] = c;
        i++;
    }
    (*size) = i;
}

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
        readLine(fp, c, &size);
        no->filhos[j] = (char *) malloc(sizeof(char)*size);
        strcpy(no->filhos[j], c);
    }
    readLine(fp, c, &size);
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
    printf("id: %d\nnum: %d \npos: %s\nnome: %s\nnasc: %s\nnum_part: %d\nnum_gols: %d\npais_time: %s\ntime: %s\npais: %s",
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
    TARVBP *a = (TARVBP *) malloc(sizeof(TARVBP));
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
    free(a);
    return 0;
}