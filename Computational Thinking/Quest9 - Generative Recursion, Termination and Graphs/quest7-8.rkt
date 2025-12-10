;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname quest7-8) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
(define-struct nodo (nome vizinhos))
;; Um nodo é um par
;; (make-nodo n v), onde
;; n : String, representa o nome do nodo
;; v : ListaDeString, representa os nodos vizinhos
(define HELENA "Helena")
(define DENVER "Denver")
(define WINNIPEG "Winnipeg")
(define DULUTH "Duluth")
(define OMAHA "Omaha")
(define OKLAHOMA_CITY "Oklahoma City")
(define SANTA_FE "Santa Fé")
(define KANSAS_CITY "Kansas City")
(define LITTLE_ROCK "Little Rock")
(define CHICAGO "Chicago")
(define SAINT_LOUIS "Saint Louis")
(define NASHVILLE "Nashville")
(define SAULT_ST_MARIE "Sault St. Marie")
(define ATLANTA "Atlanta")
(define PITTSBURGH "Pittsburgh")
(define TORONTO "Toronto")

(define HELENA_NODE (make-nodo HELENA (list WINNIPEG DULUTH OMAHA DENVER)))
(define DENVER_NODE (make-nodo DENVER (list HELENA OMAHA KANSAS_CITY OKLAHOMA_CITY SANTA_FE)))
(define SANTA_FE_NODE (make-nodo SANTA_FE (list DENVER OKLAHOMA_CITY)))
(define WINNIPEG_NODE (make-nodo WINNIPEG (list HELENA DULUTH SAULT_ST_MARIE)))
(define DULUTH_NODE (make-nodo DULUTH (list HELENA WINNIPEG OMAHA CHICAGO TORONTO SAULT_ST_MARIE)))
(define OMAHA_NODE (make-nodo OMAHA (list DULUTH HELENA DENVER KANSAS_CITY CHICAGO)))
(define KANSAS_CITY_NODE (make-nodo KANSAS_CITY (list OMAHA DENVER OKLAHOMA_CITY SAINT_LOUIS)))
(define OKLAHOMA_CITY_NODE (make-nodo OKLAHOMA_CITY (list KANSAS_CITY DENVER SANTA_FE LITTLE_ROCK)))
(define LITTLE_ROCK_NODE (make-nodo LITTLE_ROCK (list SAINT_LOUIS OKLAHOMA_CITY NASHVILLE)))
(define SAINT_LOUIS_NODE (make-nodo SAINT_LOUIS (list CHICAGO KANSAS_CITY LITTLE_ROCK NASHVILLE PITTSBURGH)))
(define CHICAGO_NODE (make-nodo CHICAGO (list TORONTO DULUTH OMAHA SAINT_LOUIS PITTSBURGH)))
(define SAULT_ST_MARIE_NODE (make-nodo SAULT_ST_MARIE (list WINNIPEG DULUTH TORONTO)))
(define NASHVILLE_NODE (make-nodo NASHVILLE (list PITTSBURGH SAINT_LOUIS LITTLE_ROCK ATLANTA)))
(define ATLANTA_NODE (make-nodo ATLANTA (list NASHVILLE)))
(define TORONTO_NODE (make-nodo TORONTO (list SAULT_ST_MARIE DULUTH CHICAGO PITTSBURGH)))
(define PITTSBURGH_NODE (make-nodo PITTSBURGH (list TORONTO CHICAGO SAINT_LOUIS NASHVILLE)))

;; Um Grafo é
;; 1. empty, ou
;; 2. (cons n g), onde
;; n : Nodo
;; g : Grafo

(define MAPA
  (list HELENA_NODE DENVER_NODE SANTA_FE_NODE WINNIPEG_NODE DULUTH_NODE OMAHA_NODE KANSAS_CITY_NODE
        OKLAHOMA_CITY_NODE LITTLE_ROCK_NODE SAINT_LOUIS_NODE CHICAGO_NODE SAULT_ST_MARIE_NODE
        NASHVILLE_NODE ATLANTA_NODE TORONTO_NODE PITTSBURGH_NODE))

;; vizinhos: String Grafo ListaDeString -> ListaDeString
;; Dados o nome de um nodo, um grafo e uma lista de nodos já visitados, devolve a lista dos 
;; nomes dos vizinhos do nodo de entrada que
;; não constam da lista de (nomes de nodos de ) entrada
;; Obs.: O nodo dado deve fazer parte do grafo.
(define (vizinhos nome grafo visitadas)
  (cond
    ;; Se o grafo grafo estiver vazio, retornar a lista vazia.
    [(empty? grafo) empty]
    ;; Se o nome do primeiro nodo do grafo for nome, devolve os vizinhos deste nodo
    [(string=? nome (nodo-nome (first grafo))) (subtrai-lista (nodo-vizinhos (first grafo)) visitadas)]

    ;; senão, procura os vizinhos do nome n
    [else (vizinhos nome (rest grafo) visitadas)])
)

