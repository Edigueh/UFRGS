

		
.text

	lw	t1, largura	# largura x altura
	lw	t2, altura
	mul	t1, t1, t2
	
	lw	t2, demao	# (largura x altura) x demao
	mul	t1, t1, t2
	
	lw	t2, rend	# ((largura x altura) x demao) / rend
	div	t1, t1, t2

	lw	t2, tinta	# (((largura x altura) x demao) / rend) / tinta
	div	t1, t1, t2
	
	sw	t1, latas, t2
	
	ebreak
	
.data
largura:	.word	10
altura:		.word	15
tinta:		.word	4
rend:		.word	15
demao:		.word	2
latas:		.word	0


