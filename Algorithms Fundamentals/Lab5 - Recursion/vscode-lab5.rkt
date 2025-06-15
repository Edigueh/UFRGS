#reader(lib "htdp-intermediate-reader.ss" "lang")((modname vscode-lab5) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
;; Nomes: André e Arthur

;; Funções úteis do pacote de imagens (para maiores informações e exemplos, consultar o manual):

;; rotate: Número Imagem -> Imagem
;; Dado um ângulo (em graus) e uma imagem, gera uma nova imagem rotacionando a imagem original
;; no ângulo dado.

;; ========================================================================================
;;                              DEFINIÇÕES DE DADOS
;; ========================================================================================

;; ---------------
;; TIPO NúmeroRGB:
;; ---------------

;; NúmeroRGB = {0, 1, 2, ..., 255} (é um número inteiro entre 0 e 255)

;; --------------------------------------------------- 
;; TIPO COLOR (tipo pré-definido no pacote de imagens):
;; ---------------------------------------------------
;; (define-struct color (red blue green alpha))
;; Um elemento de Color tem o formato
;;    (make-color red green blue alpha), one
;;    red, green, blue: NúmeroRGB, representam a quantidade de cada cor básica na cor
;;    alpha: NúmeroRGB, representa a tranparência da cor, 0 significa totalmente transparente.

;; Constantes do tipo Color
(define VERMELHO  (make-color 255 0 0 255))
(define VERDE     (make-color 0 255 0 255))
(define AZUL      (make-color 0 0 255 255))
(define CINZA     (make-color 100 100 100 255))

;; ------------ 
;; TIPO QUAD:
;; ------------
(define-struct quadrado (lado cor))
;; Um elemento do conjunto Quadrado é
;;     (make-quadrado l c), onde
;;   l: Número, é o lado do quadrado
;;   c: Color, é a cor do quadrado

;; Constantes do tipo Quadrado:
(define Q1 (make-quadrado 100 VERDE))
(define Q2 (make-quadrado 75  CINZA))
(define Q3 (make-quadrado 200 AZUL))


; ========================================================================================
;;                               DEFINIÇÕES DE FUNÇÕES
;; ========================================================================================

;; ========================
;; FUNÇÃO DESENHA-TRIANGULO:
;; ========================
;; desenha-triangulo : Número Color ->  Imagem
;; Obj.: Dados um tamanho de lado e uma cor, desenha um triângulo.
;; Exemplos:
;;     (desenha-triangulo 20 VERMELHO) = .
;;     (desenha-triangulo 50 VERDE) = .
(define (desenha-triangulo lado cor)
  (triangle lado "outline" cor))

;; ========================
;; FUNÇÃO DESENHA-QUADRADO:
;; ========================
;; desenha-quadrado : Número Color ->  Imagem
;; Obj.: Dados um tamanho de lado e uma cor, desenha um quadrado.
;; Exemplos:
;;     (desenha-quadrado 20 VERMELHO) = .
;;     (desenha-quadrado 50 VERDE) = .
(define (desenha-quadrado lado cor)
  (square lado "outline" cor))

;; ========================
;; FUNÇÃO DESENHA-QUAD:
;; ========================
;; desenha-quad : Quadrado -> Imagem
;; Dado um quadrado, gera uma imagem deste quadrado
;; Exemplos:
;;    (desenha-quad Q1) = .
;;    (desenha-quad Q2) = .
(define (desenha-quad Q)
           (overlay (square (quadrado-lado Q) "outline" "black")
                    (square (quadrado-lado Q) "solid" (quadrado-cor Q))))


;; ========================
;; FUNÇÃO ALEATORIO
;; ========================

;; aleatorio: Numero -> Numero
;; Dado o número RGB de uma cor, devolve um novo número aleatorio entre 0 e 255.
;; Exemplo:
;;     (aleaorio 10) = 245
(define (aleatorio c)
        (random 255))


;; ========================
;; FUNÇÃO FUN-MUDA-COR:
;; ========================

;; fun-muda-cor: (Número -> Número) -> (Color -> Color)
;; Dada uma função que transforma número, devolve uma função
;; que, dada uma cor, devolve uma nova cor aplicando a função
;; Exemplo:
;;     (fun-muda-cor aleatorio) gera uma função que, dada uma cor, gera uma outra aleatoriamente
;; dada a cada componente rgb da cor.
(define (fun-muda-cor fun-muda-componente)
    (lambda (cor)
      (make-color (fun-muda-componente (color-red cor))
                  (fun-muda-componente (color-green cor))
                  (fun-muda-componente (color-blue cor)))))

;; ========================
;; FUNÇÃO SIERPISNKI:
;; ========================

;; sierpinski: Número Color -> Imagem
;; Obj: Dados o tamanho do lado e uma cor, desenha um triângulo de Sierpinski
;; desta cor cujo lado do triângulo externo é o lado passado como argumento. 
;; Exemplo:
;;        (sierpinski 50 VERMELHO) = . 
(define (sierpinski lado cor);; Dados um lado e uma cor 
  (cond
       ;; se o lado for muito pequeno, desenhar um triângulo com o lado dado
       [(<= lado 5)  (desenha-triangulo lado cor)]
       ;; senão
       ;;      desenha um triângulo de sierpinksi com a metade do tamanho do lado
       ;;      e dá o nome de TRIANGULO para este desenho:
       [else (local
               (
                (define TRIANGULO (sierpinski (/ lado 2) cor))
               )
                ;; e monta a imagem do triângulo de sierpinski colocando um TRIANGULO
                ;; acima de dois outros TRIANGULOs, lado a lado:
               (above TRIANGULO
                      (beside TRIANGULO TRIANGULO)))]))

;; Argumentação de terminação:
;; Este programa sempre termina porque:
;; (a) Existe um caso base (sem recursão) que é quando o tamanho do lado é menor ou igual a 5.
;;     Neste caso, o programa simplesmente desenha um triângulo com este lado.
;; (b) Cada chamada recursiva é realizada tendo como argumento a metade do lado,
;;     que é um número estritamente menor que o lado, e portanto mais próximo
;;     de se tornar menor que 5 (lembrando que a chamada recursiva só ocorre se o lado for >5).
;; (c) As funções <=, above, beside e cond terminam, pois são pré-definidas da linguagem.
;;     A função desenha-triangulo termina, pois somente usa funções pré-definidas e não tem laços.


;; Não modifique nada até este ponto!!!
;; A partir daqui estão os exercícios a serem resolvidos.

;;===============================================================
;; 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
;;===============================================================

;; sierpinski-sem-def-local: Número Color -> Imagem
;; Obj: Dados o tamanho do lado e uma cor, desenha um triângulo de Sierpinski
;; desta cor cujo lado do triângulo externo é o lado passado como argumento. 
;; Exemplos:
;;        (sierpinski-sem-def-local 50 VERMELHO) = .


;;===============================================================
;; 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
;;===============================================================
;; tapete-sierpinski: Número Color -> Imagem
;; Obj: Dados o tamanho do lado e uma cor inicial, desenha um tapete de Sierpinski
;; com o quadrado central desta cor e lado do quadrado externo igual ao lado passado
;; como argumento. A variação de cor para os passos sucessivos é randômica.
;; Exemplos:
;;        (tapete-sierpinski 200 VERMELHO) = . ou . ou . ou . ou ...

;; Definição da função:

;; Argumentação de terminação:
;; Este programa sempre termina porque:
;; (a) ...
;; (b) ...   
;; (c) ...

;; Chamadas da função tapete-sierpinski:
;(beside (tapete-sierpinski ...)
;        (tapete-sierpinski ...)
;        (tapete-sierpinski ...))



;;===============================================================
;; 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 
;;===============================================================

;; ===> (a)
;; espiral-quad: ...


;; Argumentação de terminação:

;; Chamadas da função espiral-quad (pele menos 3, colocadas lado a lado):
;(beside (espiral-quad ...)
;        (espiral-quad ...)
;        (espiral-quad ...))


;; ===> (b)
;; espiral-quad-escurece: ...


;; Argumentação de terminação:


;; Chamadas da função espiral-quad-escurece (pele menos 3, colocadas lado a lado):
;(beside (espiral-quad-escurece ...)
;        (espiral-quad-escurece ...)
;        (espiral-quad-escurece ...))

;; ===> (c)

;; (i) 2 funcoes tipo NúmeroRGB -> NúmeroRGB:

;; (ii) 2 funcoes tipo Quadrado -> Booleano:

;; (iii) função espiral-quad-gen:



;; Chamadas da função espiral-quad-gen (pele menos 3, colocadas lado a lado):
;(beside (espiral-quad-gen ...)
;        (espiral-quad-gen ...)
;        (espiral-quad-gen ...))


;; (iv) Argumentação sobre a terminação das chamadas:  


