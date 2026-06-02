# =============================================================
# EXTENSAO.asm — calcula fatorial recursivo de um inteiro >= 0
#
# Convenções (ABI RISC-V):
#   a0 -> parâmetro de entrada da rotina E também valor de retorno
#   ra -> return address (gravado pelo `jal`)
#   sp -> stack pointer (cresce para baixo)
#
# Layout de memória deste programa:
#   .text  : código (esta seção)
#   .data  : 256 bytes reservados (`.space 0x100`)
#   stack  : rótulo no FIM da .data; sp começa nele e desce
#
# Cada chamada da rotina aloca um frame de 8 bytes na pilha
# para salvar `ra` (offset 0) e `a0` (offset 4), porque ambos
# são modificados pela chamada recursiva e precisam ser
# restaurados depois para combinar o resultado.
# =============================================================
.text
	la sp, stack # inicializa sp com endereço do topo da pilha
	             # rótulo `stack` está logo após o bloco de 256 bytes.
	             
	li a0, 5     # carrega 5 em a0 -> input (queremos 5!).
	jal rotina   # chama rotina; ra recebe endereço da próxima instrução.
	ebreak       # breakpoint: para execução, inspecione a0 = 120.
	
	# Entrada: a0 -> parâmetro de entrada (n).
	# Saída: a0 -> valor de retorno (n!).
.eqv nparam, 8 # tamanho do stack frame em bytes (2 words = 8)
rotina:
# === entry code: aloca frame e salva contexto ===
	addi sp, sp, -nparam # desce sp em 8 bytes -> reserva frame
	sw ra, 0(sp) # salva ra em offset 0 (jal recursivo vai sobrescrever ra)
	sw a0, 4(sp) # salva a0 (n) em offset 4 (precisamos do n original depois
		     # para multiplicar pelo retorno de rotina(n-1))
        
        beqz a0, rotina_1 # se n == 0, desvia para caso base (retorna 1)
        
        addi a0, a0, -1 # a0 = n - 1 (prepara argumento da chamada recursiva).
        bnez a0, rotina_rec # se (n -1) != 0, faz chamada recursiva normal.
        li a0, 1 # se (n-1) == 0 então rotina(0) = 1, evitando uma chamada recursiva.
        j rotina_join # pula direto para o ponto de combinar o resultado
        
# === caso recursivo: chama rotina(n-1) ===
rotina_rec:
	jal rotina # a0 entra como (n-1); ao retornar, a0 = (n-1)!

# === join: combina resultado com o n original salvo na pilha ===
rotina_join:
	lw a1, 4(sp) # recupera n original do frame -> a1 = n
	mul a0, a0, a1 # a0 = (n-1!) * n -> a0 = n!
	
# === exit code: libera frame e retorna ===
	lw ra,0(sp) # restaura ra (endereço de retorno do chamador)
	addi sp, sp, nparam # sobe sp em 8 -> libera frame
	ret # pula para ra (volta ao chamador)
	
# === caso base: n = 0, retorna 1 ===
rotina_1:
	li a0, 1 # 0! = 1
	lw ra,0(sp) # restaura ra (endereço de retorno do chamador)
	addi sp, sp, nparam # sobe sp em 8 -> libera frame
	ret # pula para ra (volta ao chamador)

.data 
	.space 0x100 # reserva 256 bytes para a área de pilha.
stack:
