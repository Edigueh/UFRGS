/*********************************************************************
* @brief   Problema 1: Funções Matemáticas.
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    19/05/2025
**
Escreva um programa que apresenta um menu de opções ao usuário, conforme o
exemplo abaixo. Você deverá escrever 3 funções, conforme protótipos abaixo:

// Apresenta o menu, lê e retorna a opção do usuário
// Valida a opção do usuario
int menu(void);

// Calcula a media aritmetica de 3 valores e retorna
float m_aritmetica(float a, float b, float c);

// Calcula a media harmonica de 3 valores e retorna
float m_harmonica(float a, float b, float c);

// Calcula a media geometrica de 3 valores e retorna
float m_geometrica(float a, float b, float c);

Lembrando: Para um conjunto de números reais positivos x1,…,xn
a média geométrica deste conjunto é definida como o produto de todos os membros do conjunto elevado ao inverso do
número de membros. Por exemplo, a média geométrica do conjunto (4, 1, 1/32) é definida como a
raiz cúbica de produto 4*1*1/32. A média harmônica é definida como sendo o número de membros
n dividido pela soma do inverso dos membros. Por exemplo, para o conjunto (2, 3, 6), a média
harmônica é 3/(1/2+1/3+1/6).

Abaixo exemplo de execução:

Entre com uma das opcoes:
1 – Calcula a media aritmetica de 3 numeros reais
2 - Calcula a media harmonica de 3 numeros reais
3 – Calcula a media geometrica de 3 numeros reais
4 – Sair

Opcao: 2

Entre com os 3 valores: 2.5 4.6 78.9
A media harmonica vale 4.761409
Entre com uma das opcoes:
1 – Calcula a media aritmetica de 3 numeros reais
2 - Calcula a media harmonica de 3 numeros reais
3 – Calcula a media geometrica de 3 numeros reais
4 – Sair

Opcao: 3

Entre com os 3 valores: 2.5 4.6 78.9
A media geometrica vale 9.681106

Entre com uma das opcoes:
1 – Calcula a media aritmetica de 3 numeros reais
2 - Calcula a media harmonica de 3 numeros reais
3 – Calcula a media geometrica de 3 numeros reais
4 – Sair

Opcao: 1

Entre com os 3 valores: 2.5 4.6 78.9
A media aritmetica vale 28.666666
Entre com uma das opcoes:
1 – Calcula a media aritmetica de 3 numeros reais
2 - Calcula a media harmonica de 3 numeros reais
3 – Calcula a media geometrica de 3 numeros reais
4 – Sair

Opcao: 5

Opcao invalida!

Entre com uma das opcoes:
1 – Calcula a media aritmetica de 3 numeros reais
2 - Calcula a media harmonica de 3 numeros reais
3 – Calcula a media geometrica de 3 numeros reais
4 – Sair

Opcao: 4
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARITHMETIC_AVG 1
#define HARMONIC_AVG 2
#define GEOMETRIC_AVG 3
#define EXIT 4

// Apresenta o menu, lê e retorna a opção do usuário.
// Valida a opção do usuario.
int menu(void);

// Calcula a media aritmetica de 3 valores e retorna.
float m_aritmetica(float a, float b, float c);

// Calcula a media harmonica de 3 valores e retorna.
float m_harmonica(float a, float b, float c);

// Calcula a media geometrica de 3 valores e retorna.
float m_geometrica(float a, float b, float c);

int main(void) {
    int opt;
    do {
        opt = menu();
        switch (opt){
            float a,b,c;
            case ARITHMETIC_AVG:
                printf("Entre com os 3 valores: ");
                scanf("%f %f %f", &a, &b, &c);
                printf("A media aritmetica vale %f\n\n", m_aritmetica(a, b, c));
                break;
            case HARMONIC_AVG:
                printf("Entre com os 3 valores: ");
                scanf("%f %f %f", &a, &b, &c);
                printf("A media harmonica vale %f\n\n", m_harmonica(a, b, c));
                break;
            case GEOMETRIC_AVG:
                printf("Entre com os 3 valores: ");
                scanf("%f %f %f", &a, &b, &c);
                printf("A media geometrica vale %f\n\n", m_geometrica(a, b, c));
                break;
            case EXIT:
                break;
            default:
                printf("Opcao invalida!\n\n");
                break;
        }
    } while(opt != EXIT);

    return EXIT_SUCCESS;
}

int menu(void) {
    int opt;
    printf("Entre com uma das opcoes:\n1 – Calcula a media aritmetica de 3 numeros reais\n2 - Calcula a media harmonica de 3 numeros reais\n3 – Calcula a media geometrica de 3 numeros reais\n4 – Sair\n\nOpcao: ");
    scanf(" %d", &opt);
    return opt;
}

float m_aritmetica(float a, float b, float c) {
    return (a + b + c) / 3;
}

float m_harmonica(float a, float b, float c) {
    return 3 / (1/a + 1/b + 1/c);
}

float m_geometrica(float a, float b, float c) {
    return cbrt(a * b * c);
}
