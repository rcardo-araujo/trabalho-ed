#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

static int numofnodes = 0;

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
    strcpy(j->pais, selecao);
    char c;
    char placeholder[40];
    char dia[4], mes[10], *ano = (char *)malloc(sizeof(char)*5);
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
    int i = fread(&c, sizeof(char), 1, fp);
    if(!i) return -1;
    fseek(fp, -1*sizeof(char), SEEK_CUR);
    if(c >= 48 && c <= 57){
        return 0;
    }
    return 1;
}

typedef struct arvbp {
    char *nomeArq;
    int folha;
    int num_chaves;
    int *chaves;
    TJ **reg;
    char **filhos;
    char *prox;
} TARVBP;

TARVBP *TARVBP_cria(char *nomeArq, int t){
    TARVBP *a = (TARVBP *) malloc(sizeof(TARVBP));
    a->folha = 1;
    a->num_chaves = 0;
    a->chaves = (int *)malloc(sizeof(int)*(2*t-1));
    a->reg = (TJ **)malloc(sizeof(TJ *)*(2*t-1));
    for(int i=0; i<2*t-1; i++) a->reg[i] = NULL;
    a->filhos = (char **)malloc(sizeof(char *)*2*t);
    for(int i=0; i<2*t; i++) {
        a->filhos[i] = (char *)malloc(sizeof(char)*40);
        a->filhos[i][0] = '\0';
    }
    a->nomeArq = (char *)malloc(sizeof(char)*40);
    strcpy(a->nomeArq, nomeArq);
    a->prox = (char *)malloc(sizeof(char)*40);
    a->prox[0] = '\0';
    return a;
}

void escreveNo(char *nomeF, TARVBP *no){
    char nome_com_ext[45];
    strcpy(nome_com_ext, nomeF);
    strcat(nome_com_ext, ".bin");
    FILE *fp = fopen(nome_com_ext, "wb");
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
            fwrite(no->filhos[i], sizeof(char), strlen(no->filhos[i])+1, fp);
            fwrite("\n", sizeof(char), 1, fp);
        }
    }
    //conditional jump or move depends on unitialised value
    if(no->prox[0]) fwrite(no->prox, sizeof(char), strlen(no->prox)+1, fp);
    fclose(fp);
}

TARVBP *leNo(char *nomeF, int t){
    char nome_com_ext[strlen(nomeF)+5];
    strcpy(nome_com_ext, nomeF);
    strcat(nome_com_ext, ".bin");
    FILE *fp = fopen(nomecomext, "rb");
    if(!fp) return NULL;
    TARVBP *no = TARVBP_cria(nomeF, t);
    strcpy(no->nomeArq, nomeF);
    fread(&no->folha, sizeof(int), 1, fp);
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
    if(!no->folha){
        for(int j = 0; j < no->num_chaves+1; j++){
            readLine(fp, c, &size, '\n');
            strcpy(no->filhos[j], c);
        }
    }
    readLine(fp, c, &size, '\n');
    if(size > 0){
        strcpy(no->prox, c);
    }
    fclose(fp);
    return no;
}

void imprimeJogador(TJ *j){
    printf("------Jogador------\n");
    printf("id: %d\nnum: %d \npos: %s\nnome: %s\nnasc: %s\nnum_part: %d\nnum_gols: %d\npais_time: %s\ntime: %s\npais: %s\n",
    j->id, j->num, j->pos, j->nome, j->data_nasc, j->num_part, j->num_gols, j->pais_time, j->time, j->pais);
    printf("-------------------\n");
}

void imprimeNo(TARVBP *a){
    printf("------No lido:------\n");
    printf("folha: %d\n", a->folha);
    printf("num_chaves: %d\n", a->num_chaves);
    printf("num_filhos: %d\n", a->folha ? 0 : a->num_chaves+1);
    if(a->folha){
        for(int i=0; i<a->num_chaves; i++){
            imprimeJogador(a->reg[i]);
        }
        if(a->prox) printf("prox: %s\n", a->prox);
       return;
    } else {
        for(int i=0; i < a->num_chaves; i++){
            printf("chave %d: %d\n", i, a->chaves[i]);
        }
    }
    for(int i=0; i < a->num_chaves+1; i++){
        printf("filho %d: %s\n", i, a->filhos[i]);
    }
    printf("---------------------------\n");
}


void TARVBP_libera(TARVBP *a, int t){
    free(a->chaves);
    if(a->folha){
        for(int i=0; i < 2*t-1; i++) free(a->reg[i]);
    }
    free(a->reg);
    for(int i=0; i < 2*t; i++) free(a->filhos[i]);
    free(a->prox);
    free(a->filhos);
    free(a->nomeArq);
    free(a);
}

TARVBP *buscaAux(TARVBP *a, int elem, int t){
    if(!a) return NULL;
    if(a->folha){
        for(int i=0; i<a->num_chaves; i++)
            if(a->reg[i]->id == elem) return a;
    }
    int i=0;
    while(i < a->num_chaves && a->chaves[i] < elem) i++;
    TARVBP *filho = leNo(a->filhos[i], t);
    //TARVBP_libera(a, t);
    TARVBP *no = buscaAux(filho, elem, t);
    if(no && strcmp(filho->nomeArq, no->nomeArq)) TARVBP_libera(filho, t);
    return no;
}

