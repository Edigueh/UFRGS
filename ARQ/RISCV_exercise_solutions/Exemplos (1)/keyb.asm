		
	.text

		la	sp, stack	# inicializa o stack pointer

		jal	getchar
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
			
	.data
		.space	0x100
	stack:

