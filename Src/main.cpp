#include "Graphics/Background.h"
#include "IslandController.h"
int main() {
    // 1. Khởi tạo cửa sổ
    InitWindow(1280, 900, "Tarjan Hai Do Truyen Ky - Team 7");
    SetTargetFPS(60);

    // 2. Load tài nguyên
    InitGameMap(); 

    // 3. Vòng lặp game
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);

            if (currentScreen == MENU) DrawStartMenu();
            else if (currentScreen == PLAYING) DrawGameMap();
            else if (currentScreen == INSTRUCTIONS) DrawInstructions();

        EndDrawing();
    }

    // 4. Đóng và dọn dẹp
    CloseGameMap(); 
    CloseWindow();

    return 0;
}