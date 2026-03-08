#include "raylib.h"

#define MAX_INPUT_CHARS 9
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

int init(int, char*);
int update(int, char*);
void draw(int, char*);

int main(void) {
    char nome[MAX_INPUT_CHARS + 1]="\0";
    int contLetras;
    char *nomep;

    nomep=nome;

    contLetras = init(contLetras, nomep);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Meu nome");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {
        contLetras=update(contLetras, nomep);
        draw(contLetras, nomep);
    }

    CloseWindow();

    return 0;
}

int init (int contLetras, char *nomep) {
    nomep = "\0";      // NOTE: One extra space required for line ending char '\0'
    contLetras = 0;

    return contLetras;
}

int update(int contLetras, char *nomep) {
    // Set the window's cursor to the I-Beam

    // Get char pressed (unicode character) on the queue
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0) {
        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (contLetras < MAX_INPUT_CHARS)) {
            nomep[contLetras] = (char)key;
            contLetras++;
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        contLetras--;
        if (contLetras < 0)
            contLetras = 0;
        nomep[contLetras] = '\0';
    }

    return contLetras;
}

void draw(int contLetras, char *nomep) {
    Rectangle textBox = { SCREEN_WIDTH/2 - 100, 180, 225, 50 };

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Digite o seu nome com 9 caracteres", 240, 140, 20, GRAY);

    DrawRectangleRec(textBox, LIGHTGRAY);
    DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, RED);

    DrawText(nomep, textBox.x + 5, textBox.y + 8, 40, MAROON);

    DrawText(TextFormat("NUM DE CHARS: %i/%i", contLetras, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);


    if (contLetras < MAX_INPUT_CHARS) {
        // Draw blinking underscore char
        DrawText("_", textBox.x + 8 + MeasureText(nomep, 40), textBox.y + 12, 40, MAROON);
    } else
        DrawText("Pressione BACKSPACE para deletar chars...", 210, 300, 20, GRAY);

    EndDrawing();
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed() {
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126))
        keyPressed = true;

    return keyPressed;
}
