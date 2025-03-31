/*********************************************************************
* @brief   Problema 2: Identificar o mês do pagamento do IPVA de um carro.
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    31/03/2025
**
Elaborar um programa que identifique o mês do pagamento do IPVA de um
carro, baseado na parte numérica da placa. Para isto, ler o número de uma placa de veículo
como um valor inteiro (composta por exatamente quatro dígitos – ignore a parte das letras)
e, através do número finalizador da placa (algarismo da casa das unidades), determinar e
informar o mês de vencimento do IPVA deste veículo. Para isto, aplique a tabela ao lado.
Abaixo exemplo de execução:
Final 1 – mês (1) – Janeiro Final 6 – mês (6) – Junho
Final 2 – mês (2) – Fevereiro Final 7 – mês (7) – Julho
Final 3 – mês (3) – Março Final 8 – mês (8) – Agosto
Final 4 – mês (4) – Abril Final 9 – mês (9) – Setembro
Final 5 – mês (5) – Maio Final 0 – mês (10) – Outubro
Observação: só processe se o número lido da placa este estiver entre 1000 e 9999. Caso
contrário imprima mensagem de erro ao usuário e encerre o programa.
DICA: Para encontrar apenas a unidade (último digito) pense em divisões para ajudar
Entre com a placa:1245
Mes de vencimento Maio
***********************************************************************/

#include <stdio.h>

int get_last_digit(int car_plate) {
    return car_plate % 10;
}

int main() {
    char months[10][9] = {"Outubro", "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro"};
    int car_plate;
    int last_digit;

    printf("Entre com a placa: ");
    scanf("%d", &car_plate);

    if (car_plate < 1000 || car_plate > 9999) {
        printf("Número da placa do carro fora dos limites\n");
        return -1;
    }


    last_digit = get_last_digit(car_plate);
    printf("Mês de vencimento: ");

    switch (last_digit) {
        case 0:
            printf("Outubro\n");
            break;
        case 1:
            printf("Janeiro\n");
            break;
        case 2:
            printf("Fevereiro\n");
            break;
        case 3: 
            printf("Março\n");
            break;
        case 4: 
            printf("Abril\n");
            break;
        case 5:
            printf("Maio\n");
            break;
        case 6:
            printf("Junho\n");
            break;
        case 7: 
            printf("Julho\n");
            break;
        case 8: 
            printf("Agosto\n");
            break;
        case 9:
            printf("Setembro\n");
            break;
        default:
            printf("Something gone wrong!\n");
            break;
    }

    printf("Mês de vencimento: %s\n", months[last_digit]);
    return 0;
}
