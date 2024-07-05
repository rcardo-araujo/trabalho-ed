#include "../headers/includes.h"

/**
 * @file utils.c
 * @brief   Biblioteca que vamos compor para uma série de utilidades que não
            estão diretamente relacionadas à criação das tabelas e estruturas
            de dados do trabalho. 
*/

void readLine(FILE *fp, char *string, int *size, char splitter){
    int i = 0, x;
    char c;
    while(i < 40){
        x = fread(&c, sizeof(char), 1, fp);
        if((c == splitter) || (x != 1)){
            string[i] = '\0';
            break;
        }
        string[i] = c;
        i++;
    }
    (*size) = i;
}

char *converteMes(char *str){
    if(!strcmp(str, "January")) return "01";
    if(!strcmp(str, "February")) return "02";
    if(!strcmp(str, "March")) return "03";
    if(!strcmp(str, "April")) return "04";
    if(!strcmp(str, "May")) return "05";
    if(!strcmp(str, "June")) return "06";
    if(!strcmp(str, "July")) return "07";
    if(!strcmp(str, "August")) return "08";
    if(!strcmp(str, "September")) return "09";
    if(!strcmp(str, "October")) return "10";
    if(!strcmp(str, "November")) return "11";
    if(!strcmp(str, "December")) return "12";
}

void criaData(char *destino, char *dia, char *meses, char *ano){
    destino = strcpy(destino, strcat(dia, "/"));
    strcat(meses, "/");
    strcat(destino, meses);
    strcat(destino, ano);
}
