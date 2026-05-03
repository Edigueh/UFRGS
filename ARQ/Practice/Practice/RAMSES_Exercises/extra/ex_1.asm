; Exercício 1
; ● Escrever um programa para o Computador RAMSES capaz de contar o número de
; dígitos ASCII numéricos existentes em um vetor. Os dígitos ASCII numéricos são
; representados pelos valores 48 (‘0’) até 57 (‘9’), inclusive.
; ● Considere que:
;   ○ O vetor terá, sempre, um byte com valor 0 (zero) no seu final;
;   ○ Seu programa e dados privados devem ser colocados entre o endereço 0 e 127.
; ● Considere que no início da execução de seu programa vale o seguinte:
;   ○ O endereço de início do vetor está armazenado na posição 128 da memória.
; ● Ao final da execução:
;   ○ O resultado do programa (contagem de dígitos numéricos) deverá ser escrito no endereço 129.
ORG 127
    vet_ptr:    DB
    vetor_addr: DB
    res:        DB

ORG 0
INIT:
    LDR B,#0
    LDR A,vetor_addr
    STR A,vet_ptr
LOOP:
    LDR A,vet_ptr,I
    JZ FIM
    SUB A,#48
    JN INCREMENTA_PTR ; se é menor que 48 não é ASCII numérico
    JZ INCREMENTA_B   ; se é zero é por que é '0'
    SUB A,#9          ; é maior que '0', preciso checar se é <= '9' 
    JN INCREMENTA_B   ; está entro '0' e '9' não incluindo limites. 
    JZ INCREMENTA_B   ; é '9'
    JMP INCREMENTA_PTR
INCREMENTA_B:
    ADD B,#1
INCREMENTA_PTR:
    LDR A,vet_ptr
    ADD A,#1
    STR A,vet_ptr
    JMP LOOP
FIM:
    STR B,res
    HLT
