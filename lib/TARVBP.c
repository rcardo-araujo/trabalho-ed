/**
 * @file TARVBP.c
 * @brief Funções relacionadas ao funcionamento da Árvore B+
 */

#include "../headers/includes.h"

static int numofnodes = 0; ///< Número de nós

/**
 * @brief Cria um novo nó da árvore B+.
 * @param nomeArq Nome do arquivo
 * @param t Ordem da árvore
 * @return @c TARVBP vazia
 */
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

#pragma region Utils
/**
 * @brief Escreve as informações do nó em um arquivo binário.
 * @param nomeF Nome do arquivo
 * @param no Nó
 */
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

/**
 * @brief Carrega um arquivo para um @c TARVBP.
 * @param nomeF Nome do arquivo
 * @param t Ordem da árvore
 * @return @c TARVB com as informações carregadas do arquivo.
 */
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

/**
 * @brief Libera o nó da memória
 * @param a Nó
 * @param t Ordem da árvore
 */
void TARVBP_libera(TARVBP *a, int t){
    free(a->chaves);
    if(a->folha){
        for(int i=0; i < 2*t-1; i++){
             if(a->reg[i]) free(a->reg[i]);
        }
    }
    free(a->reg);
    for(int i=0; i < 2*t; i++) free(a->filhos[i]);
    free(a->prox);
    free(a->filhos);
    free(a->nomeArq);
    free(a);
}
#pragma endregion

#pragma region Busca
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
        TARVBP_libera(a, t);
        return NULL;
    }
}

/**
 * @brief Faz a busca de um nó numa árvore B+.
 * @param a Árvore
 * @param elem Elemento a ser buscado
 * @param t Ordem da árvore
 * @return @c TARVB contendo as informações referentes ao nó.
 */
TARVBP *TARVBP_busca(TARVBP *a, int elem, int t){
    int i = 0;
    while(i < a->num_chaves && a->chaves[i] <= elem){
        i++;
    }
    TARVBP *res = buscaAux(leNo(a->filhos[i], t), elem, t);
    return res;
}

/**
 * @brief Verifica se a árvore possui um elemento
 * @param a Árvore
 * @param elem Elemento para procurar
 * @param t Ordem da árvore
 * @return 0 se não existe ou 1 se existe
 */
int TARVB_possui_elemento(TARVBP *a, int elem, int t){
    TARVBP *b = TARVBP_busca(a, elem, t);
    if(b){
        TARVBP_libera(b, t);
        return 1;
    }
    return 0;
}
#pragma endregion

#pragma region Inserção
/**
 * @brief Faz a divisão de um nó
 * @param pai Raiz da árvore a ser dividida
 * @param i nao sei
 * @param a nao sei
 * @param t Ordem da ávore
 * @return Nova raiz @c TARVBP com a divisão feita
 */
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
    if(TARVB_possui_elemento(a, elem->id, t)) return a;

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
#pragma endregion

