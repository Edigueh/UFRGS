#reader(lib "htdp-intermediate-reader.ss" "lang")((modname vscode-lab3) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
;; Nome: André Schaidhauer Luckmann

;; ==============================================================
;; 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
;; ==============================================================
;; ============================
;; DEFINIÇÕES DE TIPOS DE DADOS
;; ============================
;;   TIPO RETANGULO:
(define-struct retangulo (lado1 lado2 cor nome))
;; Um elemento de Retangulo tem o formato
;;    (make-retangulo  l1 l2 c n), onde
;;     l1: Número, é a largura do retângulo;
;;     l2: Número, é a altura do retângulo;
;;     c : String, é a cor do retângulo;
;;     n : String, é o nome do retângulo.
;; Constantes do tipo Retangulo:
(define R1 (make-retangulo 30 60 "red" "R1"))
(define R2 (make-retangulo 40 40 "green" "R2"))

;;   TIPO TRIANGULO:
(define-struct triangulo (lado cor nome))
;; Um elemento de Triangulo tem o formato
;;    (make-triangulo  l c n), onde
;;     l: Número, é o lado do triângulo;
;;     c : String, é a cor do triângulo;
;;     n : String, é o nome do triângulo.
;; Constantes do tipo Triangulo:
(define T1 (make-triangulo 30  "blue" "T1"))
(define T2 (make-triangulo 40  "red" "T2"))

;;   TIPO CIRCULO:
(define-struct circulo (raio cor nome))
;; Um elemento de Circulo tem o formato
;;    (make-circulo  r c n), onde
;;     r: Número, é o raio do circulo;
;;     c : String, é a cor do circulo;
;;     n : String, é o nome do circulo.
;; Constantes do tipo Circulo:
(define C1 (make-circulo 20  "pink" "S1"))
(define C2 (make-circulo 30  "red" "S2"))

;; Uma Forma pode ser
  ;; 1. um Retangulo, ou
  ;; 2. um Triangulo, ou
  ;; 3. um Circulo

;; Uma ListaDeFormas é
;; 1. vazia (empty), ou
;; 2. (cons f lf), onde
;;     f : Forma
;;    lf : ListaDeFormas

;; Uma ListaDeString é
;; 1. vazia (empty), ou
;; 2. (cons f lf), onde
;;     f : String
;;    lf : ListaDeString

;; Constantes do tipo ListaDeFormas:
  (define L1 (cons C1 empty))
  (define L2 (cons C1 (cons C2 (cons T1 (cons T2 (cons R1 (cons R2 empty)))))))
  (define L3 (cons T1 (cons T1 (cons R2 (cons T1 (cons R1 (cons T2 (cons R1 empty))))))))
  (define L4 (cons C2 (cons C2 (cons C2 (cons T2 empty)))))

;; =====================
;; DEFINIÇÕES DE FUNÇÕES
;; =====================

;; desenha : Forma -> Imagem
;; Dada uma forma, gera uma imagem desta forma.
;; Exemplos:
;; (desenha C1) = .
;; (desenha (T2) = .
  (define (desenha f)
    (cond
      [(retangulo? f) (rectangle (retangulo-lado1 f) (retangulo-lado2 f) "solid" (retangulo-cor f))]
      [(triangulo? f) (triangle  (triangulo-lado f)  "solid" (triangulo-cor f))]
      [(circulo? f)   (circle    (circulo-raio f)    "solid" (circulo-cor f))]))
;; Testes:
(check-expect (desenha C1) (circle   20 "solid" "pink"))
(check-expect (desenha T2) (triangle 40 "solid" "red"))

;; ==============================================================
;; A A A A A A A A A ==> lista-retangulos
;; ==============================================================
;; lista-retangulos : ListaFormas -> ListaFormas
;; Obj: Dada uma lista de formas, devolve uma lista com todos os retangulos
;;      da lista original.
;; Exemplos:
;;  (lista-retangulos L4) =  empty
;;  (lista-retangulos L2) = (cons R1 (cons R2 empty))
(define (lista-retangulos lf)
    (filter retangulo? lf)
)

;; Testes:
(check-expect (lista-retangulos L1)   empty)
(check-expect (lista-retangulos L2)  (cons R1 (cons R2 empty)))
(check-expect (lista-retangulos L3)  (cons R2 (cons R1 (cons R1 empty))))
(check-expect (lista-retangulos L4)   empty)

;; ==============================================================
;; B B B B B B B B  ==> lista-nomes-retangulos
;; ==============================================================
;; lista-nomes-retangulos : ListaDeFormas -> ListaDeString
;; Obj: Dada uma lista de formas, devolve uma lista com os nomes de todos os retangulos
;;      da lista original.
;; Exemplos:
;;  (lista-nomes-retangulos L3) =  empty
;;  (lista-nomes-retangulos L2) = (cons "E1" (cons "E2" empty))
(define (lista-nomes-retangulos lf)
    (map retangulo-nome (lista-retangulos lf))
)
;; Testes:
(check-expect (lista-nomes-retangulos L1) empty)
(check-expect (lista-nomes-retangulos L2) (cons "R1" (cons "R2" empty)))
(check-expect (lista-nomes-retangulos L3) (cons "R2" (cons "R1" (cons "R1" empty))))
(check-expect (lista-nomes-retangulos L4) empty)

;; Função auxiliar para desenhar e combinar imagens (para foldl)
;; Combina a imagem acumulada com a imagem atual, mantendo a ordem.
(define (combine-images-beside accumulated-img current-img)
  (beside accumulated-img current-img))

;; ==============================================================
;; C C C C C C C C  ==> lista-retangulos-img
;; ==============================================================
;; lista-retangulos-img : ListaDeFormas -> Imagem
;; Obj: Dada uma lista de formas, devolve uma imagem com todos
;;       os retangulos da lista original, na ordem em que
;;       eles aparecem na lista.
;; Exemplo: (lista-retangulos-img L2) = .
(define (lista-retangulos-img lf)
  ;; Mapeia os retângulos para imagens e depois combina-os da esquerda para a direita
  (foldl combine-images-beside
         empty-image
         (map desenha (lista-retangulos lf))))

;; Testes:
(check-expect (lista-retangulos-img L1) empty-image) ; L1 não tem retângulos
(check-expect (lista-retangulos-img L2) (beside (desenha R2) (desenha R1))) ; Se a ordem desejada for R2 R1
(check-expect (lista-retangulos-img L3) (beside (desenha R1) (beside (desenha R1) (desenha R2))))
(check-expect (lista-retangulos-img L4) empty-image)

;; ==============================================================
;; D D D D D D D D ==> soma-raios-circulos
;; ==============================================================
;; soma-raios-circulos : ListaDeFormas -> Numero
;; Obj:Dada uma lista de formas, devolve a soma dos tamanhos dos raios dos circulos da lista.
;; Exemplo: (soma-raios-circulos L2) = 50
(define (soma-raios-circulos lf)
  ; (cond
  ;   ;; se lf for vazia, devolver zero
  ;   [(empty? lf) 0]
  ;   ;; se o primeiro elemento de lf for um circulo,
  ;   ;; somar o raio deste circulo a soma dos raios dos circulos do resto da lista lf  
  ;   [(circulo? (first lf))
  ;         (+ (circulo-raio (first lf))(soma-raios-circulos (rest lf)))]
  ;   ;; senão, devolver a soma dos raios dos circulos do resto da lista lf  
  ;   [else (soma-raios-circulos(rest lf))])
  (foldl + 0 (map circulo-raio (filter circulo? lf)))
)
;; Testes:
(check-expect (soma-raios-circulos L1) 20)
(check-expect (soma-raios-circulos L2) 50)
(check-expect (soma-raios-circulos L3)  0)
(check-expect (soma-raios-circulos L4) 90)

;; ==============================================================
;; E E E E E E E E ==> desenha-lista-formas
;; ==============================================================
;; desenha-lista-formas: ListaDeFormas -> Imagem
;; Obj: Dada uma lista de formas, monta uma imagem com todas as formas lado a lado,
;; na mesma ordem na qual elas aparecem na lista.
;; Exemplos:
;;  (desenha-lista-formas L2) = .
;;  (desenha-lista-formas L3) = .
(define (desenha-lista-formas lf)
    (foldl beside empty-image (foldl cons empty (map desenha lf)))
)
;; Testes:
(check-expect (desenha-lista-formas L1) (desenha C1))
(check-expect (desenha-lista-formas L2) (beside (desenha C1) (beside (desenha C2) (beside (desenha T1) (beside (desenha T2) (beside (desenha R1) (desenha R2)))))))
(check-expect (desenha-lista-formas L3) (beside (desenha T1) (beside (desenha T1) (beside (desenha R2) (beside (desenha T1) (beside (desenha R1) (beside (desenha T2) (desenha R1))))))))
(check-expect (desenha-lista-formas L4) (beside (desenha C2) (beside (desenha C2) (beside (desenha C2) (desenha T2)))))

;; ==============================================================
;; 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
;; ==============================================================

;; ============================================
;; DEFINIÇÕES DE TIPOS DE DADOS
;; ============================================

;; ------------------
;; TIPO ARQUIVO:
;; ------------------
(define-struct arquivo (nome tamanho)) 
;; Um elemento do conjunto Arquivo tem o formato
;;  (make-arquivo n t), onde
;;    n: String, é o nome do arquivo
;;    t: Numero,  o espaço de memória ocupado pelo arquivo.

;; ------------------
;; TIPO CONTEUDO:
;; ------------------
;; Um Conteudo é
;; 1. empty,
;; 2. (cons a lc), onde a: Arquivo e lc: Conteudo
;; 3. (cons d lc), onde d: Diretorio e lc: Conteudo

;; ------------------
;; TIPO DIRETORIO:
;; ------------------
(define-struct diretorio (nome conteudo))
;; Um elemento do conjunto Diretorio tem o formato
;;  (make-diretorio n c), onde
;;    n: String, é o nome do diretório
;;    c: Conteudo, é o conteúdo do diretório

;; Exemplos de arquivos:

(define ARQ-geratestes (make-arquivo "gera-testes.sh" 10))
(define ARQ-lista1   (make-arquivo "lista1.rkt" 50))
(define ARQ-lista2   (make-arquivo "lista2.rkt" 30))
(define ARQ-lista3   (make-arquivo "lista3.rkt" 20))
(define ARQ-lista4   (make-arquivo "lista4.rkt" 50))

;; Exemplos de diretórios e conteúdos:

(define CONT-LISTAS (list ARQ-geratestes ARQ-lista1 ARQ-lista2 ARQ-lista3 ARQ-lista4))
                                                    
(define LISTAS (make-diretorio "Listas"  CONT-LISTAS))

(define CONT-VIDEOS  (list
                          (make-arquivo "aula1.mp4" 550 )
                          (make-arquivo "aula2.mp4" 300 )
                          (make-arquivo "aula3.mp4" 250 )))

(define VIDEOAULAS  (make-diretorio "Videoaulas"  CONT-VIDEOS))

(define AULAS (make-diretorio "Aulas"
                              (list VIDEOAULAS (make-arquivo "texto1.pdf" 120 ))))

(define CONT-INF  (list (make-arquivo "plano-de-ensino.tex" 60)
                        (make-arquivo "cronograma.xls" 150)
                        AULAS
                        LISTAS
                        (make-arquivo "texto1.pdf" 120)))

(define INF05008 (make-diretorio "INF05008"  CONT-INF))


;; =========================================================================
;;                                 QUESTÃO 2 (a)
;; =========================================================================
;; arquivo-encontrado?: Conteúdo String -> Booleano
;; Obj: dados o Conteudo de um diretorio e um nome de arquivo, verifica se existe
;; um arquivo com este nome neste conteúdo de diretório, sem considerar subdiretorios
;; Exemplos/testes: 
(check-expect (arquivo-encontrado? CONT-INF "texto1.pdf") #t)
(check-expect (arquivo-encontrado? CONT-INF "texto2.pdf") #f)
(check-expect (arquivo-encontrado? CONT-INF "aula3.mp4") #f)


(define (arquivo-encontrado? content name);; Dados um conteúdo de diretório e um nome de arquivo
 (cond
        ; se o conteudo for vazio, devolve falso
       [(empty? content) #f]
        ; se o primeiro elemento do conteudo for um arquivo,
       [(arquivo? (first content))
         (cond
               ; se este arquivo tiver o nome procurado (ARQ), devolve true
              [(string=? (arquivo-nome (first content)) name) #t]
               ; senão, verifica se há no resto do conteúdo um arquivo com o nome procurado
              [else (arquivo-encontrado? (rest content) name)])]
       [else ;; senão verifica se existe um arquivo com este nome no resto do conteudo 
              (arquivo-encontrado? (rest content) name)])
)



;; =========================================================================
;;                                 QUESTÃO 2 (b)
;; =========================================================================
;; arquivo-encontrado-na-arvore?: Diretório String -> Booleano
;; Obj: dados um diretorio e um nome de arquivo, verifica se existe
;; um arquivo com este nome neste diretório, considerando subdiretorios
;; Exemplos/testes: 
(check-expect (arquivo-encontrado-na-arvore? INF05008 "texto1.pdf") #t)
(check-expect (arquivo-encontrado-na-arvore? INF05008 "texto2.pdf") #f)
(check-expect (arquivo-encontrado-na-arvore? INF05008 "aula3.mp4") #t)


(define (arquivo-encontrado-na-arvore? DIR N-ARQ);; Dados um diretório DIR e um nome de arquivo N-ARQ
    ; verifica se existe um arquivo com o nome N-ARQ no conteúdo do diretorio DIR
    (arquivo-encontrado-no-conteudo? (diretorio-conteudo DIR) N-ARQ)
)

;; arquivo-encontrado-no-conteudo?: Conteudo String -> Booleano
;; Obj: dados um conteudo e um nome de arquivo, verifica se existe
;; um arquivo com este nome neste conteudo, considerando subdiretorios
;; Exemplos/testes: 
(check-expect (arquivo-encontrado-no-conteudo? CONT-INF "texto1.pdf") #t)
(check-expect (arquivo-encontrado-no-conteudo? CONT-INF "texto2.pdf") #f)
(check-expect (arquivo-encontrado-no-conteudo? CONT-INF "aula3.mp4") #t)


(define (arquivo-encontrado-no-conteudo? CONT N-ARQ);; Dados um conteúdo CONT e um nome de arquivo N-ARQ
 (cond
        ; se o conteudo CONT for vazio, devolve falso
       [(empty? CONT) #f]
        ; se o primeiro elemento do conteudo CONT for um arquivo,
       [(arquivo? (first CONT))
           (cond ;; se este arquivo tiver o nome procurado (N-ARQ), devolve true
             [(string=? (arquivo-nome (first CONT)) N-ARQ) #t]
               ; senão, verifica se há no resto do conteúdo um arquivo com o nome N-ARQ
              [else (arquivo-encontrado-no-conteudo? (rest CONT) N-ARQ)])]
       ; se o primeiro elemento de CONT for um diretorio,
       [(diretorio? (first CONT))
             ; se verifica se existe um arquivo com o nome N-ARQ
            (or
               ; ou neste primeiro diretorio do conteudo CONT
              (arquivo-encontrado-na-arvore? (first CONT) N-ARQ)
               ; ou no resto do conteudo CONT
              (arquivo-encontrado-no-conteudo? (rest CONT) N-ARQ))]))


;; =========================================================================
;;                                 QUESTÃO 2 (d)
;; =========================================================================

;; conta-arquivos: Diretorio String -> Número
;; Obj: dados um diretorio e um nome de arquivo, conta quanto arquivos
;; com este nome há neste diretório, considerando subdiretorios
;; Exemplos/testes: 
(check-expect (conta-arquivos INF05008 "texto1.pdf") 2)
(check-expect (conta-arquivos INF05008 "texto2.pdf") 0)
(check-expect (conta-arquivos INF05008 "aula3.mp4") 1)


; Dados um diretório DIR e um nome de arquivo N-ARQ
(define (conta-arquivos DIR N-ARQ)
    ; devolve o número de vezes que o arquivo com o nome N-ARQ ocorre no conteúdo do diretorio DIR
    (conta-arquivos-no-conteudo (diretorio-conteudo DIR) N-ARQ)
)

; conta-arquivos-no-conteudo: Conteúdo String -> Número
; Obj: dados um conteudo e um nome de arquivo, devolve o número de vezes que
; um arquivo com este nome ocorre neste conteudo, considerando subdiretorios
; Exemplos/testes: 
(check-expect (conta-arquivos-no-conteudo CONT-INF "texto1.pdf") 2)
(check-expect (conta-arquivos-no-conteudo CONT-INF "texto2.pdf") 0)
(check-expect (conta-arquivos-no-conteudo CONT-INF "aula3.mp4") 1)


; Dados um conteúdo CONT e um nome de arquivo N-ARQ
(define (conta-arquivos-no-conteudo CONT N-ARQ)
    (cond
        ; se o conteudo CONT for vazio, devolve zero
        [(empty? CONT) 0]
        ; senão soma
        [else (+
            ; o número de vezes que o arquivo N-ARQ ocorre no primeiro elemento de CONT:
            (cond
                ; se o primeiro elemento de CONT for um arquivo e o seu nome for N-ARQ, soma 1
                [(and (arquivo? (first CONT)) (string=? (arquivo-nome (first CONT)) N-ARQ)) 1]
                ; se o primeiro elemento de CONT for um diretorio, soma o numero de vezes que N-ARQ ocorre neste diretorio
                [(diretorio? (first CONT)) (conta-arquivos (first CONT) N-ARQ)]
                ; senão, soma zero
                [else 0]
            )
            ; com o número de vezes que N-ARQ ocorre no resto de CONT
            (conta-arquivos-no-conteudo (rest CONT) N-ARQ)
        )]
    )
)

;; =========================================================================
;;                                 QUESTÃO 2 (e)
;; =========================================================================

(define-struct resultado (dir msg))
;; Um elemento do conjunto Resultado tem o formato
  ;; (make-resultado d m), onde
  ;; d : Diretorio , é um diretório
  ;; m : String, é a mensagem representando se o arquivo substitui um anterio ou foi apenas inserido

;; insere-arquivo: Diretorio Arquivo -> Diretorio
;; Dado um diretorio e um arquivo, insere este arquivo no diretório.
;; Caso já exista arquivo com este nome, o arquivo é removido e o novo é inserido e a
  ;; mensagem "Arquivo substituido" é gerada. Caso não exista arquivo com este nome,
  ;; o arquivo é inserido e a mensagem "Arquivo inserido" é gerada.

;; Exemplos/testes:
   (check-expect (insere-arquivo INF05008 (make-arquivo "texto2.pdf" 200))
                 (make-resultado
                      (make-diretorio "INF05008"  (append CONT-INF (list (make-arquivo "texto2.pdf" 200))))
                       "Arquivo inserido"))
   (check-expect (insere-arquivo VIDEOAULAS (make-arquivo "aula1.mp4" 300))
                 (make-resultado
                       (make-diretorio "Videoaulas" 
                                (list
                                 (make-arquivo "aula1.mp4" 300 )
                                 (make-arquivo "aula2.mp4" 300 )
                                 (make-arquivo "aula3.mp4" 250 )))
                       "Arquivo substituido")) 


;; Dados um diretorio DIR  e um arquivo ARQ
(define (insere-arquivo DIR ARQ)
  ;; monta um resultado com
  (make-resultado
       ;; o arquivo  ARQ inserido no conteúdo do diretório DIR
       (make-diretorio (diretorio-nome DIR)
       (insere-arquivo-conteudo (diretorio-conteudo DIR) ARQ))
       ;; a msg adequada, dependendo da existência ou não do arquivo:
       (cond
            ;; se existe arquivo com o nome de ARQ no diretório DIR,  "Arquivo substituido"
            [(arquivo-encontrado? (diretorio-conteudo DIR) (arquivo-nome ARQ))  "Arquivo substituido"]
            ;; senão, "Arquivo inserido"
            [else "Arquivo inserido"]
       )
  )
)

; insere-arquivo-conteudo: Conteudo Arquivo -> Conteudo
; Dado um conteudo e um arquivo, insere o arquivo no conteudo.
; Se ja existir arquivo com este nome, ele é removido e o novo é inserido.
; Exemplos/testes:
   (check-expect (insere-arquivo-conteudo CONT-VIDEOS (make-arquivo "aula1.mp4" 300))
                                (list
                                 (make-arquivo "aula1.mp4" 300 )
                                 (make-arquivo "aula2.mp4" 300)
                                 (make-arquivo "aula3.mp4" 250)))

; Dados um conteudo CONT e um conteudo ARQ
(define (insere-arquivo-conteudo CONT ARQ)
  (cond
    ; se o conteudo CONT for vazio, devolve um cons de empty com o ARQ.
    [(empty? CONT) (cons ARQ empty)]
    ; se o primeiro elemento do conteudo for um diretorio,
    [(diretorio? (first CONT))  
    ;    constroi um conteudo com este diretorio e com a lista de conteudo inserindo o arquivo ARQ no resto do conteudo
         (cons (first CONT) (insere-arquivo-conteudo (rest CONT) ARQ))]
    ; se o primeiro elemento do conteudo for um arquivo com mesmo nome de ARQ,
    [(and (arquivo? (first CONT)) (string=? (arquivo-nome (first CONT)) (arquivo-nome ARQ)))
    ;    devolve uma lista de conteudo contendo ARQ e o resto do conteudo
         (cons ARQ (rest CONT))]
    ; senao, constrói uma lista com o arquivo do primeiro elemento de CONT com o resto do conteudo.
    ; Aqui, assumimos que o arquivo não tem o mesmo nome, logo deve ser incluido junto no diretorio.
    [else (cons (first CONT) (insere-arquivo-conteudo (rest CONT) ARQ))]
  )
)

