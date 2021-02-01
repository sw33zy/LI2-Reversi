#include <stdio.h>
#include <ctype.h>
#include "estado.h"



void comandos () {
    ESTADO e = {0};

    char linha[50];
    char c1, c2, nome[40];
    int x, y, c3;
    do {
        fgets(linha, 50, stdin);
        switch (toupper(linha[0])) {
            case 'N': {
                e.fim = 1;
                e.modo = 0;
                sscanf(linha, "%c %c", &c1, &c2);
                if (c2 == 'X') {
                    printf("M X\n");
                    e = inicia(e, VALOR_X);

                } else if (c2 == 'O') {
                    printf("M O\n");
                    e = inicia(e, VALOR_O);
                }
                printa(e);
                push(e);
                break;
            }
            case 'J' : {
                // permite efetuar uma jogada tanto em modo 1 ou 0;
                sscanf(linha, "%c %d %d", &c1, &x, &y);
                if (e.modo == 0) {
                    e = joga(e, x - 1, y - 1);
                    printa(e);
                    if (acabou(e) == 1) {
                        if (contadorX(e) > contadorO(e)) printf("Jogo acabou! Vencedor: X!\n");
                        else if (contadorX(e) < contadorO(e)) printf("Jogo acabou! Vencedor: O!\n");
                        else printf("Empate!\n");
                    }
                }
                else { //se o e.modo for automatico

                    if (validar(e, x - 1, y - 1) != 0) {
                        e = joga(e, x - 1, y - 1);
                        printa(e);
                        if (e.modo == 1) e = botfacil(e);
                        else if (e.modo == 2) e = botmedio(e);
                        else if (e.modo == 3) e = botdificil(e);
                    } else {
                        // se nao for "permitido" jogar, imprime no ecrã uma mensagem para o jogador voltar a jogar: NÃO VAI À
                        // FUNÇÂO JOGA
                        if (e.peca == VALOR_X) printf("Try again X\n");
                        else if (e.peca == VALOR_O) printf("Try again O\n");
                    }
                }

                push(e);
                break;
        }

            case 'Q' :
                break;
            case 'U': {
                pop();
                e=undo();
                break;
            }
            case 'L': {
                sscanf (linha,"%c %s", &c1,nome);
                e=load(e,nome);
                printa(e);
                break;
            }

            case 'E': {
                sscanf(linha,"%c %s", &c1, nome);
                save(e,nome);
                printf("Jogo Guardado!\n");
                break;}

            case 'S': {
                sugestao(e);
                contador (e);
                break;
            }
            case 'H':{
                help(e);
                contador (e);
            }
            case 'A': {
                // A peça que inicia é a X.
                e.peca=VALOR_X;
                // Vai à função bot para distribuir pelos diversos níveis
                sscanf(linha,"%c %c %d", &c1 ,&c2 ,&c3);
                if ((c2=='X') || (c2=='O')) {

                    e = bot(e,c2,c3);

                }

                else printf("Jogador Inválido\n");
                break;
            }


            default: {
                printf("Comando Inválido!\n");
                break;
            }
        }

    }

    while ((toupper(linha[0]) != 'Q'));
}



int main(){

    menu();

    printf("\n");
    printf("\n");


    comandos();
    return 0;
}
