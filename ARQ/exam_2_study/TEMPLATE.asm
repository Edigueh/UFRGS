#=============================================================================
# Índice das seções:
#   1. Constantes (.eqv)
#   2. Referência rápida (ABI, layout, alinhamento, imediatos, pseudos, M-ext)
#   3. main / demo
#   4. I/O primitivas:  getchar, putchar, poscur, cls
#   5. print_str        (imprime string terminada em 0)
#   6. print_uint       (número unsigned -> ASCII, recursivo)
#   7. format2          (dois dígitos com zero à esquerda)
#   8. read_uint        (lê número com eco + backspace)
#   9. Helpers de vetores/strings/bits: strlen, memcpy_bytes, vsum, popcount,
#                                       ctdig, split_hw
#  10. fatorial         (recursão canônica)
#  11. delay_ms         (espera ativa via timer MMIO)
#  12. install_timer_isr + Trap timer
#  13. install_kbd_isr  (interrupção de teclado)
#  14. .data + stack
#=============================================================================


#-----------------------------------------------------------------------------
# 1. CONSTANTES
#-----------------------------------------------------------------------------

# --- MMIO teclado (Rx) / display (Tx) ---
# Nomes do resumo do aluno (KD_Rx_Control/KD_Rx_Data/KD_Tx_Control/KD_Tx_Data) + aliases das aulas.
.eqv    KD_Rx_Control,  0xFFFF0000      # Keyboard Control  (KD_Rx_Control)
.eqv    KD_Rx_Data,     0xFFFF0004      # Keyboard Data     (KD_Rx_Data)
.eqv    KD_Tx_Control,  0xFFFF0008      # Display Control   (KD_Tx_Control)
.eqv    KD_Tx_Data,     0xFFFF000C      # Display Data      (KD_Tx_Data)

# --- MMIO timer (mtime, mtimecmp - 64 bits split em dois words) ---
.eqv    TIM_l,          0xFFFF0018      # mtime low
.eqv    TIM_h,          0xFFFF001C      # mtime high
.eqv    TIMCMP_l,       0xFFFF0020      # mtimecmp low
.eqv    TIMCMP_h,       0xFFFF0024      # mtimecmp high

# --- Comandos do display (byte enviado em KD_Tx_Data) ---
.eqv    CMD_CLS,        0x0C            # Limpa a tela
.eqv    CMD_POS,        0x07            # Posiciona cursor: (X<<20)|(Y<<8)|0x07

# --- Máscaras de interrupção ---
.eqv    PROG_UIE,       0x100           # uie bit 8  = UEIE (User External Interrupt Enable)
.eqv    PROG_UTIE,      0x10            # uie bit 4  = UTIE (User Timer Interrupt Enable)
.eqv    GLOBAL_IE,      1               # ustatus bit 0 = UIE (Global Interrupt Enable)
.eqv    PROG_TEC_INT,   0x2             # KD_Rx_Control bit 1 = habilita int do teclado

# --- Causas de trap (bit31=1 => interrupt) ---
.eqv    CAUSE_TIMER,    0x80000004      # interrupt=1, cause=4, User Timer Interrupt
.eqv    CAUSE_TEC,      0x80000008      # interrupt=1, cause=8, User External Interrupt
.eqv    CAUSE_ECALL,    8               # exception (interrupt=0), cause=8 (Environment call from User-mode)

# Máscaras / causas síncronas extras (para dispatcher genérico ou trap de exceção)
.eqv    INT_BIT_MASK,           0x80000000
.eqv    CAUSE_CODE_MASK,        0x7FFFFFFF
.eqv    CAUSE_INSTR_MISALIGN,   0
.eqv    CAUSE_ILLEGAL_INSTR,    2
.eqv    CAUSE_BREAKPOINT,       3
.eqv    CAUSE_LOAD_MISALIGN,    4
.eqv    CAUSE_STORE_MISALIGN,   6

# --- Códigos de ecall (a7) ---
.eqv    PRINT_INT,      1
.eqv    PRINT_STR,      4
.eqv    READ_INT,       5
.eqv    READ_STR,       8
.eqv    PRINT_CHAR,     11
.eqv    READ_CHAR,      12
.eqv    EXIT,           10
.eqv    TIME,           30
.eqv    SLEEP,          32

# --- ASCII ---
.eqv    BS,             8
.eqv    LF,             10
.eqv    CR,             13
.eqv    SPACE,          32
.eqv    DEL,            127

# --- Configuração ---
.eqv    TICK_MS,        1000            # período do timer ISR

# --- Página de dados (idioma lui gp, mempage + offsets nomeados) ---
.eqv    mempage,        0x10010         # topo dos 20 bits de 0x10010000
.eqv    first,          0
.eqv    second,         4
.eqv    res,            8

#-----------------------------------------------------------------------------
# 3. MAIN / DEMO
#-----------------------------------------------------------------------------
.text
        la      sp, stack               # inicializa stack pointer
        jal     main
        ebreak
# Demo: limpa tela, escreve "TEMPLATE OK" em (0,0). Substituir pela solução da prova.
main:
        addi    sp, sp, -4
        sw      ra, 0(sp)
        # USER CODE BEGIN
        jal     cls                     # limpa display

        li      a0, 0
        li      a1, 0
        jal     poscur                  # cursor -> (0,0)

        la      a0, hello
        jal     print_str

        # USER CODE ENDS

        # --- Descomentar para testar read_uint + print_uint: ---
        # li    a0, 0
        # li    a1, 2
        # jal   poscur
        # la    a0, prompt
        # jal   print_str
        # jal   read_uint               # lê número (eco + backspace)
        # mv    s0, a0                  # guarda valor
        # li    a0, 0
        # li    a1, 3
        # jal   poscur
        # la    a0, echoMsg
        # jal   print_str
        # mv    a0, s0
        # jal   print_uint

        # lw      ra, 0(sp)
        # addi    sp, sp, 4
        # ret


#-----------------------------------------------------------------------------
# 4. I/O PRIMITIVAS (polling bloqueante)
#-----------------------------------------------------------------------------

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


#-----------------------------------------------------------------------------
# 5. print_str: imprime string terminada em 0.
# Entra: a0 = endereço da string.
# Sai:   nada.
# Salva: ra, s0 (ponteiro atravessa chamadas a putchar).
#-----------------------------------------------------------------------------
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


#-----------------------------------------------------------------------------
# 6. print_uint: imprime número unsigned em decimal (recursivo).
# Entra: a0 = número (unsigned 32 bits).
# Sai:   nada.
# Salva: ra + resto local.
#-----------------------------------------------------------------------------
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


#-----------------------------------------------------------------------------
# 7. format2: imprime número (0..99) em 2 dígitos com zero à esquerda.
# Entra: a0 = número.
# Fonte: relo.asm.
#-----------------------------------------------------------------------------
format2:
        li      t0, 10
        divu    t1, a0, t0
        remu    t2, a0, t0
        addi    a0, t1, '0'
        addi    a1, t2, '0'

        addi    sp, sp, -8              # push 8
        sw      a1, 0(sp)
        sw      ra, 4(sp)

        jal     putchar                 # dezena

        lw      a0, 0(sp)               # unidade
        jal     putchar

        lw      ra, 4(sp)
        addi    sp, sp, 8
        ret


#-----------------------------------------------------------------------------
# 8. read_uint: lê número decimal com eco + backspace + Enter.
# Entra: nada. Sai: a0 = valor lido.
# Backspace/DEL: apaga último dígito (BS SPACE BS).
# CR ou LF encerra.
#-----------------------------------------------------------------------------
read_uint:
        addi    sp, sp, -8
        sw      ra, 0(sp)
        sw      s0, 4(sp)
        li      s0, 0                   # acumulador
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
        j       ru_loop

ru_bs:
        beqz    s0, ru_loop             # nada a apagar
        li      t0, 10
        divu    s0, s0, t0              # remove último dígito
        # eco: BS SPACE BS  (apaga glifo na tela)
        li      a0, BS
        jal     putchar
        li      a0, SPACE
        jal     putchar
        li      a0, BS
        jal     putchar
        j       ru_loop

ru_done:
        mv      a0, s0
        lw      s0, 4(sp)
        lw      ra, 0(sp)
        addi    sp, sp, 8
        ret


#-----------------------------------------------------------------------------
# 9. HELPERS: vetores, strings, bits (padrões da lista 18/19)
#-----------------------------------------------------------------------------

# --- strlen: comprimento de string terminada em 0 ---
# Entra: a0 = ptr.  Sai: a0 = comprimento.
strlen:
        mv      t0, a0                  # guarda início
sl_lp:
        lbu     t1, 0(a0)
        beqz    t1, sl_end
        addi    a0, a0, 1
        j       sl_lp
sl_end:
        sub     a0, a0, t0              # a0 = ptr_atual - inicio
        ret


# --- memcpy_bytes: copia n bytes de src p/ dst ---
# Entra: a0 = dst, a1 = src, a2 = n.  Sai: nada.
memcpy_bytes:
        beqz    a2, mc_end
mc_lp:
        lbu     t0, 0(a1)
        sb      t0, 0(a0)
        addi    a0, a0, 1
        addi    a1, a1, 1
        addi    a2, a2, -1
        bnez    a2, mc_lp
mc_end:
        ret


# --- vsum: soma n palavras (words) de um vetor ---
# Entra: a0 = ptr, a1 = n.  Sai: a0 = soma.
vsum:
        li      t0, 0                   # acumulador
        beqz    a1, vs_end
vs_lp:
        lw      t1, 0(a0)
        add     t0, t0, t1
        addi    a0, a0, 4               # próxima word
        addi    a1, a1, -1
        bnez    a1, vs_lp
vs_end:
        mv      a0, t0
        ret


# --- popcount: número de bits 1 numa palavra ---
# Entra: a0 = word.  Sai: a0 = contagem.
popcount:
        li      t0, 0                   # contador
        li      t1, 32                  # 32 bits
pc_lp:
        andi    t2, a0, 1
        add     t0, t0, t2
        srli    a0, a0, 1
        addi    t1, t1, -1
        bnez    t1, pc_lp
        mv      a0, t0
        ret


# --- ctdig: conta caracteres '0'..'9' em string terminada em 0 ---
# Entra: a0 = ptr string.  Sai: a0 = quantidade de dígitos.
# Versão A: dois branches explícitos com '0' e '9'.
ctdig:
        li      t0, 0                   # contador
        li      t3, '0'
        li      t4, '9'
cd_lp:
        lbu     t1, 0(a0)
        beqz    t1, cd_end              # fim de string
        bltu    t1, t3, cd_skip         # c < '0'
        bltu    t4, t1, cd_skip         # c > '9'  (bgtu t1,t4 == bltu t4,t1)
        addi    t0, t0, 1
cd_skip:
        addi    a0, a0, 1
        j       cd_lp
cd_end:
        mv      a0, t0
        ret

# Versão B (truque unsigned, sem branches internos) — mais compacta:
#   addi t2, t1, -'0'
#   sltiu t5, t2, 10              # 1 se 0..9, senão 0
#   add   t0, t0, t5


# --- split_hw: separa word em duas halfwords em res_lo/res_hi ---
# Entra: a0 = word.  Sai: escreve res_lo e res_hi (upper zerado).
split_hw:
        li      t0, 0xFFFF
        and     t1, a0, t0              # low16 = a0 & 0xFFFF
        srli    t2, a0, 16              # high16
        sw      t1, res_lo, t3
        sw      t2, res_hi, t3
        ret


#-----------------------------------------------------------------------------
# 10. fatorial: n! recursivo. Modelo canônico de recursão.
# Entra: a0 = n. Sai: a0 = n!.
# Salva: ra em 0(sp), parâmetro n em 4(sp).
# Fonte: EXTENSAO.asm.
#-----------------------------------------------------------------------------
.eqv    NPARAM, 8

fatorial:
        addi    sp, sp, -NPARAM
        sw      ra, 0(sp)
        sw      a0, 4(sp)               # salva n para depois do jal

        beqz    a0, fat_base            # 0! = 1

        addi    a0, a0, -1              # calcula (n-1)!
        bnez    a0, fat_rec
        li      a0, 1                   # 1! = 1 (evita chamada com n-1=0 dando 0)
        j       fat_join
fat_rec:
        jal     fatorial                # a0 = (n-1)!
fat_join:
        lw      a1, 4(sp)               # recupera n original
        mul     a0, a0, a1              # a0 = (n-1)! * n
        lw      ra, 0(sp)
        addi    sp, sp, NPARAM
        ret
fat_base:
        li      a0, 1
        lw      ra, 0(sp)
        addi    sp, sp, NPARAM
        ret


#-----------------------------------------------------------------------------
# 11. delay_ms: espera ativa (busy-wait) por N ms.
# Entra: a0 = ms.
# Sai:   nada.
# Fonte: relo.asm (startTimer + difTimer adaptados).
# Alternativa via ecall (se permitido): mv a0, a0; li a7, SLEEP; ecall.
#-----------------------------------------------------------------------------
delay_ms:
        mv      t6, a0                  # t6 = ms a esperar
        # snapshot inicial: leitura atômica (retry se TIM_h mudar)
dm_init:
        lw      a1, TIM_h
        lw      a0, TIM_l
        lw      t0, TIM_h
        bne     t0, a1, dm_init
        mv      t4, a0                  # t4 = ref low
        mv      t5, a1                  # t5 = ref high
dm_wait:
        # relê timer atomicamente
        lw      a1, TIM_h
        lw      a0, TIM_l
        lw      t0, TIM_h
        bne     t0, a1, dm_wait
        # diff = timer - ref (64 bits, com borrow)
        sub     t1, a0, t4              # diff low
        sltu    t2, a0, t1              # borrow?
        sub     t3, a1, t5
        sub     t3, t3, t2              # diff high
        # se diff_high != 0 => já passou muito tempo, sai
        bnez    t3, dm_done
        # senão compara diff_low com t6
        bltu    t1, t6, dm_wait
dm_done:
        ret


#-----------------------------------------------------------------------------
# 12. install_timer_isr: programa interrupção de timer periódica.
# Sai:   nada. Após esta chamada, Trap será invocado a cada TICK_MS ms.
# Handler incrementa seg/min/hora (rollover 60/60/24).
#-----------------------------------------------------------------------------
install_timer_isr:
        addi    sp, sp, -4
        sw      ra, 0(sp)

        la      t0, Trap
        csrw    t0, utvec               # trap vector (modo direto: bits[1:0]=00)

        li      t0, PROG_UTIE
        csrs    t0, uie                 # habilita interrupt de timer (UTIE)

        jal     setTimercmp             # programa próximo tick

        csrsi   ustatus, GLOBAL_IE      # habilita global (UIE)

        lw      ra, 0(sp)
        addi    sp, sp, 4
        ret

# setTimercmp: programa mtimecmp = mtime + TICK_MS.
# Trata carry do somador de 64 bits.
setTimercmp:
        li      a3, TICK_MS
stc_read:
        lw      a1, TIM_h
        lw      a0, TIM_l
        lw      a2, TIM_h
        bne     a2, a1, stc_read
        add     a2, a0, a3              # low + TICK_MS
        sltu    a0, a2, a0              # carry?
        add     a1, a1, a0              # aplica carry em high
        sw      a1, TIMCMP_h, a3        # escreve high primeiro (mais seguro)
        sw      a2, TIMCMP_l, a3
        ret


#-----------------------------------------------------------------------------
# 13. install_kbd_isr: programa interrupção de teclado.
# Handler lê tecla e guarda em Tecla (-1 quando não há tecla).
# Main polls: lw t0, Tecla; bltz t0, wait; ... ; sw -1, Tecla.
#-----------------------------------------------------------------------------
install_kbd_isr:
        la      t0, Trap
        csrw    t0, utvec

        li      t0, PROG_UIE            # habilita externa (UEIE bit 8)
        csrs    t0, uie

        li      t0, PROG_TEC_INT        # habilita gerador de int no teclado
        sw      t0, KD_Rx_Control, t1

        li      t0, -1                  # Tecla = -1 (vazio)
        sw      t0, Tecla, t1

        csrsi   ustatus, GLOBAL_IE      # habilita global
        ret


#-----------------------------------------------------------------------------
# Trap: handler único (modo direto). Distingue causa via ucause.
# ucause bit 31 = 1 => interrupt; = 0 => exceção.
# ATENÇÃO: primeiro instrução tem que ser nop (bug do simulador RARS).
#-----------------------------------------------------------------------------
Trap:
        nop                             # workaround RARS

        addi    sp, sp, -20             # salva a0-a3 + ra
        sw      a0, 0(sp)
        sw      a1, 4(sp)
        sw      a2, 8(sp)
        sw      a3, 12(sp)
        sw      ra, 16(sp)

        csrr    a0, ucause

        li      a1, CAUSE_TIMER
        beq     a0, a1, Trap_Timer

        li      a1, CAUSE_TEC
        beq     a0, a1, Trap_Tec

        j       Trap_Fim                # causa desconhecida: apenas retorna

# --- Interrupção de teclado ---
Trap_Tec:
        lbu     a0, KD_Rx_Data                # lê tecla (reseta Ready)
        sw      a0, Tecla, a1
        j       Trap_Fim

# --- Interrupção de timer: incrementa seg/min/hora ---
Trap_Timer:
        lw      a0, seg
        addi    a0, a0, 1
        sw      a0, seg, a3
        li      a1, 60
        bltu    a0, a1, Trap_Timer_End
        sw      zero, seg, a3

        lw      a0, min
        addi    a0, a0, 1
        sw      a0, min, a3
        li      a1, 60
        bltu    a0, a1, Trap_Timer_End
        sw      zero, min, a3

        lw      a0, hora
        addi    a0, a0, 1
        sw      a0, hora, a3
        li      a1, 24
        bltu    a0, a1, Trap_Timer_End
        sw      zero, hora, a3

Trap_Timer_End:
        jal     setTimercmp             # reprograma próximo tick

Trap_Fim:
        lw      a0, 0(sp)
        lw      a1, 4(sp)
        lw      a2, 8(sp)
        lw      a3, 12(sp)
        lw      ra, 16(sp)
        addi    sp, sp, 20
        uret


#=============================================================================
# 14. .data - variáveis, strings, stack
# Ordem: words primeiro (auto-alinhadas em 4), depois bytes/strings no fim.
# .data começa em 0x10010000 (múltiplo de 4), então .word e .space múltiplos
# de 4 mantêm alinhamento sem precisar de diretivas.
#=============================================================================
.data

# --- Variáveis compartilhadas com o handler ---
Tecla:          .word   -1              # -1 = nenhuma tecla; >=0 = ASCII pendente
seg:            .word   0
min:            .word   0
hora:           .word   0

# --- Referências para delay_ms se quiser guardar em .data em vez de reg ---
refTimerLow:    .word   0
refTimerHigh:   .word   0

# --- Página de dados (idioma lui gp, mempage) ---
# Alinhamento: 0=first, 4=second, 8=res. Ver ".eqv mempage/first/second/res" no topo.
# Nomes dos labels diferem dos .eqv para evitar conflito de símbolo.
mp_first:       .word   0
mp_second:      .word   0
mp_res:         .word   0

# --- Halfword split ---
res_lo:         .word   0
res_hi:         .word   0

# --- Exemplo de diretivas de dados (referência) ---
demo_word:      .word   0xDEADBEEF
demo_space:     .space  16              # 16 bytes (múltiplo de 4)

# --- Stack (topo em 'stack:', cresce para endereços menores) ---
# Colocado antes das strings/bytes: como .space é múltiplo de 4, stack: fica word-aligned.
                .space  0x200
stack:

# --- Strings (por último: bytes podem desalinhar o que vem depois) ---
hello:          .string  "TEMPLATE OK"
prompt:         .string  "N = "
echoMsg:        .string  "Lido: "
nl:             .string  "\n"
