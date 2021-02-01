#include <stdio.h>
#include "estado.h"
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>

const VALOR inv[] = {VAZIA,VALOR_O,VALOR_X};

void printa(ESTADO e) {
    char c = ' ';
    char modo,nivel,jogador;
    int linhas = 1;

 //sempre que printa o estado resultante de uma jogada irá verificar se o jogador atual pode jogar antes de escolher um comando
    if (passar(e) == 0){ //o jogador nao tem mais jogadas
        printf("\n  1 2 3 4 5 6 7 8\n");
        for (int i = 0; i < 8; i++) {
            printf("%d ", linhas);
            for (int j = 0; j < 8; j++) {
                switch (e.grelha[i][j]) {
                    case VALOR_help: {
                        c = '?';
                        break;
                    }
                    case VALOR_O: {
                        c = 'O';
                        break;
                    }
                    case VALOR_X: {
                        c = 'X';
                        break;
                    }
                    case VAZIA: {
                        c = '-';
                        break;
                    }
                }
                printf("%c ", c);
            }
            linhas++;

            printf("\n");
        }
        contador(e);
        printf("Sem Jogadas.Passou a vez.\n\n");
        e.peca=inv[e.peca];
        e.fim=0; // acabou a sua vez de jogar
        if (e.modo==0) {modo= 'M'; nivel='-';}
        else if(e.modo==1) {nivel= '1'; modo='A';}
        else if(e.modo==2) {nivel='2';modo='A';}
        else if(e.modo==3) {nivel='3';modo='A';}
        if (e.peca == VALOR_X) jogador= 'X';
        else if (e.peca == VALOR_O) jogador='O';
        printf ("%c %c %c\n",modo,jogador,nivel);
    }

    printf("\n  1 2 3 4 5 6 7 8\n");
    linhas = 1;
    for (int i = 0; i < 8; i++) {
        printf("%d ", linhas);
        for (int j = 0; j < 8; j++) {
                switch (e.grelha[i][j]) {
                    case VALOR_help: {
                        c = '?';
                        break;
                    }
                    case VALOR_O: {
                        c = 'O';
                        break;
                    }
                    case VALOR_X: {
                        c = 'X';
                        break;
                    }
                    case VAZIA: {
                        c = '-';
                        break;
                    }
                }
                printf("%c ", c);
            }
            linhas++;

            printf("\n");
        }
    contador(e);

    if (e.fim == 0) {
        if (e.modo == 1) botfacil(e);
        else if (e.modo == 2) botmedio(e);
        else if (e.modo == 3) botdificil(e);
    }
}

ESTADO inicia (ESTADO e, VALOR v){
    e.peca=v;
    e.modo=0;
    int i;
    int j=0;
    for(i=0;i <= 7;i++){
        for(j=0;j<=7;j++)
            e.grelha[i][j]=VAZIA;
    }
    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;
    //printa(e);
    return e;
}

ESTADO valida(ESTADO e,int l,int c) {
    // função que avalia se é válido jogar numa dada posição , caso seja valido troca imaediatamente a posição pretendida pela peça em jogo

    int deixa = 0;
    int deixa1=0,deixa2=0,deixa3=0,deixa4=0,deixa5=0,deixa6=0,deixa7=0,deixa8=0;
    int posc = 0;
    if (e.grelha [l][c] == VAZIA) { // nesta linha verificamos se a posicao onde queremos jogar é uma posicao vazia;

        // Este     : aqui procuramos de na direcao este existe uma peca igual à nossa;
        int i = l, j = c + 1;
        if (e.grelha[l][c+1]!=e.peca) {
            while ((j <= 7) && (e.grelha[i][j] != e.peca)) { j++; }  // o ciclo para se encontrarmos uma peca igual caso contrario so para quando chegarmos ao fim do tabuleiro
            posc = j; //vamos guardar j numa variavel que sera usada mais a frente
            if ((j <= 7) && (e.grelha[i][j] == e.peca)) { // este if serve para verificar se saimos do ciclo anterior pq encontramos uma peca igual à nossa e nao pq acabou o tabuleiro
                j--; // se a condicao se verificar vamos andar uma posicao para tras para verificar se esta nova posicao é uma inv[e.peca]
                deixa1 = 1; //pode jogar
                while ((j != c) && (deixa1 == 1)) { //neste ciclo nos andamos para tras ate chegarmos à posicao c e ao mesmo tempo verificamos se as pecas sao pecas inversas , se isto se verificar o deixa é 1 , se o deixa for 0 pq estas condicoes nao se verificam entao sai imediatamente do ciclo
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa1 = 1;
                    else deixa1 = 0;
                    j--;
                }
            }
            if (deixa1 == 1) { //se l c for uma jogada valida nesta direcao ou seja se deixa1=1 entao podemos trocar todas as pecas ate à primeira peca igual a nossa nesta direcao
                while (j != posc) { //posc é a variavel em que nos guardamos anteriormente a  posicao onde encontramos a primeira peca igual a nossa nesta direcao
                    if (e.peca == VALOR_O) e.grelha[l][j] = VALOR_O;
                    else if (e.peca == VALOR_X) e.grelha[l][j] = VALOR_X;
                    j++;
                }
            }
        }
        else deixa1=0;  // se as condicoes anteriores nao se verificarem entao nao troca as pecas e deixa1=0


        // Oeste
        i = l;
        j = c - 1;
        if (e.grelha[l][c-1]!=e.peca) {
            while ((j >= 0) && (e.grelha[i][j] != e.peca)) { j--; }
            posc = j;
            if ((j >= 0) && (e.grelha[i][j] == e.peca)) {
                j++;
                deixa2 = 1;
                while ((j != c) && (deixa2 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa2 = 1;
                    else deixa2 = 0;
                    j++;
                }
            }
            if (deixa2 == 1) {
                while (j != posc) {
                    if (e.peca == VALOR_O) e.grelha[l][j] = VALOR_O;
                    else if (e.peca == VALOR_X) e.grelha[l][j] = VALOR_X;
                    j--;
                }
            }
        }
        else deixa2=0;


        //Sul
        i = l + 1;
        j = c;
        if (e.grelha[l+1][c]!=e.peca) {
            while ((i <= 7) && (e.grelha[i][j] != e.peca)) { i++; }
            posc = i;
            if ((i <= 7) && (e.grelha[i][j] == e.peca)) {
                i--;
                deixa3 = 1;
                while ((i != l) && (deixa3 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa3 = 1;
                    else deixa3 = 0;
                    i--;
                }
            }
            if (deixa3 == 1) {
                while (i != posc) {
                    if (e.peca == VALOR_O) e.grelha[i][c] = VALOR_O;
                    else if (e.peca == VALOR_X) e.grelha[i][c] = VALOR_X;
                    i++;
                }
            }
        }
        else deixa3=0;


        //Norte
        i = l - 1;
        j = c;
        if (e.grelha[l-1][c]!=e.peca) {
            while ((i >= 0) && (e.grelha[i][j] != e.peca)) { i--; }
            posc = i;
            if ((i >= 0) && (e.grelha[i][j] == e.peca)) {
                i++;
                deixa4 = 1;
                while ((i != l) && (deixa4 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa4 = 1;
                    else deixa4 = 0;
                    i++;
                }
            }
            if (deixa4 == 1) {
                while (i != posc) {
                    if (e.peca == VALOR_O) e.grelha[i][c] = VALOR_O;
                    else if (e.peca == VALOR_X) e.grelha[i][c] = VALOR_X;
                    i--;
                }
            }
        }
        else deixa4=0;

        // SudEste
        i = l + 1;
        j = c + 1;
        if (e.grelha[l+1][c+1]!=e.peca) {
            while ((i <= 7) && (j <= 7) && (e.grelha[i][j] != e.peca)) {
                i++;
                j++;
            }
            int posx = i;
            int posy = j;
            if ((i <= 7) && (j <= 7) && (e.grelha[i][j] == e.peca)) {
                i--;
                j--;
                deixa5 = 1;
                while ((i != l) && (j != c) && (deixa5 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa5 = 1;
                    else deixa5 = 0;
                    i--;
                    j--;
                }
            }
            if (deixa5 == 1) {
                while ((i != posx) && (j != posy)) {
                    if (e.peca == VALOR_O) e.grelha[i][j] = VALOR_O;
                    else if (e.peca == VALOR_X) e.grelha[i][j] = VALOR_X;
                    i++;
                    j++;
                }
            }
        }
        else deixa5=0;


        // NorOeste
        i = l - 1;
        j = c - 1;
        if (e.grelha[l-1][c-1]!=e.peca) {
            while ((i >= 0) && (j >= 0) && (e.grelha[i][j] != e.peca)) {
                i--;
                j--;
            }
            int posx = i;
            int posy = j;
            if ((i >= 0) && (j >= 0) && (e.grelha[i][j] == e.peca)) {
                i++;
                j++;
                deixa6 = 1;
                while ((i != l) && (j != c) && (deixa6 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa6 = 1;
                    else deixa6 = 0;
                    i++;
                    j++;
                }
            }
            if (deixa6 == 1) {
                while ((i != posx) && (j != posy)) {
                    if (e.peca == VALOR_O) e.grelha[i][j] = VALOR_O;
                    else if (e.peca == VALOR_X) e.grelha[i][j] = VALOR_X;
                    i--;
                    j--;
                }
            }
        }
        else deixa6=0;


        //SudOeste
        i = l + 1;
        j = c - 1;
        if (e.grelha[l+1][c-1]!=e.peca) {
            while ((i <= 7) && (j >= 0) && (e.grelha[i][j] != e.peca)) {
                i++;
                j--;
            }
            int posx = i;
            int posy = j;
            if ((i <= 7) && (j >= 0) && (e.grelha[i][j] == e.peca)) {
                i--;
                j++;
                deixa7 = 1;
                while ((i != l) && (j != c) && (deixa7 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa7 = 1;
                    else deixa7 = 0;
                    i--;
                    j++;
                }
            }
            if (deixa7 == 1) {
                while ((i != posx) && (j != posy)) {
                    if (e.peca == VALOR_O) e.grelha[i][j] = VALOR_O;
                    else if (e.peca == VALOR_X) e.grelha[i][j] = VALOR_X;
                    i++;
                    j--;
                }
            }
        }
        else deixa7=0;

        //NorEste
        i = l - 1;
        j = c + 1;
        if (e.grelha[l-1][c+1]!=e.peca) {
            while ((i >= 0) && (j <= 7) && (e.grelha[i][j] != e.peca)) {
                i--;
                j++;
            }
            int posx = i;
            int posy = j;
            if ((i >= 0) && (j <= 7) && (e.grelha[i][j] == e.peca)) {
                i++;
                j--;
                deixa8 = 1;
                while ((i != l) && (j != c) && (deixa8 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa8 = 1;
                    else deixa8 = 0;
                    i++;
                    j--;
                }
            }
            if (deixa8 == 1) { //troca as peças do tabuleiro
                while ((i != posx) && (j != posy)) {
                    if (e.peca == VALOR_O) e.grelha[i][j] = VALOR_O;
                    else if (e.peca == VALOR_X) e.grelha[i][j] = VALOR_X;
                    i--;
                    j++;
                }
            }
        }
        else deixa8=0;
        //final
        deixa = deixa1+deixa2+deixa3+deixa4+deixa5+deixa6+deixa7+deixa8;
    }
    else deixa=0;

    if (deixa==0){
        printf("Jogada Invalida!");
        if(e.modo==0) {
            if (e.peca==VALOR_X)e.peca=VALOR_O;
            else if(e.peca==VALOR_O) e.peca=VALOR_X;
        }
    }
    return e;
}


ESTADO joga (ESTADO e, int x, int y) {
    // independentemente do modo, a funcao avalia se é permitido jogar naquela posição com recurso à função valida
    // troca a peça no final da jogada, para permitir que o outro jogador tenha a sua peça em jogo

    if (e.modo == 0) {
        e = valida(e, x, y);
        if (e.peca == VALOR_X) {
            e.peca = VALOR_O;
            printf("\nM O\n");
        } else if (e.peca == VALOR_O) {
            e.peca = VALOR_X;
            printf("\nM X\n");
        }
    } else if (e.modo != 0) {
        e = valida(e, x, y);
        if (e.peca == VALOR_X) {
            e.peca = VALOR_O;
            if (e.modo == 1) printf("\nA O 1\n");
            else if (e.modo == 2) printf("\nA O 2\n");
            else if (e.modo == 3) printf("\nA O 3\n");
        } else if (e.peca == VALOR_O) {
            e.peca = VALOR_X;
            if (e.modo == 1) printf("\nA X 1\n");
            else if (e.modo == 2) printf("\nA X 2\n");
            else if (e.modo == 3) printf("\nA X 3\n");
        }
    }
    return e;
}




ESTADO anula (ESTADO e){
    int i,j;

    for (i=0;i<8;i++) {
        for (j = 0; j < 8; j++) {
            e.grelha[i][j]=VAZIA;
        }
    }
    return e;
}

ESTADO load (ESTADO e,char c1[]) {
    char c;
    char t1,t2,t3;
    int i = 0, j = 0;
    FILE *tabuleiro;

    e=anula(e);
    tabuleiro = fopen(c1, "r");

    // 1º linha
    fscanf(tabuleiro,"%c %c %c",&t1,&t2,&t3);
    if ((t1=='M')&&(t3=='-')) e.modo=0;
    else if((t1=='A')&&(t3=='1')) e.modo=1;
    else if((t1=='A')&&(t3=='2')) e.modo=2;
    else if((t1=='A')&&(t3=='3')) e.modo=3;
    else printf("tabuleiro nao valido");
    e.peca = (t2 == 'X' ? VALOR_X : VALOR_O);
    printf ("%c %c %c\n",t1,t2,t3);

    for (i=0;i<8;i++) {
        for (j = 0; j < 8; j++) {

            fscanf(tabuleiro, "%s ", &c);
            switch (c) {
                case 'X': {
                    e.grelha[i][j] = VALOR_X;
                    break;
                }
                case 'O': {
                    e.grelha[i][j] = VALOR_O;
                    break;
                }

                case '-': {
                    e.grelha[i][j] = VAZIA;
                    break;
                }

                default:{break;}
            }
        }
    }
    fclose(tabuleiro);

    return e;
}

//escreve o ficheiro da grelha
void save (ESTADO e,char c1[])
{
    int i,j;
    char modo,nivel,jogador ;
    char c = ' ';
    FILE *fPointer;
    fPointer = fopen(c1,"w");
    if (e.modo==0) {modo= 'M'; nivel='-';}
    else if(e.modo==1) {nivel= '1'; modo='A';}
    else if(e.modo==2) {nivel='2';modo='A';}
    else if(e.modo==3) {nivel='3';modo='A';}
    if (e.peca == VALOR_X) jogador= 'X';
    else if (e.peca == VALOR_O) jogador='O';
    fprintf (fPointer,"%c %c %c\n",modo,jogador,nivel);
    for (i=0;i<8;i++) {
        for (j=0;j<8;j++) {
            switch(e.grelha[i][j]) {
                case VALOR_X:
                {
                    c = 'X';
                    break;}
                case VALOR_O:
                {
                    c = 'O';
                    break;}
                case VAZIA:
                {
                    c = '-';
                    break;}
            }
            fprintf(fPointer,"%c ",c);
        }
        fprintf(fPointer,"\n");
    }
    fclose(fPointer);
}

// Esta função diz-nos se é possível jogar na posiçao linha l e coluna c ; >= 1 é possível ; =0 nao é possível ;

int validar(ESTADO e,int l,int c) {

    int deixa = 0;
    if(e.grelha[l][c]== VAZIA) {
        int deixa1 = 0;
        // Este
        int i = l, j = c + 1;
        if (e.grelha[l][c+1]!=e.peca) {
            while ((j <= 7) && (e.grelha[i][j] != e.peca)) { j++; }
            if ((j <= 7) && (e.grelha[i][j] == e.peca)) {
                j--;
                deixa1 = 1;
                while ((j != c) && (deixa1 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa1 = 1;
                    else deixa1 = 0;
                    j--;
                }
            }
        }
        else deixa1=0;

        // Oeste
        int deixa2 = 0;
        i = l;
        j = c - 1;
        if (e.grelha[l][c-1]!=e.peca) {
            while ((j >= 0) && (e.grelha[i][j] != e.peca)) { j--; }
            if ((j >= 0) && (e.grelha[i][j] == e.peca)) {
                j++;
                deixa2 = 1;
                while ((j != c) && (deixa2 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa2 = 1;
                    else deixa2 = 0;
                    j++;
                }
            }
        }
        else deixa2=0;

        //Sul
        int deixa3 = 0;
        i = l + 1;
        j = c;
        if (e.grelha[l+1][c]!=e.peca) {
            while ((i <= 7) && (e.grelha[i][j] != e.peca)) { i++; }
            if ((i <= 7) && (e.grelha[i][j] == e.peca)) {
                i--;
                deixa3 = 1;
                while ((i != l) && (deixa3 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa3 = 1;
                    else deixa3 = 0;
                    i--;
                }
            }
        }
        else deixa3=0;

        //Norte
        int deixa4 = 0;
        i = l - 1;
        j = c;
        if (e.grelha[l-1][c]!=e.peca) {
            while ((i >= 0) && (e.grelha[i][j] != e.peca)) { i--; }
            if ((i >= 0) && (e.grelha[i][j] == e.peca)) {
                i++;
                deixa4 = 1;
                while ((i != l) && (deixa4 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa4 = 1;
                    else deixa4 = 0;
                    i++;
                }
            }
        }
        else deixa4=0;

        // SudEste
        int deixa5 = 0;
        i = l + 1;
        j = c + 1;
        if (e.grelha[l+1][c+1]!=e.peca) {
            while ((i <= 7) && (j <= 7) && (e.grelha[i][j] != e.peca)) {
                i++;
                j++;
            }
            if ((i <= 7) && (j <= 7) && (e.grelha[i][j] == e.peca)) {
                i--;
                j--;
                deixa5 = 1;
                while ((i != l) && (j != c) && (deixa5 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa5 = 1;
                    else deixa5 = 0;
                    i--;
                    j--;
                }
            }
        }
        else deixa5=0;

        // NorOeste
        int deixa6 = 0;
        i = l - 1;
        j = c - 1;
        if (e.grelha[l-1][c-1]!=e.peca) {
            while ((i >= 0) && (j >= 0) && (e.grelha[i][j] != e.peca)) {
                i--;
                j--;
            }
            if ((i >= 0) && (j >= 0) && (e.grelha[i][j] == e.peca)) {
                i++;
                j++;
                deixa6 = 1;
                while ((i != l) && (j != c) && (deixa6 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa6 = 1;
                    else deixa6 = 0;
                    i++;
                    j++;
                }
            }
        }
        else deixa6=0;

        //SudOeste
        int deixa7 = 0;
        i = l + 1;
        j = c - 1;
        if (e.grelha[l+1][c-1]!=e.peca) {
            while ((i <= 7) && (j >= 0) && (e.grelha[i][j] != e.peca)) {
                i++;
                j--;
            }
            if ((i <= 7) && (j >= 0) && (e.grelha[i][j] == e.peca)) {
                i--;
                j++;
                deixa7 = 1;
                while ((i != l) && (j != c) && (deixa7 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa7 = 1;
                    else deixa7 = 0;
                    i--;
                    j++;
                }
            }
        }
        else deixa7=0;

        //NorEste
        int deixa8 = 0;
        i = l - 1;
        j = c + 1;
        if (e.grelha[l-1][c+1]!=e.peca) {
            while ((i >= 0) && (j <= 7) && (e.grelha[i][j] != e.peca)) {
                i--;
                j++;
            }
            if ((i >= 0) && (j <= 7) && (e.grelha[i][j] == e.peca)) {
                i++;
                j--;
                deixa8 = 1;
                while ((i != l) && (j != c) && (deixa8 == 1)) {
                    if ((e.grelha[i][j] != e.peca) && (e.grelha[i][j] != VAZIA)) deixa8 = 1;
                    else deixa8 = 0;
                    i++;
                    j--;
                }
            }
        }
        else deixa8=0;

        deixa = deixa1 + deixa2 + deixa3 + deixa4 + deixa5 + deixa6 + deixa7 + deixa8;
    }
    else deixa=0;

    return deixa;
}

// printar todas a jogadas possíveis para o jogador em jogo

void printarmos(ESTADO e){
    char d = ' ';
    printf("\n  1 2 3 4 5 6 7 8\n");
    int linhas=1;
    for (int i = 0; i < 8; i++) {
        printf("%d ",linhas);
        for (int j = 0; j < 8; j++) {
            if ((e.grelha[i][j]== VAZIA) && (validar(e,i,j)!=0)) d= '*';
            else if ((e.grelha[i][j]==VAZIA) && (validar(e,i,j)==0)) d='-';
            else if (e.grelha[i][j]==VALOR_O) d = 'O';
            else if(e.grelha[i][j]==VALOR_X) d ='X';

            printf("%c ", d);
        }
        linhas++;
        printf("\n");
    }
}


ESTADO sugestao (ESTADO e){
    if(e.modo==0){
        if (e.peca == VALOR_O) printf("\nM O\n");
        else if (e.peca == VALOR_X) printf("\nM X\n");
    }
    else if (e.modo!=0){
        if (e.peca == VALOR_X) {
            if(e.modo==1) printf("\nA X 1\n");
            else if(e.modo==2) printf("\nA X 2\n");
            else if(e.modo==3) printf("\nA X 3\n");
        }
        else if (e.peca == VALOR_O) {
            if(e.modo==1) printf("\nA O 1\n");
            else if(e.modo==2) printf("\nA O 2\n");
            else if(e.modo==3) printf("\nA O 3\n");
        }

    }
    printarmos(e);
    return e;
}
void help (ESTADO e) {
    int i, j;
    int curr = 0, min = 9999;
    int a=0, b=0;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (validar(e, i, j) != 0) {
                e.grelha[i][j]=VALOR_O;
                curr = avaliaTab(e);
                e.grelha[i][j]=VAZIA;
                if (min > curr) {
                    min = curr;
                    a = i;
                    b = j;
                }
            }
        }
    }
    e.grelha[a][b]=VALOR_help;
    printa (e);
    printf("Help: Posição %d %d", (a+1),(b+1));
}


int menu () {
    printf("Lista de comandos\n");
    printf("N: Iniciar o jogo\n");
    printf("J: Efetuar uma jogada\n");
    printf("U: Desfazer jogada\n");
    printf("L: Carregar jogo\n");
    printf("E: Salvar jogo\n");
    printf("S: Sugestão de jogada\n");
    printf("H: Ajuda\n");
    printf("A: Jogador vs Bot\n");
    printf("Q: Sair do jogo\n");
    printf("\nEscolha uma opção:");
}

int contador (ESTADO e) {
    int x=0;
    int o=0;
    int soma=0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (e.grelha[i][j]==VALOR_X) {
                x++;
            }
            else  if (e.grelha[i][j]==VALOR_O)
                o++;
        }
    }
    printf ("    \nX:%d     ",x);
    printf ("      O:%d \n",o);
    soma = x+o;
    return soma;

}
int passar (ESTADO e) {
    int validacao=0;
    int i,j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (validar(e, i, j) != 0) {
                validacao++;

            }
        }
    }
    return validacao; // 0 nao tem jogadas
}

int acabou (ESTADO e){
    int final=0;
    int validacao=0;
    int i,j;
    int contar;
    contar=contadorO(e)+contadorX(e);
    e.peca=VALOR_X;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (validar(e, i, j) != 0) {
                validacao = 1;
            }
        }
    }
    e.peca=VALOR_O;
    if (validacao!=1) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (validar(e, i, j) != 0) {
                    validacao = 1;
                }
            }
        }
    }
    if ((contar==64) || (validacao==0)) final=1;
    else final=0;
    return final;
}

// final=0 o jogo ainda nao acabou


ESTADO jogador(ESTADO e) {
    // com recurso aos comandos, esra função apenas permite alerta ao jogador para efetuar a sua jogada
    // através do comando J

    printf("Efetue a sua jogada, através do comando J\n");

    return e;
}


ESTADO botfacil (ESTADO e) {
    // Função onde o bot joga, estratégia: percorre todos as posições, a primeira onde for valido jogar, efetua a jogada
    // e sai do ciclo, ou seja, passa a vez ao jogador;
    if (passar(e)!=0) {
        int i, j;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (validar(e, i, j) != 0) {
                    e = joga(e, i, j);
                    printa(e);
                    if (acabou(e) == 1) {
                        if (contadorX(e) > contadorO(e)) printf("Jogo acabou! Vencedor: X!");
                        else if (contadorX(e) < contadorO(e)) printf("Jogo acabou! Vencedor: O!");
                        else printf("Empate!");
                    }
                    else {
                        printf("\n\nO Bot jogou na posicao %d %d\n", i + 1, j + 1);
                        e = jogador(e);
                    }
                    i = 8;
                    j = 8;
                }
            }
        }
    }
    else if ((passar(e)==0)&&(acabou(e)!=1)){
        printf("Sem Jogadas.Passou a vez.");
        e.peca=inv[e.peca];
        jogador(e);
    }

    return e;
}



ESTADO facil (ESTADO e, char c2) {

    // já selecionado o nível, dependendo da peça que a pessoa selecionou para o bot, começa o jogo pelo jogador ou pelo bot
    // se selecionou X entao o bot começa, caso contrário sera o jogador
    if (c2=='X') e=botfacil(e);
    else if (c2=='O') e=jogador(e);
    return e;
}

int contadorX (ESTADO e) {
    int x=0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (e.grelha[i][j]==VALOR_X) {
                x++;
            }
        }
    }
    return x;

}

