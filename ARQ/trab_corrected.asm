# André Schaidhauer Luckmann, 601117
.eqv    KD_Rx_Control,  0xFFFF0000      # Keyboard Control  (KD_Rx_Control)
.eqv    KD_Rx_Data,     0xFFFF0004      # Keyboard Data     (KD_Rx_Data)
.eqv    KD_Tx_Control,  0xFFFF0008      # Display Control   (KD_Tx_Control)
.eqv    KD_Tx_Data,     0xFFFF000C      # Display Data      (KD_Tx_Data)

.eqv    TIM_l,          0xFFFF0018      # mtime low
.eqv    TIM_h,          0xFFFF001C      # mtime high

.eqv    CMD_CLS,        0x0C            # Limpa a tela
.eqv    CMD_POS,        0x07            # Posiciona cursor: (X<<20)|(Y<<8)|0x07

.eqv    BS,             8
.eqv    LF,             10
.eqv    CR,             13
.eqv    SPACE,          32
.eqv    DEL,            127

.text
        la      sp, stack               # inicializa stack pointer
        jal     main
        ebreak
main:
        addi    sp, sp, -4
        sw      ra, 0(sp)
        jal     cls                     # limpa display

        li      a0, 0
        li      a1, 0
        jal     poscur                  # cursor -> (0,0)

        la    a0, n1_msg
        jal   print_str
        li    a1, 28
        li    a2, 0
        jal   read_uint               # lê número 1
        sw    a0, n1, t0              # guarda valor 1 em n1
        li    a0, 0               
        li    a1, 1
        jal   poscur
        la    a0, n2_msg
        jal   print_str
        li    a1, 27
        li    a2, 1
        jal   read_uint                   # lê número 2
        sw    a0, n2, t0                  # guarda valor 2 em n2
        li a0, 0
        li a1, 2
        jal poscur
        lw a0, n1
        lw a1, n2
        jal euclides

        lw      ra, 0(sp)
        addi    sp, sp, 4
        ret

# getchar: lê 1 caractere do teclado.
# Entra: nada.
# Sai:   a0 = ASCII lido (zero-estendido).
# Usa:   a0. Não usa stack.
getchar:
        lw      a0, KD_Rx_Control                # laço de polling
        andi    a0, a0, 1               # bit 0 = Ready
        beqz    a0, getchar
        lbu     a0, KD_Rx_Data                # lê tecla, reseta Ready
        ret

# putchar: envia 1 caractere para o display.
# Entra: a0 = ASCII / byte de comando.
# Sai:   nada.
# Usa:   a1 como temp. Não usa stack.
putchar:
        lw      a1, KD_Tx_Control                # polling
        andi    a1, a1, 1
        beqz    a1, putchar
        sb      a0, KD_Tx_Data, a1            # escreve no display
        ret

# poscur: move cursor para (col, lin).
# Entra: a0 = coluna X (0..94), a1 = linha Y (0..9).
# Sai:   nada.
# Usa:   a0, a1, t0.
poscur:
        lw      t0, KD_Tx_Control                # polling
        andi    t0, t0, 1
        beqz    t0, poscur
        slli    a0, a0, 20              # X nos bits [31:20]
        slli    a1, a1, 8               # Y nos bits [19:8]
        or      a0, a0, a1
        ori     a0, a0, CMD_POS         # comando 0x07 nos bits [7:0]
        sw      a0, KD_Tx_Data, t0
        ret

# cls: limpa tela e leva cursor a (0,0).
# Sai:   nada. Usa a0/a1/t0/ra.
cls:
        addi    sp, sp, -4
        sw      ra, 0(sp)
        li      a0, CMD_CLS
        jal     putchar
        li      a0, 0
        li      a1, 0
        jal     poscur
        lw      ra, 0(sp)
        addi    sp, sp, 4
        ret


# print_str: imprime string terminada em 0.
# Entra: a0 = endereço da string.
# Sai:   nada.
# Salva: ra, s0 (ponteiro atravessa chamadas a putchar).
print_str:
        addi    sp, sp, -8
        sw      ra, 0(sp)
        sw      s0, 4(sp)
        mv      s0, a0                  # s0 = ptr
ps_loop:
        lbu     a0, 0(s0)
        beqz    a0, ps_end              # 0 termina
        jal     putchar
        addi    s0, s0, 1
        j       ps_loop
ps_end:
        lw      s0, 4(sp)
        lw      ra, 0(sp)
        addi    sp, sp, 8
        ret


# print_uint: imprime número unsigned em decimal (recursivo).
# Entra: a0 = número (unsigned 32 bits).
# Sai:   nada.
# Salva: ra + resto local.
print_uint:
        addi    sp, sp, -8
        sw      ra, 0(sp)               # ra
        # 4(sp) = resto (dígito atual)

        li      t0, 10
        remu    t1, a0, t0              # t1 = a0 % 10
        divu    a0, a0, t0              # a0 = a0 / 10
        sw      t1, 4(sp)               # salva o dígito na pilha

        beqz    a0, pu_leaf             # se quociente == 0, não recurse
        jal     print_uint              # imprime prefixo (dígitos mais altos)
