/*********************************************************************
* @brief   Problema 1: character case counter
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    14/04/2025
**
Escreva um programa que leia caracteres do teclado até que o usuário digite '!'. O
programa deve então calcular o número de caracteres em minúsculo e o número de caracteres
em maiúsculo informados. Outros caracteres podem ser lidos, mas não entram na contagem.
OBS: Para descobrir os caracteres maiúsculos e minúsculos você NÃO pode testar todas as
possibilidades (força-bruta!) e nem usar a função isalpha. Lembre-se dos valores ASCII.
Exemplo de execução:
Entre com o 1o caractere: a
Entre com o 2o caractere: n
Entre com o 3o caractere: 3
Entre com o 4o caractere: H
Entre com o 5o caractere: k
Entre com o 6o caractere: !
Voce digitou 3 caracteres em minusculo e 1 em maiúsculo
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define UPPER_ASCII_A 65
#define UPPER_ASCII_Z 90

#define LOWER_ASCII_A 97
#define LOWER_ASCII_Z 122

int main(void) {
    
    int lower_case_count = 0, upper_case_count = 0, counter = 1;
    char input;

    do {
        printf("Entre com o %do caractere: ", counter);
        scanf(" %c", &input);
        
        if(input >= UPPER_ASCII_A && input <= UPPER_ASCII_Z) {
            upper_case_count++;
        } else if (input >= LOWER_ASCII_A && input <= LOWER_ASCII_Z) lower_case_count++;

        counter++;
    } while (input != '!'); 

    printf("Voce digitou %d caracteres em minusculo e %d em maiúsculo\n", lower_case_count, upper_case_count);
    return EXIT_SUCCESS;
}