int contadorO (ESTADO e) {
    int x=0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (e.grelha[i][j]==VALOR_O) {
                x++;
            }
        }
    }
    return x;

}

ESTADO botmedio (ESTADO e) {
    if (passar(e) != 0) {
        e.fim = 1; //ainda esta a jogar
        ESTADO f;
        int i, j, a = 0, b = 0;
        int curr = 0, max = 0;

        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (validar(e, i, j) != 0) {
                    f = valida(e, i, j);
                    if (e.peca == VALOR_X)
                        curr = contadorX(f) - contadorX(e) - 1;
                    if (e.peca == VALOR_O)
                        curr = contadorO(f) - contadorO(e) - 1;
                    if (curr > max) {
                        max = curr;
                        a = i;
                        b = j;
                    }
                }
            }
        }
        e = joga(e, a, b);
        printa(e);
        if (acabou(e) == 1) {
            if (contadorX(e) > contadorO(e)) printf("Jogo acabou! Vencedor: X!");
            else if (contadorX(e) < contadorO(e)) printf("Jogo acabou! Vencedor: O!");
            else printf("Empate!");
        } else {
            printf("\n\nO Bot jogou na posicao %d %d\n", a + 1, b + 1);
            e = jogador(e);
        }
        return e;
    }
}


ESTADO medio (ESTADO e, char c2){
    if (c2=='X') e=botmedio(e);
    if (c2=='O') e=jogador(e);
    return e;
}

