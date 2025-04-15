;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname lab2-template-2025-1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
;; ===============================================================
;;                   DEFINIÇÕES DE DADOS
;; ===============================================================

;; Definição de constantes:

;; Constantes para as cartas especiais:
(define PULA_VEZ "Ø")
(define COMPRA2 "+2")
(define INVERTE "«")
(define CURINGA_COMPRA4 "+4" )
(define CURINGA "")

;; Constantes do tipo Imagem:
(define CIRCULO_BRANCO (circle 40 "solid""white"))
(define QUADRADOS_COLORIDOS
  (above
   (beside (rectangle 50 75 "solid" "red")
           (rectangle 50 75 "solid" "green"))
   (beside (rectangle 50 75 "solid" "yellow")
           (rectangle 50 75 "solid" "blue"))))
(define CONTORNO_PRETO (rectangle 110 160 "outline" "black"))


;; =============================================================================
;;  FUNÇÕES DEFINIDAS NO LABORATÓRIO 1 (revisadas para a nova definição de carta):
;; =============================================================================

;; ==> DESENHA-CARTA
;; desenha-carta : CartaUNO -> Imagem
;; Objetivo: Dada uma carta de UNO,
;; gera uma imagem para esta carta,
;; Exemplos:
;; (desenha-carta AZUL3)  desenha a carta número 3 azul
;; (desenha-carta CURINGA_COMPRA4)    desenha a carta curinga compra 4
(define (desenha-carta *carta)
  (overlay ;; sobrepor
   (escolhe-simbolo *carta)  ;; o desenho do símbolo da carta
   (escolhe-fundo *carta)))  ;; com o fundo da carta

;; ==> ESCOLHE-SIMBOLO:
; escolhe-simbolo: CartaUNO -> Imagem
;; Dada uma carta UNO, devolve uma imagem que representa este número/simbolo na carta.
;; Exemplos/testes:
;(check-expect (escolhe-simbolo (make-carta 8) (text (number->string 8) 70 "black"))
;(check-expect (escolhe-simbolo COMPRA2) (text "+2" 60 "black"))
(define (escolhe-simbolo *carta)
  (cond
    ;; se a carta for uma carta curinga, devolve a imagem correspondente
    [(curinga? *carta) (text  *carta 60 "black")]
    ;; se a carta for especial, devolve a imagem corespondente:
    [(string? (carta-valor *carta))(text  (carta-valor *carta) 60 "black")]
    ;; se a carta for numérica,     desenha a carta numérica
    [(and (>= (carta-valor *carta)  0) (<= (carta-valor *carta) 9))
     (text (number->string (carta-valor *carta)) 70 "black")]))

;; ========================
;; ESCOLHE-FUNDO
;; ========================
;; escolhe-fundo: CartaUNO -> Imagem
;; Dada uma carta,
;; gera a imagem de fundo para uma carta de UNO desta cor.
;; Exemplos:
;; (escolhe-fundo VERMELHO5)  desenha o fundo de uma carta vermelha
;; (escolhe-fundo CURINGA)     desenha o fundo de uma carta curinga
(define (escolhe-fundo *carta);; Dada uma carta *carta
  (overlay  ;; sobrepõe
   CIRCULO_BRANCO ;; circulo branco
   (cond
     ;; se carta for um curinga, desenhar os quadrados coloridos no fundo
     [(curinga? *carta) QUADRADOS_COLORIDOS]
     ;; senão, desenhar um retângulo da cor da carta
     [else (rectangle 100 150 "solid" (traduz-cor (carta-cor *carta)))])
   CONTORNO_PRETO));; contorno preto


;; ==> TRADUZ-COR
;; traduz-cor : String -> String
;; Objetivo: a função recebe uma cor de carta UNO, e retorna a respectiva cor
;; em ingles, ou seja, "blue", "green", "yellow", "red".
;; Exemplos/testes:
(check-expect (traduz-cor "azul") "blue")
(check-expect (traduz-cor "verde") "green")

(define (traduz-cor uma-cor) ;; Dada uma cor uma-cor
  (cond
    ;; se uma-cor for "azul, devolver "blue"
    [(string=? "azul" uma-cor) "blue"]
    ;; se C for "verdel, devolver "green"
    [(string=? "verde" uma-cor) "green"]
    ;; se C for "vermelho, devolver "red"
    [(string=? "vermelho" uma-cor) "red"]
    ;; se C for "amarelol, devolver "yellow"
    [(string=? "amarelo" uma-cor) "yellow"]))





;; ==============================================================
;; 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
;; ==============================================================
;; ------------------------------------
;; TIPO NÚMEROouSTRING:
;; ------------------------------------
;;  Um elemento do tipo NúmeroOUString é
;; 1. Um Número, ou
;; 2. Uma String

;; -----------------
;; TIPO CARTA:
;; -----------------
(define-struct carta (valor cor))
;; Um elemento do conjunto Carta é
;;   AZUL3     onde
;;   NúmeroOUString: valor, é o valor da carta, que pode ser qualquer inteiro entre 0 e 9,
;;                   ou as strings "pula vez", "compra 2", ou "inverte"
;;   String: cor, é a cor da carta, que pode ser "azul", "verde", "amarelo" ou "vermelho"

;; --------------------------
;; TIPO CARTAUNO:
;; --------------------------
;;  Um elemento do tipo CartaUNO é
;; 1. Uma Carta ou
;; 2. Uma String


;; Constantes do tipo Carta (ou CartaUNO, ja que o tipo Carta é um subconjunto de CartaUNO):
(define AZUL3 (make-carta 3 "azul"))
(define AZUL1 (make-carta 1 "azul"))
(define VERMELHO5 (make-carta 5 "vermelho"))
(define VERMELHO1 (make-carta 1 "vermelho"))
(define AMARELO1 (make-carta 1 "amarelo"))
(define VERDE3 (make-carta 3 "verde"))

(define AZUL-INVERTE (make-carta  INVERTE "azul"))
(define VERMELHO-COMPRA2 (make-carta COMPRA2 "vermelho"))
(define VERDE-COMPRA2 (make-carta COMPRA2 "verde"))
(define AMARELO-PULA_VEZ (make-carta PULA_VEZ "amarelo"))

;; ==============================================================
;; 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
;; ==============================================================

;; curinga? : CartaUNO -> Booleano
;; Dada uma carta UNO, diz se ela é um curinga.
;; Exemplos:
;; (curinga? VERDE3) = #f
;; (curinga? CURINGA) = #t

(define (curinga? carta) ;; a carta carta é um curinga se
  ;; a carta for uma string E
  (and (string? carta)
       ;; a string é CURINGA ou CURINGA_COMPRA4
       (or (string=? carta CURINGA)
           (string=? carta CURINGA_COMPRA4))))
;; Testes:
(check-expect (curinga? VERDE3)  #f)
(check-expect (curinga? CURINGA)  #t)

;; ==============================================================
;; 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
;; ==============================================================

;; mesmo-número-ou-símbolo: Carta Carta  -> Booleano
;; Objetivo: Dadas duas cartas, diz se elas têm o mesmo número ou símbolo,
;;  devolvendo o valor-verdade correspondente. A cor não é considerada.
;; Exemplos/testes:
(check-expect (mesmo-número-ou-símbolo VERDE3 AZUL3)  #t)
(check-expect (mesmo-número-ou-símbolo  VERDE-COMPRA2 VERDE3)  #f)
(check-expect (mesmo-número-ou-símbolo  VERDE-COMPRA2 VERMELHO-COMPRA2) #t)

(define (mesmo-número-ou-símbolo @carta1 @carta2); Dadas duas cartas @carta1 e @carta2
  (or
   ;; se a @carta1 e @carta2 forem cartas numéricas com mesmo número, devolver verdadeiro
   (and (number? (carta-valor @carta1)) (number? (carta-valor @carta2))
        (= (carta-valor @carta1) (carta-valor @carta2)))
   ;; se @carta1 e @carta2 forem especiais e iguais, devolver true
   (and (string? (carta-valor @carta1)) (string? (carta-valor @carta2))
        (string=? (carta-valor @carta1) (carta-valor @carta2)))))

;; Obs: Como esta função devolve um valor booleano, pode ser construída sem uma estrutura condicional
;; (como a questão anterior).


;; ==============================================================
;; 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4
;; ==============================================================


;; compara-cartas : CartaUNO CartaUNO -> Booleano
;; Objetivo: Dadas duas cartas UNO, diz se elas têm o mesmo número ou símbolo,
;;  devolvendo o valor-verdade correspondente. Cartas curinga devem ser consideradas
;; como qualquer tipo/símbolo (ou seja, se alguma das cartas for curinga,
;;  a função deve retornar verdadeiro). A cor não é considerada.
;; Exemplos:
(check-expect (compara-cartas  AZUL3 VERDE3)   #t)
(check-expect (compara-cartas  AZUL3 VERMELHO5) #f)
(check-expect (compara-cartas  VERMELHO5 VERMELHO-COMPRA2) #f)
(check-expect (compara-cartas  VERMELHO-COMPRA2 CURINGA)   #t)

(define (compara-cartas @carta1 @carta2)
  ; Duas cartas @carta1 e @carta2 são consideradas iguais se
  (or
   ;; OU @carta1 ou @carta2 forem curingas
   (or (curinga? @carta1) (curinga? @carta2))
   ;; OU @carta1 e @carta2 tiverem mesmo número ou símbolo
   (mesmo-número-ou-símbolo @carta1 @carta2)))


;; Testes:
(check-expect (compara-cartas AZUL3 VERMELHO5) #f)
(check-expect (compara-cartas AZUL3 VERDE3) #t)
(check-expect (compara-cartas AZUL3 CURINGA) #t)
(check-expect (compara-cartas CURINGA_COMPRA4 CURINGA) #t)
(check-expect (compara-cartas VERDE-COMPRA2 VERDE3) #f)
(check-expect (compara-cartas VERDE-COMPRA2 VERMELHO-COMPRA2) #t)


;; ==============================================================
;; 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5
;; ==============================================================

;; -----------------
;; TIPO Mão:
;; -----------------
(define-struct mão (carta1 carta2 carta3 carta4))
;; Um elemento do conjunto Mão é
;;  AZUL3 VERMELHO5 VERDE3 CURINGA     onde
;;  CartaUNO: carta1, uma carta que estará na mão do jogador contendo cor e valor.
;;  CartaUNO: carta2, uma carta que estará na mão do jogador contendo cor e valor.
;;  CartaUNO: carta3, uma carta que estará na mão do jogador contendo cor e valor.
;;  CartaUNO: carta4, uma carta que estará na mão do jogador contendo cor e valor.

;; Constantes do tipo Mão
(define M1 (make-mão AZUL3 VERMELHO5 VERDE3 CURINGA))
(define M2 (make-mão VERDE-COMPRA2  CURINGA VERMELHO-COMPRA2 CURINGA_COMPRA4 ))
(define M3 (make-mão AMARELO-PULA_VEZ VERMELHO5 AMARELO1 AZUL3))
(define M4 (make-mão CURINGA VERMELHO5  VERMELHO5  AMARELO1 ))

;; ==============================================================
;; 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
;; ==============================================================


;; Tipos necessários para o resultado:
;; -----------------
;; TIPO Par:
;; -----------------
(define-struct par (carta-escolhida motivo))
;; Um elemento do conjunto Par é
;;   (make-par c m)     onde
;;    CartaUNO: carta-escolhida, que é carta selecionada
;;    String: motivo, é a mensagem indicando porque a carta foi selecionada


;; Um  Resultado é
;; 1. em elemento do tipo Par, ou
;; 2. um elemento do tipo String

;; seleciona-carta: Mão CartaUNO -> Par
;; obj: Dada uma mão e uma carta UNO, a carta da mesa, devolve um par com a carta a ser jogada e a
;; explicação de porque esta carta foi selecionada. A explicação pode ser "mesma cor", "mesmo valor" ou
;; "curinga". Se não houver carta que possa ser jogada, devolver a mensagem "Nenhuma carta pode ser jogada."

;; Exemplos/testes:
(check-expect (seleciona-carta M1 (make-carta 2 "verde"))  (make-par VERDE3 "mesma cor"))
(check-expect (seleciona-carta M2 (make-carta 9 "vermelho")) (make-par CURINGA "curinga"))
(check-expect (seleciona-carta M2 CURINGA) (make-par VERDE-COMPRA2 "curinga"))
(check-expect (seleciona-carta M2 VERMELHO-COMPRA2) (make-par VERDE-COMPRA2 "mesmo valor"))
(check-expect (seleciona-carta M3 VERDE-COMPRA2)  "Nenhuma carta pode ser jogada.")
(check-expect (seleciona-carta M4 CURINGA) (make-par CURINGA "curinga"))


(define (seleciona-carta *mao *carta-mesa) ;; Dada uma carta *carta
  (cond
    ; se a primeira carta puder ser jogada, devolver o par com esta carta e a msg correspondente
    [(jogada-válida? (mão-carta1 *mao) *carta-mesa) (make-par (mão-carta1 *mao) (motivo (mão-carta1 *mao) *carta-mesa))]
    ; se a segunda carta puder ser jogada,  devolver o par com esta carta e a msg correspondente
    [(jogada-válida? (mão-carta2 *mao) *carta-mesa) (make-par (mão-carta2 *mao) (motivo (mão-carta2 *mao) *carta-mesa))]
    ; se a terceira carta puder ser jogada,  devolver o par com esta carta e a msg correspondente
    [(jogada-válida? (mão-carta3 *mao) *carta-mesa) (make-par (mão-carta3 *mao) (motivo (mão-carta3 *mao) *carta-mesa))]
    ; se a quarta carta puder ser jogada,  devolver o par com esta carta e a msg correspondente
    [(jogada-válida? (mão-carta4 *mao) *carta-mesa) (make-par (mão-carta4 *mao) (motivo (mão-carta4 *mao) *carta-mesa))]
    ; senão, devolver a mensagem informando que nenhuma carta pode ser jogada
    [else "Nenhuma carta pode ser jogada."]
    )
  )

;; ==================================
;; opção 2:
;; Usando as seguintes funções auxiliares:

;; jogada-válida? : CartaUNO CartaUNO -> Booleano
;; Objetivo: A função analiza duas cartas UNO, representando a carta da mão
;; e a carta da mesa, nesta ordem, e verifica se é possível
;; jogar uma sobre a outra
(define (jogada-válida? carta-mao carta-mesa)
   (or 
      (or (curinga? carta-mao) (curinga? carta-mesa))
      (string=? (carta-cor carta-mao) (carta-cor carta-mesa))
      (compara-cartas carta-mao carta-mesa)
   )
)

;; motivo: CartaUNO CartaUNO -> String
;; Objetivo: A função analiza duas cartas UNO, representando a carta da mão
;; e a carta da mesa, nesta ordem, devolve o motivo pelo qual a jogada é válida.
(define (motivo carta-mao carta-mesa)
   (cond
      [(or (curinga? carta-mao) (curinga? carta-mesa)) "curinga"]
      [(string=? (carta-cor carta-mao) (carta-cor carta-mesa)) "mesma cor"]
      [(compara-cartas carta-mao carta-mesa) "mesmo valor"]
   )
)


;; ==============================================================
;; 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7
;; ==============================================================

;; desenha-mão: Mão -> Imagem
;; Dada uma mão, gera uma imagem com as cartas da mão, lado a lado
;; Exemplos:
;; ...
;(define (desenha-mão ...) ;; Dada uma mão
;; coloca lado a lado
;; a imagem da carta da posição 1 da mao
;; a imagem da carta da posição 2 da mao
;; a imagem da carta da posição 3 da mao
;; a imagem da carta da posição 4 da mao
(define (desenha-mão *mao)
   (beside (desenha-carta (mão-carta1 *mao)) (desenha-carta (mão-carta2 *mao)) (desenha-carta (mão-carta3 *mao)) (desenha-carta (mão-carta4 *mao)))
)
