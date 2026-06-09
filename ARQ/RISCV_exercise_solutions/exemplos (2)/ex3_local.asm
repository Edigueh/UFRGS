

		
.text

	la	sp, stack
	
	# passagem de parâmetro na pilha
	# a função terá variáveis locais
	li	t1, 100
	
	addi	sp, sp, -4	# push t1
	sw	t1, 0(sp)
	jal	subrotina
	addi	sp, sp, 4	# pop
	

	ebreak	

# ra -> endereço de retorno	
# parâmetro -> na pilha
# 3 palavras de variáveis locais
# stack frame = 16 bytes
subrotina:
	addi	sp, sp, -16		# 1 word (end. retorno) 3 words (var. locais)
	sw	ra, 0(sp)		# End. retorno
	
	# 4(sp) -> var. local 1
	# 8(sp) -> var. local 2
	# 12(sp) -> var. local 3
	# 16(sp) -> parametro

	lw	s0,16(sp)
	
	lw	ra, 0(sp)
	addi	sp, sp, 16
	
	ret

	
.data
vetor:	.word	1, 2, 3, 4, 5
area:	.word	0

	.space	0x40
stack:



