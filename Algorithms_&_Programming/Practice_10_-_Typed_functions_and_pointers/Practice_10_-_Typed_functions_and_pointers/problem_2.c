/*********************************************************************
* @brief   Problema 2: Conta letra e algarismo
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    26/05/2025
**
void conta_let_alg(char a, char b, char c, char d, int *letras, int *algarismos);
que, dados 4 caracteres, calcule quantos desses correspondem a letras e quantos correspondem a
algarismos. A leitura dos quatro caracteres de entrada e impressão da quantidade de letras e
algarismos deve ser feita na função main.
Abaixo exemplo de execução:
Entre quatro caracteres: 4 A 8 !
Quantidade de letras: 1
Quantidade de algarismos: 2
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>


// conta_let_alg recebe 4 caracteres, e calcula quantos desses correspondem a letras e quantos correspondem a algarismos.
void conta_let_alg(char a, char b, char c, char d, int *letras, int *algarismos);

int main(void) {

    char a, b, c, d;
    int letras = 0, algarismos = 0;

    printf("Entre quatro caracteres: ");
    scanf("%c %c %c %c", &a, &b, &c, &d);

    conta_let_alg(a, b, c, d, &letras, &algarismos);

    printf("Quantidade de letras: %d\n", letras);
    printf("Quantidade de algarismos: %d\n", algarismos);

    return EXIT_SUCCESS;
}

void conta_let_alg(char a, char b, char c, char d, int *letras, int *algarismos) {
    char characters[4] = {a, b, c, d};

    for (int i = 0; i < 4; i++) {
        if ((characters[i] >= 'A' && characters[i] <= 'Z') || (characters[i] >= 'a' && characters[i] <= 'z')) {
            *letras += 1;
        } else if (characters[i] >= '0' && characters[i] <= '9') *algarismos += 1;
    }
}