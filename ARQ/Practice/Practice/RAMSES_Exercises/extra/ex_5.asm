; Exercício 5
; ● Escrever um programa para o Computador RAMSES capaz de contar o número de
; pares de bits existentes em um vetor de bytes. Cada byte do vetor tem 4 pares de
; bits. Os pares de bits são (i) bits 7 e 6, (ii) bits 5 e 4, (iii) bits 3 e 2 e (iv) bits 1 e 0.
; ● Considere que:
;   ○ O vetor terá tamanho fixo de 8 bytes.
;   ○ Seu programa e dados privados devem ser colocados entre o endereço 0 e 127.
; ● Considere que no início da execução de seu programa vale o seguinte:
;   ○ O endereço de início do vetor é 144.
; ● Ao final da execução:
;   ○ O resultado do programa (contagem dos pares de bits) deverá ser escrito no endereço 128 até 131.
;   ○ A contagem de pares 00 deve ser colocada no endereço 128.
;   ○ A contagem de pares 01 deve ser colocada no endereço 129.
;   ○ A contagem de pares 10 deve ser colocada no endereço 130.
;   ○ A contagem de pares 11 deve ser colocada no endereço 131.
ORG 128
    zz: DB 0 ; pares 00
    zo: DB 0 ; pares 01
    oz: DB 0 ; pares 10
    oo: DB 0 ; pares 11
ORG 144
    vetor: DAB [8] ; vetor de 8 bytes
ORG 0
    LDR X,#0
    STR X,zz
    STR X,zo
    STR X,oz
    STR X,oo
WHILE:
    LDR A,vetor,X
    JSR CONTA_PARES
    ADD X,#1
    SUB X,#8
    JZ FIM
    ADD X,#8
    JMP WHILE
FIM: 
    HLT

CONTA_PARES:
    NOP
    LDR B,#0
    STR B,j
LOOP:
    SUB B,#4
    JZ RETORNO
    SHR A
    JC ZO_OU_OO
ZZ_OU_OZ:
    SHR A
    JC INC_OZ
    JMP INC_ZZ
ZO_OU_OO:
    SHR A
    JC INC_OO
INC_ZO:
    LDR B,zo
    ADD B,#1
    STR B,zo
    JMP CONTINUA
INC_ZZ:
    LDR B,zz
    ADD B,#1
    STR B,zz
    JMP CONTINUA
INC_OZ:
    LDR B,oz
    ADD B,#1
    STR B,oz
    JMP CONTINUA
INC_OO:
    LDR B,oo
    ADD B,#1
    STR B,oo
CONTINUA:
    LDR B,j
    ADD B,#1
    STR B,j
    JMP LOOP
RETORNO:
    JMP CONTA_PARES,I

j: DB 0
