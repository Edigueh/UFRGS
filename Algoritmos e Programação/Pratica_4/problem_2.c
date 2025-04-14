/*********************************************************************
* @brief   Problema 2: Aproximação do Seno de um ângulo.
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    14/04/2025
**
O seno de um ângulo a em radianos pode ser aproximado pela série seguinte
(soma de termos):
sen(a) = a - ((a^3)/3!) + ((a^5)/5!) - ...
Escreva um programa em C que leia um valor de ângulo em graus e o erro desejado. Calcule o
seno aproximado de acordo com a fórmula acima. Não se esqueça de converter de graus para
radianos. O cálculo do seno aproximado deve ser tal que você deve parar de inserir termos no
somatório quando o valor absoluto do termo é inferior ao erro.
Exemplos de execução:
Entre com o valor do angulo em graus: 45
Entre com o valor do erro: 0.01
Valor aproximado do seno: 0.704653
Entre com o valor do angulo em graus: 30
Entre com o valor do erro: 0.0001
Valor aproximado do seno: 0.500002
Entre com o valor do angulo em graus: 30
Entre com o valor do erro: 0.01
Valor aproximado do seno: 0.499674
Entre com o valor do angulo em graus: 60
Entre com o valor do erro: 0.05
Valor aproximado do seno: 0.855801
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define HALF_CICLE 180.0
#define INIT_TERM 3

double degrees_to_rad(double angle_in_degrees) {
    return angle_in_degrees * (PI / HALF_CICLE);
}

int get_factorial(int number) {
    int factorial = 1;
    for (int i = number; i > 1; i--) factorial *= i;
    return factorial;
}

double calculate_term(double a, int index) {
    return pow(a, index) / get_factorial(index);
}

int main(void) {
    double x_degrees, error, senx;
    int init = INIT_TERM, sign = -1;

    printf("Entre com o valor do angulo em graus: ");
    scanf(" %lf", &x_degrees);
    printf("Entre com o valor do erro: ");
    scanf(" %lf", &error);

    double x_rad = degrees_to_rad(x_degrees);

    double term = calculate_term(x_rad, init);
    double sum = x_rad;
    while (fabs(term) >= error) {
        sum += sign * term;
        init += 2;
        sign *= -1;
        term = calculate_term(x_rad, init);
    }

    printf("Valor aproximado do seno: %lf\n", sum);

    return EXIT_SUCCESS;
}