#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

typedef struct {
    Vector2 Posicao;
    Vector2 Tamanho;

    int Municao;
    int Vidas;
    int Pontos;
} Jogador;

void init(Jogador*);
void update(Jogador*);
void draw(Jogador);

int main(void) {
    Jogador jog;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Meu jogador");

    init(&jog);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {  // Detect window close button or ESC key
        update(&jog);
        draw(jog);

    }

    CloseWindow();

    return 0;
}

void init (Jogador *jog) {
    jog->Posicao = (Vector2) {
        (float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2
    };
    jog->Tamanho = (Vector2) {
        50, 50
    };
}

void update (Jogador *jog) {
    if (IsKeyDown(KEY_RIGHT) && jog->Posicao.x+jog->Tamanho.x < SCREEN_WIDTH) {
        jog->Posicao.x += 2.0f;
    }
    if (IsKeyDown(KEY_LEFT) && jog->Posicao.x >= 0) {
        jog->Posicao.x -= 2.0f;
    }
    if (IsKeyDown(KEY_UP) && jog->Posicao.y >= 0) {
        jog->Posicao.y -= 2.0f;
    }
    if (IsKeyDown(KEY_DOWN) && jog->Posicao.y+jog->Tamanho.y < SCREEN_HEIGHT) {
        jog->Posicao.y += 2.0f;
    }
}

void draw (Jogador jog) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Mova o jogador com as setinhas do teclado", 10, 10, 20, DARKGRAY);

    DrawRectangleV(jog.Posicao, jog.Tamanho, MAROON);

    EndDrawing();
}
