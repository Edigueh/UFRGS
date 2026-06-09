
#
#	Soma elementos de um vetor de words
#

		
.text

	# Inicializa ponteiro do vetor e contador de elementos
	lw	a0, start		# a0 = vetor
	lw	a1, len			# a1 = len
	mv	a2, zero		# somatório

loop:
	# verifica se len chegou a zero
	beqz	a1, fim
	
	# soma um elemento
	lw	t0, 0(a0)
	add	a2, a2, t0
	
	# avança a0 e decrementa a1
	addi	a0, a0, 4
	addi	a1, a1, -1
	
	b	loop
	
fim:
	sw	a2, res, t0
			
	ebreak
	

.data

start:	.word	vetor		# word *p
len:	.word	5		# word c
res:	.word	0		# word c

	.space	0x20
vetor:	.word	1, 2, 3, 4, 5, 6 , 7, 8


	



	
	
