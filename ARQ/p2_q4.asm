# Descreva com devem ser os trechos de entrada e término de uma função escrita para o RISC-V (extensão RV32I), que permita a implementação de vários níveis de aninhamento,
# chamadas recursivas e que permita alocar “N” bytes de memória para variáveis locais da função.

# Escreva estes trechos de código para o caso da função chamada "Rotina", em que são necessários 16 bytes de variáveis locais, da seguinte forma:

# Rotina:
# Trecho de entrada (a ser escrito)
# Operações da função
# Trecho de saída (a ser escrito)

# Os trechos de código devem sempre colocar o return address atual e os parâmetros utilizados na função na pilha, incrementando o stack pointer. (push)
# Ao sair de uma função o stack pointer deve ser decrementado (pop).
# As variáveis locais também devem ser pushadas e poppadas da pilha na entrada e saída de cada função recursiva, respectivamente.

# ra -> endereço de retorno
# 16 bytes de variaveis locais
# 4 bytes pro ra
# stack frame = 20 bytes
Rotina:
    addi sp, sp, -20  # reserva o espaço de 16 bytes (4 words) para variáveis locais da função e reserva o espaço pro `ra` na pilha.
    sw ra, 0(sp) # endereço de retorno armazenado na pilha.

	# 4(sp) -> var. local 1
	# 8(sp) -> var. local 2
	# 12(sp) -> var. local 3
	# 16(sp) -> var. local 4

    # Operações da função

    lw ra, 0(sp)
    addi sp, sp, 4
    addi sp, sp, N
    ret
