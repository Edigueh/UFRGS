#lang racket

(println "hello world")

(define (my-add a b)
        (+ a b))

(my-add 1 2)

(struct person [fname lname age id alive] #:transparent)

(person "bob" "smith" 44 32 false)
