/*********************************************************************
* @brief   Problema 1: Matrix Populator
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    05/05/2025
**
Preencha uma matriz de dimensão 4x4 com números aleatórios no intervalo [2,40].
Imprima a matriz obtida na tela em formato de matriz. Em seguida monte um vetor, a partir da
matriz gerada com os maiores elementos de cada coluna. Imprima o vetor que você montou. Veja
abaixo exemplo de execução (procure na aula 13 o uso da função rand() para geração de números
aleatórios).
Matriz
38 36 11 22
28 40 31 6
18 32 17 8
17 30 35 29
Arranjo maiores elementos colunas:
38 40 35 29
// Dicas para geração de valores aleatórios
#include <time.h> // para acessar o relogio do sistema
#include <stdlib.h> // para usar rand(), srand()
srand(time(NULL)); / / inicializa a semente dinamicamente
r = min + (rand() % (max - min + 1)); // gera numero inteiro entre min e max
***********************************************************************/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MIN_RAND 2
#define MAX_RAND 40

#define MATRIX_ROWS 4
#define MATRIX_COLUMNS 4

int main(void) {

    int rand_matrix[MATRIX_ROWS][MATRIX_COLUMNS];
    int max_col_number[MATRIX_COLUMNS] = { MIN_RAND };
    srand(time(NULL));

    printf("-----Matriz-----\n");
    for(int row = 0; row < MATRIX_ROWS; row++) {
        for(int col = 0; col < MATRIX_COLUMNS; col++) {
            rand_matrix[row][col] = MIN_RAND + (rand() % (MAX_RAND - MIN_RAND + 1));

            printf("%d     ", rand_matrix[row][col]);

            if(rand_matrix[row][col] > max_col_number[col]) {
                max_col_number[col] = rand_matrix[row][col];
            }
        }
        printf("\n");
    }

    printf("Arranjo maiores elementos colunas:\n");
    for(int i = 0; i < MATRIX_COLUMNS; i++) printf("%d ", max_col_number[i]);
    printf("\n");

    return EXIT_SUCCESS;
}