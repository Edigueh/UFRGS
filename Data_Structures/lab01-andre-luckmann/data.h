// TAD PONTO (x, y)
/* TIPO DE DADO exportado */
typedef struct {
    float x, y;
} Ponto;

/* OPERAÇÕES Exportadas */

// Cria um ponto atribuindo valores às suas coordenadas.
void criaPto(Ponto *p, float x, float y);

// Calcula e retorna a distância entre dois pontos.
float distPto(Ponto p1, Ponto p2);

// Desloca um ponto no plano, somando dx à coordenada x e dy à coordenada y.
void transladaPto(Ponto *p, float dx, float dy);
