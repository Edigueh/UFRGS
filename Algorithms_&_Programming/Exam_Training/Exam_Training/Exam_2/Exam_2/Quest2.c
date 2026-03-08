#include <stdio.h>
#include <stdlib.h>

typedef struct {
 char diretor[50];
 char titulo[100];
 int ano;
 int duracao; // duracao em minutos
 char genero; // generos possiveis (a-aventura; p-policial; t-terror)
}FILME;

int main(void) {
    FILE *bf, *tf;

    bf = fopen("filmes.bin", "rb");
    tf = fopen("filmes.txt", "w");

    if (bf == NULL || tf == NULL) {
        printf("Erro ao abrir arquivos\n");
        return EXIT_FAILURE;
    }

    FILME f;

    char genInput = ' ';

    while(genInput != 'a' && genInput != 'p' && genInput != 't') {
        printf("Entre com o gênero(a, p ou t): ");
        scanf("%c", &genInput);
    }

    int startYear, endYear;
    printf("Entre com um intervalo de anos(ex: 1989-2001): ");
    scanf("%d-%d", &startYear, &endYear);

    while (!feof(bf)) {
        if (fread(&f, sizeof(FILME), 1, bf) == 1) {
            if (f.genero == genInput && (f.ano >= startYear && f.ano <= endYear)) {
                fprintf(tf, "%s - %d\n", f.titulo, f.ano);
            }
        }
    }

    fclose(bf);
    fclose(tf);

    return EXIT_SUCCESS;
}
