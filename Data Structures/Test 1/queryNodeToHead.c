#include <stdlib.h>
#include "SinglyLinkedList ADT/SinglyLinkedList.h"


bool queryNodeToHead(Node **head, int targetVal) {
    // Trata os casos em que a lista é vazia, retornando false.
    if (*head == NULL || head == NULL) {
        return false;
    }

    // Caso o primeiro elemento da lista seja o valor procurado, retorna true.
    if ((*head)->nodeInfo.id == targetVal) {
        return true;
    }

    Node *prev = *head;
    // Procura-se pelo nodo anterior ao nodo procurado.
    while (prev->nextNode != NULL && prev->nextNode->nodeInfo.id != targetVal) {
        prev = prev->nextNode;
    }

    // Caso a lista toda seja percorrida e o nodo não foi encontrado, retorna false.
    if (prev->nextNode == NULL) return false;

    // Guarda ponteiro para o nodo procurado.
    Node *targetNode = prev->nextNode;
    
    // Atualiza o ponteiro do nodo anterior ao procurado para o nodo próximo ao procurado.
    prev->nextNode = targetNode->nextNode;

    // Aponto o próximo nodo do nodo procurado para o começo da lista.
    targetNode->nextNode = *head;
    
    // Faz o primeiro elemento da lista ser o nodo procurado.
    *head = targetNode;

    // Neste caso, retorna true.
    return true;
}
