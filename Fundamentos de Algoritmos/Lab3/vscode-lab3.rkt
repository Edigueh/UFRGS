#reader(lib "htdp-intermediate-reader.ss" "lang")((modname lab2-template-2025-1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))

;; Vamos trabalhar com formas geométricas coloridas.
;; As formas serão usadas são retângulos, círculos, triângulos (equiláteros)
;; ou estrelas radiais.

;; Algumas funções pré-definidas do Racket que usaremos são:

;; rectangle: Numero Numero String String -> Imagem
;; Dados os lados de um retângulo, um string representando se o retângulo será preenchido
;; ("solid") ou vazado ("outline"), e um string representando uma cor, desenha o
;; retângulo correspondente.
;; Exemplos:
;; (rectangle 30 60 "solid" "green") = .
;; (rectangle 40 40 "outline" "red") = .

;; triangle: Numero String String -> Imagem
;; Dados o tamanho do lado, o tipo (preenchido ou vazado) e a cor,
;; desenha o triângulo correspondente.
;; Exemplo:
;; (triangle 40 "solid" "blue") = .

;; circle: Número String String -> Imagem
;; Dados o tamanho do raio,
;; o tipo (preenchido ou vazado) e a cor, desenha o círculo correspondente.
;; Exemplo:
;; (circle 40  "outline""red") = .
;; (circle 40 "solid""yellow") = .

;; radial-star: Número Número Número String String -> Imagem
;; Dados o número de pontas, o raio interno e o raio externo da estrela,
;; o tipo (preenchido ou vazado) e a cor, desenha a estrela radialcorrespondente.
;; Exemplo:
;; (radial-star 5 10 50 "outline""blue") = .
;; (radial-star 10 30 50 "solid""orange") = .


;; beside: Imagem ... Imagem -> Imagem
;; Dadas 2 (ou mais) imagens posiciona as duas lado a lado na tela, na ordem na qual foram passadas.

;; overlay Imagem ... Imagem -> Imagem
;; Dadas 2 (ou mais) imagens posiciona a primeira sobre da segunda na tela,
;; e assim sucessivamente.

;; text : String Number String-> Imagem
;; Dados um string , um tamanho de fonte e uma cor, transforma o string em imagem.
;; Exemplos:
;;      (text "XXX" 20 "red") = .
;;      (text "YYY" 10 "darkgreen") = .

;; string-append: String ...String -> String
;; Dadas várias strings, gera uma nova string concatenando essas strings, na mesma ordem dos argumentos.
;; Exemplos:
;;      (string-append "AAA" "BBB" "CCC") = "AAABBBCCC"
;;      (string-append "X" "YY") = "XYY"


;; ================================================================================================

;; ==============
;; TIPOS DE DADOS:
;; ==============


;; TIPO TipoDeForma:
;; ================
;; Um TipoDeForma pode ser
;; 1. "retângulo", ou
;; 2. "triângulo", ou
;; 3. "círculo", ou
;; 4. "estrela"

;; TIPO ListaDeNumeros:
;; ===================
;; Uma ListaDeNumeros é
;; 1. empty (lista vazia), ou
;; 2. (cons n ln), onde n: Número e ln: ListaDeNumeros

;; TIPO Forma:
;; ===========
(define-struct forma (nome tipo cor args))
;; Um elemento do conjunto Forma tem o formato
;;    (make-forma n t c a), onde
;;    n : String, é o nome da forma
;;    t : TipoDeForma, é o tipo da forma
;;    c : String, é a cor da forma
;;    a : ListaDeNumeros, é a lista de argumentos da forma, confore seu tipo:
;;                        - retângulos possuem 2 argumentos, largura e altura;
;;                        - triângulos possuem 1 argumento, o lado;
;;                        - círculos possuem 1 argumento, o raio;
;;                        - estrelas possuem 3 argumentos, o número de pontas, o
;;                          raio interno e o raio externo.

;; Exemplos de constantes do tipo ListaDeNumeros:

(define LN1 (cons 30 empty))
(define LN2 (cons 40 (cons 20 empty)))
(define LN3 (cons 5 LN2))
(define LN4 (cons 40 (cons 20 (cons 40 empty))))

;; ============================
;; FUNÇÕES PARA DESENHAR FORMAS:
;; ============================

;; ==> SOMENTE REMOVA A CAIXA DE COMENTÁRIO DO CÓDIGO DEPOIS DE FAZER O EXERCÍCIO 3!

;; desenha : Forma -> Imagem
;; Dada uma forma, desenha esta forma (sem o nome).
;; Exemplos:
;;     (desenha (make-forma "C2" "círculo" "blue"  LN1)) = .
;;     (desenha (make-forma "E1" "estrela" "red" LN4)) = .
(define (desenha f) ;; Dada uma forma f
  (cond
    ;; se f for um retângulo, desenha este retângulo
    [(string=? "retângulo" (forma-tipo f))
     (desenha-retangulo (forma-args f)(forma-cor f))]
    ;; se f for um triângulo, desenha este triângulo
    [(string=? "triângulo" (forma-tipo f))
     (desenha-triangulo (forma-args f)(forma-cor f))]
    ;; se f for um círculo, desenha este circulo
    [(string=? "círculo" (forma-tipo f))
     (desenha-circulo  (forma-args f)(forma-cor f))]
    ;; se f for uma estrela, desenha esta estrela
    [(string=? "estrela" (forma-tipo f))
     (desenha-estrela  (forma-args f)(forma-cor f))]))


;; desenha-retangulo:  ListaNumeros String -> Imagem
;; Dados  a lista de argumentos e uma cor, desenha um retângulo com esses argumentos.
;; Exemplo:
;;   (desenha-retangulo   LN2 "blue") = .
(define (desenha-retangulo  LN COR) ;; Dadas uma lista de argumentos LN e uma cor COR
  (rectangle  ;; desenha um retangulo com
   (first LN)  ;; a largura definida no primeiro argumento de LN
   (segundo LN);; a altura definida no segundo argumento de LN
   "solid"     ;; todo preenchido
   COR))       ;; na cor COR


;; desenha-triangulo:  ListaNumeros String -> Imagem
;; Dados  a lista de argumentos e uma cor, desenha um triângulo com esses argumentos.
;; Exemplo:
;;   (desenha-triangulo   LN1 "red") = .
(define (desenha-triangulo  LN COR) ;; Dadas uma lista de argumentos LN e uma cor COR
  (triangle  ;; desenha um triangulo com
   (first LN)  ;; o lado definido no primeiro argumento de LN
   "solid"     ;; todo preenchido
   COR))       ;; na cor COR

;; desenha-circulo:  ListaNumeros String -> Imagem
;; Dados  a lista de argumentos e uma cor, desenha um circulo com esses argumentos.
;; Exemplo:
;;   (desenha-circulo  LN1 "darkgreen") = .
(define (desenha-circulo  LN COR) ;; Dadas uma lista de argumentos LN e uma cor COR
  (circle  ;; desenha um triangulo com
   (first LN)  ;; o raio definido no primeiro argumento de LN
   "solid"     ;; todo preenchido
   COR))       ;; na cor COR

;; desenha-estrela:  ListaNumeros String -> Imagem
;; Dados  a lista de argumentos e uma cor, desenha uma estrela radial com esses argumentos.
;; Exemplo:
;;   (desenha-estrela  LN3 "orange") = .
(define (desenha-estrela  LN COR) ;; Dadas uma lista de argumentos LN e uma cor COR
  (radial-star  ;; desenha uma estrela radial com
   (first LN)     ;; o número de pontas definido no primeiro argumento de LN
   (segundo LN)   ;; o raio interno definido no segundo argumento de LN
   (terceiro LN)  ;; o raio externo definido no terceiro argumento de LN
   "solid"        ;; todo preenchido
   COR))          ;; na cor COR




;; ==========================================================================================
;; ================================= EXERCÍCIOS =============================================
;; ==========================================================================================

;; Modelo para funções recursivas sobre listas:

;; se <...caso trivial...> , então  <...solução caso trivial...>

;; senão <...combinar...r>
;;  <...fazer algo com..> <.. primeiro elemento da lista...>
;;  <...solucionar problema para..> <.. resto da lista...>



;; ==============================================================
;; 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
;; ==============================================================
;; (1) Defina constantes do tipo Forma, no mínimo 2 formas de cada tipo de forma.

;; Retângulos:
(define R1 (make-forma "R1" "retângulo" "green" (cons 30 (cons 60 empty))))
(define R2 (make-forma "R2" "retângulo" "blue" (cons 40 (cons 20 empty))))

;; Círculos:
(define C1 (make-forma "C1" "círculo" "green" (cons 50 empty)))
(define C2 (make-forma "C2" "círculo" "blue" (cons 10 empty)))

;; Triângulos:
(define T1 (make-forma "T1" "triângulo" "green" (cons 100 empty)))
(define T2 (make-forma "T2" "triângulo" "blue" (cons 60 empty)))

;; Estrelas:
(define S1 (make-forma "S1" "estrela" "yellow" (cons 60 (cons 30 (cons 1000 empty)))))
(define S2 (make-forma "S2" "estrela" "blue" (cons 50 (cons 20 (cons 80 empty)))))

;; ==============================================================
;; 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
;; ==============================================================

;; (2) Defina um tipo de dados para armazenar  lista de formas.
;;     Dê 4 exemplos de constantes deste tipo.

;; Uma ListaFormas é
;; 1. vazia(empty), ou
;; 2. (cons f lf), onde
;;     f : Forma
;;     lf: ListaFormas

;; Constantes do tipo ListaFormas:
(define L1 (cons C1 empty))
(define L2 (cons C1 (cons R2 (cons S1 empty))))
(define L3 (cons R1 (cons T1 empty)))
(define L4 (cons S2 (cons S1 (cons T2 (cons T1 (cons C2 (cons C1 (cons R1 L3))))))))

;; ==============================================================
;; 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
;; ==============================================================

;; (3) Construa funções chamadas segundo e terceiro que, dada uma lista de números
;; devolvem o segundo e o terceiro elementos da lista, respectivamente.
;; Assuma que as listas passadas como argumentos possuem o número de elementos necessários.

;; segundo: ListaDeNumeros -> Numero
;; Dada uma lista com pelo menos 2 números, devolve o segundo número da lista.
;; Exemplos/testes:
(check-expect (segundo (cons 1 (cons 2 empty))) 2)
(check-expect (segundo (cons 1 (cons 2 (cons 5 empty)))) 2)
(define (segundo ln)
  (first (rest ln))
  )


;; terceiro: ListaDeNumeros -> Numero
;; Dada uma lista com pelo menos 3 números, devolve o terceiro número da lista.
;; Exemplos/testes:
(check-expect (terceiro (cons 1 (cons 2 (cons 3 (cons 4 empty))))) 3)
(check-expect (terceiro (cons 1 (cons 2 (cons 5 empty)))) 5)
(define (terceiro ln)
  (segundo (rest ln))
  )


;; ==============================================================
;; 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4
;; ==============================================================

;; (4) Construa uma função que, dada uma lista de formas, monta uma imagem com
;; todas as formas lado a lado, com os nomes dentro de cada forma.

;; desenha-lista-formas: ListaFormas -> Imagem
;; Dada uma lista de formas, desenha as formas da lista lado a lado, com os nome dentro das formas.
;; Exemplos:
;;      (desenha-lista-formas lf) = Imagem

(define (desenha-lista-formas lf)
  (cond
    ;; se lf está vazia, então devolver uma imagem vazia
    [(empty? lf) empty-image]
    ;; senão desenhar a primeira forma e chamar a função denovo
    [else
     (beside
      ;; desenhar o primeiro elemento da lista
      (overlay (text (forma-nome (first lf)) 20 "black") (desenha (first lf)))
      ;; desenhar a lista de formas para o resto da lista
      (desenha-lista-formas (rest lf)))]
    )
  )

;; ==============================================================
;; 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5
;; ==============================================================

;; (5) Defina uma função chamada nome-das-formas que, dada uma lista de formas,
;; devolve uma string com os nomes das formas da lista, separadas por hífens, e com um asterisco no final.


;; nomes-das-formas: ListaFormas -> String
;; Exemplos/testes:
(check-expect (nomes-das-formas L4) "S2-S1-T2-T1-C2-C1-R1-R1-T1-*")

(define (nomes-das-formas lf)
  (cond
    ;; se lf for vazia , então retorna "*"
    [(empty? lf) "*"]

    ;; senão inclui o nome da forma na string, inclui o separador e concatena com os demais nomes
    [else
     (string-append (forma-nome (first lf)) "-" (nomes-das-formas (rest lf)))
     ]
    )
  )

;; ==============================================================
;; 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
;; ==============================================================
;; (6) Construa uma função que, dada uma lista de formas e um tipo de forma,
;; diz quantas formas deste tipo há na lista.

;; conta-formas-tipo: ListaFormas TipoDeForma -> Numero
;; Dada uma lista de formas e um tipo de forma, diz quantas formas deste tipo há na lista.
;; Exemplos/testes:
(check-expect (conta-formas-tipo L4 "estrela") 2)
(define (conta-formas-tipo lf tipof)
  (cond
    ;; lista está vazia , então  então devolve 0
    [(empty? lf) 0]
    ;; senão verificar se a forma do tipo do primeiro elemento de lf é do tipo que estou procurando,
    ;; assim, conta 1 e chama a função para o resto da lista, se não só chama o resto da lista.
    [(string=? (forma-tipo (first lf)) tipof)
     (+ 1 (conta-formas-tipo (rest lf) tipof))]

    [else (conta-formas-tipo (rest lf) tipof)]
    )
  )


;; ==============================================================
;; 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7
;; ==============================================================

;; (7) Construa uma função que, dada uma lista de formas, remove formas do mesmo tipo da lista,
;; deixando no máximo uma de cada tipo (a que estiver mais no final da lista).

;; remove-formas-mesmo-tipo: ListaFormas -> ListaFormas
;; Dada uma lista de formas, remove as formas do mesmo tipo da lista, dixando no máximo uma de cada tipo.
;; Em L4 = (S2 S1 T2 T1 C2 C1 R1 R1 T1),
;; os últimos de cada tipo (na ordem original) são S1, T1, C1, R1:
(check-expect
 (remove-formas-mesmo-tipo L4)
 (cons S1 (cons C1 (cons R1 (cons T1 empty)))))

(define (remove-formas-mesmo-tipo lf)
  (cond
    ;; se a lista estiver vazia, então  retornar a lista vazia
    [(empty? lf) empty]

    ;; senão, se existem mais formas desse tipo na lista, chamo a função denovo para o resto da lista.
    [(> (conta-formas-tipo lf (forma-tipo (first lf))) 1)
     (remove-formas-mesmo-tipo (rest lf))]
    ;; é a última desse tipo: inclui o primeiro dessa parte da lista
    [else (cons (first lf) (remove-formas-mesmo-tipo (rest lf)))]
    )
  )

;; ==============================================================
;; 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8
;; ==============================================================
;; (8) Faça uma função chamada desenha-formas-sem-tipos-repetidos que, dada uma lista de formas,
;; gera uma imagem com apenas uma forma de cada tipo desta lista.

;; desenha-formas-sem-tipos-repetidos: ListaFormas -> Imagem
;; dada uma lista de formas, gera uma imagem com apenas uma forma de cada tipo desta lista.
;; Exemplos:

(define (desenha-formas-sem-tipos-repetidos lf)
  (desenha-lista-formas (remove-formas-mesmo-tipo lf))
  )
