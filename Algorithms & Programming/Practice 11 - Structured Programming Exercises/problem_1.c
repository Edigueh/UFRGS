/*********************************************************************
* @brief   Problema 1: .
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    04/06/2025
**
Imagens em tons de cinza em computação podem ser representadas como matrizes de pixels, onde
cada pixel apresenta uma tonalidade inteira entre preto (0) e branco (255). Uma das operações mais
elementares é a binarização, que consiste em transformar todos os valores da imagem para preto (0)
ou branco (255), sem valores intermediários, a depender de um valor limite (threshold). Todos os
pixels maiores que este limite viram branco (255) e todos os menores viram preto (0).

Faça um programa que leia inicialmente a dimensão N da imagem, ou seja, o tamanho da matriz
quadrada. 2 <= N <= 10, faça validação de N. Após, ler os valores que compõem a imagem m1
entre 0 e 255 (não precisa validar). Gere uma nova matriz m2 também NxN que altera todos os
valores de m1 maiores que um valor limite (threshold) para 255 e todos valores menores para 0. O
valor limite (threshold) deve ser obtido calculando a média entre os valores de m1. Considere N = 3
para fins de teste, embora seu programa deva funcionar para qualquer valor inteiro de N. Informe o
limite (threshold) e a matriz resultante ao usuário. O seu programa deve ter no mínimo as
seguintes funções:

// Le uma matriz com as dimensoes especificadas
void LeMatriz(int imagem[][COLUNAS], int linhas, int colunas);

// Imprime na tela uma matriz com as dimensoes especificadas
void imprimeMatriz(int imagem[][COLUNAS], int linhas, int colunas);

// Calcula e retorna o valor medio da matriz com as dimensoes especificadas
float calculaMedia(int imagem[][COLUNAS], int linhas, int colunas);

//Usa o valor medio da matriz m1 para calcular a matriz binaria m2
void aplicaFiltro(int m1[][COLUNAS], int m2[][COLUNAS], int linhas, int colunas, float media);

Abaixo exemplo de execução:
Insira o número de linhas e colunas da imagem: 3 3
Insira os 9 valores da imagem:
10 50 40
120 65 15
170 14 16
Matriz Original:
10 50 40
120 65 15
170 14 16
A media da matriz lida: 55.56
Matriz Binarizada:
0 0 0
255 255 0
255 0 0
Outro exemplo
Insira o número de linhas e colunas da imagem: 4 4
Insira os 16 valores da imagem:
10 10 10 10
50 50 50 50
200 200 200 200
250 250 250 250
Matriz Original:
10 10 10 10
50 50 50 50
200 200 200 200
250 250 250 250
A media da matriz lida: 127.50
Matriz Binarizada:
0 0 0 0
0 0 0 0
255 255 255 255
255 255 255 255
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define WHITE 255

int LINHAS, COLUNAS;

// Le uma matriz com as dimensoes especificadas.
void LeMatriz(int imagem[LINHAS][COLUNAS], int linhas, int colunas);

// Imprime na tela uma matriz com as dimensoes especificadas.
void imprimeMatriz(int imagem[LINHAS][COLUNAS], int linhas, int colunas);

// Calcula e retorna o valor medio da matriz com as dimensoes especificadas.
float calculaMedia(int imagem[LINHAS][COLUNAS], int linhas, int colunas);

// Usa o valor medio da matriz m1 para calcular a matriz binaria m2.
void aplicaFiltro(int m1[LINHAS][COLUNAS], int m2[LINHAS][COLUNAS], int linhas, int colunas, float media);

int main(void) {
    do {
        printf("Insira o número de linhas e colunas da imagem: ");
        scanf("%d %d", &LINHAS, &COLUNAS);
        if (LINHAS < 2 || LINHAS > 10 || COLUNAS < 2 || COLUNAS > 10) {
            printf("As entradas N devem respeitar 2 <= N <= 10\n");
        }
    } while (LINHAS < 2 || LINHAS > 10 || COLUNAS < 2 || COLUNAS > 10);

    int imagem[LINHAS][COLUNAS];
    LeMatriz(imagem, LINHAS, COLUNAS);
    printf("\nMatriz Original:\n");
    imprimeMatriz(imagem, LINHAS, COLUNAS);

    float avg =  calculaMedia(imagem, LINHAS, COLUNAS);
    printf("A media da matriz lida: %.2f\n", avg);

    int bin_matrix[LINHAS][COLUNAS];
    aplicaFiltro(imagem, bin_matrix, LINHAS, COLUNAS, avg);
    printf("\nMatriz Binarizada:\n");
    imprimeMatriz(bin_matrix, LINHAS, COLUNAS);

    return EXIT_SUCCESS;
}

void LeMatriz(int imagem[LINHAS][COLUNAS], int linhas, int colunas) {
    printf("Insira os %d valores da imagem:\n", linhas * colunas);

    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++){
            scanf("%d", &imagem[i][j]);
        }
    }
    return;
}

void imprimeMatriz(int imagem[LINHAS][COLUNAS], int linhas, int colunas) {
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++){
            printf("%d ", imagem[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

float calculaMedia(int imagem[LINHAS][COLUNAS], int linhas, int colunas) {
    float elements_sum = 0;
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++){
            elements_sum += imagem[i][j] ;
        }
    }

    return (float)elements_sum / (linhas * colunas);
}

void aplicaFiltro(int m1[LINHAS][COLUNAS], int m2[LINHAS][COLUNAS], int linhas, int colunas, float media) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if ((float)m1[i][j] < media){
                m2[i][j] = BLACK;
            } else {
                m2[i][j] = WHITE;
            }
        }
    }

    return;
}
