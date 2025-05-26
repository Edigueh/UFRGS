/*********************************************************************
* @brief   Problema 1: Calcula área e perímetro do triângulo com ponteiro.
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    26/05/2025
**
Escreva uma função:
float triangulo(float a, float b, float c, float *area);
que recebe os três lados a, b, c de um triângulo e calcule sua área na variável area. Se algum dos
valores informados for negativo ou se os lados não corresponderem a um triângulo, a função deve
retornar o valor -1. Caso contrário deve retornar o perímetro do triângulo.
Escreva uma função main() que solicita a leitura de três lados de um triângulo e chama a função
triângulo. Se os lados de fato corresponderem a um triângulo, informe a área e o perímetro. Para
verificar que 3 valores satisfazem a condição de formarem um triângulo, você pode usar a
desigualdade triangular. A desigualdade triangular é um teorema da geometria euclidiana que
afirma que, num triângulo o comprimento de um dos lados é sempre inferior à soma dos
comprimentos dos outros dois lados.
Dica: Se T = (a + b + c)/2 é o semi-perímetro do triângulo, sua área pode ser calculada via
� = #�(� − �)(� − �)(� − �)
Abaixo exemplos de execução:
Entre os lados do triangulo: 5 4 2
Perimetro: 11.000000
Area: 3.799671
Entre os lados do triangulo: 5 1 2
Valores inválidos ou os lados não formam um triangulo
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// triangulo recebe três lados de um triângulo e calcula a sua área na variável area.
// Se algum dos valores informados for negativo ou se os lados não corresponderem a um triângulo, a função deve
// retornar o valor -1. Caso contrário deve retornar o perímetro do triângulo.
float triangulo(float a, float b, float c, float *area);

// triangleIsValid valida se o triângulo é válido.
bool triangleIsValid(float a, float b, float c);

int main(void) {
    
    float a, b, c, area, perimeter;
    
    printf("Entre os lados do triangulo: ");
    scanf("%f %f %f", &a, &b, &c);

    perimeter = triangulo(a, b, c, &area);

    if (perimeter != -1) {
        printf("Perimetro: %f\n", perimeter);
        printf("Area: %f\n", area);
    } else {
        printf("Valores inválidos ou os lados não formam um triangulo\n");
    }
    
    return EXIT_SUCCESS;
}

float triangulo(float a, float b, float c, float *area) {
    if (!triangleIsValid(a,b,c)) return -1;
    float perimeter = a + b + c;
    float t = (perimeter)/2;
    *area = sqrt(t*(t-a)*(t-b)*(t-c));

    return perimeter;
}

bool triangleIsValid(float a, float b, float c) {
    if (a < 0 || b < 0 || c < 0 || a >= b + c || b >= a + c || c >= a + b){
        return false;
    } else {
        return true;
    }
}