/*********************************************************************
* @brief   Problema 1: Série de Taylor-Maclaurin
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    07/04/2025
**
𝑠𝑒𝑛(𝑥) = 𝑥 − (𝑥^3)/3! + (𝑥^5)/5! − …

Na prática, pode-se aproximar o valor da série acima usando os N primeiros termos apenas, onde N
é um valor inteiro positivo. Escreva um programa em C que leia um ângulo em radianos x do
teclado, o número de termos desejado N, e calcule o valor aproximado de sen(x). Ao final, o
programa deve informar o valor aproximado, juntamente com o valor fornecido pela função sin,
contida na biblioteca math.h. Obs.: O programa deve validar se o valor de N é realmente um
valor positivo. Se não for, encerra a execução com mensagem de erro ao usuário.
Exemplos de execução:
Entre os valores de x e N: 2.3 5
Valor aproximado de seno de 2.300000 eh: 0.745936
Valor de sin(2.300000) pela funcao C eh: 0.745705
Entre os valores de x e N: 1.5 -5
N não é positivo!
Entre os valores de x e N: 1.57079632679 3
Valor aproximado do seno de 1.570796 eh: 1.004525
Valor de sin(1.570796) pela funcao C eh: 1.000000
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double taylor_sine(double x, int n) {
    double term = x; // first term: (x^1) / 1!
    double sum = term;

    for (int i = 1; i < n; i++) {
        term *= -x * x / ((2 * i) * (2 * i + 1));
        sum += term;
    }
    return sum;
}

int main(void) {
    double x;
    int n ;
    printf("Entre os valores de x e N: ");
    if (scanf("%lf %d", &x, &n) != 2 || n <= 0) {
        fprintf(stderr, "Entrada inválida! N deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    double approx = taylor_sine(x, n);
    printf("Valor aproximado do seno de %f eh: %f\n", x, approx);
    printf("Valor de sin(%f) pela função C eh: %f\n", x, sin(x));

    return EXIT_SUCCESS;
}