;; está-na-lista?: String ListaDeString -> Bool
;; Dados um nome (string) e uma lista de strings,
;; diz se o nome dado está na lista.
(define (está-na-lista? nome lista)
  (cond
    [(empty? lista)  false]
    [(string=? nome (first lista)) true]
    [else (está-na-lista? nome (rest lista))]))
; Exemplos/testes:
(check-expect (está-na-lista? WINNIPEG (nodo-vizinhos HELENA_NODE)) #t)
(check-expect (está-na-lista? SANTA_FE (nodo-vizinhos HELENA_NODE)) #f)


; subtrai-lista: ListaDeStrings ListaDeStrings -> ListaDeString
(define (subtrai-lista l1 l2)
  ; Dadas duas lista de strings, devolve todos os
  ; elementos da primeira lista que não estão na segunda (ou seja,
  ; subtrai a segunda lista da primeira).
  (cond
    [(empty? l1) empty]
    [(está-na-lista? (first l1) l2) (subtrai-lista (rest l1) l2)]
    [else (cons (first l1) (subtrai-lista (rest l1) l2))]
    )
)
(check-expect (subtrai-lista (nodo-vizinhos HELENA_NODE) (nodo-vizinhos DENVER_NODE)) (list WINNIPEG DULUTH DENVER))
(check-expect (subtrai-lista (nodo-vizinhos SANTA_FE_NODE) (nodo-vizinhos WINNIPEG_NODE)) (list DENVER OKLAHOMA_CITY))

;; encontra-caminho: String String Grafo ListaDeString -> ListaDeStringOUFalse
;; Dados os nome das cidades origem e destino, um grafo (mapa) e uma lista de cidades já visitadas,
;; encontra um caminho entre a origem e o destino. Se não existir caminho, devolve false.
;; Obs.: As cidades dadas devem fazer parte do grafo.
;; Testes para encontra-caminho
(check-expect (encontra-caminho ATLANTA NASHVILLE MAPA empty) (list ATLANTA NASHVILLE))
(check-expect (encontra-caminho HELENA HELENA MAPA empty) (list HELENA))
(check-expect (encontra-caminho SANTA_FE SAULT_ST_MARIE MAPA empty)
              (list SANTA_FE DENVER HELENA WINNIPEG DULUTH OMAHA KANSAS_CITY OKLAHOMA_CITY LITTLE_ROCK SAINT_LOUIS CHICAGO TORONTO SAULT_ST_MARIE))
(check-expect (encontra-caminho ATLANTA WINNIPEG MAPA (list NASHVILLE)) false)

(define (encontra-caminho origem destino grafo visitadas)
  (cond
    ;; Se a origem for igual ao destino, retornar a lista com o destino.
    [(string=? origem destino) (list destino)]
    
    [else
     (local
       (
         ;; definir um nome local (visitadas-novo) que guarda os visitados, incluindo a origem
         (define visitadas-novo (cons origem visitadas))
        
         ;; e outro nome que guarda um caminho entre um dos vizinhos não visitados
         ;; do nodo origem e o destino, se existir caminho:
         (define caminho
           (encontra-caminho-vizinhos (vizinhos origem grafo visitadas)
                                      destino
                                      grafo
                                      visitadas-novo))
       )
       ;; e testar este nome local (caminho)
       (cond
         ;; se o caminho for uma lista (foi encontrado um caminho), devolver este
         ;; caminho, colocando o nodo origem na frente
         [(list? caminho) (cons origem caminho)]
         ;; se o nome for um booleano (não há caminho), devolver false
         [else false]
       )
     )]))


;; encontra-caminho-vizinhos: ListaDeString String Grafo ListaDeString -> ListaDeStringOUFalse
;; Dados uma lista de cidades origem, um destino, um grafo (mapa) e uma lista de cidades já visitadas,
;; encontra um caminho entre alguma das origens e o destino. Se não existir caminho, devolve false.
;; Obs.: As cidades dadas devem fazer parte do grafo.
;; Testes para encontra-caminho-vizinhos
;; A primeira origem (Atlanta) já tem um caminho direto
(check-expect (encontra-caminho-vizinhos (list ATLANTA CHICAGO) NASHVILLE MAPA empty)
            (list ATLANTA NASHVILLE))

;; A primeira origem (Winnipeg) está bloqueada, mas a segunda (Atlanta) funciona
(check-expect (encontra-caminho-vizinhos (list WINNIPEG ATLANTA) NASHVILLE MAPA (list DULUTH HELENA SAULT_ST_MARIE))
            (list ATLANTA NASHVILLE))

;; Nenhuma das origens tem um caminho viável
(check-expect (encontra-caminho-vizinhos (list WINNIPEG KANSAS_CITY) ATLANTA MAPA (list DULUTH SAINT_LOUIS)) (list WINNIPEG HELENA OMAHA DENVER KANSAS_CITY OKLAHOMA_CITY LITTLE_ROCK NASHVILLE ATLANTA))

;; A lista de origens está vazia
(check-expect (encontra-caminho-vizinhos empty ATLANTA MAPA empty) false)

(define (encontra-caminho-vizinhos listaOrigens destino grafo visitadas)
  (cond
    ;; Se a lista de origens for vazia, retornar false.
    [(empty? listaOrigens) false]
    
    [else
     (local
       (
         ;; definir um nome local que guarda um caminho entre o primeiro nodo da lista de origens
         ;; e o destino, não passando pelos nodos já visitados, se não existir caminho false é armazenado
         (define caminho
           (encontra-caminho (first listaOrigens)
                             destino
                             grafo
                             visitadas))
       )
       ;; e testar este nome local (caminho):
       (cond
         ;; se o caminho for uma lista (foi encontrado um caminho), devolver este caminho
         [(list? caminho) caminho]
         ;; senão, procurar um caminho entre um nodo do resto da lista de origens até o destino
         [else (encontra-caminho-vizinhos (rest listaOrigens)
                                          destino
                                          grafo
                                          visitadas)]
       )
     )]))

;; monta-caminhos: String ListaDeListaDeString -> ListaDeListaDeString
;; Dados um nome e uma lista de listas de strings, devolve uma lista de listas, onde cada uma
;; das listas tem como primeiro elemento o nome dado na entrada.
(define (monta-caminhos nome lista)
 (cond
   ;; Se a lista de "sub-caminhos" estiver vazia, não há nada a fazer, retorna empty.
   [(empty? lista) empty]

   ;; Caso contrário, processa o primeiro sub-caminho e faz a chamada recursiva para o resto.
   [else
    (cons
      ;; 1. Pega o primeiro sub-caminho e adiciona o 'nome' na frente dele.
      (cons nome (first lista))

      ;; 2. Faz a chamada recursiva para processar o RESTO da lista de sub-caminhos.
      (monta-caminhos nome (rest lista)))]))


;; encontra-todos-caminhos: String String Grafo -> ListaDeListaDeString
;; Função principal que o usuário chama. Ela inicia a busca por todos os caminhos
;; chamando a função auxiliar com uma lista de 'visitados' vazia.
(define (encontra-todos-caminhos origem destino grafo)
  (encontra-todos-caminhos-aux origem destino grafo empty))


;; encontra-todos-caminhos-aux: String String Grafo ListaDeString -> ListaDeListaDeString
;; Encontra TODOS os caminhos da 'origem' ao 'destino', não passando pelas cidades
;; na lista 'visitados'. Retorna uma lista de todos os caminhos encontrados.
(define (encontra-todos-caminhos-aux origem destino grafo visitados)
  (cond
    ;; Caso base: Se a origem é o destino, encontramos 1 caminho completo.
    ;; Retornamos uma lista contendo esse único caminho.
    [(string=? origem destino) (list (list destino))]
    
    [else
     (local
       (
         ;; 1. Encontra todos os vizinhos que podemos visitar.
         (define vizinhos-a-explorar (vizinhos origem grafo visitados))
         
         ;; 2. Encontra TODOS os caminhos a partir DESSES vizinhos.
         (define caminhos-dos-vizinhos
           (encontra-todos-caminhos-vizinhos vizinhos-a-explorar
                                             destino
                                             grafo
                                             (cons origem visitados)))
       )
       ;; 3. Usa 'monta-caminhos' para adicionar a origem atual ao início
       ;;    de cada caminho encontrado a partir dos vizinhos.
       (monta-caminhos origem caminhos-dos-vizinhos)
     )]))



;; encontra-todos-caminhos-vizinhos: ListaDeString String Grafo ListaDeString -> ListaDeListaDeString
;; DADA uma LISTA de origens, encontra todos os caminhos para o destino e junta todos em uma única lista.
(define (encontra-todos-caminhos-vizinhos listaOrigens destino grafo visitados)
  (cond
    ;; Caso base: Se não há mais origens para tentar, não há mais caminhos a adicionar.
    [(empty? listaOrigens) empty]
    
    [else
     ;; CORREÇÃO: As definições locais foram envolvidas em um bloco 'local'.
     (local
       (
         ;; 1. Encontrar todos os caminhos a partir da PRIMEIRA origem da lista.
         (define caminhos-do-primeiro
           (encontra-todos-caminhos-aux (first listaOrigens)
                                        destino
                                        grafo
                                        visitados))
                                        
         ;; 2. Encontrar todos os caminhos a partir do RESTO das origens na lista.
         (define caminhos-do-resto
           (encontra-todos-caminhos-vizinhos (rest listaOrigens)
                                             destino
                                             grafo
                                             visitados))
       )
       ;; 3. Juntar as duas listas de caminhos em uma só.
       (append caminhos-do-primeiro caminhos-do-resto)
     )]))

;; Teste 1: Um único caminho simples.
(check-expect (encontra-todos-caminhos ATLANTA NASHVILLE MAPA)
              (list (list ATLANTA NASHVILLE)))

;; Teste 2: Não há caminho possível pois a única saída está bloqueada.
(check-expect (encontra-todos-caminhos ATLANTA CHICAGO (cons (make-nodo NASHVILLE empty) MAPA))
              empty)
