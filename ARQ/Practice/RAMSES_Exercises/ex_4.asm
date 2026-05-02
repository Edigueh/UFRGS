; Exercício 4
; ● Faça um programa para mover o conteúdo de uma área origem da memória para uma área destino.
;   ○ As áreas não se sobrepõem.
; ● São fornecidos como entradas:
;   ○ Endereço inicial da área origem: está no endereço 128;
;   ○ Endereço inicial da área de destino: está no endereço 129;
;   ○ Tamanho da área (número de bytes a serem transferidos): está no endereço 130.

ORG 128
    INICIO_ORIGEM:  DB 134
    INICIO_DESTINO: DB 140
    TAMANHO_AREA:   DB 4
    PTR_ORIGEM:     DB 0
    PTR_DESTINO:    DB 0

ORG 0
    LDR A,INICIO_ORIGEM
    STR A,PTR_ORIGEM
    LDR A,INICIO_DESTINO
    STR A,PTR_DESTINO
LOOP:
    LDR A,TAMANHO_AREA
    JZ FIM
    SUB A,#1
    STR A,TAMANHO_AREA
    LDR A,PTR_ORIGEM,I
    STR A,PTR_DESTINO,I
    LDR A,TAMANHO_AREA
    JZ FIM
    LDR A,PTR_ORIGEM
    ADD A,#1
    STR A,PTR_ORIGEM
    LDR A,PTR_DESTINO
    ADD A,#1
    STR A,PTR_DESTINO
    JMP LOOP
FIM:
    HLT
