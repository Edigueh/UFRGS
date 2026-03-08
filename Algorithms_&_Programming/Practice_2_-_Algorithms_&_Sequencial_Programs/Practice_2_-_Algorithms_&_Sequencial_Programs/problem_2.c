/*********************************************************************
* @brief   Problema 2: Área de quadrado inscrito
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    23/03/2025
**
* Escreva um programa que leia do teclado o raio de um círculo, e após calcule (e informe na
* tela) o perímetro e a área do maior quadrado inscrito nesse círculo. DICA: veja como o
* lado do quadrado está relacionado ao raio do círculo.
* Abaixo exemplo de execução:
* Entre com um valor para o raio: 1
* Perímetro do maior quadrado: 5.66
* Área do maior quadrado: 2
* 
* Entre com um valor para o raio: 2.3
* Perímetro do maior quadrado: 13.01
* Área do maior quadrado: 10.58
***********************************************************************/

#include <stdio.h>
#include <math.h>

static const int SQUARE_SIDES = 4;

double calc_square_side(double radius) {
    return radius * sqrt(2);
}

double calc_square_perimeter(double side_length) {
    return side_length * SQUARE_SIDES;
}

double calc_square_area(double side_length) {
    return pow(side_length, 2);
}

int main() {
    double radius;

    printf("Entre com um valor para o raio: ");
    scanf("%lf", &radius);

    double side_length = calc_square_side(radius);

    printf("Perímetro do maior quadrado: %.2f\n", calc_square_perimeter(side_length));
    printf("Área do maior quadrado: %.2f\n", calc_square_area(side_length));

    return 0;
}
