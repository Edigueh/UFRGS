#include <stdio.h>
#include <stdlib.h>

#define MAX_SEQUENCE 50
#define STOP_INPUT 0

int main(void) {
    int seq[MAX_SEQUENCE] = { 0 }, seq_i = 0, input;
    
    printf("Entre com 50 valores inteiros ou o valor 0 para parar de ler números: \n");
    do {
        scanf("%d", &input);
        if (seq_i <= MAX_SEQUENCE && input != STOP_INPUT) {
            seq[seq_i]=input;
            seq_i++;
        }
    } while(seq_i <= MAX_SEQUENCE && input != STOP_INPUT);

    printf("Sequencia\n");
    for(int i = 0; i < seq_i; i++) {
        int soma = 0;
        
        for(int j = i; j < seq_i; j++) {
            soma += seq[j];
        }
        printf("%d ", soma);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
