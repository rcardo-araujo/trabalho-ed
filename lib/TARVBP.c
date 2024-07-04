#include "../headers/includes.h"

static int numofnodes = 0;

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
    char nome_com_ext[50];
    strcpy(nome_com_ext, "./db/");
    strcat(nome_com_ext, nomeF);
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
        for(int i=0; i < no->num_chaves+1; i++){
            fwrite(no->filhos[i], sizeof(char), strlen(no->filhos[i])+1, fp);
            fwrite("\n", sizeof(char), 1, fp);
        }
    }
    //conditional jump or move depends on unitialised value
    if(no->prox[0]) fwrite(no->prox, sizeof(char), strlen(no->prox)+1, fp);
    fclose(fp);
}

TARVBP *leNo(char *nomeF, int t){
    char nome_com_ext[strlen(nomeF)+10];
    strcpy(nome_com_ext, "./db/");
    strcat(nome_com_ext, nomeF);
    strcat(nome_com_ext, ".bin");
    FILE *fp = fopen(nome_com_ext, "rb");
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
    if(!a->folha){
        int i = 0;
        while(i < a->num_chaves && a->chaves[i] < elem){
            i++;
        }
        TARVBP *filho = leNo(a->filhos[i], t);
        TARVBP *res = buscaAux(filho, elem, t);
        TARVBP_libera(a, t);
        return res;
    }else{
        for(int i = 0; i < a->num_chaves; i++){
            if(a->reg[i]->id == elem) return a;
        }
        return NULL;
    }
}

/**
 * Faz a busca de um nó numa árvore B+.
 * @param a Árvore
 * @param elem Elemento a ser buscado
 * @param t Ordem da árvore
 * @return TARVB contendo as informações referentes ao nó.
 */
TARVBP *TARVBP_busca(TARVBP *a, int elem, int t){
    int i = 0;
    while(i < a->num_chaves && a->chaves[i] < elem){
        i++;
    }
    TARVBP *res = buscaAux(leNo(a->filhos[i], t), elem, t);
    return res;
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

TARVBP *TARVBP_insere(TARVBP *a, TJ *elem, int t){
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
        pai = insere_nao_completo(pai, elem, t);
        return pai;
    }
    a = insere_nao_completo(a, elem, t);
    return a;
}
