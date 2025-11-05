#include <stdlib.h>

typedef struct Node {
    int id;
    struct Node *right, *left;
} Node;

/**
 * Encontra o Ancestral Comum Mais Baixo (LCA) de dois nós (v e w)
 * em uma Árvore Binária de Pesquisa (ABP).
 * @param r Ponteiro para o nó raiz da (sub)árvore atual.
 * @param v O valor do primeiro nó.
 * @param w O valor do segundo nó.
 * @return Ponteiro para o nó que é o LCA de v e w.
 */
Node* lowestCommonAncestor(Node *r, int v, int w) {
    // Caso base: Se a árvore estiver vazia, não há LCA.
    if (r == NULL) return NULL;

    // Garante que 'min' seja o menor valor e 'max' o maior,
    // independentemente da ordem em que v e w foram passados.
    int max, min;
    if (v > w) {
        max = v;
        min = w;
    } else {
        max = w;
        min = v;
    }

    // --- O Ponto Chave da Lógica ---
    
    // CASO 1: O nó atual é o "ponto de divisão" (split point).
    // Se o id do nó atual está entre os dois valores (inclusive),
    // então este nó é o primeiro ancestral comum a ambos.
    // (Também cobre o caso onde o LCA é um dos próprios nós).
    if (r->id >= min && r->id <= max) {
        return r;
    }

    // CASO 2: Ambos os valores (min e max) são menores que o nó atual.
    // Se o id do nó atual é maior que o valor máximo, então
    // ambos os nós (v e w) devem estar na subárvore ESQUERDA.
    // A condição (r->id > min) é redundante, mas inofensiva.
    if (r->id > max) { // (r->id > min && r->id > max) é o mesmo que (r->id > max)
        return lowestCommonAncestor(r->left, v, w);
    } 
    
    // CASO 3: Ambos os valores (min e max) são maiores que o nó atual.
    // Se não for o CASO 1 nem o CASO 2, só pode significar que
    // o id do nó atual é menor que o valor mínimo (r->id < min).
    // Portanto, ambos os nós (v e w) devem estar na subárvore DIREITA.
    else {
        return lowestCommonAncestor(r->right, v, w);
    }
}

int queryLevel(Node *r, int k) {
    if (r == NULL) return 0;

    if (r->id == k) {
        return 1;
    }

    if (r->id > k) {
        int leftLevel = queryLevel(r->left, k);
        if (leftLevel > 0) return 1 + leftLevel;
        else return 0;
    }

    if (r->id < k) {
        int rightLevel = queryLevel(r->right, k);
        if (rightLevel > 0) return 1 + rightLevel;
        else return 0;
    }
}
