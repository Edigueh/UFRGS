

		
.text

	# inicializa o stack pointer
	la	sp, stack
	

	jal	rotA

	
	ebreak
	
	
rotA:
	#entry - salva ra na pilha
	addi	sp, sp, -4
	sw	ra,0(sp)
	
	jal	rotB
	
	#exit - retorna ra da pilha
	lw	ra,0(sp)
	addi	sp, sp, 4
	ret

rotB:
	#entry - salva ra na pilha
	addi	sp, sp, -4
	sw	ra,0(sp)
	
	jal	rotC
	
	#exit - retorna ra da pilha
	lw	ra,0(sp)
	addi	sp, sp, 4
	ret

rotC:
	#entry - salva ra na pilha
	addi	sp, sp, -4
	sw	ra,0(sp)
	
	# rotina
	
	#exit - retorna ra da pilha
	lw	ra,0(sp)
	addi	sp, sp, 4
	ret
	
	
.data

	.space	0x100
stack:

