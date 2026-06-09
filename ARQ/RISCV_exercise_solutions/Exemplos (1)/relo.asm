		
	.text

		la	sp, stack	# inicializa o stack pointer
		
		# inicializa relogio
		li	t0, 0
		sw	t0, hora, t1	# Inicializa relogio de apresentação
		sw	t0, min, t1
		sw	t0, seg, t1
		
		jal	startTimer	# Inicializa a informação de tempo
		
	loop:	
		# (1) apresenta relogio no display
		li	a0, 0		# coordenada X
		li	a1, 0		# coordenada Y
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
		
		# (2) verifica se passou 1 segundo
		# senão, vai para (2)
		# se passou, incrementa relogio e vai para (1)
		
		jal	difTimer		# if (timer - refTimer < 1000) goto loop
		li	t0, 1000
		bltu	a0, t0, loop
		jal	startTimer		# restart timer
		
		lw	t0, seg			# seg++
		addi	t0, t0, 1
		sw	t0, seg, t3
		
		li	t1, 60			# if (seg < 60) goto loop
		bltu	t0, t1, loop
		li	t2, 0			# seg = 0
		sw	t2, seg, t3
	
		lw	t0, min			# min++
		addi	t0, t0, 1
		sw	t0, min, t3
		
		li	t1, 60			# if (min < 60) goto loop
		bltu	t0, t1, loop
		li	t2, 0			# min = 0
		sw	t2, min, t3

		lw	t0, hora		# hora++
		addi	t0, t0, 1
		sw	t0, hora, t3
		
		li	t1, 24			# if (hora < 24) goto loop
		bltu	t0, t1, loop
		li	t2, 0			# hora = 0
		sw	t2, hora, t3
		
		b	loop

	fim:		
		ebreak
		
		
	# coloca dois digitos no display
	# entra: a0 -> numero	
	format2:
		# dezenas = a0 /10
		# unidades = a0 %10
		
		li	t0, 10
		divu	t1, a0, t0
		remu	t2, a0, t0
		
		addi	a0, t1, '0'
		addi	a1, t2, '0'
		
		addi	sp, sp, -8	# push 8
		sw	a1,0(sp)
		sw	ra,4(sp)
		
		jal	putchar
		
		lw	a0,0(sp)	# get a1 -> a0
		jal	putchar
		
		lw	ra,4(sp)	# get ra
		addi	sp, sp, 8	# pop 8
		
		ret
	
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
		
		sb	a0, KD_Tx_Data, a1	# escreve no display
	
		ret
		
	# Entra: a0 -> coordenada X (coluna) -> nos bits [31:20]
	#	 a1 -> coordenada Y (linha)  -> nos bits [19:8]
	poscur:
		lw	t0, KD_Tx_Control	# laço de polling
		andi	t0, t0, 1
		beqz	t0, poscur
		
		slli	a0, a0, 20		# a0 = a0<<20
		slli	a1, a1, 8		# a1 = a1<<8
		or	a0, a0, a1		# a0 = a0<<20 | a1<<8
		ori	a0, a0, 7 		# a0 = a0<<20 | a1<<8 | 7
		
		sw	a0, KD_Tx_Data, t0	# escreve no display
	
		ret
			
	# seta refTimer com o valor atual do timer	
	.eqv	TIM_h, 0xffff001C
	.eqv	TIM_l, 0xffff0018
	startTimer:
		lw	a1, TIM_h
		lw	a0, TIM_l
		lw	t0, TIM_h
		bne	t0, a1, startTimer
		
		sw	a0, refTimerLow, t0
		sw	a1, refTimerHigh, t0
		ret

	# calcula a diferença entre timer e refTimer
	# Saida: a0 -> dif
	difTimer:
		lw	a1, TIM_h		# read timer
		lw	a0, TIM_l
		lw	t0, TIM_h
		bne	t0, a1, difTimer
		
		lw	a2, refTimerLow		# pega refTimer
		lw	a3, refTimerHigh
		
		sub	t0, a0, a2		# Dif lower
		sltu	t1, a0, t0		# Se a parte lower resultante for maior do que a original, então houve um borrow
		sub	a1, a1, a3		# Dif upper
		sub	a1, a1, t1		# Dif borrow
		mv	a0, t0
		# return lower(Timer - refTimer)
		
		ret
		
		
			
	.data
	hora:	.word	0
	min:	.word	0
	seg:	.word	0
	
	refTimerLow:	.word	0
	refTimerHigh:	.word	0
	
		.space	0x100
	stack:

