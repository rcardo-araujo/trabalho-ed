#ifndef TLSE_CHAR_H
#define TLSE_CHAR_H

typedef struct lse_char {
    char nome_pais[12];
    struct lse_char* prox;
} TLSECHAR;

TLSECHAR* TLSECHAR_inicializa(void);
TLSECHAR* TLSECHAR_insere(TLSECHAR* l, char* nome_pais);
TLSECHAR* TLSECHAR_libera(TLSECHAR* l);
void TLSECHAR_imprime(TLSECHAR* l);

#endif
