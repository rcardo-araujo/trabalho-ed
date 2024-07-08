#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/TABSELE.h"

const char* TAB_SELECOES = "tabelas/tabela_selecoes.bin";
const int QTD_EQUIPES = 11;
const int TAM_TABSELE = (sizeof(TSELE)) * QTD_EQUIPES;
const char EQUIPES[11][12] = {"Germany", "Scotland", "Croatia", "Albania", "Slovenia", "Denmark", "Netherlands", "France", "Ukraine", "Georgia", "Portugal"};

int TABSELE_indiceEquipe(char* nome_pais) {
    int i;
    for(i = 0; i < QTD_EQUIPES; i++) {
        if(!strcmp(nome_pais, EQUIPES[i])) {
            return i * sizeof(TSELE);
        }
    }
    return -1;
}

int existeEquipe(char* nome_pais) {
    if(TABSELE_indiceEquipe(nome_pais) != -1) return 1;
    return 0;
}

int existeJogador(FILE* ftab, TJ* jogador) {
    if(!existeEquipe(jogador->pais)) return 0;
    int ind_sele = TABSELE_indiceEquipe(jogador->pais), i;
    fseek(ftab, ind_sele, SEEK_SET);

    TSELE reg_aux;
    fread(&reg_aux, sizeof(TSELE), 1, ftab);
    if(reg_aux.num_jogadores) {
        for(i = 0; i < reg_aux.num_jogadores; i++) {
            if(reg_aux.jogadores[i] == jogador->id) return 1;
        }
    }
    return 0;
}

TSELE* TABSELE_criaReg(const char* nome_pais) {
    TSELE* novo = (TSELE*)malloc(sizeof(TSELE));
    strncpy(novo->nome_pais, nome_pais, 12);
    novo->tem_capitao = 0;
    novo->ind_capitao = 0;
    novo->num_jogadores = 0;
    return novo;
}

void TABSELE_inicializa(void) {
    FILE* ftab = fopen(TAB_SELECOES, "wb");
    if(!ftab) exit(1);

    int i;
    TSELE* reg;
    for(i = 0; i < QTD_EQUIPES; i++) {
        reg = TABSELE_criaReg(EQUIPES[i]);
        fseek(ftab, i * sizeof(TSELE), SEEK_SET);
        fwrite(reg, sizeof(TSELE), 1, ftab);
        free(reg);
    }
    fclose(ftab);
}

void TABSELE_adicionaJogador(TJ* jogador) {
    FILE* ftab = fopen(TAB_SELECOES, "rb+");
    if(!ftab) exit(1);
    
    if(existeJogador(ftab, jogador)) {
        fclose(ftab);
        return;
    }
    else {
        int ind_sele = TABSELE_indiceEquipe(jogador->pais);
        TSELE reg_aux;
        fseek(ftab, ind_sele, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        
        if(jogador->capitao) {
            reg_aux.tem_capitao = 1;
            reg_aux.ind_capitao = reg_aux.num_jogadores;
        }
        reg_aux.jogadores[reg_aux.num_jogadores++] = jogador->id;
        fseek(ftab, ind_sele, SEEK_SET);
        fwrite(&reg_aux, sizeof(TSELE), 1, ftab);
    }
    fclose(ftab);
}

void TABSELE_removeJogador(TJ* jogador) {
    FILE* ftab = fopen(TAB_SELECOES, "rb+");
    if(!ftab) return;

    if(existeJogador(ftab, jogador)) {
        TSELE reg_aux;
        int ind_sele = TABSELE_indiceEquipe(jogador->pais), i, j;
        fseek(ftab, ind_sele, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);

        for(i = 0; i < reg_aux.num_jogadores; i++) {
            if(jogador->id == reg_aux.jogadores[i]) {
                reg_aux.num_jogadores--;
                for(j = i; j < reg_aux.num_jogadores; j++)
                    reg_aux.jogadores[j] = reg_aux.jogadores[j + 1];
                if(jogador->capitao) reg_aux.tem_capitao = 0;
                fseek(ftab, ind_sele, SEEK_SET);
                fwrite(&reg_aux, sizeof(TSELE), 1, ftab);
                break;
            }
        }
    }
    fclose(ftab);
}

void TABSELE_alteraCapitao(TJ* jogador, int novoCapitao) {
    FILE* ftab = fopen(TAB_SELECOES, "rb+");
    if(!ftab) exit(1);

    if(existeJogador(ftab, jogador)) {
        int ind_e = TABSELE_indiceEquipe(jogador->pais), i;
        TSELE reg_aux;
        fseek(ftab, ind_e, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);

        if((!novoCapitao) && (jogador->id == reg_aux.jogadores[reg_aux.ind_capitao])) {
            reg_aux.tem_capitao = 0;
        }
        else if((novoCapitao) && (jogador->id != reg_aux.jogadores[reg_aux.ind_capitao])) {
            if(!reg_aux.tem_capitao) reg_aux.tem_capitao = 1;
            for(i = 0; i < reg_aux.num_jogadores; i++) {
                if(jogador->id == reg_aux.jogadores[i]) {
                    reg_aux.ind_capitao = i;
                    break;
                }
            }
        }
        fseek(ftab, ind_e, SEEK_SET);
        fwrite(&reg_aux, sizeof(TSELE), 1, ftab);
    }
    fclose(ftab);
}

void TABSELE_imprime(void) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) exit(1);

    int i = 0, j;
    TSELE reg_aux;
    printf("\n*********** Tabela de Seleções ***********\n");
    while(i < TAM_TABSELE) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);

        printf("\n------------- %s -------------\n", reg_aux.nome_pais);
        printf("Tem capitão?: %s\n", (reg_aux.tem_capitao) ? "Sim" : "Não");
        if(reg_aux.tem_capitao) printf("ID do capitão: %d\n", reg_aux.jogadores[reg_aux.ind_capitao]);
        printf("Número de jogadores: %d\n", reg_aux.num_jogadores);
        if(reg_aux.num_jogadores) {
            printf("IDs dos jogadores: ");
            for(j = 0; j < reg_aux.num_jogadores; j++) {
                printf("%d ", reg_aux.jogadores[j]);
            }
            printf("\n");
        }
        printf("---------------------------------------\n");
        i += sizeof(TSELE);
    }
    printf("\n******************************************\n");
    fclose(ftab);
}
