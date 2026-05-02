; Escreva um trecho de programa que faça a atribuição “j=k”,
; apenas quando o bit 6 de “k” for 1.
; ● Considere:
;   ○ char j,k;

ORG 128
    j: DB ; char j;
    k: DB ; char k;

ORG 0
    LDR A,k
    AND A,#64
    JZ FIM
    LDR A,k
    STR A,j
FIM:
    HLT