#pragma region Remoção
TARVBP *remover(TARVBP *a, int id, int t){
    if(!a) return a;
    int i;
    if(!a->folha)
        for(i=0; i< a->num_chaves && a->chaves[i] < id; i++);
    else
        for(i=0; i< a->num_chaves && a->reg[i]->id < id; i++);
    
    if((i < a->num_chaves) && (a->folha) && (id == a->reg[i]->id)){
        //FUNCIONANDO !!
        printf("\nCASO 1\n");
        int j;
        free(a->reg[i]);
        for(j=i; j < a->num_chaves-1; j++) a->reg[j] = a->reg[j+1];
        a->reg[a->num_chaves-1] = NULL;
        a->num_chaves--;
        escreveNo(a->nomeArq, a);
        if(!a->num_chaves){
            char path[60] = "./db/";
            strcat(path, a->nomeArq);
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
        if(i <= a->num_chaves) z = leNo(a->filhos[i+1], t);
        if((i < a->num_chaves) && (z->num_chaves >= t)){ //caso 3A
            //FUNCIONANDO!!
            printf("\nCASO 3A: i menor que num_chaves\n");
            if(!y->folha){
                y->chaves[t-1] = a->chaves[i];
                a->chaves[i] = z->chaves[0];
            } else {
                a->chaves[i] = z->reg[0]->id + 1;
                y->reg[t-1] = z->reg[0];
                z->reg[0] = NULL;
            }
            y->num_chaves++;

            int j;
            if(z->folha){
                for(j = 0; j < z->num_chaves-1; j++) z->reg[j] = z->reg[j+1];
                z->reg[z->num_chaves-1] = NULL;
            } else {
                for(j = 0; j< z->num_chaves-1; j++) z->chaves[j] = z->chaves[j+1];
                strcpy(y->filhos[y->num_chaves], z->filhos[0]);
                for(j=0; j < z->num_chaves; j++) strcpy(z->filhos[j], z->filhos[j+1]);
            }
            z->num_chaves--;
            escreveNo(z->nomeArq, z);
            escreveNo(y->nomeArq, y);
            y = remover(y, id, t);
            TARVBP_libera(y, t);
            TARVBP_libera(z, t);
            return a;
        }
        if(z) TARVBP_libera(z, t);
        z = NULL;
        if(i) z = leNo(a->filhos[i-1], t);
        if((i > 0) && (z->num_chaves >= t)){ //CASO 3A 
            // FUNCIONANDO!!!!
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
                z->reg[z->num_chaves-1] = NULL;
            }
            y->num_chaves++;
            if(!y->folha) strcpy(y->filhos[0], z->filhos[z->num_chaves]);
            z->num_chaves--;
            escreveNo(z->nomeArq, z);
            TARVBP_libera(z, t);
            y = remover(y, id, t);
            escreveNo(y->nomeArq, y);
            TARVBP_libera(y, t);
            return a;
        }
        if(z) TARVBP_libera(z, t);
        z = leNo(a->filhos[i+1], t);
        if(i < a->num_chaves && z->num_chaves == t-1){
            //FUNCIONANDO!!
            printf("\nCASO 3B: i menor que num_chaves\n");
            if(!y->folha){
                y->chaves[t-1] = a->chaves[i];
                y->num_chaves++;
            }
            int j=0;
            while(j < t-1){
                if(!y->folha) y->chaves[t+j] = z->chaves[j];
                else {
                    y->reg[t+j-1] = z->reg[j];
                    z->reg[j] = NULL;
                }
                y->num_chaves++;
                j++;
            }
            strcpy(y->prox, z->prox);
            if(!y->folha){
                for(j=0; j<t; j++){
                    strcpy(y->filhos[t+j], z->filhos[j]);
                }
            }
            char str[60] = "./db/";
            strcat(str, z->nomeArq);
            strcat(str, ".bin");
            remove(str);
            TARVBP_libera(z, t);

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
                strcat(f, tmp->nomeArq);
                strcat(f, ".bin");
                remove(f);
                TARVBP_libera(tmp, t);
            }
            escreveNo(y->nomeArq, y);
            TARVBP_libera(y, t);
            a = remover(a, id, t);
            return a;
        }
        if(z) TARVBP_libera(z, t);
        z = leNo(a->filhos[i-1], t);
        if((i > 0) && (z->num_chaves == t-1)){
            printf("\nCASO 3B: i igual a num_chaves\n");
            if(!y->folha){
                if(i == a->num_chaves) z->chaves[t-1] = a->chaves[i-1];
                else z->chaves[t-1] = a->chaves[i];

                z->num_chaves++;
            }
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
                strcat(str, y->nomeArq);
                strcat(str, ".bin");
                remove(str);
                TARVBP_libera(y, t);
            }
            escreveNo(z->nomeArq, z);
            strcpy(a->filhos[a->num_chaves], "");
            a->num_chaves--;
            if(!a->num_chaves){
                // ta errado (double free)
                TARVBP *tmp = a;
                a = leNo(a->filhos[0], t);
                strcpy(tmp->filhos[0], "");
                char f[60] = "./db/";
                strcat(f, tmp->nomeArq);
                strcat(f, ".bin");
                remove(f);
                TARVBP_libera(tmp, t);
                a = remover(a, id, t);
            } else{
                i--;
                // TARVBP *x = leNo(a->filhos[i], t);
                z = remover(z, id, t);
                escreveNo(z->nomeArq, z);
                TARVBP_libera(z, t);
                z = NULL;
            }
            if(z && z->folha) TARVBP_libera(y, t);
            if(z) TARVBP_libera(z, t);
            return a;
        }
        TARVBP_libera(z, t);
    }
    y = remover(y, id, t);
    escreveNo(y->nomeArq, y);
    TARVBP_libera(y, t);
    return a;
}

TARVBP *TARVBP_retira(TARVBP* a, int id, int t){
    if(!a || !TARVB_possui_elemento(a, id, t)) return a;
    printf("vai remover\n");
    a = remover(a, id, t);
    escreveNo(a->nomeArq, a);
    return a;
}
#pragma endregion

#pragma region Impressao
/**
 * @brief Imprime um nó da árvore
 * @param a Nó
 */
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

/**
 * @brief Imprime os registros da árvore
 * @param a Árvore
 * @param t Ordem da árvore
 */
void TARVBP_imprime_registros(TARVBP *a, int t){
    if(!a) return;
    TARVBP *p = a;
    TARVBP *no = leNo(p->filhos[0], t);
    while(no) {
        if(p != a) TARVBP_libera(p, t);
        p = no;
        no = leNo(p->filhos[0], t);
    }
    while(p){
        int i;
        for(i = 0; i < p->num_chaves; i++) printf("%d ", p->reg[i]->id);
        TARVBP *temp = p;
        p = leNo(p->prox, t);
        TARVBP_libera(temp, t);
    }
    printf("\n");
}

void TARVBP_imprime_aux(TARVBP *arv, int andar, int t){
    if(arv){
        int i,j;
        for(i=0; i<=arv->num_chaves-1; i++){
            TARVBP *filho = leNo(arv->filhos[i], t);
            TARVBP_imprime_aux(filho, andar+1, t);
            if(filho) TARVBP_libera(filho, t);
            for(j=0; j<=andar; j++) printf("\t");
            if(!arv->folha){
                printf("%d\n", arv->chaves[i]);
            }else{
                printf("%d\n", arv->reg[i]->id);
            }
        }
        TARVBP *filho = leNo(arv->filhos[i], t);
        TARVBP_imprime_aux(filho, andar+1, t);
        if(filho) TARVBP_libera(filho, t);
    }
}

/**
 * @brief Imprime a árvore
 * @param arv Árvore
 * @param t Ordem da árvore
 */
void TARVBP_imprime(TARVBP *arv, int t){
    TARVBP_imprime_aux(arv, 0, t);
    printf("\n");
    TARVBP_imprime_registros(arv, t);
}
#pragma endregion