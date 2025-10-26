### Medição de Tempo em Jogos Digitais

1. Objetivo
O objetivo do trabalho é comparar o desempenho de diferentes estruturas de dados vistas na
disciplina em uma aplicação de estimativa de tempo de jogo com base em dados da plataforma Steam.
2. Especificação da Aplicação
Um jogador está montando uma lista de jogos que pretende jogar nas próximas semanas. Ele
gostaria de saber quanto tempo, em média, precisará investir para jogar todos eles. Para isso, ele
consulta um arquivo com estatísticas públicas de jogos da Steam, contendo o nome do jogo e o tempo
médio de jogo efetivamente “jogado” pelos usuários, medido em horas (número float).
Esse processo de estimar o tempo total é demorado e sujeito a erros, especialmente quando há
centenas de jogos disponíveis. Por isso, o jogador decidiu automatizar a tarefa.
★ Sua tarefa é projetar uma aplicação que recebe dois arquivos de entrada:
3. Um arquivo CSV contendo o nome dos jogos e o número médio de horas jogadas. Para
teste, use o dataset disponível no Moodle que foi gerado a partir do dataset “steam video
games” [1].
4. Um arquivo texto contendo uma lista de jogos que o jogador deseja jogar (um jogo por
linha).
A tabela de jogos e suas horas médias devem ser armazenadas em duas estruturas de dados.
Você deve criar diferentes versões da aplicação utilizando pelo menos duas das quatro árvores vistas em
aula (ABP, AVL, Rubro-Negra ou Splay).
★ A tabela de jogos (arquivo CSV) deve ser carregada na árvore na ordem em que os jogos
aparecem no arquivo. As chaves devem ser os nomes dos jogos. Assuma que não haverá repetição de
nomes.
★ A aplicação não é case sensitive: letras maiúsculas e minúsculas devem ser tratadas como
iguais.
★ A lista de jogos escolhidos pelo jogador não deve ser armazenada em nenhuma estrutura.
Cada jogo deve ser usado apenas para consultar a árvore e encontrar seu respectivo tempo médio. Se
um jogo da lista não se encontra na tabela de jogos, utilize zero como tempo médio e compute seu
tempo.
★ Seu programa deverá ser chamado a partir da linha de comando (passando parâmetros para o
main).
Exemplo de chamada: C:\estimador\_horas steam\_games.csv lista\_jogos.txt
saida\_lista.txt
As entradas e saídas da sua aplicação são:
Entradas:
(i) nome do arquivo com a tabela de jogos e suas horas médias;
(ii) nome do arquivo com os jogos escolhidos pelo jogador.