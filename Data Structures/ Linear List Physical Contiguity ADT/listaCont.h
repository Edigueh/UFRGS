#define CAPACIDADE 50

typedef struct {
    int cod;
    char nome[50];
    float preco;
} Produto;

typedef struct {
    int ini;
    int fim;
    Produto dados[CAPACIDADE];
} ListaCont;

void inicializa(ListaCont *l);
int tamanho(ListaCont *l);
int insere(ListaCont *l, Produto novo, int pos);
Produto consulta(ListaCont *l, int pos);
int remover(ListaCont *l, int pos);
void destroi(ListaCont *l);
