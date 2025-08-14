#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 10
#define WATER 0
#define SHIP  3
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
    for (int c = 0; c < BOARD_SIZE; c++) {
        printf("%2d ", c);
    }
    printf("\n    ");
    for (int c = 0; c < BOARD_SIZE; c++) {
        printf("---");
    }
    printf("\n");

    for (int lin = 0; lin < BOARD_SIZE; lin++) {
        printf("%2d |", lin);
        for (int col = 0; col < BOARD_SIZE; col++) {
            printf(" %d ", board[lin][col]);
        }
        printf("\n");
    }
}

// Verifica se o navio cabe no tabuleiro (H, V, D, d)
bool fitsInsideBoard(int row, int col, char orientation) {
    switch (orientation) {
        case 'H': return col + SHIP_SIZE <= BOARD_SIZE;
        case 'V': return row + SHIP_SIZE <= BOARD_SIZE;
        case 'D': // diagonal principal ↘
            return row + SHIP_SIZE <= BOARD_SIZE && col + SHIP_SIZE <= BOARD_SIZE;
        case 'd': // diagonal secundária ↙
            return row + SHIP_SIZE <= BOARD_SIZE && col - (SHIP_SIZE - 1) >= 0;
        default: return false;
    }
}

// Verifica se não há sobreposição
bool hasNoOverlap(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, char orientation) {
    switch (orientation) {
        case 'H':
            for (int i = 0; i < SHIP_SIZE; i++)
                if (board[row][col + i] != WATER) return false;
            break;
        case 'V':
            for (int i = 0; i < SHIP_SIZE; i++)
                if (board[row + i][col] != WATER) return false;
            break;
        case 'D':
            for (int i = 0; i < SHIP_SIZE; i++)
                if (board[row + i][col + i] != WATER) return false;
            break;
        case 'd':
            for (int i = 0; i < SHIP_SIZE; i++)
                if (board[row + i][col - i] != WATER) return false;
            break;
    }
    return true;
}

// Posiciona o navio
bool placeShip(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, char orientation) {
    if (!fitsInsideBoard(row, col, orientation) || !hasNoOverlap(board, row, col, orientation)) {
        return false;
    }

    switch (orientation) {
        case 'H':
            for (int i = 0; i < SHIP_SIZE; i++)
                board[row][col + i] = SHIP;
            break;
        case 'V':
            for (int i = 0; i < SHIP_SIZE; i++)
                board[row + i][col] = SHIP;
            break;
        case 'D':
            for (int i = 0; i < SHIP_SIZE; i++)
                board[row + i][col + i] = SHIP;
            break;
        case 'd':
            for (int i = 0; i < SHIP_SIZE; i++)
                board[row + i][col - i] = SHIP;
            break;
    }
    return true;
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    initBoard(board);

    // Definição das coordenadas (fixas no código)
    int startRowH = 2, startColH = 1; // Horizontal
    int startRowV = 0, startColV = 7; // Vertical
    int startRowD = 4, startColD = 0; // Diagonal principal ↘
    int startRowd = 5, startCold = 9; // Diagonal secundária ↙

    // Posicionando os navios
    if (!placeShip(board, startRowH, startColH, 'H'))
        printf("Erro ao posicionar navio horizontal.\n");
    if (!placeShip(board, startRowV, startColV, 'V'))
        printf("Erro ao posicionar navio vertical.\n");
    if (!placeShip(board, startRowD, startColD, 'D'))
        printf("Erro ao posicionar navio diagonal principal.\n");
    if (!placeShip(board, startRowd, startCold, 'd'))
        printf("Erro ao posicionar navio diagonal secundaria.\n");

    printf("Tabuleiro 10x10 - 0 = agua | 3 = navio\n");
    printBoard(board);

    return 0;
}
