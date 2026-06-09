

		
.text

	la	sp, stack

	# passagem de parâmetro por VALOR em REGISTRADOR
	la	a0, vetor
	lw	t1,8(a0)	# t1 -> parametro em registrador (valor)
	jal	rotA
	
	# passagem de parâmetro por REFERÊNCIA em REGISTRADOR
	la	a0, vetor
	addi	t1, a0, 8	# t1 -> parâmetro em registrador (referência)
	jal	rotB
	
	# passagem de parâmetro por VALOR em ÁREA ESPECÍFICA
	la	a0, vetor
	lw	t1,8(a0)
	sw	t1, area, t2	# area -> parâmetro em memória (valor)
	jal	rotC
	
	# passagem de parâmetro na pilha
	la	a0, vetor
	lw	t1,8(a0)
	
	addi	sp, sp, -4	# push t1
	sw	t1, 0(sp)
	jal	rotD
	addi	sp, sp, 4	# pop
	

	ebreak	

# ra -> endereço de retorno	
# parâmetro -> t1 (valor)
rotA:
	mv	s0, t1
	ret

# ra -> endereço de retorno	
# parâmetro -> t1 (referência)
rotB:
	lw	s0,(t1)
	ret
	
# ra -> endereço de retorno	
# parâmetro -> area
rotC:
	lw	s0, area
	ret

# ra -> endereço de retorno	
# parâmetro -> word na pilha
rotD:
	lw	s0,0(sp)
	ret

	
.data
vetor:	.word	1, 2, 3, 4, 5
area:	.word	0

	.space	0x40
stack:



