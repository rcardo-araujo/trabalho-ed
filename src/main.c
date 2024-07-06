#include "../headers/includes.h"
#include <locale.h>

<<<<<<< HEAD
TARVBP* catalogo2Arv(char *nomeArq, int t){
    TARVBP *a = TARVBP_cria(nomeArq, t);
    FILE *fp = fopen("catalogo.txt", "r");
    char selecao[40];
    int size;
    TJ *j;
    int i = 284;
    while(i > 0){
        if(verificaSelecao(fp)){
            readLine(fp, selecao, &size, '\n');
        } else {
            j = leJogador(fp, selecao);
            a = TARVBP_insere(a, j, t);
            i--;
        }
    }
    return a;
}

void menu(TARVBP* a, int t) {
    do {
        printf("\n-----------Menu-------------\n");
        printf("Selecione a opcao desejada: \n");
        printf("[2] Jogadores que mais e menos atuaram por equipe\n");
        printf("[3] Jogadores que mais e menos atuaram no total\n");
        printf("[4] Seleções com mais e menos convocações no total\n");
        printf("[5] Buscar jogadores que atuam fora da origem\n");
        printf("[6] Buscar jogadores que atuam na origem\n");
        printf("[9] Equipes com mais jogadores atuando fora da origem\n");
        printf("[10] Equipes com mais jogadores atuando na origem\n");
        printf("[11] Buscar jogador\n");
        printf("[13] Buscar todos os jogadores de uma equipe\n");
        printf("[14] Buscar ou remover os capitães\n");
        printf("[17] Remover todos os jogadores de uma equipe que jogam na origem\n");
        printf("[18] Remover todos os jogadores de uma equipe que não jogam na origem\n");
        printf("[19] Remover todos os jogadores de uma equipe\n");
        printf("\n[0] Imprimir IDs da árvore\n");
        printf("[-1] Sair\n");
        printf("------------------------------\n");
        printf("\nDigite a opcao desejada: ");

        int opcao, qtd;
        char nome_equipe[12];
        scanf("%d", &opcao);
        // [-1] Voltar do menu
        if(opcao == -1) return;
        
        // [0] Imprimir IDs da árvore
        if(opcao == 0) {
            TARVBP_imprime(a, t);
            continue;
        }
        
        // [2] Jogadores que mais e menos atuaram por equipe
        if(opcao == 2) {
            printf("\n[1] Jogadores que mais atuaram em equipe específica\n");
            printf("[2] Jogadores que menos atuaram em equipe específica\n");
            printf("[3] Jogadores que menos atuaram em cada equipe\n");
            printf("\nDigite a opcao desejada: ");
            scanf("%d", &opcao);
            if(opcao == 1) {
                printf("\nDigite o país desejado: ");
                scanf(" %11[^\n]", nome_equipe);
                TLSETJ* l = maisAtuaramEquipe(a, t, nome_equipe);
                if(!l) {
                    printf("\nBase de dados OU seleção vazia!\n");
                    continue;
                }

                printf("\nJogadores que mais atuaram em %s", nome_equipe);
                printf("\n*****************************************\n");
                TLSETJ_imprime(l);
                printf("\n*****************************************\n");
                TLSETJ_libera(l);
                continue;
            }
            if(opcao == 2) {
                printf("\nDigite o país desejado: ");
                scanf(" %11[^\n]", nome_equipe);
                TLSETJ* l = menosAtuaramEquipe(a, t, nome_equipe);
                if(!l) {
                    printf("\nBase de dados OU seleção vazia!\n");
                    continue;
                }

                printf("\nJogadores que menos atuaram em %s", nome_equipe);
                printf("\n*****************************************\n");
                TLSETJ_imprime(l);
                printf("\n*****************************************\n");
                TLSETJ_libera(l);
                continue;
            }
            printf("Opcao invalida!\n");
            continue;
        }

        // [3] Jogadores que mais e menos atuaram no total
        if(opcao == 3) {
            printf("\n[1] Jogadores que mais atuaram\n");
            printf("[2] Jogadores que menos atuaram\n");
            printf("\nDigite a opcao desejada: ");
            scanf("%d", &opcao);
            if(opcao == 1) {
                TLSETJ* l = maisAtuaramTotal(a, t);
                if(!l) {
                    printf("\nBase de dados vazia!\n");
                    continue;
                }

                printf("\nJogadores que mais atuaram no total");
                printf("\n*************************************\n");
                TLSETJ_imprime(l);
                printf("\n*************************************\n");
                TLSETJ_libera(l);
                continue;
            }
            if(opcao == 2) {
                TLSETJ* l = menosAtuaramTotal(a, t);
                if(!l) {
                    printf("\nBase de dados vazia!\n");
                    continue;
                }

                printf("\nJogadores que menos atuaram no total");
                printf("\n*************************************\n");
                TLSETJ_imprime(l);
                printf("\n*************************************\n");
                TLSETJ_libera(l);
                continue;
            }
            printf("Opcao invalida!\n");
            continue;
        }

        // [04] Maior e menor selecao
        if(opcao == 4) {
            printf("\n[1] Maior seleção (mais convocados)\n");
            printf("[2] Menor seleção (menos convocados)\n");
            printf("\nDigite a opção desejada: ");
            scanf("%d", &opcao);
            if(opcao == 1) {
                qtd = 0;
                TLSECHAR* l = maioresEquipes(&qtd);
                if(!l) {
                    printf("\nBase de dados vazia!\n");
                    continue;
                }
                
                printf("\nMaiores seleções (%d convocados)", qtd);
                printf("\n*************************************\n");
                TLSECHAR_imprime(l);
                printf("\n*************************************\n");
                TLSECHAR_libera(l);
                continue;
            }
            if(opcao == 2) {
                qtd = 0;
                TLSECHAR* l = menoresEquipes(&qtd);
                if(!l) {
                    printf("\nBase de dados vazia!\n");
                    continue;
                }
                
                printf("\nMenores seleções (%d convocados)", qtd);
                printf("\n*************************************\n");
                TLSECHAR_imprime(l);
                printf("\n*************************************\n");
                TLSECHAR_libera(l);
                continue;
            }
            printf("Opção inválida!\n");
            continue;
        }

        // [05] Jogadores que atuam fora da origem
        if(opcao == 5) {
            printf("\n[1] Buscar todos de uma equipe\n");
            printf("[2] Buscar todos os jogadores\n");
            printf("\nDigite a opcao desejada: ");
            scanf("%d", &opcao);
            if(opcao == 1) {
                printf("\nDigite a equipe desejada: ");
                scanf(" %11[^\n]", nome_equipe);
                TLSETJ* l = buscaAllForaOrigemEquipe(a, t, nome_equipe);
                if(!l) {
                    printf("\nNenhum jogador dessa seleção atua fora da origem!\n");
                    continue;
                }

                printf("\nJogadores de %s que não atuam na origem\n", nome_equipe);
                printf("********************************************************\n");
                TLSETJ_imprime(l);
                printf("\n********************************************************\n");
                TLSETJ_libera(l);
                continue;
            }
            if(opcao == 2) {
                TLSETJ* l = buscaAllForaOrigem(a, t);
                if(!l) {
                    printf("\nNenhum jogador atua fora da origem!\n");
                    continue;
                }

                printf("\nJogadores que não atuam na origem\n");
                printf("***********************************\n");
                TLSETJ_imprime(l);
                printf("\n*********************************\n");
                TLSETJ_libera(l);
                continue;
            }
            printf("\nOpção inválida!\n");
            continue;
        }

        // [06] Jogadores que atuam na origem
        if(opcao == 6) {
            printf("\n[1] Buscar todos de uma equipe\n");
            printf("[2] Buscar todos os jogadores\n");
            printf("\nDigite a opcao desejada: ");
            scanf("%d", &opcao);
            if(opcao == 1) {
                printf("\nDigite a equipe desejada: ");
                scanf(" %11[^\n]", nome_equipe);
                TLSETJ* l = buscaAllNaOrigemEquipe(a, t, nome_equipe);
                if(!l) {
                    printf("\nNenhum jogador dessa seleção atua na origem!\n");
                    continue;
                }

                printf("\nJogadores de %s que atuam na origem\n", nome_equipe);
                printf("********************************************************\n");
                TLSETJ_imprime(l);
                printf("\n********************************************************\n");
                TLSETJ_libera(l);
                continue;
            }
            if(opcao == 2) {
                TLSETJ* l = buscaAllNaOrigem(a, t);
                if(!l) {
                    printf("\nNenhum jogador atua na origem!\n");
                    continue;
                }

                printf("\nJogadores que atuam na origem\n");
                printf("*******************************\n");
                TLSETJ_imprime(l);
                printf("\n*****************************\n");
                TLSETJ_libera(l);
                continue;
            }
            printf("\nOpção inválida!\n");
            continue;
        }

        // [09] Seleções com mais jogadores
        // atuando fora da origem
        if(opcao == 9) {
            qtd = 0;
            TLSECHAR* l = maioresEquipesForaOrigem(a, t, &qtd);
            if(!l) {
                printf("\nNenhuma equipe possui jogador atuando fora da origem!\n");
                continue;
            }

            printf("\nEquipes com mais jogadores\natuando fora da origem (%d)\n", qtd);
            printf("*****************************\n\n");
            TLSECHAR_imprime(l);
            printf("\n***************************\n");
            continue;
        }

        // [10] Seleções com mais 
        // jogadores atuando na origem
        if(opcao == 10) {
            qtd = 0;
            TLSECHAR* l = maioresEquipesNaOrigem(a, t, &qtd);
            if(!l) {
                printf("\nNenhuma equipe possui jogador atuando na origem!\n");
                continue;
            }

            printf("Equipes com mais jogadores\natuando na origem (%d)\n", qtd);
            printf("********************************\n\n");
            TLSECHAR_imprime(l);
            printf("\n********************************\n");
            continue;
        }

        // [11] Buscar jogador
        if(opcao == 11) {
            printf("\nDigite o ID: ");
            scanf("%d", &opcao);
            TJ* jog = TARVBP_buscaJogador(a, opcao, t);
            if(!jog) {
                printf("\nNão existe jogador com este ID!\n");
                continue;
            }

            imprimeJogador(jog);
            continue;
        }

        // [13] Busca dos jogadores de uma equipe
        if(opcao == 13) {
            printf("\nDigite o nome da seleção: ");
            scanf(" %11[^\n]", nome_equipe);
            TLSETJ* l = buscaAllJogadoresEquipe(a, t, nome_equipe);
            if(!l) {
                printf("\nSeleção vazia!\n");
                continue;
            }

            printf("\nJogadores de %s", nome_equipe);
            printf("\n***************************\n");
            TLSETJ_imprime(l);
            printf("\n***************************\n");
            TLSETJ_libera(l);
            continue;
        }

        // [14] Busca e remoção dos capitães
        if(opcao == 14) {
            printf("\n[1] Busca do capitão de equipe específica\n");
            printf("[2] Remoção do capitão de equipe específica\n");
            printf("[3] Busca de todos os capitães\n");
            printf("[4] Remoção de todos os capitães\n");
            printf("\nDigite a opção desejada: ");
            scanf("%d", &opcao);
            if(opcao == 1) {
                printf("\nDigite a equipe desejada: ");
                scanf(" %11[^\n]", nome_equipe);
                TJ* jog = buscaCapitaoEquipe(a, t, nome_equipe);
                if(!jog) {
                    printf("Seleção não possui capitão!\n");
                    continue;
                }

                printf("\nCapitão de %s", nome_equipe);
                printf("\n***********************\n");
                imprimeJogador(jog);
                printf("\n***********************\n");
                free(jog);
                continue;
            }
            if(opcao == 2) {
                printf("\nDigite a equipe desejada: ");
                scanf(" %11[^\n]", nome_equipe);
                a = retiraCapitaoEquipe(a, t, nome_equipe);
                continue;
            }
            if(opcao == 3) {
                TLSETJ* l = buscaAllCapitaes(a, t);
                if(!l) {
                    printf("\nNenhuma seleção possui capitão!\n");
                    continue;
                }

                printf("\nCaptão de cada equipe");
                printf("\n*********************\n");
                TLSETJ_imprime(l);
                printf("\n*********************\n");
                TLSETJ_libera(l);
                continue;
            }
            if(opcao == 4) {
                printf("\nDigite a equipe desejada: ");
                scanf(" %11[^\n]", nome_equipe);
                a = retiraAllCapitaes(a, t);
                continue;
            }
            printf("\nOpção inválida!\n");
            continue;
        }

        // [16] Remoção dos jogadores de uma equipe
        //  que atuam num determinado país
        if(opcao == 16) {
            char nome_pais[12];
            printf("\nDigite o nome da seleção: ");
            scanf(" %11[^\n]", nome_equipe);
            printf("\nDigite o nome do país de atuação: ");
            scanf(" %11[^\n]", nome_pais);
            a = retiraAllEquipePais(a, t, nome_equipe, nome_pais);
            continue;
        }

        // [17] Remoção dos que jogam na origem
        if(opcao == 17) {
            printf("\nDigite a equipe: ");
            scanf(" %11[^\n]", nome_equipe);
            a = retiraAllNaOrigem(a, t, nome_equipe);
            continue;
        }

        // [18] Remoção dos que jogam fora da origem
        if(opcao == 18) {
            printf("\nDigite a equipe: ");
            scanf(" %11[^\n]", nome_equipe);
            a = retiraAllForaOrigem(a, t, nome_equipe);
            continue;
        }

        // [19] Remoção dos jogadores de uma equipe
        if(opcao == 19) {
            printf("\nDigite a equipe: ");
            scanf(" %11[^\n]", nome_equipe);
            a = retiraAllEquipe(a, t, nome_equipe);
            continue;
        }

        printf("\nOpção inválida!\n");
        continue;
    } while(1);
}

