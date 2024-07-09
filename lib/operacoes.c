#include "../headers/includes.h"
#include <limits.h>

// Operação [02] - Mais atuaram por equipe específica
TLSETJ* maisAtuaramEquipe(TARVBP* a, int t, char* pais) {
    FILE* ftab  = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    int ind = TABSELE_indiceEquipe(pais), i, maior = INT_MIN;
    TLSETJ* l = TLSETJ_inicializa();
    TJ* jog_aux;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    for(i = 0; i < reg_aux.num_jogadores; i++) {
        jog_aux = TARVBP_buscaJogador(a, reg_aux.jogadores[i], t);
        if(jog_aux->num_part > maior) {
            if(l) l = TLSETJ_libera(l);
            l = TLSETJ_insere(l, jog_aux);
            maior = jog_aux->num_part;
        }
        else if(jog_aux->num_part == maior) {
            l = TLSETJ_insere(l, jog_aux);
        }
        else free(jog_aux);
    }
    fclose(ftab);
    return l;
}

// Operação [02] - Menos atuaram por equipe específica
TLSETJ* menosAtuaramEquipe(TARVBP* a, int t, char* pais) {
    FILE* ftab  = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    int ind = TABSELE_indiceEquipe(pais), i, menor = INT_MAX;
    TLSETJ* l = TLSETJ_inicializa();
    TJ* jog_aux;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    for(i = 0; i < reg_aux.num_jogadores; i++) {
        jog_aux = TARVBP_buscaJogador(a, reg_aux.jogadores[i], t);
        if(jog_aux->num_part < menor) {
            if(l) l = TLSETJ_libera(l);
            l = TLSETJ_insere(l, jog_aux);
            menor = jog_aux->num_part;
        }
        else if(jog_aux->num_part == menor) {
            l = TLSETJ_insere(l, jog_aux);
        }
        else free(jog_aux);
    }
    fclose(ftab);
    return l;
}

// Operação [02] - Mais atuaram em cada equipe
TLSETJ* maisAtuaramCadaEquipe(TARVBP* a, int t) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    TLSETJ* l = TLSETJ_inicializa(), * l_aux, * p;
    TSELE reg_aux;
    int i = 0;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        l_aux = maisAtuaramEquipe(a, t, reg_aux.nome_pais);
        p = l_aux;
        while(p) {
            l = TLSETJ_insere(l, TJ_copiaJogador(p->jogador));
            p = p->prox;
        }
        l_aux = TLSETJ_libera(l_aux);
        i += sizeof(TSELE);
    }
    fclose(ftab);
    return l;
}

// Operação [02] - Menos atuaram em cada equipe
TLSETJ* menosAtuaramCadaEquipe(TARVBP* a, int t) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    TLSETJ* l = TLSETJ_inicializa(), * l_aux, * p;
    TSELE reg_aux;
    int i = 0;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        l_aux = menosAtuaramEquipe(a, t, reg_aux.nome_pais);
        p = l_aux;
        while(p) {
            l = TLSETJ_insere(l, TJ_copiaJogador(p->jogador));
            p = p->prox;
        }
        TLSETJ_libera(l_aux);
        i += sizeof(TSELE);
    }
    fclose(ftab);
    return l;
}

// Operação [03] - Menos atuaram no total
TLSETJ* menosAtuaramTotal(TARVBP* a, int t) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    TLSETJ* l = TLSETJ_inicializa();
    int i = 0, j, menor = INT_MAX;
    TSELE reg_aux;
    TJ* jog_aux;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        for(j = 0; j < reg_aux.num_jogadores; j++) {
            jog_aux = TARVBP_buscaJogador(a, reg_aux.jogadores[j], t);
            if(jog_aux->num_part < menor) {
                if(l) l = TLSETJ_libera(l);
                l = TLSETJ_insere(l, jog_aux);
                menor = jog_aux->num_part;
            }
            else if(jog_aux->num_part == menor) {
                l = TLSETJ_insere(l, jog_aux);
            }
            else free(jog_aux);
        }
        i += sizeof(TSELE);
    }
    fclose(ftab);
    return l;
}

// Operação [03] - Mais atuaram no total
TLSETJ* maisAtuaramTotal(TARVBP* a, int t) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    TLSETJ* l = TLSETJ_inicializa();
    int i = 0, j, maior = INT_MIN;
    TSELE reg_aux;
    TJ* jog_aux;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        for(j = 0; j < reg_aux.num_jogadores; j++) {
            jog_aux = TARVBP_buscaJogador(a, reg_aux.jogadores[j], t);
            if(jog_aux->num_part > maior) {
                if(l) l = TLSETJ_libera(l);
                l = TLSETJ_insere(l, jog_aux);
                maior = jog_aux->num_part;
            }
            else if(jog_aux->num_part == maior) {
                l = TLSETJ_insere(l, jog_aux);
            }
            else free(jog_aux);
        }
        i += sizeof(TSELE);
    }
    fclose(ftab);
    return l;
}

// Operação [04] - Maiores seleções (convocados)
TLSECHAR* maioresEquipes(int* qtd) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);
    
    TLSECHAR* l = TLSECHAR_inicializa();
    int i = 0, j, maior = INT_MIN;
    TSELE reg_aux;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        if(reg_aux.num_jogadores > maior) {
            if(l) l = TLSECHAR_libera(l);
            l = TLSECHAR_insere(l, reg_aux.nome_pais);
            maior = reg_aux.num_jogadores;
        }
        else if(reg_aux.num_jogadores == maior) {
            l = TLSECHAR_insere(l, reg_aux.nome_pais);
        }
        i += sizeof(TSELE);
    }
    fclose(ftab);
    (*qtd) = maior;
    return l;
}

// Operação [04] - Menores seleções (convocados)
TLSECHAR* menoresEquipes(int* qtd) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);
    
    TLSECHAR* l = TLSECHAR_inicializa();
    int i = 0, j, menor = INT_MAX;
    TSELE reg_aux;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        if(reg_aux.num_jogadores < menor) {
            if(l) l = TLSECHAR_libera(l);
            l = TLSECHAR_insere(l, reg_aux.nome_pais);
            menor = reg_aux.num_jogadores;
        }
        else if(reg_aux.num_jogadores == menor) {
            l = TLSECHAR_insere(l, reg_aux.nome_pais);
        }
        i += sizeof(TSELE);
    }
    fclose(ftab);
    (*qtd) = menor;
    return l;
}

// Operação [05] - Busca de todos os jogadores
// de uma equipe que atuam fora da origem
TLSETJ* buscaAllForaOrigemEquipe(TARVBP* a, int t, char* nome_pais) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    TLSETJ* l = TLSETJ_inicializa();
    int ind = TABSELE_indiceEquipe(nome_pais), i;
    TJ* jog_aux;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    for(i = 0; i < reg_aux.num_jogadores; i++) {
        jog_aux = TARVBP_buscaJogador(a, reg_aux.jogadores[i], t);
        if(strcmp(nome_pais, jog_aux->pais_time)) {
            l = TLSETJ_insere(l, jog_aux);
        }
        else free(jog_aux);
    }
    fclose(ftab);
    return l;
}

// Operação [05] - Busca de todos os
// jogadores que atuam fora da origem
TLSETJ* buscaAllForaOrigem(TARVBP* a, int t) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    TLSETJ* l = TLSETJ_inicializa(), *l_aux, *p;
    TSELE reg_aux;
    int i = 0;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        l_aux = buscaAllForaOrigemEquipe(a, t, reg_aux.nome_pais);
        
        p = l_aux;
        while(p) {
            l = TLSETJ_insere(l, p->jogador);
            p = p->prox;
        }
        l_aux = TLSETJ_libera(l_aux);
        i += sizeof(TSELE);
    }
    fclose(ftab);
    return l;
}

// Operação [06] - Busca de todos os jogadores
// de uma equipe que atuam na origem
TLSETJ* buscaAllNaOrigemEquipe(TARVBP* a, int t, char* nome_pais) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    TLSETJ* l = TLSETJ_inicializa();
    int ind = TABSELE_indiceEquipe(nome_pais), i;
    TJ* jog_aux;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    for(i = 0; i < reg_aux.num_jogadores; i++) {
        jog_aux = TARVBP_buscaJogador(a, reg_aux.jogadores[i], t);
        if(!strcmp(nome_pais, jog_aux->pais_time)) {
            l = TLSETJ_insere(l, jog_aux);
        }
        else free(jog_aux);
    }
    fclose(ftab);
    return l;
}

// Operação [06] - Busca de todos os
// jogadores que atuam na origem
TLSETJ* buscaAllNaOrigem(TARVBP* a, int t) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    TLSETJ* l = TLSETJ_inicializa(), *l_aux, *p;
    TSELE reg_aux;
    int i = 0;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        l_aux = buscaAllNaOrigemEquipe(a, t, reg_aux.nome_pais);
        
        p = l_aux;
        while(p) {
            l = TLSETJ_insere(l, TJ_copiaJogador(p->jogador));
            p = p->prox;
        }
        l_aux = TLSETJ_libera(l_aux);
        i += sizeof(TSELE);
    }
    fclose(ftab);
    return l;
}

// Operação [09] - Seleções com mais
// jogadores que atuam fora da origem
TLSECHAR* maioresEquipesForaOrigem(TARVBP* a, int t, int* qtd) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    TLSECHAR* l = TLSECHAR_inicializa();
    TLSETJ* l_aux, *p;
    TSELE reg_aux;
    int i = 0, maior = INT_MIN, qtd_aux;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        l_aux = buscaAllForaOrigemEquipe(a, t, reg_aux.nome_pais);
        qtd_aux = 0;
        p = l_aux;
        while(p) {
            qtd_aux++;
            p = p->prox;
        }
        if(qtd_aux > maior) {
            if(l) l = TLSECHAR_libera(l);
            l = TLSECHAR_insere(l, reg_aux.nome_pais);
            maior = qtd_aux;
        }
        else if(qtd_aux == maior) {
            l = TLSECHAR_insere(l, reg_aux.nome_pais);
        }
        l_aux = TLSETJ_libera(l_aux);
        i += sizeof(TSELE);
    }
    fclose(ftab);
    (*qtd) = maior;
    return l;
}

// Operação [10] - Seleções com mais
// jogadores que atuam na origem
TLSECHAR* maioresEquipesNaOrigem(TARVBP* a, int t, int* qtd) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    TLSECHAR* l = TLSECHAR_inicializa();
    TLSETJ* l_aux, *p;
    TSELE reg_aux;
    int i = 0, maior = INT_MIN, qtd_aux;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        l_aux = buscaAllNaOrigemEquipe(a, t, reg_aux.nome_pais);
        qtd_aux = 0;
        p = l_aux;
        while(p) {
            qtd_aux++;
            p = p->prox;
        }
        if(qtd_aux > maior) {
            if(l) l = TLSECHAR_libera(l);
            l = TLSECHAR_insere(l, reg_aux.nome_pais);
            maior = qtd_aux;
        }
        else if(qtd_aux == maior) {
            l = TLSECHAR_insere(l, reg_aux.nome_pais);
        }
        l_aux = TLSETJ_libera(l_aux);
        i += sizeof(TSELE);
    }
    fclose(ftab);
    (*qtd) = maior;
    return l;
}

// Operação [12] - Alteração de algumas informações dos jogadores
void alteraPosicao(TARVBP *a, int t, int id, char *pos){
    if(!strcmp(pos, "GK")) return;
    if(!TARVBP_possui_elemento(a, id, t)) return;
    TARVBP *b = TARVBP_busca(a, id, t);
    int i = 0;
    while(i < b->num_chaves && b->reg[i]->id < id) i++;
    if(strcmp(b->reg[i]->pos, "GK")) {
        strcpy(b->reg[i]->pos, pos);
        escreveNo(b->nomeArq, b);
    }
    TARVBP_libera(b, t);
}

void alteraTime(TARVBP *a, int t, int id, char *time){
    if(!strcmp(time, "")) return;
    if(!TARVBP_possui_elemento(a, id, t)) return;
    TARVBP *b = TARVBP_busca(a, id, t);
    int i = 0;
    while(i < b->num_chaves && b->reg[i]->id < id) i++;
    strcpy(b->reg[i]->time, time);
    escreveNo(b->nomeArq, b);
    TARVBP_libera(b, t);
}

void alteraPaisTime(TARVBP *a, int t, int id, char *pais_time){
    if(!strcmp(pais_time, "")) return;
    if(!TARVBP_possui_elemento(a, id, t)) return;
    TARVBP *b = TARVBP_busca(a, id, t);
    int i = 0;
    while(i < b->num_chaves && b->reg[i]->id < id) i++;
    strcpy(b->reg[i]->pais_time, pais_time);
    escreveNo(b->nomeArq, b);
    TARVBP_libera(b, t);
}

void alteraGols(TARVBP *a, int t, int id, int gols){
    if(gols < 0) return;
    if(!TARVBP_possui_elemento(a, id, t)) return;
    TARVBP *b = TARVBP_busca(a, id, t);
    int i = 0;
    while(i < b->num_chaves && b->reg[i]->id < id) i++;
    b->reg[i]->num_gols = gols;
    escreveNo(b->nomeArq, b);
    TARVBP_libera(b, t);
}

void alteraNumero(TARVBP *a, int t, int id, int num){
    if(num < 1) return;
    if(!TARVBP_possui_elemento(a, id, t)) return;
    TARVBP *b = TARVBP_busca(a, id, t);
    int i = 0;
    while(i < b->num_chaves && b->reg[i]->id < id) i++;
    b->reg[i]->num = num;
    escreveNo(b->nomeArq, b);
    TARVBP_libera(b, t);
}

void alteraPartidas(TARVBP *a, int t, int id, int part){
    if(part < 0) return;
    if(!TARVBP_possui_elemento(a, id, t)) return;
    TARVBP *b = TARVBP_busca(a, id, t);
    int i = 0;
    while(i < b->num_chaves && b->reg[i]->id < id) i++;
    b->reg[i]->num_part = part;
    escreveNo(b->nomeArq, b);
    TARVBP_libera(b, t);
}

// Operação [13] - Busca todos os jogadores de uma seleção
TLSETJ* buscaAllJogadoresEquipe(TARVBP* a, int t, char* nome_pais) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    int ind = TABSELE_indiceEquipe(nome_pais), i;
    TLSETJ* l = TLSETJ_inicializa();
    TJ* jog_aux;
    TSELE reg_aux;
    
    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    for(i = 0; i < reg_aux.num_jogadores; i++) {
        jog_aux = TARVBP_buscaJogador(a, reg_aux.jogadores[i], t);
        l = TLSETJ_insere(l, jog_aux);
    }
    fclose(ftab);
    return l;
}

// Operação [14] - Busca do capitão de uma equipe
TJ* buscaCapitaoEquipe(TARVBP* a, int t, char* nome_pais) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    int ind = TABSELE_indiceEquipe(nome_pais), i;
    TJ* jog_aux = NULL;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    if(reg_aux.tem_capitao) jog_aux = TARVBP_buscaJogador(a, reg_aux.jogadores[reg_aux.ind_capitao], t);
    fclose(ftab);
    return jog_aux;
}

// Operação [14] - Busca de todos os capitães
TLSETJ* buscaAllCapitaes(TARVBP* a, int t) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);
    
    TLSETJ* l = TLSETJ_inicializa();
    TJ* jog_aux;
    TSELE reg_aux;
    int i = 0;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        jog_aux = buscaCapitaoEquipe(a, t, reg_aux.nome_pais);
        if(jog_aux) l = TLSETJ_insere(l, jog_aux);
        i += sizeof(TSELE);
    }
    fclose(ftab);
    return l;
}

// Operação [14] - Retira capitão de uma equipe
TARVBP* retiraCapitaoEquipe(TARVBP* a, int t, char* nome_pais) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    int ind = TABSELE_indiceEquipe(nome_pais), i;
    TJ* jog_aux = NULL;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    if(reg_aux.tem_capitao) {
        a = TARVBP_retira(a, reg_aux.jogadores[reg_aux.ind_capitao], t);
    }
    fclose(ftab);
    return a;
}

