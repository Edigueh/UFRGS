; Exercício 3
; ● Escrever um programa para o Computador RAMSES capaz de calcular o endereço de
; memória correspondente a um dos elementos de uma matriz quadrada.
; ● Considere que:
;   ○ As coordenadas da matriz (linha e coluna) são valores entre 1 e 8. 
      -> Logo, a matriz tem tamanho 8x8
;   ○ Na memória, a matriz está organizada por linhas e, dentro das linhas, por colunas.
;   ○ Seu programa e dados privados devem ser colocados entre os endereços 0 e 127.
; ● Considere que no início da execução de seu programa vale o seguinte:
;   ○ O endereço de início da matriz está escrito no endereço 128.
;   ○ A coordenada “linha” da matriz está no endereço 129.
;   ○ A coordenada “coluna” da matriz está no endereço 130.
; ● Ao final da execução:
;   ○ Seu programa deve escrever no endereço 131 o endereço da posição de memória correspondente às
; coordenadas solicitadas.
ORG 127
    tmp:         DB
    matrix_addr: DB
    row:         DB
    col:         DB
    target_addr: DB
ORG 0
    LDR A,row
    SUB A,#1

    STR A,tmp
    ADD A,tmp
    STR A,tmp
    ADD A,tmp
    STR A,tmp
    ADD A,tmp ; row * 8(2^3) (dado que a matriz tem tamanho 8)

    ADD A,col
    SUB A,#1
    ADD A,matrix_addr ; 8 * (row - 1) + (col - 1) + matrix_addr

    STR A,target_addr
    HLT