int avaliaTab (ESTADO e) {
    int i = 0;
    if (e.grelha[0][0] == VAZIA) i +=99;
    if (e.grelha[0][1] == VAZIA) i +=-8;
    if (e.grelha[0][2] == VAZIA) i += 8;
    if (e.grelha[0][3] == VAZIA) i += 6;
    if (e.grelha[0][4] == VAZIA) i += 6;
    if (e.grelha[0][5] == VAZIA) i += 8;
    if (e.grelha[0][6] == VAZIA) i +=-8;
    if (e.grelha[0][7] == VAZIA) i +=99;
    if (e.grelha[1][0] == VAZIA) i +=-8;
    if (e.grelha[1][1] == VAZIA) i +=-24;
    if (e.grelha[1][2] == VAZIA) i +=-4;
    if (e.grelha[1][3] == VAZIA) i +=-3;
    if (e.grelha[1][4] == VAZIA) i +=-3;
    if (e.grelha[1][5] == VAZIA) i +=-4;
    if (e.grelha[1][6] == VAZIA) i +=-24;
    if (e.grelha[1][7] == VAZIA) i +=-8;
    if (e.grelha[2][0] == VAZIA) i += 8;
    if (e.grelha[2][1] == VAZIA) i +=-4;
    if (e.grelha[2][2] == VAZIA) i += 7;
    if (e.grelha[2][3] == VAZIA) i += 4;
    if (e.grelha[2][4] == VAZIA) i += 4;
    if (e.grelha[2][5] == VAZIA) i += 7;
    if (e.grelha[2][6] == VAZIA) i +=-4;
    if (e.grelha[2][7] == VAZIA) i +=-8;
    if (e.grelha[3][0] == VAZIA) i += 6;
    if (e.grelha[3][1] == VAZIA) i +=-3;
    if (e.grelha[3][2] == VAZIA) i += 4;
    if (e.grelha[3][3] == VAZIA) i += 0;
    if (e.grelha[3][4] == VAZIA) i += 0;
    if (e.grelha[3][5] == VAZIA) i += 4;
    if (e.grelha[3][6] == VAZIA) i +=-3;
    if (e.grelha[3][7] == VAZIA) i += 6;
    if (e.grelha[4][0] == VAZIA) i += 6;
    if (e.grelha[4][1] == VAZIA) i +=-3;
    if (e.grelha[4][2] == VAZIA) i += 4;
    if (e.grelha[4][3] == VAZIA) i += 0;
    if (e.grelha[4][4] == VAZIA) i += 0;
    if (e.grelha[4][5] == VAZIA) i += 4;
    if (e.grelha[4][6] == VAZIA) i +=-3;
    if (e.grelha[4][7] == VAZIA) i += 6;
    if (e.grelha[5][0] == VAZIA) i += 8;
    if (e.grelha[5][1] == VAZIA) i +=-4;
    if (e.grelha[5][2] == VAZIA) i += 7;
    if (e.grelha[5][3] == VAZIA) i += 4;
    if (e.grelha[5][4] == VAZIA) i += 4;
    if (e.grelha[5][5] == VAZIA) i += 7;
    if (e.grelha[5][6] == VAZIA) i +=-4;
    if (e.grelha[5][7] == VAZIA) i +=-8;
    if (e.grelha[6][0] == VAZIA) i +=-8;
    if (e.grelha[6][1] == VAZIA) i +=-24;
    if (e.grelha[6][2] == VAZIA) i +=-4;
    if (e.grelha[6][3] == VAZIA) i +=-3;
    if (e.grelha[6][4] == VAZIA) i +=-3;
    if (e.grelha[6][5] == VAZIA) i +=-4;
    if (e.grelha[6][6] == VAZIA) i +=-24;
    if (e.grelha[6][7] == VAZIA) i +=-8;
    if (e.grelha[7][0] == VAZIA) i +=99;
    if (e.grelha[7][1] == VAZIA) i +=-8;
    if (e.grelha[7][2] == VAZIA) i += 8;
    if (e.grelha[7][3] == VAZIA) i += 6;
    if (e.grelha[7][4] == VAZIA) i += 6;
    if (e.grelha[7][5] == VAZIA) i += 8;
    if (e.grelha[7][6] == VAZIA) i +=-8;
    if (e.grelha[7][7] == VAZIA) i +=99;
    return i;
}

