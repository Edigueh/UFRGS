#include "data.h"
#include <math.h>

// Cria um ponto atribuindo valores às suas coordenadas.
void criaPto(Ponto *p, float x, float y) {
    p->x = x;
    p->y = y;
}

// Calcula e retorna a distância entre dois pontos.
float distPto(Ponto p1, Ponto p2) {
    double delta_x = fabs(p1.x - p2.x);
    double delta_y = fabs(p1.y - p2.y);

    return sqrt(pow(delta_x, 2) + pow(delta_y, 2));
}

// Desloca um ponto no plano, somando dx à coordenada x e dy à coordenada y.
void transladaPto(Ponto *p, float dx, float dy) {
    p->x += dx;
    p->y += dy;
}
