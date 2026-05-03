; Exercício 1
; ● Implementar um programa capaz de calcular o número de caracteres de um vetor
;   ○ O resultado deverá ser colocado no endereço 128;
;   ○ O vetor inicia no endereço 129.
; ● O “vetor” é um string em “C”, que termina com ‘\0’
; ● Utilize o modo indexado, pois o endereço do vetor é conhecido.

ORG 128
    resultado: DB 0
    vetor: DAB [50]
ORG 0
    LDR X,#0
LOOP:
    LDR A,vetor,X
    JZ FIM
    ADD X,#1
    JMP LOOP
FIM:
    STR X,resultado
    HLT
