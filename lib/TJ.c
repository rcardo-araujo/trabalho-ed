/**
 * @file TJ.c
 * @brief Implementação das funções relacionadas ao TJ
 */

#include "../headers/includes.h"

int capitao(char* nome) {
    return strstr(nome, "(captain)") != NULL; 
}

/**
 * @brief Retorna uma estrutura com as informações do jogador carregadas de um arquivo
 * @param fp Ponteiro para o arquivo
 * @param selecao Nome da seleção do jogador
 * @return Ponteiro para estrutura do jogador @c TJ
 */
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
    j->capitao = capitao(j->nome);
    if (j->capitao) {
        char* pos = strstr(j->nome, " (captain)");
        if(pos) *pos = '\0';
    }
    fscanf(fp, "%c", &c);
    fscanf(fp, "%s", dia);
    fscanf(fp, "%s", mes);
    fscanf(fp, "%s", ano);
    converteDia(dia);
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
    fscanf(fp, "%24[^\n\r]", j->time);
    fscanf(fp, "%c", &c);
    fscanf(fp, "%c", &c);
    return j;
}

/**
 * @brief Imprime o jogador
 * @param j Jogador
 */
void imprimeJogador(TJ *j){
    if(!j) return;
    printf("\n------Jogador------\n");
    printf("id: %d\nnum: %d \npos: %s\nnome: %s\nnasc: %s\nnum_part: %d\nnum_gols: %d\npais_time: %s\ntime: %s\npais: %s\n",
    j->id, j->num, j->pos, j->nome, j->data_nasc, j->num_part, j->num_gols, j->pais_time, j->time, j->pais);
    printf("-------------------\n");
}

/**
 * @brief Le uma linha do arquivo e verifica se leu uma seleção
 * @param fp Ponteiro para o arquivo
 * @return 0 se não for seleção ou 1 se for seleção
 */
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

TJ *TJ_copiaJogador(TJ *j){
    TJ *novo = malloc(sizeof(TJ));
    
    novo->id = j->id;            
    novo->num = j->num;
    strcpy(novo->pos, j->pos);
    strcpy(novo->nome, j->nome);  
    novo->capitao = j->capitao;
    strcpy(novo->data_nasc, j->data_nasc);
    novo->num_part = j->num_part;
    novo->num_gols = j->num_gols;
    strcpy(novo->pais_time, j->pais_time);
    strcpy(novo->time, j->time);
    strcpy(novo->pais, j->pais);

    return novo;
}