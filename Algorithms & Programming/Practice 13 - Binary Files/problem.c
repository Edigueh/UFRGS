/*********************************************************************
* @brief   Problema 1: Arquivos Binários.
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    16/06/2025
**
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LE_ARQUIVO 1
#define SALVA_ARRAY_ARQUIVO 2
#define IMPRIME_CONTEUDO_ARRAY 3
#define TROCA_INFO_ARQUIVO 4
#define FIM 5

#define MAXSCORES 5

typedef struct{
char nome[45];
int pontos;
}JOGADOR;

// Imprime menu na tela, faz validação e retorna a opção desejada.
int menu(void);

// Recebe o nome do arquivo a ser lido (ler no main) e armazena o
// conteúdo no array top5
// Abre e fecha o arquivo dentro desta função.
// Retorna TRUE em caso de sucesso e FALSE no caso contrário.
int le_arquivo(char nome_arq[], JOGADOR top5[MAXSCORES]);

// Recebe o nome do arquivo a ser escrito e armazena o
// conteúdo no array top5
// Abre e fecha o arquivo dentro desta função
// Retorna TRUE em caso de sucesso e FALSE no caso contrário
int salva_arquivo(char nome_arq[], JOGADOR top5[MAXSCORES]);

// Troca no array as informações do jogador na posição posicao pelas informações
// do novo jogador novoj
void troca_info_array(JOGADOR top5[], JOGADOR novoj, int posicao);

// imprime as informações sobre o array de jogadores na tela
void imprime_top5(JOGADOR top5[]);

int main(void) {
    JOGADOR top5[MAXSCORES] = {0};
    int opt;
    char nome_arq[100];
    do {
        printf("\n================================\n");
        opt = menu();

        switch (opt) {
            case LE_ARQUIVO:
                printf("Entre com o nome do arquivo a ser lido:");
                scanf("%s", nome_arq);
                if (le_arquivo(nome_arq, top5)) {
                    printf("Arquivo lido com sucesso!\n");

                } else {
                    printf("Erro ao ler arquivo!\n");
                }
                break;
            case SALVA_ARRAY_ARQUIVO:
                if (salva_arquivo(nome_arq, top5)) {
                    printf("Arquivo escrito com sucesso!\n");
                } else {
                    printf("Erro ao escrever no arquivo!\n");
                }
                break;
            case IMPRIME_CONTEUDO_ARRAY:
                imprime_top5(top5);
                break;
            case TROCA_INFO_ARQUIVO:;
                JOGADOR novoj;
                int posicao;
                printf("Entre com o nome do jogador: ");
                scanf("%s", novoj.nome);

                printf("Entre com os pontos do jogador: ");
                scanf("%d", &novoj.pontos);

                printf("Entre em qual posicao voce quer adicionar o jogador: ");
                scanf("%d", &posicao);
                troca_info_array(top5, novoj, posicao);
                break;
            case FIM:
                break;
            default:
                printf("Opcao invalida! Digite novamente!");
                break;
        }

        printf("\n================================\n");
    } while (opt != FIM);
    return EXIT_SUCCESS;
}

int menu(void) {
    int opt;

    printf("\n%d – Le conteudo arquivo para o array\n%d – Salva array no arquivo\n%d – Imprime conteudo do array\n%d – Troca informacao do arquivo\n%d – Fim\n",
        LE_ARQUIVO, SALVA_ARRAY_ARQUIVO, IMPRIME_CONTEUDO_ARRAY, TROCA_INFO_ARQUIVO, FIM);
    printf("Entre com sua opção:");
    scanf("%d", &opt);

    if (opt >= LE_ARQUIVO && opt <= FIM) {
        return opt;
    }
    // Opção inválida.
    return -1;

}

int le_arquivo(char nome_arq[], JOGADOR top5[MAXSCORES]) {
    JOGADOR j;
    FILE *file;

    if(!(file = fopen(nome_arq,"rb"))) {
        printf("Erro na abertura\n");
        return false;
    } else {
        int i = 0;
        while(!feof(file) && i < MAXSCORES){ 
            if(fread(&j, sizeof(JOGADOR), 1 ,file) == 1){
                top5[i] = j;
            }
            i++;
        }
        fclose(file); 
    }

    return true;
}

int salva_arquivo(char nome_arq[], JOGADOR top5[MAXSCORES]) {
    FILE *file;
    if(!(file = fopen(nome_arq,"wb"))) {
        printf("Erro na abertura\n");
        return false;
    } else {
        if (fwrite(top5, sizeof(JOGADOR[MAXSCORES]), 1, file) != 1) {
            printf("Erro na escrita!\n");
            return false;
        }
        fclose(file); 
    }

    return true;
}

void troca_info_array(JOGADOR top5[], JOGADOR novoj, int posicao) {
    if (posicao < 0 && posicao >= MAXSCORES) {
        printf("Posicao não existe!");
        return;
    }

    top5[posicao] = novoj;
    printf("\nInformacao trocada no array!\n");
}

void imprime_top5(JOGADOR top5[]) {
    if (top5[0].pontos == 0) {
        printf("Não ha arquivo lido p impressao!");
        return;
    }
    printf("%-16s | %-1s\n", "Jogador", "Score");
    printf("---------------------------\n");

    for (int i = 0; i < MAXSCORES; i++) {
        printf("%-16s | %-1d\n", top5[i].nome, top5[i].pontos);
    }
}