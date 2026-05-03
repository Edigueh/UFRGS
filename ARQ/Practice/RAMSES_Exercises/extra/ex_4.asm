; Exercício 4
; ● Escrever um programa para o Computador RAMSES capaz de calcular a soma/diferença dos elementos de um
; vetor da memória, composto por números de 16 bits com sinal (complemento de 2).
; ● Partindo de zero, o cálculo deve somar os elementos de posição par (0, 2, 4, etc) e diminuir os elementos de
; posição impar (1, 3, 5, etc).
;   ○ Ex: Se no vetor houver “10, 3, 5, 15, 20”, o resultado será: 10 – 3 + 5 – 15 + 20 = 17
; ● Considere que:
;   ○ O vetor terá, sempre, um número zero no seu final.
;   ○ Cada elemento do vetor vai ocupar 2 bytes. O menor endereço desses dois receberá o byte mais significativo; o maior endereço
; desses dois receberá o byte menos significativo. ; Little endian.
;   ○ Ignorar overflow de representação.
;   ○ Seu programa e dados privados devem ser colocados entre o endereço 0 e 127.
; ● Considere que no início da execução de seu programa vale o seguinte:
;   ○ O endereço de início do vetor é 130.
; ● Ao final da execução:
;   ○ O resultado do programa (operação com os elementos) deverá ser escrito nos endereços 128 (parte mais significativa) e 129 (parte
; menos significativa).
ORG 128
    ANS: DW 0 ; Little endian [MSBy, LSBy]
    vet: DAW 10,3,5,15,20,0
ORG 0
INIT:
    LDR X,#0
    STR X,FLAG
LOOP:
    LDR A,vet,X
    OR A,vet+1,X
    JZ FIM
    LDR A,FLAG
    JZ SOMA
SUBTRAI:
    NOT A
    STR A,FLAG
    
    LDR A,ANS
    SUB A,vet,X
    STR A,ANS

    LDR B,ANS+1
    SUB B,vet+1,X
    STR B,ANS+1

    JC INC_X
    SUB A,#1
    STR A,ANS
    JMP INC_X
SOMA:
    NOT A
    STR A,FLAG
    
    LDR A,ANS
    ADD A,vet,X
    STR A,ANS

    LDR B,ANS+1
    ADD B,vet+1,X
    STR B,ANS+1

    JC VAI_UM
    JMP INC_X
VAI_UM:
    ADD A,#1
    STR A,ANS
INC_X:
    ADD X,#2
    JMP LOOP
FIM:
    HLT
FLAG: DB 0