ESTADO botdificil (ESTADO e){
        if (passar(e) != 0) {
            e.fim=1;
            int i, j;
            ESTADO f;
            int curr = 0, min = 9999;
            int a = 0, b = 0;
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    if (validar(e, i, j) != 0) {
                        f = valida(e, i, j);
                        curr = avaliaTab(f);
                        if (min > curr) {
                            min = curr;
                            a = i;
                            b = j;
                        }
                    }
                }
            }
            e = joga(e, a, b);
            printa(e);
            if (acabou (e)==1) {
                if (contadorX(e) > contadorO(e)) printf("Jogo acabou! Vencedor: X!\n");
                else if (contadorX(e) < contadorO(e)) printf("Jogo acabou! Vencedor: O!\n");
                else printf ("Empate!\n");
            }
            else {
                printf("\n\nO Bot jogou na posicao %d %d\n", a + 1, b + 1);
                e = jogador(e);
            }
        }

    return e;

}

ESTADO dificil (ESTADO e, char c2){
    if (c2=='X') e=botdificil(e);
    if (c2=='O') e=jogador(e);
    return e;
}


ESTADO bot (ESTADO e, char c2, int c3) {
    // dependendo do nível selecionado pela pessoa, vai a cada auxiliar; é smp acompanhado pela peça que a pessoa
    // selecionou para o bot

    if (c3==1) {e.modo=1;
        e=facil(e,c2);}
    else if (c3==2){e.modo=2;
        e=medio(e,c2); }
    else if (c3==3){e.modo=3;
        e=dificil(e,c2); }
    else printf("Nível Inválido\n");

    return e;
}


