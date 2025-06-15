#reader(lib "htdp-intermediate-reader.ss" "lang")((modname vscode-lab5) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
;; h: Número -> String
(define (h n)
   (cond
            [(<= n 0) "Zero"]
            [(= n 1) "Um"]
            [(= n 2) (string-append (h (h1 n)) (h (h2 n)))]
            [else (string-append (h (h3 n)) "*")]))

;; h1,h2,h3: Número -> Número
(define (h1 n) (- n 1))
(define (h2 n) (- n 2))
(define (h3 n) (round (/ n 2)))
