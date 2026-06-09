
	# Keyboard and Display MMIO
	.eqv	KD_Tx_Control, 0xffff0008		# low order bit - Transmitter Control Register - if 1, Tx ready
	.eqv	KD_Tx_Data,    0xffff000C		# low order byte - Transmitter Data Register - trigger display char usando "sw"

	# Timer
	.eqv	TIM_l, 0xffff0018		# Timer
	.eqv	TIM_h, 0xffff001C
	.eqv	timercmp_l, 0xFFFF0020		# Valor para comparação do Time, para gerar a interrupção
	.eqv	timercmp_h, 0xFFFF0024
	
	# Processador
	.eqv	PROG_UTIE, 0x10			# Habilitação da interrupção de timer em uie
	.eqv	GLOBAL_IE, 1			# Habilitação global da interrupção, em ustatus
	.eqv	CAUSE_TIMER, 0x80000004		# Interrupção (bit[31:31] = 1), causa externa (bit[30:0] = 4)
						
	.text

		la	sp, stack		# inicializa o stack pointer
		
		# Programação da interrupção - "N" Extension - Trap no modo direto	
		la	t0, Trap		# Como Trap é um endereço na memória, já está com os bits[1:0] = 00
		csrw	t0, utvec


		# Controle do TIMER
		
		li	t0, PROG_UTIE			# Habilitação da interrupção externa - causa 8 - teclado
		csrs	t0, uie	
				
		jal	setTimercmp			# programa timercmp para timer + 1000 ms
		
		# Habilita interrupção global
		csrsi	ustatus, GLOBAL_IE		# MIE = 1 - habilitação global
		
		
	Loop:
		
		# Atualiza relogio na tela
		li	a0, 0				# coordenada X
		li	a1, 0				# coordenada Y
		jal	poscur
		
		lw	a0, hora
		jal	format2
		li	a0, ':'
		jal	putchar
		lw	a0, min
		jal	format2
		li	a0, ':'
		jal	putchar
		lw	a0, seg
		jal	format2
		
		j	Loop

	# Reprograma timercmp
	# timercmp = timer + 1000
	setTimercmp:	
		li	a3, 1000
		
	getTime:
		lw	a1, TIM_h			# Le timer para a1,a0
		lw	a0, TIM_l
		lw	a2, TIM_h
		bne	a2, a1, getTime
		
		add	a2, a0, a3			# a1,a2 = a1,a0 + 1000
		sltu	a0, a2, a0			# Se a parte lower resultante for MENOR do que a original, então houve um CARRY
		add	a1, a1, a0			# Add carry
		
		sw	a1, timercmp_h, a3		# timercmp = timer + 1000 (sem glitch)
		sw	a2, timercmp_l, a3
		
		ret


	# coloca dois digitos no display
	# entra: a0 -> numero	
	format2:
		li	t0, 10
		divu	t1, a0, t0			# dezenas = a0 /10
		remu	t2, a0, t0			# unidades = a0 %10
		
		addi	a0, t1, '0'
		addi	a1, t2, '0'
		
		addi	sp, sp, -8			# push 8
		sw	a1, 0(sp)
		sw	ra, 4(sp)
		
		jal	putchar
		
		lw	a0, 0(sp)			# get a1 -> a0
		jal	putchar
		
		lw	ra, 4(sp)			# get ra
		addi	sp, sp, 8			# pop 8
		
		ret


	# Entra: a0 -> caractere ASCII a ser colocado no Display
	# Saída: none
	# Stack: not used
	# Uses:  Keyboard And Display MMIO Simulator
	# Blocking poll
	putchar:
		lw	a1, KD_Tx_Control		# laço de polling
		andi	a1, a1, 1
		beqz	a1, putchar
		
		sb	a0, KD_Tx_Data, a1		# escreve no display
	
		ret


	# Entra: a0 -> coordenada X (coluna) -> nos bits [31:20]
	#	 a1 -> coordenada Y (linha)  -> nos bits [19:8]
	poscur:
		lw	t0, KD_Tx_Control		# laço de polling
		andi	t0, t0, 1
		beqz	t0, poscur
		
		slli	a0, a0, 20			# a0 = a0<<20
		slli	a1, a1, 8			# a1 = a1<<8
		or	a0, a0, a1			# a0 = a0<<20 | a1<<8
		ori	a0, a0, 7 			# a0 = a0<<20 | a1<<8 | 7
		
		sw	a0, KD_Tx_Data, t0		# escreve no display
	
		ret
		
		
	# Trap -- modo direto
	# Atenção: usando os registradores a0 e a1
	Trap:
		nop					# Resolve o "bug" do simulador
		
		addi	sp, sp, -20			# Salva a0-a3 e ra
		sw	a0, 0(sp)
		sw	a1, 4(sp)
		sw	a2, 8(sp)
		sw	a3, 12(sp)
		sw	ra, 16(sp)
		
		csrr	a0, ucause			# Verifica a fonte da interrupção
		
		li	a1, CAUSE_TIMER
		beq	a0, a1, Trap_Timer
		
		j	Trap_Fim
		
	Trap_Timer:		
		lw	a0, seg				# seg++
		addi	a0, a0, 1
		sw	a0, seg, a3
		
		li	a1, 60				# if (seg >= 60)
		bltu	a0, a1, Trap_Timer_Fim
		li	a2, 0				# 	seg = 0
		sw	a2, seg, a3
	
		lw	a0, min				# 	min++
		addi	a0, a0, 1
		sw	a0, min, a3
		
		li	a1, 60				# 	if (min >= 60)
		bltu	a0, a1, Trap_Timer_Fim
		li	a2, 0				# 		min = 0
		sw	a2, min, a3

		lw	a0, hora			# 		hora++
		addi	a0, a0, 1
		sw	a0, hora, a3
		
		li	a1, 24				# 		if (hora >= 24)
		bltu	a0, a1, Trap_Timer_Fim
		li	a2, 0				# 			hora = 0
		sw	a2, hora, a3

	Trap_Timer_Fim:		
		jal	setTimercmp			# programa timercmp para timer + 1000
		
	Trap_Fim:
		lw	a0, 0(sp)			# Retorna a0-a3, ra
		lw	a1, 4(sp)
		lw	a2, 8(sp)
		lw	a3, 12(sp)
		lw	ra, 16(sp)
		addi	sp, sp, 20
			
		uret
		
	
	.data	
	hora:	.word	0
	min:	.word	0
	seg:	.word	0

	
		.space	0x100
	stack:

