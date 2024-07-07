#include "../headers/includes.h"

const char* TAB_SELECOES = "tabelas/tab_selecoes.bin";
const int TAM_TABSELE = (sizeof(TSELE)) * 11;

int TABSELE_tam() {
    return TAM_TABSELE;
}

void TABSELE_inicializa(void) {
    FILE* ftab = fopen(TAB_SELECOES, "wb");
    printf("%s", TAB_SELECOES);
    if(!ftab) {
        printf("Nao foi possivel abrir arquivo em tab_selecao->inicializa\n");
        exit(1);
    }
    fclose(ftab);
}

int indSelecao(FILE* ftab, char* nome_pais) {
    int i = 0;
    TSELE reg_aux;
    while(i < TABSELE_tam()) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);
        if(!strncmp(nome_pais, reg_aux.nome_pais, 3)) {
            return i;
        }
        i += sizeof(TSELE);
    }
    return -1;
}

int existeSelecao(FILE* ftab, char* nome_pais) {
    if(indSelecao(ftab, nome_pais) != -1) return 1;
    return 0;
}

int existeJogador(FILE* ftab, TJ* jogador) {
    if(!existeSelecao(ftab, jogador->pais)) return 0;
    int ind_sele = indSelecao(ftab, jogador->pais), i;
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

TSELE* TABSELE_criaReg(char* nome_pais) {
    TSELE* novo = (TSELE*)malloc(sizeof(TSELE));
    strncpy(novo->nome_pais, nome_pais, 12);
    novo->tem_capitao = 0;
    novo->ind_capitao = 0;
    novo->num_jogadores = 0;
    return novo;
}

void TABSELE_adicionaJogador(TJ* jogador) {
    FILE* ftab = fopen(TAB_SELECOES, "rb+");
    if(!ftab) exit(1);
    
    if(existeJogador(ftab, jogador)) {
        fclose(ftab);
        return;
    }
    if(!existeSelecao(ftab, jogador->pais)) {
        TSELE* novo = TABSELE_criaReg(jogador->pais);
        fseek(ftab, 0L, SEEK_END);
        novo->num_jogadores = 1;
        novo->jogadores[0] = jogador->id;
        if(jogador->capitao) {
            novo->tem_capitao = 1;
            novo->ind_capitao = 0;
        }
        fwrite(novo, sizeof(TSELE), 1, ftab);
        free(novo);
    }
    else {
        int ind_sele = indSelecao(ftab, jogador->pais);
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
        int ind_sele = indSelecao(ftab, jogador->pais), i, j;
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

void TABSELE_imprimeTabela(void) {
    FILE* ftab = fopen(TAB_SELECOES, "rb");
    if(!ftab) {
        printf("Nao foi possivel abrir arquivo em tab_selecao->imprimeTabela\n");
        exit(1);
    }

    fseek(ftab, 0L, SEEK_END);
    int tam_arq = ftell(ftab), i = 0, j;
    TSELE reg_aux;

    printf("\n@@@ Tabela de Selecoes @@@\n");
    while(i < tam_arq) {
        fseek(ftab, i, SEEK_SET);
        fread(&reg_aux, sizeof(TSELE), 1, ftab);

        printf("\n-------------------------\n");
        printf("%s\n", reg_aux.nome_pais);
        printf("Tem capitao?: %s\n", (reg_aux.tem_capitao) ? "Sim" : "Nao");
        if(reg_aux.tem_capitao) printf("ID do capitao: %d\n", reg_aux.jogadores[reg_aux.ind_capitao]);
        printf("Numero de jogadores: %d\n", reg_aux.num_jogadores);
        if(reg_aux.num_jogadores) {
            printf("IDs dos jogadores: ");
            for(j = 0; j < reg_aux.num_jogadores; j++) {
                printf("%d ", reg_aux.jogadores[j]);
            }
            printf("\n");
        }
        printf("-------------------------\n");
        i += sizeof(TSELE);
    }
    fclose(ftab);
}
