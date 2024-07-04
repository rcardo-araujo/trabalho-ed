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
    a->nome_arq = (char *)malloc(sizeof(char)*40);
    strcpy(a->nome_arq, nomeArq);
    a->prox = (char *)malloc(sizeof(char)*40);
    a->prox[0] = '\0';
    return a;
}

void escreveNo(char *nomeF, TARVBP *no){
    // Tratar NULL!!!
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
    strcpy(no->nome_arq, nomeF);
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
    // Remover arquivos!!!

    free(a->chaves);
    if(a->folha){
        for(int i=0; i < 2*t-1; i++) free(a->reg[i]);
    }
    free(a->reg);
    for(int i=0; i < 2*t; i++) free(a->filhos[i]);
    free(a->prox);
    free(a->filhos);
    free(a->nome_arq);
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
    if(no && strcmp(filho->nome_arq, no->nome_arq)) TARVBP_libera(filho, t);
    return no;
}

//Rever como os nós são liberados na busca
//A busca não está liberando nós antigos, deixando memória alocada, o que pode dar muito problema
TARVBP *TARVBP_busca(TARVBP *a, int id, int t){
    if(!a) return NULL;
    if(!a->folha){
        int i = 0;
        while(i < a->num_chaves && a->chaves[i] < id){
            i++;
        }
        TARVBP *filho = leNo(a->filhos[i], t);
        return buscaAux(filho, id, t);
    }
    int i = 0;
    while(i < a->num_chaves && a->reg[i]->id < id){
        i++;
    }
    if(i < a->num_chaves && a->reg[i]->id == id) return a;
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
        strcpy(a->prox, z->nome_arq);
    }
    a->num_chaves = t-1;
    for(j=pai->num_chaves; j>=i; j--) strcpy(pai->filhos[j+1], pai->filhos[j]);
    strcpy(pai->filhos[i], z->nome_arq);
    for(j=pai->num_chaves; j>=i; j--) pai->chaves[j] = pai->chaves[j-1];
    if(a->folha) pai->chaves[i-1] = a->reg[t-1]->id; // a->folha, logo não possui chaves e sim registros!
    else pai->chaves[i-1] = a->chaves[t-1];
    pai->num_chaves++;
    for(int k=t-1; k<2*t-1; k++) a->reg[k] = NULL;
    escreveNo(a->nome_arq, a);
    escreveNo(z->nome_arq, z);
    escreveNo(pai->nome_arq, pai);
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
        escreveNo(a->nome_arq, a);
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
    escreveNo(filho->nome_arq, filho);
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
        strcpy(pai->filhos[0], a->nome_arq);
        pai = divisao(pai, 1, a, t);
        TARVBP_libera(a, t);
        pai = insere_nao_completo(pai, elem, t);
        return pai;
    }
    a = insere_nao_completo(a, elem, t);
    return a;
}

// TARVBP* remover(TARVBP* a, int id, int t) {
//     if(!a) {
//         printf("Arvore vazia!");
//         return NULL;
//     }

//     int i, j;
//     if(a->folha) {
//         for(i = 0; (i < a->num_chaves) && (a->reg[i]->id < id); i++);
//         // Caso 1
//         if((i < a->num_chaves) && (id == a->reg[i]->id)) {
//             for(j = i; j < (a->num_chaves - 1); j++)
//                 a->reg[j] = a->reg[j + 1];
//             a->num_chaves--;
//             if(!a->num_chaves) {
//                 TARVBP_libera(a, t);
//                 return NULL;
//             }
//             escreveNo(a->nome_arq, a);
//             return a;
//         }
//     }
//     for(i = 0; (i < a->num_chaves) && (a->chaves[i] < id); i++);
//     TARVBP* y = leNo(a->filhos[i], t), *z = NULL;
//     // Casos 3A e 3B
//     if(y->num_chaves == t - 1) {
//         // Casos 3A
//         TARVBP* g = leNo(a->filhos[i + 1], t); // Irmão imediato de y
//         if((i < a->num_chaves) && (g->num_chaves >= t)) {
//             z = g;
//             y->num_chaves++;
//             if(!y->folha) {
//                 y->chaves[t - 1] = a->chaves[i];
//                 a->chaves[i] = z->chaves[0];
//                 for(j = 0; j < (z->num_chaves - 1); j++)
//                     z->chaves[j] = z->chaves[j + 1];
//                 strcpy(y->filhos[y->num_chaves], z->filhos[0]);
//                 for(j = 0; j < z->num_chaves; j++) 
//                     strcpy(z->filhos[j], z->filhos[j + 1]);
//             }
//             else {
//                 a->chaves[i] = z->reg[0]->id + 1;
//                 y->reg[t - 1] = z->reg[0];
//                 for(j = 0; j < (z->num_chaves - 1); j++)
//                     z->reg[j] = z->reg[j + 1];
//             }
//             y->num_chaves++;
            
            
//             z->num_chaves--;
//             y = remover(y, id, t);
            
