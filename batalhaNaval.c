#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 10
#define WATER 0
#define SHIP  3
#define EFFECT 5
#define SHIP_SIZE 3

// Inicializa o tabuleiro com água
void initBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int lin = 0; lin < BOARD_SIZE; lin++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board[lin][col] = WATER;
        }
    }
}

// Imprime o tabuleiro no console
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("    ");
    for (int c = 0; c < BOARD_SIZE; c++)
        printf("%2d ", c);
    printf("\n    ");
    for (int c = 0; c < BOARD_SIZE; c++)
        printf("---");
    printf("\n");

    for (int lin = 0; lin < BOARD_SIZE; lin++) {
        printf("%2d |", lin);
        for (int col = 0; col < BOARD_SIZE; col++) {
            printf(" %d ", board[lin][col]);
        }
        printf("\n");
    }
}

// Funções do nível Aventureiro para posicionamento de navios
bool fitsInsideBoard(int row, int col, char orientation) {
    switch (orientation) {
        case 'H': return col + SHIP_SIZE <= BOARD_SIZE;
        case 'V': return row + SHIP_SIZE <= BOARD_SIZE;
        case 'D': return row + SHIP_SIZE <= BOARD_SIZE && col + SHIP_SIZE <= BOARD_SIZE;
        case 'd': return row + SHIP_SIZE <= BOARD_SIZE && col - (SHIP_SIZE-1) >= 0;
        default: return false;
    }
}

bool hasNoOverlap(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, char orientation) {
    switch (orientation) {
        case 'H':
            for (int i=0;i<SHIP_SIZE;i++) if (board[row][col+i]!=WATER) return false;
            break;
        case 'V':
            for (int i=0;i<SHIP_SIZE;i++) if (board[row+i][col]!=WATER) return false;
            break;
        case 'D':
            for (int i=0;i<SHIP_SIZE;i++) if (board[row+i][col+i]!=WATER) return false;
            break;
        case 'd':
            for (int i=0;i<SHIP_SIZE;i++) if (board[row+i][col-i]!=WATER) return false;
            break;
    }
    return true;
}

bool placeShip(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, char orientation) {
    if (!fitsInsideBoard(row,col,orientation) || !hasNoOverlap(board,row,col,orientation)) return false;

    switch (orientation) {
        case 'H':
            for (int i=0;i<SHIP_SIZE;i++) board[row][col+i] = SHIP;
            break;
        case 'V':
            for (int i=0;i<SHIP_SIZE;i++) board[row+i][col] = SHIP;
            break;
        case 'D':
            for (int i=0;i<SHIP_SIZE;i++) board[row+i][col+i] = SHIP;
            break;
        case 'd':
            for (int i=0;i<SHIP_SIZE;i++) board[row+i][col-i] = SHIP;
            break;
    }
    return true;
}

// --------------------- Funções Mestre ------------------------

// Aplica uma matriz de habilidade sobre o tabuleiro
void applyAbility(int board[BOARD_SIZE][BOARD_SIZE],
                  int ability[5][5],
                  int originRow, int originCol) {
    int abilitySize = 5;
    int center = abilitySize/2; // ponto central da matriz

    for (int i=0;i<abilitySize;i++) {
        for (int j=0;j<abilitySize;j++) {
            if (ability[i][j]==1) {
                int targetRow = originRow + (i - center);
                int targetCol = originCol + (j - center);

                // Verifica limites do tabuleiro
                if (targetRow>=0 && targetRow<BOARD_SIZE &&
                    targetCol>=0 && targetCol<BOARD_SIZE) {
                    // Marca a área de efeito apenas se não houver navio
                    if (board[targetRow][targetCol] == WATER)
                        board[targetRow][targetCol] = EFFECT;
                }
            }
        }
    }
}

// Cria as matrizes de habilidade
void createAbilities(int cone[5][5], int cross[5][5], int octa[5][5]) {
    // Cone ↘ (topo em cima, base expandindo)
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if (j>=2-i && j<=2+i) cone[i][j]=1;
            else cone[i][j]=0;
        }
    }
    // Cruz
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if (i==2 || j==2) cross[i][j]=1;
            else cross[i][j]=0;
        }
    }
    // Octaedro (losango)
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if (j>=2-abs(2-i) && j<=2+abs(2-i)) octa[i][j]=1;
            else octa[i][j]=0;
        }
    }
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    initBoard(board);

    // ----------- Posicionamento de navios -----------
    int startRowH=2, startColH=1;
    int startRowV=0, startColV=7;
    int startRowD=4, startColD=0;
    int startRowd=5, startCold=9;

    placeShip(board,startRowH,startColH,'H');
    placeShip(board,startRowV,startColV,'V');
    placeShip(board,startRowD,startColD,'D');
    placeShip(board,startRowd,startCold,'d');

    // ----------- Criação de habilidades -----------
    int cone[5][5], cross[5][5], octa[5][5];
    createAbilities(cone,cross,octa);

    // ----------- Pontos de origem no tabuleiro -----------
    int originConeRow=1, originConeCol=2;
    int originCrossRow=6, originCrossCol=5;
    int originOctaRow=3, originOctaCol=7;

    // ----------- Aplica habilidades sobre o tabuleiro -----------
    applyAbility(board,cone,originConeRow,originConeCol);
    applyAbility(board,cross,originCrossRow,originCrossCol);
    applyAbility(board,octa,originOctaRow,originOctaCol);

    // ----------- Exibe o tabuleiro final -----------
    printf("Tabuleiro 10x10 - 0=agua | 3=navio | 5=area de efeito\n");
    printBoard(board);

    return 0;
}
