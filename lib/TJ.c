#include "../headers/includes.h"

int capitao(char* nome) {
    return strstr(nome, "(captain)") != NULL; 
}

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

void imprimeJogador(TJ *j){
    printf("------Jogador------\n");
    printf("id: %d\nnum: %d \npos: %s\nnome: %s\nnasc: %s\nnum_part: %d\nnum_gols: %d\npais_time: %s\ntime: %s\npais: %s\n",
    j->id, j->num, j->pos, j->nome, j->data_nasc, j->num_part, j->num_gols, j->pais_time, j->time, j->pais);
    printf("-------------------\n");
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