void push (ESTADO e){
    struct Node* temp;
    temp = malloc(sizeof(struct Node));
    temp->estado = e;
    temp->prox = top;
    top = temp;
}


void pop(){
    struct Node* temp;
    temp = top;
    top = top->prox;
    free(temp);
}



ESTADO undo(){
    struct Node* temp;
    if (top == NULL) {
        printf("\nStack vazia");
    }
    else {
        temp = top;
        ESTADO e = temp->estado;
        if (e.modo==0) {
            if (e.peca == VALOR_X) {
                e.peca = VALOR_O;
                printf("\nM O\n");
            }
            else if (e.peca == VALOR_O) {
                e.peca = VALOR_X;
                printf("\nM X\n");
            }
        }
        else if (e.modo!=0){
            if (e.peca == VALOR_X) {
                if(e.modo==1) printf("\nA X 1\n");
                else if(e.modo==2) printf("\nA X 2\n");
                else if(e.modo==3) printf("\nA X 3\n");
            }
            else if (e.peca == VALOR_O) {
                if(e.modo==1) printf("\nA O 1\n");
                else if(e.modo==2) printf("\nA O 2\n");
                else if(e.modo==3) printf("\nA O 3\n");
            }

        }
        printa(temp->estado);
        contador(temp->estado);
    }
    return temp->estado;
}



