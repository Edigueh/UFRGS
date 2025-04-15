;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname lab2-template-2025-1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
;; => Complete todos os locais pontilhados.
;; => Não esqueça de tirar o ponto-e-vírgula da frente das linhas de teste para testar suas funções

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
;;   .......     onde
;;   ..... : ......., é o valor da carta, que pode ser qualquer inteiro entre 0 e 9,
;;               ou as strings "pula vez", "compra 2", ou "inverte"
;;   ..... : ......., é a cor da carta, que pode ser "azul", "verde", "amarelo" ou "vermelho"

;; --------------------------
;; TIPO CARTAUNO:
;; --------------------------
;;  Um elemento do tipo CartaUNO é 
;; 1. Uma ..... ou
;; 2. Uma .....


;; Constantes do tipo Carta (ou CartaUNO, ja que o tipo Carta é um subconjunto de CartaUNO):
 (define AZUL3 (make-carta  3 "azul"))
; (define AZUL1 .....)
; (define VERMELHO5 .....)
; (define VERMELHO1 .....)
; (define AMARELO1 .....)
; (define VERDE3 .....)

 (define AZUL-INVERTE (make-carta  INVERTE "azul"))
; (define VERMELHO-COMPRA2 .....)
; (define VERDE-COMPRA2 .....)
; (define AMARELO-PULA_VEZ .....)

;; ==============================================================
;; 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
;; ==============================================================

;; curinga? : .... -> ....
;; Dada uma carta UNO, diz se ela é um curinga.
;; Exemplos:
   ;; (curinga? VERDE3) = #f
   ;; (curinga? CURINGA) = #t

(define (curinga? ...) ;; a carta ... é um curinga se
   ;; a carta for uma string E
   (and (string? ...)
        ;; a string é CURINGA ou CURINGA_COMPRA4
        (or (... ... CURINGA)
            (... ... CURINGA_COMPRA4))))
;; Testes:
;   (check-expect (curinga? VERDE3)  #f)
;   (check-expect (curinga? CURINGA)  #t)

;; ==============================================================
;; 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
;; ==============================================================

;; mesmo-número-ou-símbolo: Carta Carta  -> Booleano
;; Objetivo: Dadas duas cartas, diz se elas têm o mesmo número ou símbolo,
;;  devolvendo o valor-verdade correspondente. A cor não é considerada.
;; Exemplos/testes:
   ;(check-expect (mesmo-número-ou-símbolo VERDE3 AZUL3)  #t)
   ;(check-expect (mesmo-número-ou-símbolo  VERDE-COMPRA2 VERDE3)  #f)
   ;(check-expect (mesmo-número-ou-símbolo  VERDE-COMPRA2 VERMELHO-COMPRA2) #t)

;(define (mesmo-número-ou-símbolo @carta1 @carta2); Dadas duas cartas @carta1 e @carta2
;  (cond
;       ;; se a @carta1 e @carta2 forem cartas numéricas com mesmo número, devolver verdadeiro
;       [(and (number? (carta-valor @carta1)) (number? (carta-valor @carta2))
;          (= (carta-valor @carta1) (carta-valor @carta2))) ...
;       ;; se @carta1 e @carta2 forem especiais e iguais, devolver true
;       [(and ...
;             ...)))...]
;       ;; senão, devolver falso
;       [else ...]))

;; Obs: Como esta função devolve um valor booleano, pode ser construída sem uma estrutura condicional
;; (como a questão anterior).


;; ==============================================================
;; 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 
;; ==============================================================


;; compara-cartas : ....  -> ....
;; Objetivo: Dadas duas cartas UNO, diz se elas têm o mesmo número ou símbolo,
;;  devolvendo o valor-verdade correspondente. Cartas curinga devem ser consideradas
;; como qualquer tipo/símbolo (ou seja, se alguma das cartas for curinga,
;;  a função deve retornar verdadeiro). A cor não é considerada.
;; Exemplos:
;;    (check-expect (compara-cartas  AZUL3 VERDE3)   #t)
;;    (check-expect (compara-cartas  AZUL3 VERMELHO5) #f)
;;    (check-expect (compara-cartas  VERMELHO5 VERMELHO-COMPRA2) #f)
;;    (check-expect (compara-cartas  VERMELHO-COMPRA2 CURINGA)   #t)

;(define (compara-cartas @carta1 @carta2)
  ;; Duas cartas @carta1 e @carta2 são consideradas iguais se
;  (...
;    ;; OU @carta1 ou @carta2 forem curingas
;    .....
;    ;; OU @carta1 e @carta2 tiverem mesmo número ou símbolo
;    ...))


;; Testes:
;   (check-expect (compara-cartas AZUL3 VERMELHO5) #f)
;   (check-expect (compara-cartas AZUL3 VERDE3) #t)
;   (check-expect (compara-cartas AZUL3 CURINGA) #t)
;   (check-expect (compara-cartas CURINGA_COMPRA4 CURINGA) #t)
;   (check-expect (compara-cartas VERDE-COMPRA2 VERDE3) #f)
;   (check-expect (compara-cartas VERDE-COMPRA2 VERMELHO-COMPRA2) #t)


;; ==============================================================
;; 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 
;; ==============================================================

;; -----------------
;; TIPO Mão:
;; -----------------
;(define-struct mão (.....)
;; Um elemento do conjunto Mão é
;;   .............     onde
;;  ...............
  
;; Constantes do tipo Mão
;(define M1 (make-mão AZUL3 VERMELHO5 VERDE3 CURINGA))
;(define M2 (make-mão VERDE-COMPRA2  CURINGA VERMELHO-COMPRA2 CURINGA_COMPRA4 ))
;(define M3 (make-mão AMARELO-PULA_VEZ VERMELHO5 AMARELO1 AZUL3))
;(define M4 (make-mão CURINGA VERMELHO5  VERMELHO5  AMARELO1 ))
;; (define ... ...)
;; (define ... ...)
;; (define ... ...)
;; (define ... ...)


;; ==============================================================
;; 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 
;; ==============================================================


;; Tipos necessários para o resultado:
;; -----------------
;; TIPO Par:
;; -----------------
;(define-struct par (.....))
;; Um elemento do conjunto Par é
;;   (make-par c m)     onde
;;    ...: ..., que é carta selecionada
;;    ...: ..., é a mensagem indicando porque a carta foi selecionada
  

;; Um  Resultado é
;; 1. em elemento do tipo Par, ou
;; 2. um elemento do tipo String

;; seleciona-carta: .... -> ....
;; obj: Dada uma mão e uma carta UNO, a carta da mesa, devolve um par com a carta a ser jogada e a
;; explicação de porque esta carta foi selecionada. A explicação pode ser "mesma cor", "mesmo valor" ou
;; "curinga". Se não houver carta que possa ser jogada, devolver a mensagem "Nenhuma carta pode ser jogada."

;; Exemplos/testes:
;    (check-expect (seleciona-carta2 M1 (make-carta 2 "verde"))  (make-par VERDE3 "mesma cor"))
;    (check-expect (seleciona-carta2 M2 (make-carta 9 "vermelho")) (make-par CURINGA "curinga"))
;    (check-expect (seleciona-carta2 M2 CURINGA) (make-par VERDE-COMPRA2 "curinga"))
;    (check-expect (seleciona-carta2 M2 VERMELHO-COMPRA2) (make-par VERDE-COMPRA2 "mesmo valor"))
;    (check-expect (seleciona-carta2 M3 VERDE-COMPRA2)  "Nenhuma carta pode ser jogada.")
;    (check-expect (seleciona-carta2 M4 CURINGA) (make-par CURINGA "curinga"))


;(define (seleciona-carta *mao *carta-mesa) ;; Dada uma carta *carta
;  (cond
          ;; se a primeira carta puder ser jogada, devolver o par com esta carta e a msg correspondente
        
          ;; se a segunda carta puder ser jogada,  devolver o par com esta carta e a msg correspondente
       
          ;; se a terceira carta puder ser jogada,  devolver o par com esta carta e a msg correspondente
         
          ;; se a quarta carta puder ser jogada,  devolver o par com esta carta e a msg correspondente
        
          ;; senão, devolver a mensagem informando que nenhuma carta pode ser jogada
;         )

;; ==================================
;; opcao1:
;; Usando a seguinte função auxiliar:
;; jogada : CartaUNO CartaUNO -> Resultado
;; Objetivo: A função analiza duas cartas UNO, representando a carta da mão 
;; e a carta da mesa, nesta ordem, e verifica se é possível
;; jogar uma sobre a outra, devolvendo um par com a carta e o motivo
;; pelo qual a jogada pode ser realizada, caso seja possível. Caso
;; contrário, devolve uma mensagem indicando que não é possível fazer a jogada.


;; ==================================
;; opção 2:
;; Usando as seguintes funções auxiliares:

;; jogada-válida? : CartaUNO CartaUNO -> Booleano
;; Objetivo: A função analiza duas cartas UNO, representando a carta da mão 
;; e a carta da mesa, nesta ordem, e verifica se é possível
;; jogar uma sobre a outra

;; motivo: CartaUNO CartaUNO -> String
;; Objetivo: A função analiza duas cartas UNO, representando a carta da mão 
;; e a carta da mesa, nesta ordem, devolve o motivo pelo qual a jogada é válida.

 

;; ==============================================================
;; 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 
;; ==============================================================
 
;; desenha-mão: ... -> ...
;; Dada uma mão, gera uma imagem com as cartas da mão, lado a lado
;; Exemplos:
    ;; ...
;(define (desenha-mão ...) ;; Dada uma mão 
  ;; coloca lado a lado
         ;; a imagem da carta da posição 1 da mao
         ;; a imagem da carta da posição 2 da mao
         ;; a imagem da carta da posição 3 da mao
         ;; a imagem da carta da posição 4 da mao