//             escreveNo(z->nome_arq, z);
//             escreveNo(y->nome_arq, y);
//             escreveNo(a->nome_arq, a);
//             return a;
//         }
//         printf("\nI: %d\t\n", i);
//         for(int k = 0; k <= a->num_chaves; k++) {
//             printf("%s\n", a->filhos[k]);
//         }
//         g = leNo(a->filhos[i - 1], t);
//         if((i > 0) && (!z) && (g->num_chaves >= t)) {
//             z = g;
//             if(!y->folha) {
//                 for(j = y->num_chaves + 1; j > 0; j--)
//                     strcpy(y->filhos[j], y->filhos[j - 1]);
//                 for(j = y->num_chaves; j > 0; j--)
//                     y->chaves[j] = y->chaves[j - 1];
//                 y->chaves[0] = a->chaves[i - 1];
//                 a->chaves[i - 1] = z->chaves[z->num_chaves - 1];
//                 strcpy(y->filhos[0], z->filhos[z->num_chaves]);
//             }
//             else {
//                 for(j = y->num_chaves; j > 0; j--)
//                     y->reg[j] = y->reg[j - 1];
//                 a->chaves[i - 1] = z->reg[z->num_chaves - 1]->id;
//                 y->reg[0] = z->reg[z->num_chaves - 1];
//             }
//             y->num_chaves++;
//             z->num_chaves--;
//             y = remover(y, id, t);

//             escreveNo(y->nome_arq, y);
//             escreveNo(z->nome_arq, z);
//             escreveNo(a->nome_arq, a);
//             return a;
//         }
//         // Caso 3B
//         if(!z) {
//             g = leNo(a->filhos[i + 1], t);
//             if((i < a->num_chaves) && (g->num_chaves == t - 1)) {
//                 z = g;
//                 if(!y->folha) {
//                     y->chaves[t - 1] = a->chaves[i];
//                     y->num_chaves++;
//                 }
//                 j = 0;
//                 while(j < t - 1) {
//                     if(!y->folha) y->chaves[t + j] = z->chaves[j];
//                     else y->reg[t + j - 1] =  z->reg[j];
//                     y->num_chaves++;
//                     j++;
//                 }
//                 if(!y->folha) {
//                     for(j = 0; j < t; j++) {
//                         strcpy(y->filhos[t + j], z->filhos[j]);
//                         z->filhos[j] = NULL;
//                     }
//                     TARVBP_libera(z, t);
//                 }
//                 else {
//                     strcpy(y->prox, z->prox);
//                 }
//                 for(j = i; j < a->num_chaves - 1; j++) {
//                     a->chaves[j] = a->chaves[j + 1];
//                     strcpy(a->filhos[j + 1], a->filhos[j + 2]);
//                 }
//                 a->filhos[a->num_chaves] = NULL;
//                 a->num_chaves--;
//                 if(!a->num_chaves) {
//                     TARVBP* temp = a;
//                     a = y;
//                     temp->filhos[0] = NULL;
//                     TARVBP_libera(temp, t);
//                 }
//                 escreveNo(y->nome_arq, y);
//                 escreveNo(z->nome_arq, z);
//                 a = remover(a, id, t);
//                 escreveNo(a->nome_arq, a);
//                 return a;
//             }
//             g = leNo(a->filhos[i - 1], t);
//             if((i > 0) && (g->num_chaves == t - 1)) {
//                 z = g;
//                 if(!y->folha) {
//                     if(i == a->num_chaves) {
//                         z->chaves[t - 1] = a->chaves[i - 1];
//                     }
//                     else {
//                         z->chaves[t - 1] = a->chaves[i];
//                     }
//                     z->num_chaves++;
//                 }
//                 j = 0;
//                 while(j < t - 1) {
//                     if(!y->folha) z->chaves[t + j] = y->chaves[j];
//                     else z->reg[t + j - 1] = y->reg[j];
//                     z->num_chaves++;
//                     j++;
//                 }
//                 if(!z->folha) {
//                     for(j = 0; j < t; j++) {
//                         strcpy(z->filhos[t + j], y->filhos[j]);
//                         y->filhos[j] = NULL;
//                     }
//                     TARVBP_libera(y, t);
//                 }
//                 else {
//                     strcpy(z->prox, y->prox);
//                 }
//                 a->filhos[a->num_chaves] = NULL;
//                 a->num_chaves--;
//                 if(!a->num_chaves) {
//                     TARVBP* temp = a;
//                     a = z;
//                     temp->filhos[0] = NULL;
//                     TARVBP_libera(temp, t);
//                     a = remover(a, id, t);
//                 }
//                 else {
//                     i--;
//                     y = remover(y, id, t);
//                     escreveNo(y->nome_arq, y);
//                 }
//                 escreveNo(a->nome_arq, a);
//                 return a;
//             }
//         }
//     }
//     y = remover(y, id, t);
//     escreveNo(y->nome_arq, y);
//     escreveNo(a->nome_arq, a);
//     return a;
//  }

