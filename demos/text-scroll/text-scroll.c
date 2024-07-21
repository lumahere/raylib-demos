#include "../../raylib/include/raylib.h"

const int width = 1200;
const int height = 800;

int main(){
    InitWindow(width, height,  "hello");

    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTextEx(GetFontDefault(), "Hello", (Vector2){0,height / 2.0f}, 30, 2.0f, GRAY);
        ClearBackground(WHITE);
        EndDrawing();
    }
    CloseWindow();
}
