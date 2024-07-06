#include "../headers/includes.h"

TARVBP *BuscaJogadorMaisNovo_1(TARVBP *arv, int t){
    TIJ *menor = NULL;
    int c = 0;
    for(int i = 2012; i >= 1977; i--){
        if(c) break;
        for(int j = 12; j >= 1; j--){
            if(c) break;
            char s[11];
            if(j < 10){
                sprintf(s, "01/0%d/%d", j, i);
            }else{
                sprintf(s, "01/%d/%d", j, i);
            }
            int tam = 0;
            TIJ **v = TH_busca_mes_ano("hash.dat", "dados.dat", s, &tam);
            if(v){
                menor = v[0];
                c = 1;
            }

            for(int f = !c ? 0 : 1; f < tam; f++){
                free(v[f]);
            }
            free(v);
        }
    }

    TARVBP *b = TARVBP_busca(arv, menor->id, t);
    free(menor);
    return b;
}

TARVBP *BuscaJogadorMaisVelho_2(TARVBP *arv, int t){
    TIJ *maior = NULL;
    int c = 0;
    for(int i = 1977; i <= 2012; i++){
        if(c) break;
        for(int j = 1; j <= 12; j++){
            if(c) break;
            char s[11];
            if(j < 10){
                sprintf(s, "01/0%d/%d", j, i);
            }else{
                sprintf(s, "01/%d/%d", j, i);
            }
            int tam = 0;
            TIJ **v = TH_busca_mes_ano("hash.dat", "dados.dat", s, &tam);
            if(v){
                maior = v[0];
                c = 1;
            }

            for(int f = !c ? tam-1 : tam-2; f >= 0; f--){
                free(v[f]);
            }
            free(v);
        }
    }

    TARVBP *b = TARVBP_busca(arv, maior->id, t);
    free(maior);
    return b;
}

TARVBP **BuscaJogadoresPorAno_7(TARVBP *arv, int t, char *ano, int *tam){
    if(strlen(ano) > 4) return NULL;

    TARVBP **lista = NULL; int size = 0;
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
        if(jogadores) lista = realloc(lista, sizeof(TARVBP *) * size);
        for(int j = size-n; j < size; j++){
            int a = j-(size-n);
            lista[j] = TARVBP_busca(arv, jogadores[j-(size-n)]->id, t);
        }

        for(int f = 0; f < n; f++){
            free(jogadores[f]);
        }
        free(jogadores);
    }

    *tam = size;
    return lista;
}

TARVBP **BuscaJogadoresPorMes_8(TARVBP *arv, int t, char *mes, int *tam){
    if(strlen(mes) > 2) return NULL;

    TARVBP **lista = NULL; int size = 0;
    for(int i = 1992; i <= 2012; i++){
        char s[11];
        if(i < 10){
            sprintf(s, "01/%s/%d", mes, i);
        }else{
            sprintf(s, "01/%s/%d", mes, i);
        }

        int n = 0;
        TIJ **jogadores = TH_busca_mes_ano("hash.dat", "dados.dat", s, &n);
        size += n;
        if(jogadores) lista = realloc(lista, sizeof(TARVBP *) * size);
        for(int j = size-n; j < size; j++){
            int a = j-(size-n);
            lista[j] = TARVBP_busca(arv, jogadores[j-(size-n)]->id, t);
        }

        for(int f = 0; f < n; f++){
            free(jogadores[f]);
        }
        free(jogadores);
    }

    *tam = size;
    return lista;
}