#include "../headers/includes.h"

/**
 * @file utils.c
 * @brief   Biblioteca que vamos compor para uma série de utilidades que não
            estão diretamente relacionadas à criação das tabelas e estruturas
            de dados do trabalho. 
*/

void readLine(FILE *fp, char *string, int *size, char splitter) {
    int i = 0, x;
    char c;

    while(i < 40) {
        x = fread(&c, sizeof(char), 1, fp);
        if ((c == splitter) || (x != 1)) {
            string[i] = '\0';
            break;
        }
        if (c != '\n' && c != '\r') { // Ignorar nova linha e retorno de carro
            string[i] = c;
            i++;
        }
    }

    // Garantir que a string é terminada corretamente
    if (i < 40) {
        string[i] = '\0';
    } else {
        string[39] = '\0';
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

void converteDia(char *str){
    if(atoi(str) < 10){
        str[1] = str[0];
        str[0] = '0';
        str[2] = '\0';
    }
}

void criaData(char *destino, char *dia, char *meses, char *ano){
    destino = strcpy(destino, strcat(dia, "/"));
    strcat(meses, "/");
    strcat(destino, meses);
    strcat(destino, ano);
}

void skip_bom(FILE *fp) {
    unsigned char bom[3];
    if (fread(bom, 1, 3, fp) == 3) {
        if (bom[0] != 0xEF || bom[1] != 0xBB || bom[2] != 0xBF) {
            // Não é BOM, então volte o ponteiro de leitura para o início
            fseek(fp, 0, SEEK_SET);
        }
    } else {
        // Não há bytes suficientes para ser um BOM, então volte o ponteiro de leitura para o início
        fseek(fp, 0, SEEK_SET);
    }
}

int datacmp(char *data1, char *data2){
    for(int i = 6; i <= 9; i++){
        if(data1[i] < data2[i]) return -1;
        if(data1[i] > data2[i]) return 1;
    }

    for(int i = 3; i <= 4; i++){
        if(data1[i] < data2[i]) return -1;
        if(data1[i] > data2[i]) return 1;
    }

    for(int i = 0; i <= 1; i++){
        if(data1[i] < data2[i]) return -1;
        if(data1[i] > data2[i]) return 1;
    }

    return 0;
}

TARVBP* catalogo2Arv(char *nomeArq, int t){
    TARVBP *a = TARVBP_cria(nomeArq, t);
    TABSELE_inicializa();
    TH_inicializa("hash.dat", "dados.dat");
    FILE *fp = fopen("catalogo.txt", "r");
    if(!fp) exit(1);
    skip_bom(fp);

    char selecao[40];
    int size;
    TJ *j;
    int i = 284;
    while(i > 0){
        if(verificaSelecao(fp)){
            readLine(fp, selecao, &size, '\n');
        } else {
            j = leJogador(fp, selecao);
            TH_insere("hash.dat", "dados.dat", j->data_nasc, j->id);
            a = TARVBP_insere(a, j, t);
            i--;
        }
    }
    return a;
}


TARVBP* menu(TARVBP* a, int t) {
    do {
        printf("\n----------- Menu -------------\n");
        printf("Selecione a opcao desejada: \n");
        printf("[1] Buscar jogadores mais novos e mais velhos\n");
        printf("[2] Jogadores que mais e menos atuaram por equipe\n");
        printf("[3] Jogadores que mais e menos atuaram no total\n");
        printf("[4] Seleções com mais e menos convocações no total\n");
        printf("[5] Buscar jogadores que atuam fora da origem\n");
        printf("[6] Buscar jogadores que atuam na origem\n");
        printf("[7] Buscar jogadores que nasceram no mesmo ano\n");
        printf("[8] Buscar jogadores que nasceram no mesmo mês\n");
        printf("[9] Equipes com mais jogadores atuando fora da origem\n");
        printf("[10] Equipes com mais jogadores atuando na origem\n");
        printf("[11] Buscar jogador\n");
        printf("[12] Alterar informações de jogadores\n");
        printf("[13] Buscar todos os jogadores de uma equipe\n");
        printf("[14] Buscar ou remover os capitães\n");
        printf("[15] Remover jogadores a partir de determinada idade\n");
        printf("[16] Remover jogadores de um equipe que atuam num determinado país\n");
        printf("[17] Remover todos os jogadores de uma equipe que jogam na origem\n");
        printf("[18] Remover todos os jogadores de uma equipe que não jogam na origem\n");
        printf("[19] Remover todos os jogadores de uma equipe\n");
        printf("[20] Remover jogadores dado um conjunto de suas chaves primárias\n");
        printf("\n[0] Imprimir IDs da árvore\n");
        printf("[-1] Sair\n");
        printf("--------------------------------\n");
        printf("\nDigite a opcao desejada: ");

        int opcao, qtd;
        char nome_equipe[12];
        scanf("%d", &opcao);
        // [-1] Voltar do menu
        if(opcao == -1) return a;
        
        // [0] Imprimir IDs da árvore
        if(opcao == 0) {
            TARVBP_imprime(a, t);
            continue;
        }


        // [1] Retorno do jogador mais novo e mais velho da competição, ilustrando essas mesmas informações
        //     por seleções e por posições;
        if(opcao == 1){
            printf("\n[1] Jogador mais novo por equipe\n");
            printf("[2] Jogador mais velho por equipe\n");
            printf("[3] Jogador mais novo\n");
            printf("[4] Jogador mais velho\n");
            printf("\nDigite a opcao desejada: ");
            scanf("%d", &opcao);

            if(opcao == 1){
                printf("\nDigite o país desejado: ");
                scanf(" %11[^\n]", nome_equipe);
                if(!existeEquipe(nome_equipe)) {
                    printf("\nOpção de equipe inválida!\n");
                    continue;
                }

                TJ *j = maisNovosPorEquipe(a, t, nome_equipe);
                if(j){
                    imprimeJogador(j);
                    free(j);
                }else{
                    printf("\nNão foram encontrados jogadores\n");
                }
                continue;
            }else if(opcao == 2){
                printf("\nDigite o país desejado: ");
                scanf(" %11[^\n]", nome_equipe);
                TJ *j = maisVelhosPorEquipe(a, t, nome_equipe);
                if(j){
                    imprimeJogador(j);
                    free(j);
                }else{
                    printf("\nNão foram encontrados jogadores\n");
                }
                continue;
            }else if(opcao == 3){
                TJ *j = maisNovo(a, t);
                if(j){
                    imprimeJogador(j);
                    free(j);
                }else{
                    printf("\nNão foram encontrados jogadores\n");
                }
                continue;
            }else if(opcao == 4){
                TJ *j = maisVelho(a, t);
                if(j){
                    imprimeJogador(j);
                    free(j);
                }else{
                    printf("\nNão foram encontrados jogadores\n");
                }
                continue;
            }
        }

        
        // [2] Jogadores que mais e menos atuaram por equipe
        if(opcao == 2) {
            printf("\n[1] Jogadores que mais atuaram em equipe específica\n");
            printf("[2] Jogadores que menos atuaram em equipe específica\n");
            printf("[3] Jogadores que mais atuaram em cada equipe\n");
            printf("[4] Jogadores que menos atuaram em cada equipe\n");
            printf("\nDigite a opcao desejada: ");
            scanf("%d", &opcao);
            if(opcao == 1) {
                printf("\nDigite o país desejado: ");
                scanf(" %11[^\n]", nome_equipe);
                if(!existeEquipe(nome_equipe)) {
                    printf("\nOpção de equipe inválida!\n");
                    continue;
                }

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
                if(!existeEquipe(nome_equipe)) {
                    printf("\nOpção de equipe inválida!\n");
                    continue;
                }

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
            if(opcao == 3) {
                TLSETJ* l = maisAtuaramCadaEquipe(a, t);
                if(!l) {
                    printf("\nBase dados vazia!\n");
                    continue;
                }

                printf("\nJogadores que mais atuaram em cada equipe");
                printf("\n*****************************************\n");
                TLSETJ_imprime(l);
                printf("\n*****************************************\n");
                TLSETJ_libera(l);
                continue;
            }
            if(opcao == 4) {
                TLSETJ* l = menosAtuaramCadaEquipe(a, t);
                if(!l) {
                    printf("\nBase dados vazia!\n");
                    continue;
                }

                printf("\nJogadores que menos atuaram em cada equipe");
                printf("\n*****************************************\n");
                TLSETJ_imprime(l);
                printf("\n*****************************************\n");
                TLSETJ_libera(l);
                continue;
            }
            printf("\nOpcao invalida!\n");
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
            printf("\nOpcao invalida!\n");
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
                printf("\n*************************************\n\n");
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
                printf("\n*************************************\n\n");
                TLSECHAR_imprime(l);
                printf("\n*************************************\n");
                TLSECHAR_libera(l);
                continue;
            }
            printf("\nOpção inválida!\n");
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
                if(!existeEquipe(nome_equipe)) {
                    printf("\nOpção de equipe inválida!\n");
                    continue;
                }

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
                if(!existeEquipe(nome_equipe)) {
                    printf("\nOpção de equipe inválida!\n");
                    continue;
                }

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

        // Busca de todos os jogadores que nasceram no mesmo ano
        if(opcao == 7){
            char s[5];
            printf("Digite o ano: ");
            scanf("%s", s);
            int tam = 0;
            TJ **l = buscaJogadorAno(a, t, s, &tam);
            if(!l) printf("Não foram encontrados jogadores nascidos nesse ano.\n");
            for(int i = 0; i < tam; i++){
                imprimeJogador(l[i]);
                free(l[i]);
            }
            free(l);
            continue;
        }

        if(opcao == 8){
            char s[5];
            printf("Digite o mês: ");
            scanf("%s", s);
            int tam = 0;
            TJ **l = buscaJogadorMes(a, t, s, &tam);
            if(!l) printf("Não foram encontrados jogadores nascidos nesse mês.\n");
            for(int i = 0; i < tam; i++){
                imprimeJogador(l[i]);
                free(l[i]);
            }
            free(l);
            continue;
        }

        // [09] Seleções com mais jogadores
        //      atuando fora da origem
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
            TLSECHAR_libera(l);
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

            printf("\nEquipes com mais jogadores\natuando na origem (%d)\n", qtd);
            printf("********************************\n\n");
            TLSECHAR_imprime(l);
            printf("\n********************************\n");
            TLSECHAR_libera(l);
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
            free(jog);
            continue;
        }

        // [12] Alterar infos dos jogadores
        if(opcao == 12){
            printf("\n[1] Alterar posição de um jogador\n");
            printf("[2] Alterar quantidade de gols de um jogador\n");
            printf("[3] Alterar numeração de um jogador\n");
            printf("[4] Alterar time de um jogador\n");
            printf("[5] Alterar país do time de um jogador\n");
            printf("[6] Alterar participações de um jogador\n");
            printf("[7] Tornar um jogador capitão de sua seleção\nou fazer um jogador deixar de ser\n");
            printf("\nDigite a opção desejada: ");
            do{
                scanf(" %d", &opcao);
                if(opcao < 1 || opcao > 7) printf("\nOpção inválida\n");
                else break;
            } while(1);
            char str[40];
            int id, val;
            printf("\nDigite o id do jogador que sofrerá alterações: ");
            do{
                scanf(" %d", &id);
                if(id < 1 || id > 284) printf("ID inválido!\n");
                else break;
            } while(1);
            switch (opcao)
            {
            case 1:
                printf("\nDigite a nova posição do jogador: ");
                scanf(" %2[^\n]", str);
                alteraPosicao(a, t, id, str);
                break;
            case 2:
                printf("\nDigite o novo número de gols do jogador: ");
                scanf(" %d", &val);
                alteraGols(a, t, id, val);
                break;
            case 3:
                printf("\nDigite o novo número de camisa do jogador: ");
                scanf(" %d", &val);
                alteraNumero(a, t, id, val);
                break;
            case 4:
                printf("\nDigite o novo time do jogador: ");
                scanf(" %23[^\n]", str);
                alteraTime(a, t, id, str);
                break;
            case 5:
                printf("\nDigite o novo país do time do jogador: ");
                scanf(" %20[^\n]", str);
                alteraPaisTime(a, t, id, str);
                break;
            case 6:
                printf("\nDigite o novo número de participações do jogador: ");
                scanf(" %d", &val);
                alteraPartidas(a, t, id, val);
                break;
            case 7:
                alteraCapitao(a, t, id);
                break;
            default:
                break;
            }
            continue;
        }

        // [13] Busca dos jogadores de uma equipe
        if(opcao == 13) {
            printf("\nDigite o nome da seleção: ");
            scanf(" %11[^\n]", nome_equipe);
            if(!existeEquipe(nome_equipe)) {
                printf("\nOpção de equipe inválida!\n");
                continue;
            }

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
                if(!existeEquipe(nome_equipe)) {
                    printf("\nOpção de equipe inválida!\n");
                    continue;
                }

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
                if(!existeEquipe(nome_equipe)) {
                    printf("\nOpção de equipe inválida!\n");
                    continue;
                }

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
                a = retiraAllCapitaes(a, t);
                continue;
            }
            printf("\nOpção inválida!\n");
            continue;
        }

        if(opcao == 15){
            int idade;
            printf("Digite a idade: ");
            scanf("%d", &idade);
            a = remocaoPorIdade(a, t, idade);
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
            if(!existeEquipe(nome_equipe) || !existeEquipe(nome_pais)) {
                printf("\nOpção de equipe inválida!\n");
                continue;
            }
            a = retiraAllEquipeAtuaPais(a, t, nome_equipe, nome_pais);
            continue;
        }

        // [17] Remoção dos que jogam na origem
        if(opcao == 17) {
            printf("\nDigite a equipe: ");
            scanf(" %11[^\n]", nome_equipe);
            if(!existeEquipe(nome_equipe)) {
                printf("\nOpção de equipe inválida!\n");
                continue;
            }

            a = retiraAllNaOrigem(a, t, nome_equipe);
            continue;
        }

        // [18] Remoção dos que jogam fora da origem
        if(opcao == 18) {
            printf("\nDigite a equipe: ");
            scanf(" %11[^\n]", nome_equipe);
            if(!existeEquipe(nome_equipe)) {
                printf("\nOpção de equipe inválida!\n");
                continue;
            }

            a = retiraAllForaOrigem(a, t, nome_equipe);
            continue;
        }

        // [19] Remoção dos jogadores de uma equipe
        if(opcao == 19) {
            printf("\nDigite a equipe: ");
            scanf(" %11[^\n]", nome_equipe);
            if(!existeEquipe(nome_equipe)) {
                printf("\nOpção de equipe inválida!\n");
                continue;
            }

            a = retiraAllEquipe(a, t, nome_equipe);
            continue;
        }
        // [20] Remoção de jogadores dado um vetor de suas chaves primárias
        if(opcao == 20){
            int num, idJ;
            printf("\nDigite quantos jogadores você quer remover: ");
            do{
                scanf(" %d", &num);
                if(num < 1 || num > 284) printf("\nDigite uma quantidade válida...\n");
                else break;
            } while(1);
            int vet[num];
            for(int i = 0; i < num; i++){
                printf("\nDigite o ID do jogador: ");
                do{
                    scanf(" %d", &idJ);
                    if(!TARVBP_possui_elemento(a, idJ, t)){
                        printf("\nNão existe jogador com esse id!\n");
                    } else {
                        vet[i] = idJ;
                        break;
                    }
                } while(1);
            }
            a = retiraIds(a, t, vet, num);
            continue;
        }

        printf("\nOpção inválida!\n");
        continue;
    } while(1);
}
