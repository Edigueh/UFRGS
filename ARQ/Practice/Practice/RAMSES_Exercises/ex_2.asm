; Implementar um programa capaz de calcular o número de caracteres de um vetor,
; conforme o programa abaixo:
; ● O “vetor” é um string em “C”, que termina com ‘\0’
; ● Utilize o modo indireto, pois o acesso ao vetor está sendo feito por um ponteiro.

ORG 128
    n: DB         ; unsigned char n
    p: DB         ; char* p
    vetor: DAB [50] ; char vetor[50]

ORG 0
    LDR A,#vetor ; #vetor em um array byte dá o endereço do primeiro numero
    STR A,p
    LDR A,#0
    STR A,n
WHILE:
    LDR A,p,I
    JZ FIM
    LDR A,n
    ADD A,#1
    STR A,n
    LDR A,p
    ADD A,#1
    STR A,p
    JMP WHILE
FIM:
    HLT
