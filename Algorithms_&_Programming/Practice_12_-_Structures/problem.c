/*********************************************************************
* @brief   Problema 1: Concessionária.
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    09/06/2025
**
Elabore um programa para o problema abaixo. Ao final chame o professor para mostrar.
Dada a seguinte estrutura
typedef struct carro{
int cod;
char modelo[45];
char marca[45];
float preco;
int ano;
}CARRO;

Escrever um programa em C que apresenta um menu com as seguintes opções:
1 – Cadastro de carro
2 – Consulta de carro
3 – Preco médio dos carros
4 – Imprime estoque revenda
5 – Fim
Entre com sua opção:
O número máximo de carros a ser cadastrado é 3 em um vetor de estruturas (faça consistência, não
pode deixar incluir mais do que 3 carros). À medida que novos carros vão sendo inseridos, eles
devem ser armazenados no vetor. Você deverá implementar as seguintes funções (EXATAMENTE
COMO ESTÃO ABAIXO):

// Imprime menu na tela, faz validação e retorna a opção desejada
int menu(void);

// Le informações e cadastra um carro c recebido por referência
void cadastraCarro(CARRO *c);

// imprime as informações de um determinado carro c na tela na opção consulta de
// carro. Esta função deverá ser usada também para a impressão de toda o estoque
// da revenda
void print_carro(CARRO c);

// calcula o preco médio de todos os carros cadastrados. A variável ncarros é o
número atual de carros da revenda
float calcMediaPreco(CARRO carros[], int ncarros);

// Procura um carro com o código fornecido entre todos os cadastrados. Caso não
exista o carro, retorna -1 no campo cod do carro retornado. A variável ncarros é
o número atual de carros da revenda
CARRO procuraCarro(CARROS carros[], int ncarros, int cod);

Exemplo de execução:
1 – Cadastro de carro
2 – Consulta de carro
3 – Preco médio dos carros
4 – Imprime estoque revenda
5 – Fim
Entre com sua opção: 1
Codigo: 1
Marca: VW
Modelo: Fox
Preco: 25000
Ano: 2010
1 – Cadastro de carro
2 – Consulta de carro
3 – Preco médio dos carros
4 – Imprime estoque revenda
5 – Fim
Entre com sua opção: 1
Codigo: 2
Marca: Fiat
Modelo: Palio
Preco: 30000
Ano: 2017
1 – Cadastro de carro
2 – Consulta de carro
3 – Preco médio dos carros
4 – Imprime estoque revenda
5 – Fim
Entre com sua opção: 3
O Preco medio dos carros eh 27500.00
1 – Cadastro de carro
2 – Consulta de carro
3 – Preco médio dos carros
4 – Imprime estoque revenda
5 – Fim
Entre com sua opção: 2
Informe o codigo do carro: 3
Carro nao existe!
1 – Cadastro de carro
2 – Consulta de carro
3 – Preco médio dos carros
4 – Imprime estoque revenda
5 – Fim
Entre com sua opção: 2
Informe o codigo do carro: 1
Codigo: 1
Marca VW
Modelo Fox
Preco: 25000.00
Ano: 2010
1 – Cadastro de carro
2 – Consulta de carro
3 – Preco médio dos carros
4 – Imprime estoque revenda
5 – Fim
Entre com sua opção: 5
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CADASTRO_CARRO 1
#define CONSULTA_CARRO 2
#define PRECO_MEDIO_CARROS 3
#define IMPRIME_ESTOQUE_REVENDA 4
#define FIM 5

#define MAX_CARROS 3
#define CARRO_NAO_EXISTE -1

typedef struct carro {
    int cod;
    char modelo[45];
    char marca[45];
    float preco;
    int ano;
} CARRO;


int numCarrosCadastrados = 0;
CARRO estoque[MAX_CARROS] = {0};

// Imprime menu na tela, faz validação e retorna a opção desejada
int menu(void);

// Le informações e cadastra um carro c recebido por referência
void cadastraCarro(CARRO *c);

// imprime as informações de um determinado carro c na tela na opção consulta de
// carro. Esta função deverá ser usada também para a impressão de toda o estoque
// da revenda
void print_carro(CARRO c);

// calcula o preco médio de todos os carros cadastrados. A variável ncarros é o
// número atual de carros da revenda.
float calcMediaPreco(CARRO carros[], int ncarros);

// Procura um carro com o código fornecido entre todos os cadastrados. Caso não
// exista o carro, retorna -1 no campo cod do carro retornado. A variável ncarros é
// o número atual de carros da revenda.
CARRO procuraCarro(CARRO carros[], int ncarros, int cod);

int main(void) {
    int opt;
    do {
        printf("\n================================\n");
        opt = menu();

        switch (opt) {
            CARRO carro;
            case CADASTRO_CARRO:
                cadastraCarro(&carro);
                break;
            case CONSULTA_CARRO:
                int codCarro;
                printf("Informe o codigo do carro: ");
                scanf("%d", &codCarro);
                carro = procuraCarro(estoque, numCarrosCadastrados, codCarro);
                print_carro(carro);
                break;
            case PRECO_MEDIO_CARROS:
                printf("O Preco medio dos carros eh %.2f\n", calcMediaPreco(estoque, numCarrosCadastrados));
                break;
            case IMPRIME_ESTOQUE_REVENDA:
                for (int i = 0; i < numCarrosCadastrados; i++) {
                    printf("\n-----\n");
                    print_carro(estoque[i]);
                    printf("\n-----\n");
                }
                break;
            case FIM:
                break;
            default:
                printf("Opção Inválida!");
        }
        printf("\n================================\n");
    } while (opt != FIM);
    
    return EXIT_SUCCESS;
}

int menu(void) {
    printf("\n%d – Cadastro de carro\n%d – Consulta de carro\n%d – Preco médio dos carros\n%d – Imprime estoque revenda\n%d – Fim\nEntre com sua opção: ", 
        CADASTRO_CARRO, CONSULTA_CARRO, PRECO_MEDIO_CARROS, IMPRIME_ESTOQUE_REVENDA, FIM);
    int opt;
    scanf("%d", &opt);

    if (opt >= CADASTRO_CARRO && opt <= FIM) {
        return opt;
    }
    // Opção inválida.
    return -1;
}

void cadastraCarro(CARRO *c) {
    if (numCarrosCadastrados == MAX_CARROS) {
        printf("Não é possível cadastrar o carro devido a que o número máximo de carros cadastrados já foi atingido: %d.\n", MAX_CARROS);
        return;
    }

    printf("Codigo: ");
    scanf("%d", &c->cod);

    printf("Marca: ");
    scanf("%s", c->marca);

    printf("Modelo: ");
    scanf("%s", c->modelo);

    printf("Preco: ");
    scanf("%f", &c->preco);

    printf("Ano: ");
    scanf("%d", &c->ano);

    estoque[numCarrosCadastrados] = *c;
    numCarrosCadastrados++;
}

void print_carro(CARRO c) {
    if (c.cod == CARRO_NAO_EXISTE) {
        printf("Carro nao existe!");
        return;
    }
    printf("Codigo: %d\n", c.cod);
    printf("Marca: %s\n", c.marca);
    printf("Modelo: %s\n", c.modelo);
    printf("Preco: %.2f\n", c.preco);
    printf("Ano: %d\n", c.ano);
}

CARRO procuraCarro(CARRO carros[], int ncarros, int cod) {
    for (int i = 0; i < ncarros; i++) {
        if (carros[i].cod == cod) {
            return carros[i];
        }
    }
    
    CARRO carroDummy;
    carroDummy.cod = -1;
    return carroDummy;
}

float calcMediaPreco(CARRO carros[], int ncarros) {
    float totalSum = 0.0f;
    for (int i = 0; i < ncarros; i++) {
        totalSum += carros[i].preco;
    }

    return (float)totalSum / ncarros;
}