//  TARVBP* TARVBP_retira(TARVBP* a, int id, int t) {
//     if((!a) || (!TARVBP_busca(a, id, t))) return a;
//     return remover(a, id, t);
//  }

TARVBP *remover(TARVBP *a, int id, int t){
    if(!a) return a;
    int i;
    if(!a->folha)
        for(i=0; i< a->num_chaves && a->chaves[i] < id; i++);
    else
        for(i=0; i< a->num_chaves && a->reg[i]->id < id; i++);
    if((i < a->num_chaves) && (a->folha) && (id == a->reg[i]->id)){
        printf("\nCASO 1\n");
        int j;
        for(j=i; j < a->num_chaves-1; j++) a->reg[i] = a->reg[j+1];
        a->num_chaves--;
        escreveNo(a->nome_arq, a);
        if(!a->num_chaves){
            char path[60] = "./db/";
            strcat(path, a->nome_arq);
            strcat(path, ".bin");
            remove(path);
            TARVBP_libera(a, t);
            a = NULL;
        }
        return a;
    }

    if((i < a->num_chaves) && (id == a->chaves[i])) i++;
    TARVBP *y = leNo(a->filhos[i], t), *z = NULL;
    if(y->num_chaves == t-1) { //CASOS 3A e 3B
        z = leNo(a->filhos[i+1], t);
        if((i < a->num_chaves) && (z->num_chaves >= t)){ //caso 3A
            printf("\nCASO 3A: i menor que num_chaves\n");
            if(!y->folha){
                y->chaves[t-1] = a->chaves[i];
                a->chaves[i] = z->chaves[0];
            } else {
                a->chaves[i] = z->reg[0]->id + 1;
                y->reg[t-1] = z->reg[0];
            }
            y->num_chaves++;

            int j;
            if(z->folha){
                for(j = 0; j< z->num_chaves-1; j++) z->reg[j] = z->reg[j+1];
            } else {
                for(j = 0; j< z->num_chaves-1; j++) z->chaves[j] = z->chaves[j+1];
                strcpy(y->filhos[y->num_chaves], z->filhos[0]);
                for(j=0; j < z->num_chaves; j++) strcpy(z->filhos[j], z->filhos[j+1]);
            }
            z->num_chaves--;
            escreveNo(z->nome_arq, z);
            TARVBP_libera(z, t);
            y = remover(y, id, t);
            escreveNo(y->nome_arq, y);
            TARVBP_libera(y, t);
            return a;
        }
        TARVBP_libera(z, t);
        printf("\nI: %d\t\n", i);
        for(int k = 0; k <= a->num_chaves; k++) {
            printf("%s\n", a->filhos[k]);
        }
        z = leNo(a->filhos[i-1], t);
        if((i > 0) && (z->num_chaves >= t)){ //CASO 3A 
            printf("\nCASO 3A: i igual a num_chaves\n");
            int j;
            if(!y->folha){
                for(j = y->num_chaves; j > 0; j--) y->chaves[j] = y->chaves[j-1];
                y->chaves[0] = a->chaves[i-1];
                a->chaves[i-1] = z->chaves[z->num_chaves-1];
            } else{
                for(j = y->num_chaves; j > 0; j--) y->reg[j] = y->reg[j-1];
                a->chaves[i-1] = z->reg[z->num_chaves-1]->id;
                y->reg[0] = z->reg[z->num_chaves-1];
            }
            y->num_chaves++;
            if(!y->folha) strcpy(y->filhos[0], z->filhos[z->num_chaves]);
            z->num_chaves--;
            escreveNo(z->nome_arq, z);
            TARVBP_libera(z, t);
            y = remover(y, id, t);
            escreveNo(y->nome_arq, y);
            TARVBP_libera(y, t);
            return a;
        }
        //falta resolver o caso 3B!
        TARVBP_libera(z, t);
        z = leNo(a->filhos[i+1], t);
        if(i < a->num_chaves && z->num_chaves == t-1){
            printf("\nCASO 3B: i menor que num_chaves\n");
            if(!y->folha){
                y->chaves[t-1] = a->chaves[i];
                y->num_chaves++;
            }
            int j=0;
            while(j < t-1){
                if(!y->folha) y->chaves[t+j] = z->chaves[j];
                else y->reg[t+j-1] = z->reg[j];
                y->num_chaves++;
                j++;
            }
            strcpy(y->prox, z->prox);
            if(!y->folha){
                for(j=0; j<t; j++){
                    strcpy(y->filhos[t+j], z->filhos[j]);
                }
                char str[60] = "./db/";
                strcat(str, z->nome_arq);
                strcat(str, ".bin");
                remove(str);
                TARVBP_libera(z, t);
            }
            for(j=i; j<a->num_chaves-1; j++){
                a->chaves[j] = a->chaves[j+1];
                strcpy(a->filhos[j+1], a->filhos[j+2]);
            }
            strcpy(a->filhos[a->num_chaves], "");
            a->num_chaves--;
            if(!a->num_chaves){
                TARVBP *tmp = a;
                a = leNo(a->filhos[0], t);
                strcpy(tmp->filhos[0], "");
                char f[60] = "./db/";
                strcat(f, tmp->nome_arq);
                strcat(f, ".bin");
                remove(f);
                TARVBP_libera(tmp, t);
            }
            a = remover(a, id, t);
            escreveNo(y->nome_arq, y);
            TARVBP_libera(y, t);
            if(y->folha) TARVBP_libera(z, t);
            return a;
        }
        TARVBP_libera(z, t);
        z = leNo(a->filhos[i-1], t);
        if((i > 0) && (z->num_chaves == t-1)){
            printf("\nCASO 3B: i igual a num_chaves\n");
            if(!y->folha){
                if(i == a->num_chaves) z->chaves[t-1] = a->chaves[i-1];
            } else {
                z->chaves[t-1] = a->chaves[i];
            }
            z->num_chaves++;
            int j = 0;
            while(j < t-1){
                if(!y->folha) z->chaves[t+j] = y->chaves[j];
                else z->reg[t+j-1] = y->reg[j];
                z->num_chaves++;
                j++;
            }
            strcpy(z->prox, y->prox);
            if(!z->folha){
                for(j=0; j<t; j++){
                    strcpy(z->filhos[t+j], y->filhos[j]);
                    strcpy(y->filhos[j], "");
                }
                char str[60] = "./db/";
                strcat(str, y->nome_arq);
                strcat(str, ".bin");
                remove(str);
                TARVBP_libera(y, t);
            }
            strcpy(a->filhos[a->num_chaves], "");
            a->num_chaves--;
            if(!a->num_chaves){
                TARVBP *tmp = a;
                a = leNo(a->filhos[0], t);
                strcpy(tmp->filhos[0], "");
                char f[60] = "./db/";
                strcat(f, tmp->nome_arq);
                strcat(f, ".bin");
                remove(f);
                TARVBP_libera(tmp, t);
                a = remover(a, id, t);
            } else{
                i--;
                TARVBP *x = leNo(a->filhos[i], t);
                x = remover(x, id, t);
                escreveNo(x->nome_arq, x);
                TARVBP_libera(x, t);
            }
            if(z->folha) TARVBP_libera(y, t);
            escreveNo(z->nome_arq, z);
            TARVBP_libera(z, t);
            return a;
        }
        TARVBP_libera(z, t);
    }
    y = remover(y, id, t);
    escreveNo(y->nome_arq, y);
    TARVBP_libera(y, t);
    return a;
}

TARVBP *TARVBP_retira(TARVBP* a, int id, int t){
    if(!a || !TARVBP_busca(a, id, t)) return a;
    a = remover(a, id, t);
    escreveNo(a->nome_arq, a);
    return a;
}