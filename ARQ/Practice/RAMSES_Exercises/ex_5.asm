; Exercício 5
; ● Escreva um programa para multiplicar duas variáveis de oito bits, sem sinal.
;   ○ M = X * Y.
; ● Para isso, utilizar somas sucessivas
; ● O endereço das variáveis “X” e “Y” são:
;   ○ Endereço de X é 128;
;   ○ Endereço de Y é 129.
; ● O resultado deverá ter 16 bits
;   ○ Os endereços da variável M são 130 e 131;
;   ○ Armazenar o valor de M em formato Big Endian.

ORG 128
    X: DB
    Y: DB
    M: DAB 0,0

ORG 0
LOOP:
    LDR A,Y
    JZ FIM
    SUB A,#1
    STR A,Y
    LDR A,M+1
    ADD A,X
    STR A,M+1
    JC INCREMENTA_ALTO
    JMP LOOP
INCREMENTA_ALTO:
    LDR A,M
    ADD A,#1
    STR A,M
    JMP LOOP
FIM:
    HLT
