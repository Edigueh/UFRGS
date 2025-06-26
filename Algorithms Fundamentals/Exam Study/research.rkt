#reader(lib "htdp-intermediate-reader.ss" "lang")((modname quest7-8) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))

(define-struct artigo (titulo autores texto))
;; Um artigo do conjunto Artigo é uma estrutura
;; (make-artigo t aut txt)
;; onde t : Simbolo, é o título do artigo;
;; aut : Lista-de-simbolos , é a lista de autores do artigo; e
;; txt : Texto-cientifico, é o texto do artigo.

;; Uma Lista-de-simbolos é
;; 1) empty ou
;; 2) (cons s ls), onde s é Simbolo e ls é Lista-de-símbolos

;; Um Texto-cientifico é
;; 1) empty, ou
;; 2) (cons s tc), onde s é um Símbolo e tc é do tipo Texto-científico;
;; 3) (cons a tc), onde a é um Artigo, e tc é do tipo Texto-cientifico.

;  (1 ponto) Defina as constantes A1 e A2 como dois elementos (não triviais) do tipo Artigo e
; TC1 e TC2 como dois elementos (não triviais) do tipo Texto-cientifico. Você pode usar
; essas constantes nos exemplos das funções a seguir.

(define TC1 (list 'Este 'eh 'um 'texto 'cientifico))
(define A1 (make-artigo 'Artigo1 (list 'Andre 'Arthur) TC1))
(define TC2 (list 'Mais 'um 'texto 'cientifico A1))
(define A2 (make-artigo 'Artigo2 (list 'Lucas 'Vitor) TC2))

; (2 pontos) Desenvolva uma função que recebe um artigo e um símbolo. A função deve
; retornar o número total de ocorrências do símbolo no próprio artigo e em todos os artigos
; referenciados a partir do artigo inicial (passado como parâmetro). Note que se A referencia
; B, e B referencia C, então C é referenciado a partir do artigo inicial A

;; ocorrencias-simbolo: Artigo Símbolo -> Número
;; Dados um artigo e um símbolo, retorna o número total
;; de ocorrências do símbolo no próprio artigo e em todos os artigos
;; referenciados a partir do artigo inicial (parâmetro).
(define (ocorrencias-simbolo art sym)
  (ocorrencias-simbolo-texto (artigo-texto art) sym)
  )
;; Exemplos/testes:
(check-expect (ocorrencias-simbolo A1 'Mais) 0)
(check-expect (ocorrencias-simbolo A2 'um) 2)
(check-expect (ocorrencias-simbolo A2 'cientifico) 2)

;; ocorrencias-simbolo-texto: Texto-cientifico Símbolo -> Número
;; Dados um Texto-cientifico e um símbolo, retorna o número total
;; de ocorrências do símbolo no próprio Texto-cientifico e em todos os artigos
;; referenciados no Texto-cientifico inicial (parâmetro).
(define (ocorrencias-simbolo-texto txt sym)
  (cond
    [(empty? txt) 0]
    [(and (symbol? (first txt)) (symbol=? (first txt) sym))
     (+ 1 (ocorrencias-simbolo-texto (rest txt) sym))]
    [(symbol? (first txt)) (ocorrencias-simbolo-texto (rest txt) sym)]
    [(artigo? (first txt))
     (+ (ocorrencias-simbolo (first txt) sym)
        (ocorrencias-simbolo-texto (rest txt) sym)
        )]
    )
  )
;; Exemplos/testes:
(check-expect (ocorrencias-simbolo-texto TC1 'texto) 1)
(check-expect (ocorrencias-simbolo-texto TC2 'texto) 2)

; (c) (2 pontos) Para fazer estatísticas sobre as palavras contidas em artigos, pode-se utilizar
; funções que, dados um artigo, uma palavra e um número, compara este número com o
; número de ocorrências da palavra no artigo (ou em artigos referenciados por ele).
; Para não termos que fazer uma função para cada tipo de comparação possível, seria interessante termos uma função genérica, que recebe, além dos argumentos acima,
; o critério de comparação que deve ser usado.
; Faça uma função de alta-ordem para implementar esta análise de um
; artigo. Construa uma critério de comparação (diferente dos operadores relacionais <, >, =,
; etc), e use seu critério como um dos exemplos na definição da função de alta-ordem.

;; criterio-metade: Número Número -> Booleano
;; Dados dois números, indica se o segundo número é metade do primeiro.
(define (criterio-metade n1 n2)
    (= n2 (/ n1 2))
)
(check-expect (criterio-metade 4 2) true)
(check-expect (criterio-metade 2 4) false)
;; ehPlagio: Número Número -> String
(define (ehPlagio numOcorrencias numLim)
 (cond
    [(>= numOcorrencias numLim) "É plágio"]
    [else "Não é Plágio"]
 )
)

;; analisa-artigo: Artigo Símbolo Número (Número Número -> Tipo) -> Tipo
;; Dado um artigo, uma palavra, e um número, compara este número com o número de ocorrências da palavra no artigo
;; (ou em artigos referenciados por ele) utilizando a função genérica passada como parâmetro.
;; Dessa forma, indica se o artigo indica a ocorrencia do criterio ou não.
(define (analisa-artigo art pal fun-criterio num)
  (fun-criterio (ocorrencias-simbolo art pal) num)
)

;; Exemplos/teste:
(check-expect (analisa-artigo A1 'Mais > 1) false)
(check-expect (analisa-artigo A2 'um < 3) true)
(check-expect (analisa-artigo A2 'cientifico criterio-metade 1) true)
(check-expect (analisa-artigo A2 'cientifico criterio-metade 2) false)
(check-expect (analisa-artigo A2 'cientifico ehPlagio 1) "É plágio")
(check-expect (analisa-artigo A2 'cientifico ehPlagio 3) "Não é Plágio")

; (d) (2 pontos) Desenvolva um algoritmo que, dada uma palavra e um artigo, retorna os nomes
; dos autores que citaram esta palavra no texto de seus artigos. A pesquisa deve englobar
; todos artigos referenciados a partir do artigo recebido (incluindo este). Se a palavra não
; ocorrer em nenhum artigo, a função deve retornar false.

;; Uma ListaDeSímbolosOUBooleano é:
;; 1) Uma ListaDeSímbolos, OU
;; 2) Um Booleano.

;; autores-que-citam: Símbolo Artigo -> ListaDeSímbolosOUBooleano
;; Dada uma palavra e um artigo, retorna os nomes
;; dos autores que citaram esta palavra no texto de seus artigos. A pesquisa deve englobar
;; todos artigos referenciados a partir do artigo recebido (incluindo este). Se a palavra não
;; ocorrer em nenhum artigo, a função deve retornar false.
;; Exemplos/testes:
(check-expect (autores-que-citam 'Este A1) (list 'Andre 'Arthur))
(check-expect (autores-que-citam 'Mais A2) (list 'Lucas 'Vitor))
(check-expect (autores-que-citam 'um A2) (list 'Lucas 'Vitor 'Andre 'Arthur))
(check-expect (autores-que-citam 'banana A2) false)

(define (autores-que-citam pal art)
    (cond
        [(empty? (busca-autores pal art)) false]
        [else (busca-autores pal art)]
    )
)

;; busca-autores: Símbolo Artigo -> ListaDeSímbolos
;; Dada uma palavra e um artigo, retorna os autores que citaram essa palavra no texto científico desse artigo ou sub-artigo.
;; Exemplos/testes:
(check-expect (busca-autores 'Este A1) (list 'Andre 'Arthur))
(check-expect (busca-autores 'Mais A2) (list 'Lucas 'Vitor))
(check-expect (busca-autores 'um A2) (list 'Lucas 'Vitor 'Andre 'Arthur))
(check-expect (busca-autores 'banana A2) empty)

(define (busca-autores pal art)
    (cond 
        [(= 0 (ocorrencias-simbolo art pal)) empty]
        [else (append (artigo-autores art)
                      (busca-autores-texto pal (artigo-texto art)))]
    )
)

;; busca-autores-texto: Símbolo Texto-científico -> ListaDeSímbolos
;; Dada uma palavra e um texto científico, retorna a lista de autores que citaram essa palavra em seus textos científicos ou sub-textos.
;; Exemplos/testes:
(check-expect (busca-autores-texto 'Este TC1) empty)
(check-expect (busca-autores-texto 'um TC2) (list 'Andre 'Arthur))
(check-expect (busca-autores-texto 'banana TC2) empty)

(define (busca-autores-texto pal txt)
    (cond
        [(empty? txt) empty]
        [(symbol? (first txt)) (busca-autores-texto pal (rest txt))]
        [(artigo? (first txt)) 
            (append
                (busca-autores pal (first txt))
                (busca-autores-texto pal (rest txt))
            )
        ]
    )
)
