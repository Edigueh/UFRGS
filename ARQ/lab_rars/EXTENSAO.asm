
	.text

		la	sp, stack	# inicializa o stack pointer

		li	a0, 5
		jal	rotina
		ebreak

	# Entra: a0 -> parâmetro de entrada
	# Saída: a0 -> valor de retorno
	.eqv	nparam, 8
	rotina:
		addi	sp, sp, -nparam	# entry code
		sw	ra,0(sp)
		sw	a0,4(sp)

		beqz	a0, rotina_1

		addi	a0, a0, -1
		bnez	a0, rotina_rec	# se proximo parametro != 0, chama recursivamente
		li	a0, 1		# senao, rotina(0) = 1, evita chamada recursiva
		j	rotina_join
	rotina_rec:
		jal	rotina
	rotina_join:
		lw	a1, 4(sp)
		mul	a0, a0, a1

		lw	ra,0(sp)	# exit code
		addi	sp, sp, nparam
		ret

	rotina_1:
		li	a0, 1
		lw	ra,0(sp)	# exit code
		addi	sp, sp, nparam
		ret

	.data
		.space	0x100
	stack:
