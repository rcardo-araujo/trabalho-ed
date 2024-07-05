#include "../headers/includes.h"
#include <limits.h>

// Operação [2]
void menosAtuaramEquipes() {
    FILE* ftab  = fopen(tab_selecoes, "rb");
    if(!ftab) exit(1);
    fseek(ftab, 0L, SEEK_END);
    int tam_arq = ftell(ftab);

    int menor, i = 0;
    TSELE reg_aux;
    while(i < tam_arq) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);

    }
}

// Operação [4]
char* maiorSelecao(void) {
    FILE* ftab = fopen(tab_selecoes, "rb");
    if(!ftab) exit(1);
    fseek(ftab, 0L, SEEK_END);
    int tam_arq = ftell(ftab);
    
    int maior = INT_MIN, i = 0, qtd_aux;
    char* maior_pais = (char*)malloc(sizeof(char) * 12);
    TSELE reg_aux;
    while(i < tam_arq) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        qtd_aux = (reg_aux.tem_capitao) ? 1 : 0;
        qtd_aux += reg_aux.num_jogadores;
        if(qtd_aux > maior) {
            maior = qtd_aux;
            strcpy(maior_pais, reg_aux.nome);
        }
        i += sizeof(TSELE);
    }
    fclose(ftab);
    return maior_pais;
}

// Operação [6]
TJ** buscaAllJogadoresNaOrigem(TARVBP* a, int t, int* tam) {

}

// Operação [13] 
TJ** buscaAllJogadoresSelecao(TARVBP* a, int t, int* tam, char* nome_pais) {
    FILE* ftab = fopen(tab_selecoes, "rb+");
    if(!ftab) exit(1);
    fseek(ftab, 0L, SEEK_END);
    int tam_arq = ftell(ftab);

    int ind = indSelecao(ftab, nome_pais), i;
    TSELE reg_aux;
    TARVBP* no_aux;
    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    
    (*tam) = (reg_aux.tem_capitao) ? 1 : 0;
    (*tam) += reg_aux.num_jogadores;
    if(!(*tam)) return NULL;
    TJ** vet = (TJ**)malloc(sizeof(TJ*) * (*tam));
    for(i = 0; i < (*tam); i++) vet[i] = (TJ*)malloc(sizeof(TJ));

    if(reg_aux.tem_capitao) {
        no_aux = TARVBP_busca(a, reg_aux.id_capitao, t);
        vet[0] = buscaJogador(no_aux, reg_aux.id_capitao);
    }
    for(i = 0; i < reg_aux.num_jogadores; i++) {
        no_aux = TARVBP_busca(a, reg_aux.jogadores[i], t);
        vet[(!reg_aux.tem_capitao) ? i : i + 1] = buscaJogador(no_aux, reg_aux.jogadores[i]);
    }

    fclose(ftab);
    return vet;
}

// Função auxiliar -> Operação [14]
int qtdCapitaes() {
    FILE* ftab = fopen(tab_selecoes, "rb+");
    if(!ftab) exit(1);
    fseek(ftab, 0L, SEEK_END);
    int tam_arq = ftell(ftab);

    int qtd = 0, i = 0;
    TSELE reg_aux;
    while(i < tam_arq) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        if(reg_aux.tem_capitao) qtd++;
        i += sizeof(TSELE);
    }
    return qtd;
}

// Operação [14] - Busca dos capitães
TJ** buscaAllCapitaes(TARVBP* a, int t, int* tam) {
    FILE* ftab = fopen(tab_selecoes, "rb+");
    if(!ftab) exit(1);
    fseek(ftab, 0L, SEEK_END);
    int tam_arq = ftell(ftab), i, j;

    (*tam) = qtdCapitaes();
    if(!(*tam)) return NULL;
    TJ** vet = (TJ**)malloc(sizeof(TJ*) * (*tam));
    for(i = 0; i < (*tam); i++) vet[i] = (TJ*)malloc(sizeof(TJ));

    i = 0, j = 0;
    TSELE reg_aux;
    TARVBP* no_aux;
    while(i < tam_arq) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        if(reg_aux.tem_capitao) {
            (*tam)++;
            no_aux = TARVBP_busca(a, reg_aux.id_capitao, t);
            vet[j++] = buscaJogador(no_aux, reg_aux.id_capitao);
        }
        i += sizeof(TSELE);
    }
    fclose(ftab);
    return vet;
}