// Operação [14] - Retira todos os capitães
TARVBP* retiraAllCapitaes(TARVBP* a, int t) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    TSELE reg_aux;
    int i = 0;
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        a = retiraCapitaoEquipe(a, t, reg_aux.nome_pais);
        i += sizeof(TSELE);
    }
    fclose(ftab);
    return a;
}

// Operação [16] - Remoção de jogadores
// de uma equipe que atuam num determinado país
TARVBP* retiraAllEquipeAtuaPais(TARVBP* a, int t, char* nome_equipe, char* nome_pais) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    int ind = TABSELE_indiceEquipe(nome_equipe), i;
    TJ* jog_aux;
    TSELE reg_aux;
    
    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    for(i = 0; i < reg_aux.num_jogadores; i++) {
        jog_aux = TARVBP_buscaJogador(a, reg_aux.jogadores[i], t);
        if(!strcmp(nome_equipe, jog_aux->pais_time)) {
            a = TARVBP_retira(a, jog_aux->id, t);
        }
        free(jog_aux);
    }
    fclose(ftab);
    return a;
}

// Operação [17] - Retira todos
// de uma equipe que jogam na origem
TARVBP* retiraAllNaOrigem(TARVBP* a, int t, char* nome_pais) {
    FILE* ftab = fopen(TAB_SELECOES, "rb+");
    if(!ftab) exit(1);
    
    int ind = TABSELE_indiceEquipe(nome_pais), i;
    TJ* jog_aux;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    for(i = 0; i < reg_aux.num_jogadores; i++) {
        jog_aux = TARVBP_buscaJogador(a, reg_aux.jogadores[i], t);
        if(!strcmp(jog_aux->pais_time, nome_pais)) {
            a = TARVBP_retira(a, jog_aux->id, t);
        }
        free(jog_aux);
    }
    fclose(ftab);
    return a;
}

// Operação [18] - Retira todos de uma 
// equipe que jogam fora da origem
TARVBP* retiraAllForaOrigem(TARVBP* a, int t, char* nome_pais) {
    FILE* ftab = fopen(TAB_SELECOES, "rb+");
    if(!ftab) exit(1);
    
    int ind = TABSELE_indiceEquipe(nome_pais), i;
    TJ* jog_aux;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    for(i = 0; i < reg_aux.num_jogadores; i++) {
        printf("ID: %d\n", reg_aux.jogadores[i]);
        jog_aux = TARVBP_buscaJogador(a, reg_aux.jogadores[i], t);
        if(!jog_aux) printf("\nJogador não enccontrado!\n");
        if(strcmp(jog_aux->pais_time, nome_pais)) {
            a = TARVBP_retira(a, jog_aux->id, t);
        }
        free(jog_aux);
    }
    fclose(ftab);
    return a;
}

// Operação [19] - Retira todos 
// os jogadores de uma equipe
TARVBP* retiraAllEquipe(TARVBP* a, int t, char* nome_pais) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    int ind = TABSELE_indiceEquipe(nome_pais), i;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    for(i = 0; i < reg_aux.num_jogadores; i++) {
        a = TARVBP_retira(a, reg_aux.jogadores[i], t);
    }
    fclose(ftab);
    return a;
}

TJ **buscaJogadorAno(TARVBP *arv, int t, char *ano, int *tam){
    if(strlen(ano) > 4) return NULL;

    TJ **lista = NULL; int size = 0;
    for(int i = 1; i <= 12; i++){
        char s[11];
        if(i < 10){
            sprintf(s, "01/0%d/%s", i, ano);
        }else{
            sprintf(s, "01/%d/%s", i, ano);
        }

        int n = 0;
        TIJ **jogadores = TH_busca_mes_ano("hash.dat", "dados.dat", s, &n);
        size += n;
        if(jogadores) lista = realloc(lista, sizeof(TJ *) * size);
        for(int j = size-n; j < size; j++){
            lista[j] = TARVBP_buscaJogador(arv, jogadores[j-(size-n)]->id, t);
        }

        for(int f = 0; f < n; f++){
            free(jogadores[f]);
        }
        free(jogadores);
    }

    *tam = size;
    return lista;
}

