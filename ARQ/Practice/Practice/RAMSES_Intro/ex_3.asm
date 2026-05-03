; Exercício 3
; ● Implemente usando instruções do RAMSES os seguintes comandos em C
;   ○ k = c;
;   ○ k = i;
;   ○ i = k;
;   ○ x = c;
; ● Considere que as variáveis foram definidas da seguinte forma
;   ○ char c;
;   ○ unsigned char k;
;   ○ unsigned short int i;
;   ○ short int x;
; ● Considere que
;   ○ char               = 8 bits com sinal
;   ○ unsigned char      = 8 bits sem sinal
;   ○ unsigned short int = 16 bits sem sinal
;   ○ short int          = 16 bits com sinal
; Considere little endian sempre que necessário.

ORG 128
    c: DB 0     ; char c;
    k: DB 0     ; unsigned char k;
    i: DAB 0,0   ; unsigned short int i;
    x: DAB 0,0   ; short int x;

ORG 0
    LDR A,c
    STR A,k ; k = c -> Cópia direta 8→8 bits.

    LDR A,i
    STR A,k ; k = i -> Little-endian, i é o low byte, truncar para 8 bits pega o low byte.

    LDR A,k
    STR A,i 
    LDR A,#0
    STR A,i+1 ; i = k -> Low byte recebe k, high byte zerado (zero extension para unsigned).

    LDR A,c
    STR A,x
    JN TRATA_NEGATIVO
    LDR A,#0
    STR A,x+1
    JMP FIM
TRATA_NEGATIVO:
    LDR A,#255
    STR A,x+1 ; x = c -> Low byte recebe c inteiro, depois o JN testa o flag N (que foi setado pelo LDR A,c / STR A,x refletindo o bit 7 de c).
              ;  Se negativo, high byte = 255 (0xFF); se positivo, high byte = 0.
FIM:
    HLT