//Rever como os nós são liberados na busca
//A busca não está liberando nós antigos, deixando memória alocada, o que pode dar muito problema
TARVBP *TARVBP_busca(TARVBP *a, int elem, int t){
    if(!a) return NULL;
    if(!a->folha){
        int i = 0;
        while(i < a->num_chaves && a->chaves[i] < elem){
            i++;
        }
        TARVBP *filho = leNo(a->filhos[i], t);
        return buscaAux(filho, elem, t);
    }
    int i = 0;
    while(i < a->num_chaves && a->reg[i]->id < elem){
        i++;
    }
    if(i < a->num_chaves && a->reg[i]->id == elem) return a;
    return NULL;
}


TARVBP *divisao(TARVBP *pai, int i, TARVBP *a, int t){
    numofnodes++;
    char str[10];
    sprintf(str, "%d", numofnodes);
    TARVBP *z = TARVBP_cria(str, t);
    z->folha = a->folha;
    int j;
    if(!a->folha){
        //esse if ainda nao foi verificado
        z->num_chaves = t-1;
        for(j=0;j<t-1;j++) {
            z->chaves[j] = a->chaves[j+t];
        }
        for(j=0;j<t;j++){
            strcpy(z->filhos[j], a->filhos[j+t]);
            strcpy(a->filhos[j+t], "");
        }
    } else {
        z->num_chaves = t;
        for(j=0;j < t;j++){
            z->reg[j] = a->reg[j+t-1];
        }
        strcpy(z->prox, a->prox);
        strcpy(a->prox, z->nomeArq);
    }
    a->num_chaves = t-1;
    for(j=pai->num_chaves; j>=i; j--) strcpy(pai->filhos[j+1], pai->filhos[j]);
    strcpy(pai->filhos[i], z->nomeArq);
    for(j=pai->num_chaves; j>=i; j--) pai->chaves[j] = pai->chaves[j-1];
    if(a->folha) pai->chaves[i-1] = a->reg[t-1]->id; // a->folha, logo não possui chaves e sim registros!
    else pai->chaves[i-1] = a->chaves[t-1];
    pai->num_chaves++;
    for(int k=t-1; k<2*t-1; k++) a->reg[k] = NULL;
    escreveNo(a->nomeArq, a);
    escreveNo(z->nomeArq, z);
    escreveNo(pai->nomeArq, pai);
    TARVBP_libera(z, t);
    return pai;
}

TARVBP *insere_nao_completo(TARVBP *a, TJ *j, int t){
    int i = a->num_chaves-1;
    if(a->folha){
        while((i>=0) && (j->id < a->reg[i]->id)){
            a->reg[i+1] = a->reg[i];
            i--;
        }
        a->reg[i+1] = j;
        a->num_chaves++;
        escreveNo(a->nomeArq, a);
        return a;
    }
    while((i>=0) && (j->id < a->chaves[i])) i--;
    i++;
    TARVBP *filho = leNo(a->filhos[i], t);
    if(filho->num_chaves == ((2*t)-1)){
        //esse if tambem nao foi verificado!
        a = divisao(a, (i+1), filho, t);
        TARVBP_libera(filho, t);
        filho = NULL;
        if(!a->folha && j->id > a->chaves[i]) i++;
        if(a->folha && j->id > a->reg[i]->id) i++;
    }
    if(!filho) filho = leNo(a->filhos[i], t);
    filho = insere_nao_completo(filho, j, t);
    escreveNo(filho->nomeArq, filho);
    TARVBP_libera(filho, t);
    return a;
}

TARVBP *TARVBP_insere(TARVBP *a, TJ *j, int t){
    //if(TARVBP_busca(a, j->id, t)) return a;
    //tirei essa linha pq a busca nao esta funcionando de maneira ideal
    //mas para continuar de fato, vamos ter que adicionar a busca de se o no ja existe
    if(!a) {
        printf("A arvore nao foi criada com um nome para os arquivos!\n");
        exit(1);
    }
    if(a->num_chaves == 2*t-1){
        numofnodes++;
        char str[10];
        sprintf(str, "%d", numofnodes);
        TARVBP *pai = TARVBP_cria(str, t);
        pai->folha = 0;
        strcpy(pai->filhos[0], a->nomeArq);
        pai = divisao(pai, 1, a, t);
        TARVBP_libera(a, t);
        pai = insere_nao_completo(pai, j, t);
        return pai;
    }
    a = insere_nao_completo(a, j, t);
    return a;
}


TARVBP *arq2Tree(char *nomeArq, int t){
    TARVBP *a = TARVBP_cria(nomeArq, t);
    FILE *fp = fopen("EURO.txt", "r");
    char selecao[40];
    int size;
    TJ *j;
    int i = 284;
    while(i > 0){
        if(verificaSelecao(fp)){
            readLine(fp, selecao, &size, '\n');
        } else {
            j = leJogador(fp, selecao);
            a = TARVBP_insere(a, j, t);
            i--;
        }
    }
    return a;
}

int main(void){
    TARVBP *a = arq2Tree("igor", 2);
    TARVBP *b = TARVBP_busca(a, 1, 2);
    imprimeNo(a);
    char *p = (char *)malloc(sizeof(char)*40);
    imprimeNo(b);
    p = strcpy(p, b->prox);
    while(strcmp(p, "\0")){
        TARVBP *c = leNo(p, 2);
        imprimeNo(c);
        p = strcpy(p, c->prox);
        TARVBP_libera(c, 2);
    }
    TARVBP_libera(b, 2);
    TARVBP_libera(a, 2);
    free(p);

    return 0;
}