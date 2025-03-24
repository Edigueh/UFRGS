/*********************************************************************
* @brief   Problema 1: Modelando o Crescimento da População Alienígena
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    23/03/2025
**
* Cientistas descobriram um planeta distante com uma população crescente de alienígenas
* inteligentes. A população cresce exponencialmente ao longo do tempo, e o crescimento
* pode ser modelado usando a fórmula:
* P(t) = P0 * e^(r*t)
* Onde:
* • P(t) é a população após t anos
* • P0 é a população inicial (lida do usuário)
* • r é a taxa de crescimento em percentual (lida do usuário)
* • t é o tempo que passou em anos (lido do usuário)
* • e é o número de Euler
***********************************************************************/

#include <stdio.h>
#include <math.h>

double calc_alien_population_growth(int initial_population, int years, float growth_rate){
    return initial_population * exp(growth_rate/100 * years);
}

int main() {
    int initial_population, years;
    float growth_rate;

    printf("Entre com a população inicial: ");
    scanf("%d", &initial_population);
    printf("Entre com o tempo em anos: ");
    scanf("%d", &years);
    printf("Entre com a taxa de crescimento (em porcentagem): ");
    scanf("%f", &growth_rate);

    float alien_population_growth = floor(calc_alien_population_growth(initial_population, years, growth_rate));

    printf("Apos %d anos, a populacao sera aproximadamente %.0f aliens!\n", years, alien_population_growth);
    return alien_population_growth;
}