TJ **buscaJogadorMes(TARVBP *arv, int t, char *mes, int *tam){
    if(strlen(mes) > 2) return NULL;
    int m = atoi(mes);
    TJ **lista = NULL; int size = 0;
    for(int i = 1977; i <= 2012; i++){
        char s[11];
        if(m < 10){
            sprintf(s, "01/0%d/%d", m, i);
        }else{
            sprintf(s, "01/%d/%d", m, i);
        }

        int n = 0;
        TIJ **jogadores = TH_busca_mes_ano("hash.dat", "dados.dat", s, &n);
        size += n;
        if(jogadores) lista = realloc(lista, sizeof(TJ *) * size);
        for(int j = size-n; j < size; j++){
            lista[j] = TARVBP_buscaJogador(arv, jogadores[j-(size-n)]->id, t);
        }

        for(int f = 0; f < n; f++){
            free(jogadores[f]);
        }
        free(jogadores);
    }

    *tam = size;
    return lista;
}

TJ *maisNovosPorEquipe(TARVBP *arv, int t, char *pais){
    TLSETJ *l = buscaAllJogadoresEquipe(arv, t, pais);
    
    TJ *menor = NULL;
    for(TLSETJ *i = l; i != NULL; i = i->prox) {
        if(!menor){
            menor = TJ_copiaJogador(i->jogador);
        }

        if(datacmp(menor->data_nasc, i->jogador->data_nasc) < 0){
            free(menor);
            menor = TJ_copiaJogador(i->jogador);
        }
    }
    TLSETJ_libera(l);
    return menor;
}

TJ *maisVelhosPorEquipe(TARVBP *arv, int t, char *pais){
    TLSETJ *l = buscaAllJogadoresEquipe(arv, t, pais);
    
    TJ *menor = NULL;
    for(TLSETJ *i = l; i != NULL; i = i->prox) {
        if(!menor){
            menor = TJ_copiaJogador(i->jogador);
        }

        if(datacmp(menor->data_nasc, i->jogador->data_nasc) > 0){
            free(menor);
            menor = TJ_copiaJogador(i->jogador);
        }
    }
    TLSETJ_libera(l);
    return menor;
}

TJ *maisNovo(TARVBP *arv, int t){
    char paises[11][12] = {"Germany", "Scotland", "Croatia", "Albania", "Slovenia", "Denmark", "Netherlands", "France", "Ukraine", "Georgia", "Portugal"};
    TJ *menor = NULL;
    for(int i = 0; i < 11; i++){
        if(!menor) menor = maisNovosPorEquipe(arv, t, paises[i]);

        TJ *temp = maisNovosPorEquipe(arv, t, paises[i]);
        if(datacmp(menor->data_nasc, temp->data_nasc) < 0){
            free(menor);
            menor = temp;
        }else{
            free(temp);
        }
    }
    return menor;
}

TJ *maisVelho(TARVBP *arv, int t){
    char paises[11][12] = {"Germany", "Scotland", "Croatia", "Albania", "Slovenia", "Denmark", "Netherlands", "France", "Ukraine", "Georgia", "Portugal"};
    TJ *menor = NULL;
    for(int i = 0; i < 11; i++){
        if(!menor) menor = maisVelhosPorEquipe(arv, t, paises[i]);

        TJ *temp = maisVelhosPorEquipe(arv, t, paises[i]);
        if(datacmp(menor->data_nasc, temp->data_nasc) > 0){
            free(menor);
            menor = temp;
        }else{
            free(temp);
        }
    }
    return menor;
}

// Operação [20] - Retira jogadores dado um 
// vetor de suas chaves primárias
TARVBP *retiraIds(TARVBP *arv, int t, int *vet, int n){
    for(int i = 0; i < n; i++){
        arv = TARVBP_retira(arv, vet[i], t);
    }
    return arv;
}