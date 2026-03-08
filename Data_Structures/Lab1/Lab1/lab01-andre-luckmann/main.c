#include "data.h"
#include <stdio.h>

int main(void) {
    Ponto p1, p2;
    
    criaPto(&p1, 5, 7);
    criaPto(&p2, 10.5, 14.2);

    printf("Distância entre p1 e p2: %.2f\n", distPto(p1, p2));

    transladaPto(&p1, 1.5, 3.1);
    transladaPto(&p2, 0.5, 0.8);

    printf("Novas cordenadas de p1: x:%.2f, y:%.2f\n", p1.x, p1.y);
    printf("Novas cordenadas de p2: x:%.2f, y:%.2f\n", p2.x, p2.y);
    return 0;
}
