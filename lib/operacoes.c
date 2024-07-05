#include "../headers/includes.h"

TARVBP *BuscaJogadorMaisNovo_1(TARVBP *arv, int t){
    TIJ *menor = NULL;
    int c = 0;
    for(int i = 2012; i > 1983; i--){
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