// Operação [14] - Remoção dos capitães
TARVBP* retiraAllCapitaes(TARVBP* a, int t) {
    FILE* ftab = fopen(tab_selecoes, "rb+");
    if(!ftab) exit(1);
    fseek(ftab, 0L, SEEK_END);
    int tam_arq = ftell(ftab);

    int i = 0;
    TSELE reg_aux;
    while(i < tam_arq) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        if(reg_aux.tem_capitao) a = TARVBP_retira(a, reg_aux.id_capitao, t);
        i += sizeof(TSELE);
    }
    fclose(ftab);
    return a;
}

// Operação [17]
TARVBP* retiraAllNaOrigem(TARVBP* a, int t, char* nome_pais) {
    FILE* ftab = fopen(tab_selecoes, "rb+");
    if(!ftab) exit(1);
    
    int ind = indSelecao(ftab, nome_pais), i;
    TJ* jogador_aux;
    TARVBP* no_aux;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    if(reg_aux.tem_capitao) {
        no_aux = TARVBP_busca(a, reg_aux.id_capitao, t);
        jogador_aux = buscaJogador(no_aux, reg_aux.id_capitao);
        if(!strcmp(jogador_aux->pais_time, nome_pais)) a = TARVBP_retira(a, reg_aux.id_capitao, t);
    }
    if(reg_aux.num_jogadores) {
        for(i = 0; i < reg_aux.num_jogadores; i++) {
            no_aux = TARVBP_busca(a, reg_aux.jogadores[i], t);
            jogador_aux = buscaJogador(no_aux, reg_aux.jogadores[i]);
            if(!strcmp(jogador_aux->pais_time, nome_pais)) a = TARVBP_retira(a, reg_aux.jogadores[i], t);
        }
    }
    fclose(ftab);
    return a;
}

// Operação [18]
TARVBP* retiraAllForaOrigem(TARVBP* a, int t, char* nome_pais) {
    FILE* ftab = fopen(tab_selecoes, "rb+");
    if(!ftab) exit(1);
    
    int ind = indSelecao(ftab, nome_pais), i;
    TJ* jogador_aux;
    TARVBP* no_aux;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    if(reg_aux.tem_capitao) {
        no_aux = TARVBP_busca(a, reg_aux.id_capitao, t);
        jogador_aux = buscaJogador(no_aux, reg_aux.id_capitao);
        if(strcmp(jogador_aux->pais_time, nome_pais)) a = TARVBP_retira(a, reg_aux.id_capitao, t);
    }
    if(reg_aux.num_jogadores) {
        for(i = 0; i < reg_aux.num_jogadores; i++) {
            no_aux = TARVBP_busca(a, reg_aux.jogadores[i], t);
            jogador_aux = buscaJogador(no_aux, reg_aux.jogadores[i]);
            if(strcmp(jogador_aux->pais_time, nome_pais)) a = TARVBP_retira(a, reg_aux.jogadores[i], t);
        }
    }
    fclose(ftab);
    return a;
}

// Operação [19]
TARVBP* retiraAllSelecao(TARVBP* a, int t, char* nome_pais) {
    FILE* ftab = fopen(tab_selecoes, "rb+");
    if(!ftab) exit(1);

    int ind = indSelecao(ftab, nome_pais), i;
    TSELE reg_aux;

    fseek(ftab, ind, SEEK_SET);
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    if(reg_aux.tem_capitao) a = TARVBP_retira(a, reg_aux.id_capitao, t);
    if(reg_aux.num_jogadores) {
        for(i = 0; i < reg_aux.num_jogadores; i++) {
            a = TARVBP_retira(a, reg_aux.jogadores[i], t);
        }
    }
    fclose(ftab);
    return a;
}
