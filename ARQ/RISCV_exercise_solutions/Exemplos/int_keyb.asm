
		
	.eqv	KD_Rx_Control, 0xffff0000	# low order bit - Receiver Control Register - set 1 if key
	.eqv	KD_Rx_Data, 0xffff0004		# low order byte - Receiver Data Register - resets RCR on read, usindo "lw"
	.eqv	PROG_UIE, 0x100			# Habilitação da interrupção externa em uie
	.eqv	GLOBAL_IE, 1			# Habilitação global da interrupção, em ustatus
	.eqv	PROG_TEC_INT, 0x2		# Programa o teclado para gerar interrupção
	.eqv	CAUSE_TEC, 0x80000008		# Interrupção (bit[31:31] = 1), causa externa (bit[30:0] = 8)
						
	.text

		la	sp, stack		# inicializa o stack pointer
		
		# Programação da interrupção - "N" Extension - Trap no modo direto
		
		la	t0, Trap		# Como Trap é um endereço na memória, já está com os bits[1:0] = 00
		csrw	t0, utvec
		
		li	t0, PROG_UIE		# Habilitação da interrupção externa - causa 8 - teclado
		csrs	t0, uie	
		
		li	t0, PROG_TEC_INT	# Programa o teclado para gerar interrupção
		sw	t0, KD_Rx_Control, t1
		
		li	t0, -1			# Variavel Tecla -> não tem tecla
		sw	t0, Tecla, t1
		
		csrsi	ustatus, GLOBAL_IE	# MIE = 1 - habilitação global
		
		
	Loop:
		lw	t0, Tecla		# Verifica se foi digitada uma tecla
		bltz	t0, Loop
		
		# Pega a Tecla
		
		li	t0, -1			# Reset Tecla
		sw	t0, Tecla, t1
		j	Loop
		
		
	# Trap -- modo direto
	# Atenção: usando os registradores a0 e a1
	Trap:
		nop				# Resolve o "bug" do simulador
		
		csrr	a0, ucause		# Verifica a fonte da interrupção
		li	a1, CAUSE_TEC
		beq	a0, a1, Trap1
		uret
		
	Trap1:		
		lbu	a0, KD_Rx_Data		# Le tecla e salva emna variável Tecla
		sw	a0, Tecla, a1
		uret
		
	
	.data
	Tecla:	.word	-1
	
		.space	0x100
	stack:

