#include "raylib.h"

int main(void){
    // Largura da tela
    const int screenWidth = 800;
    // Altura da tela
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Meu texto");
    // Defina nosso jogo para rodar a 60 quadros por segundo
    SetTargetFPS(60);
    // Detectar botão de fechar janela ou tecla ESC
    while (!WindowShouldClose()){
    BeginDrawing();
    // Limpa a tela
    ClearBackground(RAYWHITE);
    // Desenha um texto na tela na posição 190x200,
    // tamnho da fonte 20 e cor cinza
    DrawText("Texto", 190, 200, 20, GRAY);
    // Desenha um retângulo na posição 360x100
    // de tamanho 80x80 e cor vermelho
    DrawRectangle(screenWidth/2 - 40, 100, 80, 80, RED);
    EndDrawing();
    }
    // Fecha a janela
    CloseWindow();
    return 0;
}
