/*********************************************************************
* @brief   Problema 2: Guess the number.
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    05/05/2025
**
Implemente em C um jogo simples de adivinhar um número inteiro sorteado pelo
computador. O computador irá sortear um número inteiro no intervalo [1,10]. Após o sorteio o
usuário tentará adivinhar o número que foi sorteado. O programa deverá comparar o número
sorteado com o número fornecido pelo usuário e imprimir uma mensagem adequada de acordo se o
número for maior ou menor do que o valor sorteado.
Caso o usuário acerte o número em menos de 5 tentativas, o programa imprime a mensagem:
“Parabéns! Você acertou o número em XX tentativas” (XX corresponde ao número de tentativas).
Caso o usuário não tenha acertado, imprime a mensagem “Você ultrapassou o numero máximo de
tentativas! O numero sorteado foi YY” (imprime o numero sorteado para conferência pelo usuário)
Abaixo exemplos de execução:
Digite seu chute: 1
Seu chute é menor do que o valor sorteado!
Digite seu chute: 2
Seu chute é menor do que o valor sorteado!
Digite seu chute: 3
Seu chute é menor do que o valor sorteado!
Digite seu chute: 4
Seu chute é menor do que o valor sorteado!
Digite seu chute: 5
Seu chute é menor do que o valor sorteado!
Voce ultrapassou o numero maximo de tentativas! O numero sorteado foi 9.
Digite seu chute: 2
Seu chute é maior do que o valor sorteado!
Digite seu chute: 1
Parabens! Voce acertou em 2 tentativa(s)!
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_RAND 1
#define MAX_RAND 10
#define MAX_ATTEMPTS 5

int main(void) {

    srand(time(NULL));
    int num_guesses = 0, guess;
    int draw_num = MIN_RAND + (rand() % (MAX_RAND - MIN_RAND + 1));

    do {
        printf("Digite seu chute: ");
        scanf(" %d", &guess);

        if(guess < draw_num) {
            printf("Seu chute é menor do que o valor sorteado!\n");
        } else if(guess > draw_num) {
            printf("Seu chute é maior do que o valor sorteado!\n");
        }

        num_guesses++;
    } while (num_guesses < MAX_ATTEMPTS && guess != draw_num);

    if(num_guesses < MAX_ATTEMPTS || guess == draw_num){
        printf("Parabéns! Você acertou o número em %d tentativas\n", num_guesses);
    } else {
        printf("Você ultrapassou o numero máximo de tentativas! O numero sorteado foi %d\n", draw_num);
    }

    return EXIT_SUCCESS;
}
