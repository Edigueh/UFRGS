
#
#	Conta bits 1
#

		
.text

	# zera contador
	li	a0,0		# a0 = contagem=0
	lw	a1,bitcont	# a1 = bitcont

loop:
	# se a palavra com os bits for zero, terminou
	beqz	a1, fim
	
	# aplica ascara AND 1 e conta se o resultado for diferente de zero
	andi	t1, a1, 1
	beqz	t1, naoConta
	addi	a0,a0,1
naoConta:

	# shifta logico para a direnta
	srli	a1,a1,1
	b	loop
	
fim:
	sw	a0, contagem, t0
			
	ebreak
	

.data

bitcont:	.word	0x1
contagem:	.word	0
	



	
	
