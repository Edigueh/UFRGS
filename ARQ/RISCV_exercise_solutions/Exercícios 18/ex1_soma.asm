
#
#	Escrever um programa para o RISC-V (RV32IM) capaz de somar duas palavras de 32 bits (word) da memória e colocar o resultado em uma terceira word.
#	Parâmetros
#		first: Primeira palavra
#		second: Segunda palavra
#		res: Resultado
#
#	A área de dados terá tamanho de 2048 bytes
#	Assim, a parte mais significativa do endereço desta área será, sempre, o mesmo
#	0x10010000 -> Valor definido pelo ambiente
#

	.eqv	mempage, 0x10010


	.eqv	first, 0
	.eqv	second, 4
	.eqv	res, 8

		
.text
	# Inicializa gp com o endereço da página
	lui	gp,mempage
		
	# t0 = Mem(first)
	lw	t0, first(gp)
	
	# t1 = Mem(second)
	lw	t1, second(gp)
	
	# t0 = t0 + t1
	add	t0, t0, t1
	
	# Mem(res) = t0
	sw	t0, res(gp)
	
			
	ebreak
	

.data
	
_first:		.word	0x11112222
_second:	.word	0x33336666
_res:		.word	0



	
	
