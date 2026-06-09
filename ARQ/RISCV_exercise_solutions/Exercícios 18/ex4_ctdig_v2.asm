
#
#	Escrever um programa para o RISC-V (RV32IM) capaz de contar o números de dígitos (valores entre '0' e '9') de um string do tipo C
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
	addi	a2, zero, '0'		# '0' -> a2
	addi	a3, zero, '9'		# '9' -> a3
	
loop:
	lb	t1, 0(t0)		# t1 = (*t0 & 0xFF)
	andi	t1, t1, 0x7F
	beq	t1, zero, final		# if (t1==0) final
					# else {
	addi	t0, t0, 1		#	t0++
	
	# if t1>='0' && t1<='9' then conta; else não conta
	bltu	t1, a2, naoConta	# if(t1<'0') nao conta
	bltu	a3, t1, naoConta	# if('9'<t1) nao conta
	addi	t2, t2, 1		#	t2++
		
naoConta:
	beq	t0, t0, loop		#	goto loop
					# }
						
final:
	sw	t2,len(gp)		# mem(len) = k
	
			
	ebreak
	

.data
	
_len:	.word	0
_str:	.string	"INF01075"		# String terminado com "\0"






	
	
