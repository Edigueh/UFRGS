/*********************************************************************
* @brief   Problema 1: Validador de doador de sangue.
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    31/03/2025
**
* Para que uma pessoa seja doadora de sangue, é necessário que todas as
* condições abaixo sejam satisfeitas (exemplo apenas didático, baseado nas condições reais):
* • Não ter feito tatuagem nos últimos 12 meses
* • Peso no mínimo de 50kg
* • Idade entre 16 e 69 anos
* Escreva um programa que informa na tela se a pessoa pode doar sangue ou não. Para isso,
* seu programa deverá perguntar: (i) se fez tatuagem nos últimos 12 meses (resposta ‘S’ ou
* ‘N’); (ii) a idade do candidato a doador; (iii) peso. Baseado nas respostas a essas perguntas
* o programa deverá emitir a mensagem “Você está apto a doar sangue” ou “Você não está
* apto a doar sangue”. 
* DICA: Para leitura do caracter, usar scanf com o formatador “ %c”,
* com um espaço antes do formatador. Abaixo exemplos de execução:
* Voce fez tatuagem nos ultimos 12 meses (S/N)? N
* Qual seu peso? 67.5
* Qual a sua idade? 21
* Parabens! Voce pode ser doador!
* Voce fez tatuagem nos ultimos 12 meses (S/N)? s
* Voce não pode ser doador!
* Voce fez tatuagem nos ultimos 12 meses (S/N)? n
* Qual seu peso? 48.7
* Voce não pode ser doador!
* Voce fez tatuagem nos ultimos 12 meses (S/N)? n
* Qual seu peso? 70
* Qual a sua idade? 15
* Voce NAO pode ser doador!
***********************************************************************/

#include <stdio.h>
#include <stdbool.h>

#define MINIMUM_WEIGHT 50
#define MINIMUM_AGE 16
#define MAXIMUM_AGE 69

int main () {

    char did_tatoo;
    float weight;
    int age;
    
    printf("Voce fez tatuagem nos ultimos 12 meses (S/N)? ");
    scanf(" %c", &did_tatoo);
    if (did_tatoo == 'S' || did_tatoo != 's') {
        printf("Qual seu peso? ");
        scanf("%f", &weight);
        if (weight >= MINIMUM_WEIGHT) {
            printf("Qual a sua idade? ");
            scanf("%d", &age);
            if (age >= MINIMUM_AGE && age <= MAXIMUM_AGE) {
                printf("Você está apto a doar sangue!\n");
            } else {
                printf("Você não está apto a doar sangue!\n");
            }
        } else {
            printf("Você não está apto a doar sangue!\n");
        }
    } else {
        printf("Você não está apto a doar sangue!\n");
    }
    return 0;
}
