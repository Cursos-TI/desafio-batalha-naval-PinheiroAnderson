#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 10
#define WATER 0
#define SHIP  3
#define SHIP_SIZE 3

// Função para inicializar o tabuleiro
void initBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int lin = 0; lin < BOARD_SIZE; lin++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board[lin][col] = WATER;
        }
    }
}

// Função para imprimir o tabuleiro
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("    ");
    for (int c = 0; c < BOARD_SIZE; c++) {
        printf("%2d ", c);
    }
    printf("\n");

    printf("    ");
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

// Verifica se o navio cabe no tabuleiro
bool fitsInsideBoard(int row, int col, char orientation) {
    if (orientation == 'H') {
        return col + SHIP_SIZE <= BOARD_SIZE;
    } else if (orientation == 'V') {
        return row + SHIP_SIZE <= BOARD_SIZE;
    }
    return false;
}

// Verifica se a posição está livre
bool hasNoOverlap(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, char orientation) {
    if (orientation == 'H') {
        for (int i = 0; i < SHIP_SIZE; i++) {
            if (board[row][col + i] != WATER) return false;
        }
    } else {
        for (int i = 0; i < SHIP_SIZE; i++) {
            if (board[row + i][col] != WATER) return false;
        }
    }
    return true;
}

// Posiciona o navio
bool placeShip(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, char orientation) {
    if (!fitsInsideBoard(row, col, orientation) || !hasNoOverlap(board, row, col, orientation)) {
        return false;
    }
    if (orientation == 'H') {
        for (int i = 0; i < SHIP_SIZE; i++) {
            board[row][col + i] = SHIP;
        }
    } else {
        for (int i = 0; i < SHIP_SIZE; i++) {
            board[row + i][col] = SHIP;
        }
    }
    return true;
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    initBoard(board);

    // Coordenadas dos navios definidas no código
    int startRowH = 2, startColH = 1; // horizontal
    int startRowV = 0, startColV = 7; // vertical

    if (!placeShip(board, startRowH, startColH, 'H')) {
        printf("Erro ao posicionar navio horizontal.\n");
        return 1;
    }

    if (!placeShip(board, startRowV, startColV, 'V')) {
        printf("Erro ao posicionar navio vertical.\n");
        return 1;
    }

    printf("Tabuleiro 10x10 - 0 = água | 3 = navio\n");
    printBoard(board);

    return 0;
}
