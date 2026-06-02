
# =============================================================
# lab1.asm — calcula fatorial recursivo de um inteiro >= 0
#
# Versão BASE (sem otimização). Para cada chamada com n > 0,
# desce um nível recursivo até atingir rotina(0), que retorna 1
# pelo caso base. A versão otimizada está em EXTENSAO.asm.
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

		la	sp, stack	# inicializa sp com endereço do topo da pilha
					# (rótulo `stack` está logo após o bloco de 256 bytes)

		li	a0, 5		# carrega 5 em a0 (entrada: queremos 5!)
		jal	rotina		# chama rotina; ra recebe endereço da próxima instrução
		ebreak			# breakpoint: para execução; inspecione a0 = 120 (0x78)

	# Entra: a0 -> par metro de entrada (n)
	# Sa da: a0 -> valor de retorno (n!)
	.eqv	nparam, 8		# tamanho do stack frame em bytes (2 words = 8)
	rotina:
	# === entry code: aloca frame e salva contexto ===
		addi	sp, sp, -nparam	# desce sp em 8 bytes -> reserva frame
		sw	ra,0(sp)	# salva ra em offset 0 (jal recursivo vai sobrescrever ra)
		sw	a0,4(sp)	# salva a0 (n) em offset 4 (precisamos do n original
					#  depois para multiplicar pelo retorno de rotina(n-1))

		beqz	a0, rotina_1	# se n == 0, desvia para caso base (retorna 1)

	# === recursão: chama rotina(n-1) sempre que n > 0 ===
		addi	a0, a0, -1	# a0 = n - 1 (argumento da chamada recursiva)
		jal	rotina		# chama rotina(n-1); ao retornar, a0 = (n-1)!

	# === join: combina resultado com o n original salvo na pilha ===
		lw	a1, 4(sp)	# recupera n original do frame -> a1 = n
		mul	a0, a0, a1	# a0 = (n-1)! * n  -> a0 = n!

	# === exit code: libera frame e retorna ===
		lw	ra,0(sp)	# restaura ra (endereço de retorno do chamador)
		addi	sp, sp, nparam	# sobe sp em 8 -> libera frame
		ret			# pula para ra (volta ao chamador)

	# === caso base: n == 0, retorna 1 ===
	rotina_1:
		li	a0, 1		# 0! = 1
		lw	ra,0(sp)	# restaura ra (mesmo exit code do bloco acima)
		addi	sp, sp, nparam	# libera frame
		ret			# retorna ao chamador

	.data
		.space	0x100		# reserva 256 bytes para área de pilha
	stack:				# topo inicial da pilha (sp aponta aqui no início)