pu_leaf:
        lw      a0, 4(sp)               # recupera dígito
        addi    a0, a0, '0'
        jal     putchar

        lw      ra, 0(sp)
        addi    sp, sp, 8
        ret


# printFmt: imprime dois numeros na forma (n1,n2).
# Entra: a0 = n1; a1 = n2.
printFmt:
        addi sp, sp, -4
        sw ra, 0(sp)
        li a0, '('
        jal putchar
        lw a0, n1
        jal print_uint
        li a0, ','
        jal putchar
        lw a0, n2
        jal print_uint
        li a0, ')'
        jal putchar
        lw ra, 0(sp)
        addi sp, sp, 4
        ret


# read_uint: lê número decimal com eco + backspace + Enter.
# Entra: nada. Sai: a0 = valor lido.
# Backspace/DEL: apaga último dígito (BS SPACE BS).
# CR ou LF encerra.
read_uint:
        addi    sp, sp, -16
        sw      ra, 0(sp)
        sw      s0, 4(sp)
        sw	s1, 8(sp)
        sw	s2, 12(sp)
        li      s0, 0                   # acumulador
	mv	s1, a1
	mv 	s2, a2
ru_loop:
        jal     getchar                 # a0 = tecla
        mv      t3, a0

        # CR ou LF => fim
        li      t0, CR
        beq     t3, t0, ru_done
        li      t0, LF
        beq     t3, t0, ru_done

        # BS ou DEL => apaga
        li      t0, BS
        beq     t3, t0, ru_bs
        li      t0, DEL
        beq     t3, t0, ru_bs

        # dígito '0'..'9' ?
        li      t0, '0'
        bltu    t3, t0, ru_loop         # < '0' => ignora
        li      t0, 58                  # '9' + 1
        bgeu    t3, t0, ru_loop         # > '9' => ignora

        # acumula: s0 = s0*10 + (t3 - '0')
        li      t0, 10
        mul     s0, s0, t0
        addi    t3, t3, -48             # -'0'
        add     s0, s0, t3

        # eco do dígito
        addi    t3, t3, '0'
        mv      a0, t3
        jal     putchar
        addi 	s1, s1, 1
        j       ru_loop

ru_bs:
        beqz    s0, ru_loop             # nada a apagar
        li      t0, 10
        divu    s0, s0, t0              # remove último dígito
        addi	s1, s1, -1
        mv	a0, s1
        mv 	a1, s2
        jal	poscur
        li	a0, SPACE
        jal     putchar
	mv	a0, s1
	mv	a1, s2
	jal 	poscur
	j	ru_loop
ru_done:
        mv      a0, s0
        lw	s2, 12(sp)
        lw	s1, 8(sp)
        lw      s0, 4(sp)
        lw      ra, 0(sp)
        addi    sp, sp, 16
        ret

# Euclides.
# Entra a0 = n1; a2 = n2;
# Saída: Retorna o MDC em a0.
.eqv    NPARAM, 12 # n1, n2, ra.
euclides:
        addi    sp, sp, -NPARAM
        sw      ra, 0(sp)
        sw      a0, 4(sp)               # salva n1 para depois do jal
        sw      a1, 8(sp)               # salva n2 para depois do jal
        
        li      a2, 1000
        jal delay_ms
        
        lw  a0, 4(sp)
        lw  a1, 8(sp)
        jal printFmt
	
	lw a0, 4(sp)
	lw a1, 8(sp)
        beqz    a1, final              # b = 0
        remu	t5, a0, a1		# t5 = n1 % n2
        mv a0, a1 # mdc(a=b)
        sw a0, n1, t0
        mv a1, t5 # mdc(b=n1%n2)
        sw a1, n2, t0
        jal     euclides
final:
        lw      ra, 0(sp)
        addi    sp, sp, NPARAM
        ret


# delay_ms: espera ativa (busy-wait) por N ms.
# Entra: a2 = ms.
delay_ms:
        mv      t6, a2                  # t6 = ms a esperar
dm_init:
        lw      t5, TIM_h
        lw      t4, TIM_l
        lw      t0, TIM_h
        bne     t0, t5, dm_init
dm_wait:
        # relê timer atomicamente
        lw      a3, TIM_h
        lw      a2, TIM_l
        lw      t0, TIM_h
        bne     t0, a3, dm_wait
        # diff = timer - ref (64 bits, com borrow)
        sub     t1, a2, t4              # diff low
        sltu    t2, a2, t4              # borrow?
        sub     t3, a3, t5
        sub     t3, t3, t2              # diff high
        # se diff_high != 0 => já passou muito tempo, sai
        bnez    t3, dm_done
        # senão compara diff_low com t6
        bltu    t1, t6, dm_wait
dm_done:
        ret


.data

n1:             .word   0
n2:             .word   0

                .space  0x200
stack:

# --- Strings (por último: bytes podem desalinhar o que vem depois) ---
n1_msg:         .string  "Fornecer o primeiro numero: "
n2_msg:         .string  "Fornecer o segundo numero: "
