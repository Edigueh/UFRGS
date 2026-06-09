
#
#	Escrever um programa para o RISC-V (RV32IM) capaz de contar o números de caracteres de um string do tipo C
#		len: endereço onde escrever o tamanho do string
#		str: endereço de inicio do string (terminado com \0)
#
#	A área de dados terá tamanho de 2048 bytes
#	Assim, a parte mais significativa do endereço desta área será, sempre, o mesmo
#	0x10010000 -> Valor definido pelo ambiente
#


	.eqv	mempage, 0x10010


	.eqv	len, 0
	.eqv	str, 4

		
.text
	# Inicializa gp com o endereço da página
	lui	gp, mempage
		
	# t0 -> indice para o string
	addi	t0, gp, str		# t0 = &(str)
	add	t2, zero, zero		# k = 0
	
loop:
	lb	t1, 0(t0)		# t1 = (*t0 & 0xFF)
	andi	t1, t1, 0x7F
	beq	t1, zero, final		# if (t1==0) final
	
	addi	t0, t0, 1		# else: { t0++
	addi	t2, t2, 1		#	t2++
	beq	t0, t0, loop		#	goto loop }
	
final:
	sw	t2,len(gp)		# mem(len) = k
	
			
	ebreak
	

.data
	
_len:	.word	0
_str:	.string	"INF01075"		# String terminado com "\0"






	
	
