#include <stdio.h>
#include <stdlib.h>

#include "DoublyLinkedList.h"

int main(void) {
    int n;

    printf("Quantos produtos você deseja inserir?\n");
    scanf("%d", &n);

    Node* productList = initLinkedList();

    for (int i = 0; i < n; i++) {
        Product productToInsert;
        printf("\nCódigo: "); scanf("%d", &productToInsert.id);
        getchar();
        printf("Nome: "); fgets(productToInsert.name, sizeof(productToInsert.name), stdin);
        printf("Preço: "); scanf("%f", &productToInsert.price);
        productList = insertProduct(productList, productToInsert);
        printf("\n");
    }


    printList(productList);

    productList = removeProductById(productList, 3);

    printListReverse(productList);
    
    destroyLinkedList(productList);

    return EXIT_SUCCESS;
}
