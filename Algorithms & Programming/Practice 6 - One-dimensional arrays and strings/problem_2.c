/*********************************************************************
* @brief   Problema 2: 
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    28/04/2025
**
Escreva um programa em C que leia uma quantidade indefinida, mas limitada de
valores reais positivos (um valor negativo é usado para indicar o fim da entrada de dados e não faz
parte dos valores lidos), e armazene-os em um arranjo unidimensional. O número máximo de
valores a ser lido é definido por um #define MAXLIDOS 10, mas o usuário pode digitar menos
valores que esse máximo. Após leitura, o programa deve calcular e imprimir na tela:
a) A média dos quadrados dos valores informados;
b) A média das raízes quadradas dos valores informados;
c) A quantidade de valores que estão entre as duas médias calculadas acima (incluindo os
extremos).
Exemplo de execução:
Entre os valores: 2 3 5 1 2.4 3 -5
Media dos quadrados: 8.960000
Media das raizes quadradas: 1.610596
Quantidade de valores entre as duas medias: 5
Entre os valores: 1.1 2.3 5.5 -7
Media dos quadrados: 12.250000
Media das raizes quadrados: 1.636864
Quantidade de valores entre as duas medias 2
Entre os valores: 1 2 3 4 5 6 7 8 9 10 11 12
Media dos quadrados: 38.500000
Media das raizes quadrados: 2.246828
Quantidade de valores entre as duas medias 8
(Neste exemplo, ele lê até o limite de 10 valores!)
***********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXLIDOS 10

float get_squares_avg(float inputs[], int n) {
    float squares_avg = 0;
    for (int i = 0; i < n; i++){
        squares_avg += pow(inputs[i], 2);
    }

    return squares_avg / n;
}

float get_sqroots_avg(float inputs[], int n) {
    float sqroots_avg = 0;
    for (int i = 0; i < n; i++){
        sqroots_avg += sqrt(inputs[i]);
    }

    return sqroots_avg / n;
}

int get_number_of_elements_between_values(float inputs[], int n_entries, float value_a, float value_b){
    float min, max;
    int n_elements = 0;
    if (value_a < value_b) {
        min = value_a;
        max = value_b;
    } else {
        min = value_b;
        max = value_a;
    }

    for(int i = 0; i < n_entries; i++) {
        if (inputs[i] >= min && inputs[i] <= max) n_elements++;
    }

    return n_elements;
}

int main(void) {
    float inputs[MAXLIDOS];
    int n_entries = 0;
    printf("Entre os valores: ");

    /* lê até valor negativo ou até atingir MAXLIDOS */
    float entry;
    do {
        scanf(" %f", &entry);
        if (entry > 0.0f) {
            inputs[n_entries++] = entry;
        }
    } while (entry > 0.0f && n_entries < MAXLIDOS);

    float squares_avg = get_squares_avg(inputs, n_entries);
    float sqroots_avg = get_sqroots_avg(inputs, n_entries);
    printf("Media dos quadrados: %f\n", squares_avg);
    printf("Media das raizes quadradas: %f\n", sqroots_avg);
    printf("Quantidade de valores entre as duas medias: %d\n", get_number_of_elements_between_values(inputs, n_entries, squares_avg, sqroots_avg));

    return EXIT_SUCCESS;
}
