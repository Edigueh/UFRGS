#include <stdio.h>
#include <string.h>

#define MAX_LEN 51

int main(void) {
    char input[MAX_LEN];

    printf("Digite o string: ");
    fgets(input, MAX_LEN, stdin);
    input[strlen(input) - 1] = '\0';

    printf("Input: %s\n", input);
    char output[strlen(input)];

    for(int c = 0; c < MAX_LEN; c++){
        if(input[c] >= 'A' && input[c] <= 'Z') {
            if(input[c] <= 'M') { 
                output[c] = ((input[c] + 13) % 'A') + 'A';
            } else {
                output[c] = input[c] - 13;
            }
        } else if(input[c] >= 'a' && input[c] <= 'z') {
            if(input[c] <= 'm') { 
                output[c] = ((input[c] + 13) % 'a') + 'a';
            } else {
                output[c] = input[c] - 13;
            }
        } else {
            output[c] = input[c];
        }
    }

    printf("String invertido: %s\n", output);
    return 0;
}
