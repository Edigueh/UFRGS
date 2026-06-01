.eqv	mempage, 0x10010
.eqv	first, 0
.eqv	second, 4
.eqv	res, 8

.text

lui	gp, mempage	# Inicializa gp com o endereço da página.
lw	t0, first(gp)	# t0 = Mem(first)
lw	t1, second(gp)	# t1 = Mem(second)
add	t0, t0, t1	# t0 = t0 + t1
sw	t0, res(gp)	# Mem(res) = t0

ebreak
