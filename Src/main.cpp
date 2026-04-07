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
        UpdateGameAudio();

        BeginDrawing();
            ClearBackground(BLACK);

            // Điều hướng màn hình
            if (currentScreen == MENU) {
                DrawStartMenu();
            } 
            else if (currentScreen == CHOOSE_ALGORITHM) {
                DrawChooseAlgorithmScreen();
            }
            else if (currentScreen == CHOOSE_ISLAND) {
                DrawChooseIslandScreen();
            }
            else if (currentScreen == PLAYING) {
                DrawGameplayScreen();
            }
            else if (currentScreen == RESULT) {
                DrawResultScreen();
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