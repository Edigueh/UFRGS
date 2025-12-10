;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname UNO-lista-lab1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))

;; Este arquivo contém um modelo para a solução dos exercícios da
;; lista a ser resolvida no laboratório 1 de INF05008.
;; Este exercício não será entregue, é um exercício de fixação.

;; Em cada questão, há um início da solução. Deixamos essas linhas
;; sempre comentadas para não causar erros de compilação, pois
;; não estão completas (em muitos pontos há '...' que deve ser
;; completado por você).

;;===============================================================
;;                     CONSTANTES
;;===============================================================
;; A seguir, são definidas algumas constantes do tipo Imagem:
(define IMG_PULA_VEZ (text "Ø" 60 "black"))
(define IMG_COMPRA2  (text "+2" 60 "black"))
(define IMG_INVERTE  (text "«" 60 "black"))
(define IMG_CURINGA   empty-image)
(define IMG_CURINGA_COMPRA4 (text "+4" 60 "black"))

;;===============================================================
;; 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
;;===============================================================

(define PULA_VEZ -1)
(define COMPRA2 -2)
(define CURINGA -3)
(define CURINGA_COMPRA4 -4)
(define INVERTE -5)
;...

;; Questão: Por que não é necessário definir contratos, objetivos
;; ou exemplos aqui?

;;===============================================================
;; 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
;;===============================================================

(define CIRCULO_BRANCO (circle 40 "solid" "white"))

(define QUADRADOS_COLORIDOS (above (beside (rectangle 50 75 "solid" "red") (rectangle 50 75 "solid" "green"))
                                   (beside (rectangle 50 75 "solid" "yellow") (rectangle 50 75 "solid" "blue"))))

(define CONTORNO_BRANCO (rectangle 110 160 "outline" "white"))

; ...

;;===============================================================
;; 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
;;===============================================================
;; ==> TRADUZ-COR
;; traduz-cor : string -> string
;; Objetivo: Dada uma cor, que pode ser  amarelo, verde, vermelho, azul ou 4cores,
;; retorna a respectiva cor em ingles, ou seja, "blue", "green", "yellow", "red" ou "4colors".
;; Exemplos:
;; (traduz-cor "azul") = "blue"
;; (traduz-cor "verde") = "blue"

(define (traduz-cor cor) ;; Dada uma cor ...
  (cond
    ;; se ... for "azul, devolver "blue"
    [(string=? cor "azul") "blue"]
    ;; se ... for "verde", devolver "green"
    [(string=? cor "verde") "green"]
    ;; se ... for "vermelho, devolver "red"
    [(string=? cor "vermelho") "red"]
    ;; se ... for "amarelo, devolver "yellow"
    [(string=? cor "amarelo") "yellow"]
    ;; senão, devolver "4colors"
    [else "4colors"]))

;;; Testes:
(check-expect (traduz-cor "vermelho") "red")
(check-expect (traduz-cor "azul") "blue")
(check-expect (traduz-cor "amarelo") "yellow")
(check-expect (traduz-cor "verde") "green")
(check-expect (traduz-cor "4cores") "4colors")

;;===============================================================
;; 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 
;;===============================================================

;; ========================
;; ESCOLHE-FUNDO - versão 1
;; ========================
;; escolhe-fundo: String -> Imagem
;; Dada uma cor, que pode ser amarelo, verde, vermelho, azul ou 4cores
;; gera a imagem de fundo para uma carta de UNO desta cor.
;; Exemplos:
;; (escolhe-fundo "vermelho")  desenha o fundo de uma carta vermelha
;; (escolhe-fundo "4cores")     desenha o fundo de uma carta curinga

(define (escolhe-fundo cor) ;; dada uma cor ...
  (overlay ;; sobrepor
   CIRCULO_BRANCO ;; circulo branco
   (cond
     ;; se a cor ... for 4cores, desenhar os quadrados coloridos no fundo
     [(string=? cor "4cores") QUADRADOS_COLORIDOS]
     ;; senão, desenhar um retângulo da cor desejada
     [else (rectangle 100 150 "solid" (traduz-cor cor))])  ;; retangulo da cor da carta
   CONTORNO_BRANCO));; contorno preto

;; ========================
;; ESCOLHE-FUNDO - versão 2
;; ========================
;; escolhe-fundo-v2: String -> Imagem
;; Dada uma cor, que pode ser amarelo, verde, vermelho, azul ou 4cores
;; gera a imagem de fundo para uma carta de UNO desta cor.
;; Exemplos:
;; (escolhe-fundo "vermelho")  desenha o fundo de uma carta vermelha
;; (escolhe-fundo "4cores")     desenha o fundo de uma carta curinga

(define (escolhe-fundo-v2 cor) ;; Dada uma cor...
  (cond
    ;; se a cor COR for 4cores, desenhar os quadrados coloridos no fundo
    [(string=? cor "4cores")
     (overlay ;; sobrepor
      CIRCULO_BRANCO
      QUADRADOS_COLORIDOS
      CONTORNO_BRANCO)]
    ;; senão, desenhar um retângulo da cor desejada
    [else
     (overlay ;; sobrepor
      CIRCULO_BRANCO
      (rectangle 100 150 "solid" (traduz-cor cor))
      CONTORNO_BRANCO)]))


;; Testes:       

(check-expect (escolhe-fundo "vermelho") (overlay  CIRCULO_BRANCO (rectangle 100 150 "solid" "red") CONTORNO_BRANCO))
(check-expect (escolhe-fundo "azul") (overlay  CIRCULO_BRANCO (rectangle 100 150 "solid" "blue") CONTORNO_BRANCO))
(check-expect (escolhe-fundo "amarelo") (overlay  CIRCULO_BRANCO (rectangle 100 150 "solid" "yellow") CONTORNO_BRANCO))
(check-expect (escolhe-fundo "verde") (overlay  CIRCULO_BRANCO (rectangle 100 150 "solid" "green") CONTORNO_BRANCO))
(check-expect (escolhe-fundo "4cores") (overlay  CIRCULO_BRANCO QUADRADOS_COLORIDOS CONTORNO_BRANCO))

;; Qual a diferença entre as versões desta função?

;;===============================================================
;; 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5
;;===============================================================
;; ========================
;; DESENHA-CARTAS
;; ========================
;; desenha-carta : Número String -> Imagem
;; Objetivo: Dados um número e uma cor, representando uma carta de UNO,
;; gera uma imagem para esta carta,
;; Exemplos:
;; (desenha-carta 4 "vermelha")  desenha a carta número 4 vermelha
;; (desenha-carta COMPRA4 "4cores")    desenha a carta curinga compra 4
(define (desenha-carta num cor)
  (cond
    [(or (= num CURINGA_COMPRA4) (= num CURINGA))
     (overlay    ;; sobrepor
      (escolhe-simbolo num) ;; o desenho do símbolo da carta e
      (escolhe-fundo "4cores"))]
    [else
     (overlay    ;; sobrepor
      (escolhe-simbolo num) ;; o desenho do símbolo da carta e
      (escolhe-fundo cor))])) ;; o desenho do fundo da carta

;; escolhe-simbolo: Número -> Imagem
;; Dado um número, que pode ser de 0 a 9 ou as constantes referentes às
;; cartas especiais de UNO, devolve uma imagem que representa este número na carta.
;; Exemplos:
;;    (escolhe-simbolo 8) devolve a imagem do número oito
;;    (escolhe-simbolo COMPRA2) devolve a imagem +2

(define (escolhe-simbolo num)
  (cond
    ;; se a carta for numérica, desenha a carta numérica
    [(positive? num) (text (number->string num) 20 "black")]
    ;; se a carta for um COMPRA2, desenha +2
    [(= num COMPRA2) (text "+2" 20 "black")]
    ;; se a carta for um INVERTE, desenha «
    [(= num INVERTE) (text "«" 20 "black")]
    ;; se a carta for um PULA_VEZ, desenha Ø
    [(= num PULA_VEZ) (text "Ø" 20 "black")]
    ;; se a carta for um CURINGA, não desenha nada (devolve uma imagem vazia)
    [(= num CURINGA) (text "" 20 "black")] 
    ;; se a carta for um CURINGA_COMPRA4, devolve +4
    [(= num CURINGA_COMPRA4) (text "+4" 20 "black")])) 


;;===============================================================
;; 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 
;;===============================================================

;; jogada-válida? : Numero String Numero String -> Booleano
;; Objetivo: A função analiza duas cartas (representadas por 4 argumentos: um
;; número e uma string, representando a carta da mão e um número e uma string,
;; representando a carta da mesa, nesta ordem) e verifica se é possível
;; jogar uma sobre a outra, de acordo com as regras do UNO
;; Exemplos:
;;    (jogada-válida? 2 "vermelho" 4 "vermelho")=  #t 
;;    (jogada-válida? 2 "vermelho" CURINGA "4cores") = #t 
;;    (jogada-válida? CURINGA "4cores" 2 "vermelho") = #t
;;    (jogada-válida? 2 "vermelho" 2 "verde") = #t
;;    (jogada-válida? 2 "vermelho" 3 "verde") = #f

(define (jogada-válida? n-mao cor-mao n-mesa cor-mesa)
  (or
   ;; n-mesa == CURINGA -> true
   (or (= n-mesa CURINGA) (= n-mesa CURINGA_COMPRA4))
   ;; n-mao == CURINGA -> true
   (or (= n-mao CURINGA) (= n-mao CURINGA_COMPRA4))
   ;; n-mao == n-mesa -> true
   (= n-mao n-mesa)
   ;; cor-mao == cor-mesa -> true
   (string=? cor-mao cor-mesa)
   )
  )

;;; Testes:
(check-expect (jogada-válida? 3 "azul" 3 "verde")  #t )
(check-expect (jogada-válida? 8 "verde" CURINGA "4cores")  #t )
(check-expect (jogada-válida? CURINGA_COMPRA4 "4cores" PULA_VEZ "amarelo")  #t )
(check-expect (jogada-válida? INVERTE "azul" INVERTE "verde")  #t )
(check-expect (jogada-válida? 8 "verde" PULA_VEZ "amarelo")  #f )
(check-expect (jogada-válida? PULA_VEZ "amarelo" 5 "vermelho")  #f )
(check-expect (jogada-válida? 8 "verde" 5 "vermelho")  #f )

;;===============================================================
;; 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7
;;===============================================================
;; mostra-jogada: Numero String Numero String -> Imagem
;; Objetivo: A função analiza duas cartas (representadas por 4 argumentos: um
;; número e uma string, representando a carta da mesa e um número e uma string,
;; representando a carta da mão, nesta ordem) e verifica se é possível
;; jogar uma sobre a outra, de acordo com as regras do UNO, desenhando uma
;; imagem mostrando as cartas e se é possível fazer a jogada ou não.
;; Exemplos:


(define (mostra-jogada n-mesa cor-mesa n-mao cor-mao)
  (cond
    ;; se a jogada é válida, desenha a carta da mão encima da carta da mesa
    [(boolean=? (jogada-válida? n-mao cor-mao n-mesa cor-mesa) #t) (overlay/xy ;; sobrepor com deslocamento
                                                                    (desenha-carta n-mao cor-mao)
                                                                    0
                                                                    37.5                                                                           
                                                                    (desenha-carta n-mesa cor-mesa))]
    ;; senão, desenha somente a carta da mesa
    [else (desenha-carta n-mesa cor-mesa)]
    )
  )

(check-expect (mostra-jogada 1 "azul" 2 "azul") (overlay/xy
                                                 (desenha-carta 2 "azul")
                                                 0
                                                 37.5                                                                           
                                                 (desenha-carta 1 "azul")))

(check-expect (mostra-jogada 1 "vermelho" 2 "azul") (desenha-carta 1 "vermelho"))
