#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>


/* Exemplo de uso dos argumentos para main
O programa l� um arquivo texto como entrada e gera um arquivo como sa�da com o conte�do do arquivo de entrada convertido para letras min�sculas
Para chamar, digite "exemplo entrada.txt saida.txt" */




int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    clock_t start, end; //para contar o tempo decorrido

    FILE * entrada;
    FILE * saida;

    char *palavra, linha[1000]; // linhas a serem lidas do arquivo
    char separador[]= {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

    if (argc!=3)  //o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
    {
        printf ("N�mero incorreto de par�metros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
        return 1;
    }
    else
    {

        entrada = fopen (argv[1], "r"); // abre o arquivo para leitura -- argv[1] � o primeiro par�metro ap�s o nome do arquivo.
        if (entrada == NULL) //se n�o conseguiu abrir o arquivo
        {
            printf ("Erro ao abrir o arquivo %s",argv[1]);
            return 1;
        }
        else // arquivo de entrada OK

        {
            saida = fopen (argv[2], "w"); // abre o arquivo para saida -- argv[2] � o segundo par�metro ap�s o nome do arquivo.

            start = clock(); //inicia a contagem do tempo


            //percorre todo o arquivo lendo linha por linha
            while (fgets(linha,1000,entrada))
            {
                palavra = strtok (linha, separador); //considera qquer caractere n�o alfab�tico como separador
                while (palavra != NULL)
                {
                    fprintf(saida,"%s ", strlwr(palavra)); //strlwr � a fun��o que converte palavras para min�sculo
                    palavra = strtok (NULL, separador);
                }
            }

            printf("\nArquivo %s gerado com sucesso.\n",argv[2]);

            end = clock(); // finaliza contagem do tempo
            float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
            printf("Tempo: %.5f ms\n",miliseconds);
        }
        fclose (entrada); //fecha os arquivos
        fclose (saida);
        return 0;
    }
}
