
#
#	Escrver um programa para o RISC-V (RV32IM) capaz de separar uma word (palavra de 32 bits) em duas halfwords
#	Cada halfword deverá ser escrita na halfword menos significativa de uma variáveis word diferente
#		start: word de origem
#		lower: half menos significativa
#		higher: half mais significativa
#
#	A área de dados terá tamanho de 2048 bytes
#	Assim, a parte mais significativa do endereço desta área será, sempre, o mesmo
#	0x10010000 -> Valor definido pelo ambiente
#


	.eqv	mempage, 0x10010


	.eqv	start, 0
	.eqv	lower, 4
	.eqv	higher, 8

		
.text
	# Inicializa gp com o endereço da página
	lui	gp,mempage
		
	# Mem(lower) = Mem(start) & 0xFFFF
	lui	t1, 0xFFFF0		# t1 = 0x0000FFFF
	srli	t1, t1, 16
	lw	t0, start(gp)		# t0 = start & 0x0000FFFF
	and	t0, t0, t1		
	sw	t0, lower(gp)
	
	# Mem(higher) = Mem(start) >> 16
	lw	t0, start(gp)
	srli	t1, t0, 16		# t1 = start >> 16
	sw	t1, higher(gp)
		
			
	ebreak
	

.data
	
	.word	0x11112222
	.word	0x33336666
	.word	0x55557777



	
	
