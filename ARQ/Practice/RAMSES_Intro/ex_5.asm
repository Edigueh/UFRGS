; Exercício 5
; ● Escreva um trecho de programa que atribua para “x” o valor “x – y”, apenas quando “x>=y”.
; ● Considere que “x” e “y” foram declarados da seguintes forma:
;   ○ char x,y;
; ● Dica: usar SUB e JN

ORG 128
    x: DB ; char x;
    y: DB ; char y;

ORG 0
    LDR A,x
    SUB A,y
    JN FIM
    STR A,x
FIM:
    HLT
