		
	.text

		la	sp, stack	# inicializa o stack pointer

		li	a0, 'I'
		jal	putchar
		li	a0, 'N'
		jal	putchar
		li	a0, 'F'
		jal	putchar
				
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		
		ebreak
	
	# Entra: a0 -> caractere ASCII a ser colocado no Display
	# Saída: none
	# Stack: not used
	# Uses:  Keyboard And Display MMIO Simulator
	# Blocking poll
	.eqv	KD_Tx_Control, 0xffff0008	# low order bit - Transmitter Control Register - if 1, Tx ready
	.eqv	KD_Tx_Data, 0xffff000C		# low order byte - Transmitter Data Register - trigger display char usando "sw"
	putchar:
		lw	a1, KD_Tx_Control	# laço de polling
		andi	a1, a1, 1
		beqz	a1, putchar
		
		sb	a0, KD_Tx_Data, a1	# lê tecla e reseta bit Ready
	
		ret
			
	.data
		.space	0x100
	stack:

