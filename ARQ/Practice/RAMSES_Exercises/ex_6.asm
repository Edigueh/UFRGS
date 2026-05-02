; Exercício 6
; ● Escrever um programa que converta 2 dígitos ASCII em um número hexadecimal de 8 bits.
;   ○ Os dígitos ASCII estão armazenados na variável “Ascii”, em formato Big Endian;
;   ○ Os endereços da variável Ascii são 128 e 129.
; ● O resultado do programa deve ser colocado na variável “Hexa”
;   ○ Seu endereço é 130.
; ● Exemplo:
;   ○ Conteúdo do endereço 128 = 032H (ASCII ‘2’);
;   ○ Conteúdo do endereço 129 = 041H (ASCII ‘A’);
;   ○ Resultado da conversão, no endereço 130 = 02AH.
ORG 128
    Ascii: DAB H32,H41 ; 2 Dígitos ASCII
    Hexa: DB 0     ; Resultado

ORG 0
    LDR A,Ascii
    JSR ASCII_TO_HEX
    STR A,Hexa

    ADD A,Hexa
    STR A,Hexa

    ADD A,Hexa
    STR A,Hexa

    ADD A,Hexa
    STR A,Hexa

    ADD A,Hexa
    STR A,Hexa

    LDR A,Ascii+1
    JSR ASCII_TO_HEX
    ADD A,Hexa
FIM:
    STR A,Hexa
    HLT

ASCII_TO_HEX:
    NOP
    SUB A,#H41
    JN EH_NUM
EH_LETRA:
    ADD A,#HA
    JMP RETORNO
EH_NUM:
    ADD A,#H11
RETORNO:
    JMP ASCII_TO_HEX,I
