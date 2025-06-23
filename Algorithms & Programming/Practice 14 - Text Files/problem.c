/*********************************************************************
* @brief   Problema 1: Arquivos Texto.
* @author  André Schaidhauer Luckmann
*
* @version 0.1
* @date    23/06/2025
**
 Um arquivo texto brasileiro.txt contém, em cada linha, o nome de um
time de futebol, o numero de vitórias, empates e derrotas, e a média de público, seguindo o formato
abaixo:
Time vitorias empates derrotas publico
Considere o tipo de dados CLUBE abaixo, que contém os campos para armazenar os dados de cada
partida.
typedef struct
{
 char nome[30];
 int vit, emp, der;
 int pontos;
 float publico;
}CLUBE;
1. Escreva uma função que leia o arquivo texto brasileiro.txt, e armazene os dados de todos
os clubes lidos em um arranjo do tipo CLUBE, e retorne o número de clubes contidos no arquivo. A
função também deve calcular o número de pontos total de cada clube, lembrando que vitória vale 3
pontos e empate 1 ponto. Assuma que há no máximo MAX_CLUBES no arquivo (dado através de um
#define).
2. Escreva uma função que receba como entrada um arranjo do tipo CLUBE e o tamanho do arranjo,
e escreva em cada linha de um arquivo texto pontuacao.txt na primeira linha, o número de
clubes lidos. Nas linhas seguintes escreva o nome do clube, sua pontuação, e o aproveitamento
(percentual dos pontos ganhos sobre o total possível).
3. Escreva um programa que chame as duas rotinas acima. Exemplo de execução para o arquivo
fornecido:
Numero de clubes: 6
Cruzeiro, 75 pontos, aproveitamento de 71.43%.
Gremio, 60 pontos, aproveitamento de 57.14%.
Goias, 59 pontos, aproveitamento de 56.19%.
Atletico-PR, 58 pontos, aproveitamento de 55.24%.
Botafogo, 57 pontos, aproveitamento de 54.29%.
Vitoria, 54 pontos, aproveitamento de 51.43%.
*********************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_CLUBES 10

#define WIN_PTS 3
#define DRAW_PTS 1

typedef struct {
 char nome[30];
 int vit, emp, der;
 int pontos;
 float publico;
} CLUBE;

int fetchClubs(char file_name[], CLUBE club[MAX_CLUBES]);

void saveClubs(CLUBE club[MAX_CLUBES], int numCLubs);

int main(void) {
    CLUBE clubs[MAX_CLUBES];
    char file_name[] = "brasileiro.txt";
    int numClubs = fetchClubs(file_name, clubs);

    printf("Há %d clubes no arquivo %s!\n", numClubs, file_name);

    saveClubs(clubs, numClubs);

    return EXIT_SUCCESS;
}

int fetchClubs(char file_name[], CLUBE club[MAX_CLUBES]) {
    FILE *file;
    char buffer[256];
    int n_clubs = 0;

    if (!(file = fopen(file_name, "r"))) {
        printf("Erro na abertura de %s", file_name);
    } else {
        while (!feof(file) && n_clubs <= MAX_CLUBES) {
            fscanf(file, "%s", club[n_clubs].nome);
            fscanf(file, "%d", &club[n_clubs].vit);
            fscanf(file, "%d", &club[n_clubs].emp);
            fscanf(file, "%d", &club[n_clubs].der);
            fscanf(file, "%f", &club[n_clubs].publico);
            club[n_clubs].pontos = (club[n_clubs].vit * WIN_PTS) + (club[n_clubs].emp * DRAW_PTS);
            n_clubs++;
        }
    }

    fclose(file);
    return n_clubs;
}

float getRating(CLUBE club) {
    return (float) club.pontos / (WIN_PTS * (club.vit + club.emp + club.der)) * 100;
}

void saveClubs(CLUBE clubs[MAX_CLUBES], int numCLubs) {
    FILE *file;
    char file_name[] = "pontuacao.txt";
    if (!(file = fopen(file_name, "w"))) {
        printf("Erro na abertura de %s", file_name);
    } else {
        fprintf(file, "Numero de clubes: %d\n", numCLubs);
        for (int i = 0; i < numCLubs; i++) {
            // Cruzeiro, 75 pontos, aproveitamento de 71.43%.
		    fprintf(file, "%s, %d pontos, aproveitamento de %.2f%%.\n", clubs[i].nome, clubs[i].pontos, getRating(clubs[i]));
        }
    }

    fclose(file);
    return;
}
