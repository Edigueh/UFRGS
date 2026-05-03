; Exercício 3
; ● Implementar o cálculo da raiz quadrada, usando a expressão abaixo:
;   ○ N: valor que se deseja calcular a raiz;
;   ○ k: quando “k” atingir o valor da raiz de N, então o somatório será N.
; ● Portanto, o programa deve contar o número de elementos que devem ser somados
; para atingir o valor de “N”
;   ○ Notar que, se N não tiver raiz exata,
;   ○ deve-se procurar o valor mais próximo.

ORG 128
    N: DB 16
    S: DB 1
    K: DB 1
    I: DB 1
ORG 0
LOOP:
    LDR A,S
    SUB A,N
    JZ FIM
    JN PULA_BREAK
    LDR A,K
    SUB A,#1
    STR A,K
    JMP FIM
PULA_BREAK:
    LDR A,I
    ADD A,#2
    STR A,I
    LDR A,S
    ADD A,I
    STR A,S
    LDR A,K
    ADD A,#1
    STR A,K
    JMP LOOP
FIM:
    HLT
