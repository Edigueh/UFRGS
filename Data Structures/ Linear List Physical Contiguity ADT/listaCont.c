#include <stdio.h>
#include <stdlib.h>
#include "listaCont.h"

void inicializa(ListaCont *l){
    l->ini = -1;
    l->fim = -1;
}

int tamanho(ListaCont *l){
    if(l->ini == -1 || l->fim == -1) //Lista vazia, tamanho 0
        return 0;

    return l->fim - l->ini + 1;
}

int insere(ListaCont *l, Produto novo, int pos){
    int i;

    if(CAPACIDADE == tamanho(l)) return 0; //lista cheia
    if(pos > tamanho(l) || pos < 0) return 0; //posi��o inv�lida

    if(l->ini == -1){ //Lista previamente vazia, inicializar in�cio e fim
        l->ini = 0;
        l->fim = 0;
    } else if(l->fim < CAPACIDADE - 1) { //Tem espa�o no final
        for(i=l->fim; i >= l->ini + pos; i--)
            l->dados[i+1] = l->dados[i];
        l->fim++;
    } else { //Tem espa�o no come�o
        for(i=l->ini; i < l->ini + pos; i++)
            l->dados[i-1] = l->dados[i];
        l->ini--;
    }
    l->dados[l->ini + pos] = novo;

    return 1;
}

Produto consulta(ListaCont *l, int pos){
    Produto pAux;

    if(pos >= tamanho(l) || pos < 0) //Posi��o inv�lida
        pAux.cod = -1;
    else
        pAux = l->dados[l->ini + pos];

    return pAux;
}

int remover(ListaCont *l, int pos){
    int i;

    if(pos >= tamanho(l) || pos < 0) return 0; //posi��o inv�lida

    if(tamanho(l) == 1){ //Lista s� tinha 1 elemento, agora ficou vazia
        l->ini = -1;
        l->fim = -1;
        return 1;
    }

    for(i=l->ini + pos; i< l->fim; i++) //Puxa elementos do fim
        l->dados[i] = l->dados[i+1];
    l->fim--;

    return 1;
}

void destroi(ListaCont *l)
{
    l->ini = -1;
    l->fim = -1;
}
