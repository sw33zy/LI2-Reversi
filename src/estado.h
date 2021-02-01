#ifndef PROJETOINICIAL_ESTADO_H
#define PROJETOINICIAL_ESTADO_H



/*
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/


// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O,VALOR_help} VALOR;


/*
Estrutura que armazena o estado do jogo
*/
typedef struct estado {
    VALOR peca; // peça do jogador que vai jogar!
    VALOR grelha[8][8];
    char modo; // modo em que se está a jogar! 0-> manual, 1-> contra computador nivel 1 , 2 -> nivel 2 , 3-> nivel 3
    char fim; // 0 acabou a sua vez ........ 1 ainda esta a jogar;
} ESTADO;


void printa(ESTADO);
ESTADO inicia (ESTADO e,VALOR v);
ESTADO valida(ESTADO e,int l,int c);

ESTADO joga (ESTADO e, int x, int y);

ESTADO load (ESTADO ,char []);
void save (ESTADO ,char []);
int validar(ESTADO e,int l,int c);
void printarmos(ESTADO e);
ESTADO sugestao (ESTADO e);
void help (ESTADO e);
int contador (ESTADO e);
ESTADO bot (ESTADO e, char c2, int c3);
ESTADO facil (ESTADO e, char c2);
ESTADO medio (ESTADO e, char c2);
ESTADO dificil (ESTADO e, char c2);
int acabou (ESTADO e);
ESTADO jogador (ESTADO e);
ESTADO botfacil (ESTADO e);
int menu ();
ESTADO anula (ESTADO e);
ESTADO botmedio (ESTADO e);
int contadorX (ESTADO e);
int contadorO (ESTADO e);
ESTADO botdificil (ESTADO e);
int passar (ESTADO e);




struct Node {
    ESTADO estado;
    struct Node* prox;
} Node;

struct Node* top;


void push(ESTADO e);

void pop();
ESTADO undo();

int avaliaTab (ESTADO e);


#endif //PROJETOINICIAL_ESTADO_H
