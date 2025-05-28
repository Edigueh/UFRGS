/*********************************************************************
* @brief   Problema 1: Soma dos pares até N e soma dos quadrados pares até N.
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    07/04/2025
**
Faça um programa que leia um valor inteiro N ≥ 0 do teclado. Após, o programa deve
calcular e imprimir na tela os valores de
S1 = 0 + 2 + 4 + 6 +...+M
S2 = 0^2 + 2^2 + 4^2 + 6^2 + M^2
onde M é o “maior número par menor ou igual a N”.
Exemplo de execução:
Entre com o valor de N: 9
Valor de S1: 20
Valor de S2: 120
Entre com o valor de N: 21
Valor de S1: 110
Valor de S2: 1540
***********************************************************************/
#include <stdio.h>
#include <math.h>

typedef struct {
    int s1;
    int s2;
} Sums;

Sums calc_sums(int n) {
    Sums result = {0, 0};

    for(int i = 2; i < n; i += 2) {
        result.s1 += i;
        result.s2 += pow(i, 2);
    }

    return result;
}

int main(void) {
    int n;

    printf("Entre com o valor de N: ");
    scanf(" %d", &n);

    Sums sums = calc_sums(n);

    printf("Valor de S1: %d\n", sums.s1);
    printf("Valor de S2: %d\n", sums.s2);

    return 0;
}
