#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

/* Exemplo de uso dos argumentos para main
O programa lê um arquivo texto como entrada e gera um arquivo como saída com o conteúdo do arquivo de entrada convertido para letras minúsculas
Para chamar, digite "exemplo entrada.txt saida.txt"
*/

// argc conta o número de parâmetros e argv armazena as strings correspondentes aos parâmetros digitados
int main(int argc, char *argv[]) {
    // para imprimir corretamente na tela os caracteres acentuadoss
    setlocale(LC_ALL, "");

    if (argc != 3) {
        // o numero de parametros esperado é 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
        printf("Número incorreto de parâmetros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
        return 1;
    }

    // abre o arquivo para leitura -- argv[1] é o primeiro parâmetro após o nome do arquivo.
    FILE *entrada = fopen(argv[1], "r"); 
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo %s", argv[1]);
        return 1;
    }

    // abre o arquivo para saida -- argv[2] é o segundo parâmetro após o nome do arquivo.
    FILE *saida = fopen(argv[2], "w"); 

    // linhas a serem lidas do arquivo
    char linha[1000], separador[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

    // inicia a contagem do tempo
    clock_t start = clock();

    // percorre todo o arquivo lendo linha por linha
    while (fgets(linha, 1000, entrada)) {
        // considera qquer caractere não alfabético como separador
        char *palavra = strtok(linha, separador);
        while (palavra != NULL) {
            // strlwr é a função que converte palavras para minúsculo
            fprintf(saida, "%s ", strlwr(palavra));
            palavra = strtok(NULL, separador);
        }
    }

    printf("\nArquivo %s gerado com sucesso.\n", argv[2]);

    // finaliza contagem do tempo
    clock_t end = clock();

    // calcula o tempo decorridos
    printf("Tempo: %.5f ms\n", (float)(end - start) / CLOCKS_PER_SEC * 1000);

    // fecha os arquivos
    fclose(entrada); 
    fclose(saida);
    return 0;
}
