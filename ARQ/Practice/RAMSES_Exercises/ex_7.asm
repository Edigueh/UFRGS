; Exercício 7
; - Escrever um programa para contar o número de bits “1” existentes em uma determinada região da memória.
; - A região da memória é identificada pelo endereço de início e seu tamanho.
; - O endereço de início está na variável “Inicio”, que está no endereço 128.
; - O tamanho da área está na variável “Tamanho”, que está no endereço 129.
; - O resultado da contagem deve ser colocado na variável “NumBits”, que está no endereço 130.
; - O conteúdo da região de memória não pode ser alterado.
ORG 128
    Inicio: DB
    Tamanho: DB
    NumBits: DB 0
    Ptr: DB
    Final: DB
ORG 0
    LDR X,#0
    LDR B,#0
    LDR A,Inicio ; Carrega endereço armazenado em Inicio para A.
    STR A,Ptr    ; Armazena endereço em A.
    ADD A,Tamanho
    STR A,Final
LOOP:
    LDR A,Ptr,I  ; Carrega conteúdo endereço armazenado em Ptr para A.
    JZ INCREMENTA_PTR
BITSHIFT:
    SHR A
    JC SOMA_UM
    JZ INCREMENTA_PTR
    JMP BITSHIFT
INCREMENTA_PTR:
    LDR A,Final
    SUB A,Ptr
    JZ FIM
    LDR A,Ptr
    ADD A,#1
    STR A,Ptr
    JMP LOOP
SOMA_UM:
    ADD B,#1
    JMP BITSHIFT
FIM:
    STR B,NumBits
    HLT
