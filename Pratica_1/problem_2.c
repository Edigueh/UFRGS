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

#define SQUARE_SIDES 4

float calculateSquareSides(float radius) {
    return radius * sqrt(2);
}

float calculateSquarePerimeter(float squareSidesMeasure) {
    return squareSidesMeasure * SQUARE_SIDES;
}

float calculateSquareArea(float squareSidesMeasure) {
    return pow(squareSidesMeasure, 2);
}

int main() {
    float radius;

    printf("Entre com um valor para o raio: ");
    scanf("%f", &radius);

    float squareSidesMeasure = calculateSquareSides(radius);

    printf("Perímetro do maior quadrado: %.2f\n", calculateSquarePerimeter(squareSidesMeasure));
    printf("Área do maior quadrado: %.2f\n", calculateSquareArea(squareSidesMeasure));

    return 0;
}
