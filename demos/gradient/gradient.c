
#include "../../raylib/include/raylib.h"


int main(){
    const int width = 1200;
    const int height = 800;
    SetTargetFPS(144);
    InitWindow(width,height, "mama");

    const Color grad1 = GetColor(0x051937FF);
    const Color grad2 = GetColor(0x004d7aFF);
    const Color grad3 = GetColor(0x008793FF);
    const Color grad4 = GetColor(0x00bf72FF);
    const Color grad5 = GetColor(0xa8eb12FF);

    while(!WindowShouldClose()){
        for (int i=0; i < height * 7;i++){
        BeginDrawing();
            DrawRectangleGradientV(0, -i, width, height , grad1, grad2);
            DrawRectangleGradientV(0, -i + height, width, height , grad2, grad3);
            DrawRectangleGradientV(0, -i + height * 2, width, height, grad3, grad4);
            DrawRectangleGradientV(0, -i + height * 3, width, height, grad4, grad5);
            DrawRectangleGradientV(0, -i + height * 4, width, height, grad5, grad4);
            DrawRectangleGradientV(0, -i + height * 5, width, height, grad4, grad3);
            DrawRectangleGradientV(0, -i + height * 6, width, height, grad3, grad2);
            DrawRectangleGradientV(0, -i + height * 7, width, height, grad2, grad1);
            ClearBackground(WHITE);
        EndDrawing();
        }
    }
    CloseWindow();
}