=======
>>>>>>> c3f0b770fe432a03e369708fa873e390853315b8
int main(void){
    setlocale(LC_ALL, "pt_BR.UTF-8");

    TABSELE_inicializa();
    TARVBP *a = catalogo2Arv("root", 2);
<<<<<<< HEAD
    
    menu(a, 2);
    
=======
    a = TARVBP_retira(a, 1, 2);
    a = TARVBP_retira(a, 38, 2);
    a = TARVBP_retira(a, 216, 2);
    a = TARVBP_retira(a, 131, 2);
    a = TARVBP_retira(a, 152, 2);
    a = TARVBP_retira(a, 63, 2);
    a = TARVBP_retira(a, 14, 2);
    a = TARVBP_retira(a, 194, 2);
    a = TARVBP_retira(a, 267, 2);
    a = TARVBP_retira(a, 110, 2);
    a = TARVBP_retira(a, 149, 2);
    a = TARVBP_retira(a, 237, 2);
    a = TARVBP_retira(a, 10, 2);
    a = TARVBP_retira(a, 16, 2);
    a = TARVBP_retira(a, 151, 2);
    a = TARVBP_retira(a, 192, 2);
    a = TARVBP_retira(a, 3, 2);
    a = TARVBP_retira(a, 20, 2);
    a = TARVBP_retira(a, 119, 2);
    a = TARVBP_retira(a, 196, 2);
    a = TARVBP_retira(a, 168, 2);
    a = TARVBP_retira(a, 266, 2);
    a = TARVBP_retira(a, 242, 2);
    a = TARVBP_retira(a, 27, 2);
    a = TARVBP_retira(a, 187, 2);
    a = TARVBP_retira(a, 200, 2);
    imprimeNo(a);
    // char *p = (char *)malloc(sizeof(char)*40);
    TARVBP *b = TARVBP_busca(a, 16, 2);
    if(b) {
        imprimeNo(b);
        TARVBP_libera(b, 2);
    }
    TARVBP_imprime(a, 2);
>>>>>>> c3f0b770fe432a03e369708fa873e390853315b8
    TARVBP_libera(a, 2);

    return 0;
}