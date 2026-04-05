#include "Graphics/Background.h"

int main() {
    // 1. Khởi tạo cửa sổ
    InitWindow(1280, 900, "Tarjan Hai Do Truyen Ky - Team 7");
    SetTargetFPS(60);

    // 2. Load tài nguyên (Hàm này nằm trong Background.h)
    InitGameMap(); 

    // 3. Vòng lặp game
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);

            // Điều hướng màn hình
            if (currentScreen == MENU) {
                DrawStartMenu();
            } 
            else if (currentScreen == PLAYING) {
                DrawGameMap();
            } 
            else if (currentScreen == INSTRUCTIONS) {
                DrawInstructions();
            }

        EndDrawing();
    }

    // 4. Giải phóng và đóng
    CloseGameMap(); 
    CloseWindow();

    return 0;
}