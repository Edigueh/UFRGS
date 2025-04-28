/*********************************************************************
* @brief   Problema 1: String Converter
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    28/04/2025
**
Leia uma string do usuário de comprimento máximo igual a 25 (não precisa validar) e
crie duas outras strings a partir da string lida: uma string com todas as letras maiúsculas e outra
invertida (a primeira letra da string original corresponde à última da string invertido e assim
sucessivamente). Imprima na tela as 2 novas strings. Veja abaixo exemplo de execução:
Entre com uma string: Universidade Federal
String todo maiusculo: UNIVERSIDADE FEDERAL
String invertido: laredeF edadisrevinU
***********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_INPUT_LEN 27

int main(void) {

    // Read user input.
    char input[MAX_INPUT_LEN];
    printf("Entre com uma string: ");
    fgets(input, MAX_INPUT_LEN, stdin);
    input[strlen(input) - 1] = '\0';

    char uppercase[MAX_INPUT_LEN], reverse[MAX_INPUT_LEN];
    for(int i = 0, j = strlen(input) - 1;i < strlen(input); i++, j--) {
        uppercase[i] = toupper(input[i]);
        reverse[i] = input[j];
    }

    printf("String todo maiusculo: %s\n", uppercase);
    printf("String invertido: %s\n", reverse);
    
    return EXIT_SUCCESS;
}
