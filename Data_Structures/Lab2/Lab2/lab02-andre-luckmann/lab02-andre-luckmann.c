#include <stdio.h>
#include <stdlib.h>

#define NAME_MAX_CHAR 50

// A definição da estrutura Jogo que armazena um jogo (nome, preço, estoque).
typedef struct {
    char nome[NAME_MAX_CHAR];
    float preco;
    int estoque;
} Jogo;

/*
Exercício Extra. [0%] Altere a função alocaJogos para que suporte passagem por
referência de um ponteiro, isto é, usando ponteiro de ponteiro. Use o protótipo abaixo:
void alocaJogos(Jogo **pJogo, int numJogos);
*/
// alocaJogos aloca dinamicamente memória para armazenar n jogos, retornando o ponteiro desse trecho de memória.
void alocaJogos(Jogo **pJogo, int numJogos);

// cadastraJogos lê do teclado os dados de cada jogo e armazena no vetor alocado.
void cadastraJogos(Jogo jogos[], int numJogos);

// imprimeJogos imprime as informações de todos os jogos cadastrados.
void imprimeJogos(Jogo jogos[], int numJogos);

// liberaJogos libera a memória alocada com free, e retorna NULL.
Jogo* liberaJogos(Jogo jogos[]);

/*
* main():
* 1. Pede ao usuário quantos jogos ele deseja cadastrar;
* 2. Usa alocaJogos para alocar a memória;
* 3. Chama cadastraJogos;
* 4. Chama imprimeJogos;
* 5. Chama liberaJogos, deixando o ponteiro como nulo (NULL).
*/
int main(void) {
    int numJogos;
    Jogo* jogos;

    // 1
    printf("Quantos jogos você deseja cadastrar? ");
    scanf("%d", &numJogos);
    printf("-------------------------------------\n");

    // 2
    alocaJogos(&jogos, numJogos);

    // 3
    cadastraJogos(jogos, numJogos);

    // 4
    imprimeJogos(jogos, numJogos);

    // 5
    jogos = liberaJogos(jogos);

    return EXIT_SUCCESS;
}

// alocaJogos aloca dinamicamente memória para armazenar n jogos, retornando o ponteiro desse trecho de memória.
void alocaJogos(Jogo **pJogo, int numJogos) {
    *pJogo = (Jogo *) malloc(numJogos * sizeof(Jogo));
    
    if (*pJogo == NULL) {
        printf("Erro ao alocar memoria!\n");
    }
}

// cadastraJogos lê do teclado os dados de cada jogo e armazena no vetor alocado.
void cadastraJogos(Jogo jogos[], int numJogos) {
    for (int i = 0; i < numJogos; i++) {
        printf("Digite o nome do jogo %d: ", i+1); scanf("%s", jogos[i].nome);
        printf("Digite o preço de %s: ", jogos[i].nome); scanf("%f", &jogos[i].preco);
        printf("Digite a quantidade de %s no estoque: ", jogos[i].nome); scanf("%d", &jogos[i].estoque);
    }
    printf("\n");
}

// imprimeJogos imprime as informações de todos os jogos cadastrados.
void imprimeJogos(Jogo jogos[], int numJogos) {
    printf("%-20s %-5s %-5s\n", "Nome", "Preço", "Estoque");
    printf("-------------------- ----- -----\n");
    for (int i = 0; i < numJogos; i++) {
        printf("%-20s %-5.2f %-5d\n", jogos[i].nome, jogos[i].preco, jogos[i].estoque);
    }
}

// liberaJogos libera a memória alocada com free, e retorna NULL.
Jogo* liberaJogos(Jogo jogos[]) {
    free(jogos);
    return NULL;
}
