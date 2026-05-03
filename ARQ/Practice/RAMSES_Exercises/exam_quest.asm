; Utilizar, exclusivamente, os modo de endereçamento IMEDIATO, DIRETO ou INDEXADO, escrever um trecho de programa, 
; iniciando no endereço 0 (zero), para ler o conteúdo do elemento "m" do string "v" de caracteres, para o registrador "A".
; Ou seja, deseja-se que:
; A ← v[m]
; Cada caractere ocupa 1 byte no string, e existe uma marca de fim de string de valor 0 (zero).
; Para escrever o programa considere que:
; 	org	100
; m:	db	0	; Contém o índice do elemento do string a ser lido
; ev:	db	0	; Contém o endereço de início do string "v"
ORG 100
    m:  DB 0 ; Contém o índice do elemento do string a ser lido
    ev: DB 0 ; Contém o endereço de início do string "v"

ORG 0
    LDR A,m
    ADD A,ev
    STR A,LOAD+1
LOAD:
    LDR A,0 ; '0' será substituído por LOAD+1
FIM:
    HLT
