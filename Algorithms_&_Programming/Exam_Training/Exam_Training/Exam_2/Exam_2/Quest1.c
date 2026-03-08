#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_D 9

void leMatriz(int matrix[MAX_D][MAX_D], int d) {
    printf("Entre com a matriz:\n");
    for(int r = 0; r < d; r++) {
        for (int c = 0; c < d; c++) {
            printf("matrix[%d][%d]: ", r, c);
            scanf("%d", &matrix[r][c]);
        }
    }
}

bool assertRows(int matrix [MAX_D][MAX_D], int d) {
    int rowsSum[MAX_D] = {0};
    for(int r = 0; r < d; r++) {
        for(int c = 0; c < d; c++){
            rowsSum[r] += matrix[r][c];
        }
    }

    for (int i = 1; i < d; i++) if (rowsSum[i] != rowsSum[i - 1]) return false;
    return true;
}

bool assertColumns(int matrix [MAX_D][MAX_D], int d) {
    int colsSum[MAX_D] = {0};
    for(int c = 0; c < d; c++) {
        for(int r = 0; r < d; r++){
            colsSum[c] += matrix[r][c];
        }
    }

    for (int i = 1; i < d; i++) if (colsSum[i] != colsSum[i - 1]) return false;
    return true;
}

int main(void) {
    int d = 0;
    while ( d < 3 || d > MAX_D) {
        printf("Insira a dimensão da matrix(3<=d<=9): ");
        scanf("%d", &d);
    }
    int matrix[MAX_D][MAX_D];
    leMatriz(matrix, d);

    if(assertRows(matrix, d) && assertColumns(matrix, d)) {
        printf ("Matriz satisfaz a condição!\n");
    } else printf ("Matriz NÃO satisfaz a condição!\n");

    return EXIT_SUCCESS;
}
