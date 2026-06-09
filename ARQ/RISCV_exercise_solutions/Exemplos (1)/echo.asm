		
	.text

		la	sp, stack	# inicializa o stack pointer
	loop:	
		jal	getchar
		li	a1, 'f'
		beq	a0, a1, fim
		
		jal	putchar
		b	loop

	fim:		
		ebreak
	
	# Entra: none
	# Saída: a0 -> valor de retorno
	# Stack: not used
	# Uses:  Keyboard And Display MMIO Simulator
	# Blocking poll
	.eqv	KD_Rx_Control, 0xffff0000	# low order bit - Receiver Control Register - set 1 if key
	.eqv	KD_Rx_Data, 0xffff0004		# low order byte - Receiver Data Register - resets RCR on read, usindo "lw"
	getchar:
		lw	a0, KD_Rx_Control	# laço de polling
		andi	a0, a0, 1
		beqz	a0, getchar
		
		lbu	a0, KD_Rx_Data		# lê tecla e reseta bit Ready
	
		ret

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

