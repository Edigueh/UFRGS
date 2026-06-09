#
#	Escrever um programa para o RISC-V (RV32I) que seja capaz de mover o conteúdo de uma área de memória de origem para uma área destino.
#	As áreas não se sobrepoem e estão localizadas no segmento de dados
#	São fornecidos como entrada para o programa as variáveis que indicam os endereços das áreas:
#		O endereço de início da área origem está armazenado em "src" (em 0x1001 0000);
#		O endereço de início da área destino está armazenado em “dst” (em 0x1001 0004);
#		O tamanho a ser movido, em bytes, está armazenado em “len” (em 0x1001 0008).

.text

	lw	a0, src
	lw	a1, dst
	lw	a2, len
	
loop:
	beqz	a2, fim
	
	lb	t1,(a0)
	sb	t1,(a1)
	
	addi	a0, a0, 1
	addi	a1, a1, 1
	addi	a2, a2, -1
	
	b	loop

fim:
	
	ebreak
	
.data
src:	.word	area
dst:	.word	area_dst
len:	.word	10

area:	.string "Hello Word"
	.space	16
area_dst:

	
	
