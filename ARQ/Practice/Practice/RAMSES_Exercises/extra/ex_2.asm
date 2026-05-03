; Exercício 2
; ● Escrever um programa para o Computador RAMSES capaz de codificar quatro valores
; existentes na memória, conforme uma tabela de códigos.
; ● Considere que:
;   ○ Somente serão codificados os 4 bits menos significativos dos bytes. Os 4 bits mais significativos devem
; ser ignorados.
;   ○ A codificação de cada valor é feita pela posição correspondente da tabela. (ex: se o valor for 5, deverá
; ser usada a 5 da tabela para obter o dódigo)
;   ○ Seu programa e dados privados devem ser colocados entre os endereços 0 e 127.
; ● Considere que no início da execução de seu programa vale o seguinte:
;   ○ Os quatro bytes a serem codificados estão nos endereços 128 até 131.
;   ○ A tabela de codificação está nos endereços 144 até 159.
; ● Ao final da execução:
;   ○ Cada byte codificado deverá ser escrito nos endereços 132 até 135, correspondendo aos conteúdos
; dos endereços 128 até 131, respectivamente.
ORG 128
    in:  DAB [4]
    out: DAB [4]
ORG 144
    tab: DAB '0123456789ABCDEF'
ORG 0
    LDR X,in
    JSR ENCODE
    STR A,out

    LDR X,in+1
    JSR ENCODE
    STR A,out+1

    LDR X,in+2
    JSR ENCODE
    STR A,out+2

    LDR X,in+3
    JSR ENCODE
    STR A,out+3
FIM:
    HLT
ENCODE:
    NOP
    AND X,#H0F
    LDR A,tab,X
    JMP ENCODE,I
