#include "global.h"
#include <iostream>
#include "Graphics/IslandRender.h"
#include "Graphics/Background.h"
int main() {
    // 1. Cấu hình cửa sổ game mới (Full HD)
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    
    // Khởi tạo cửa sổ


    InitWindow(screenWidth, screenHeight, "Tarjan Hai Do Truyen Ky - Team 3");

    SetTargetFPS(60);
    LoadGameBackground(); // <--- THÊM DÒNG NÀY
    // 2. Vòng lặp game chính
    while (!WindowShouldClose()) {
        // --- Cập nhật logic (Update) ---
        // Tại đây bạn có thể thêm logic kiểm tra va chạm chuột vào các đảo sau này
        
        // --- Vẽ đồ họa (Drawing) ---
        BeginDrawing();
        
        DrawGameBackground(); // đổi nền
        // Vẽ tiêu đề game
        DrawText("DO HOA TRO CHOI: TARJAN HAI DO", 20, 20, 25, GOLD);

        DrawText("Team 3 - PTIT Project", 20, 55, 18, LIGHTGRAY);


        // A. Vẽ các đường đi (Edges) - Vẽ trước để nằm dưới các hòn đảo
        for (const auto& edge : mapEdges) {
            Vector2 startPos = mapIslands[edge.u].position;
            Vector2 endPos = mapIslands[edge.v].position;
            
            // Vẽ đường nối giữa 2 đảo.
            DrawLineEx(startPos, endPos, 4.0f, DARKGRAY);
            
            // Vẽ mũi tên hoặc hướng đi (tùy chọn)
            DrawCircleV(endPos, 5, MAROON); 
        }

        // B. Vẽ các hòn đảo (Islands)
        for (const auto& island : mapIslands) {
            // Vẽ bóng đổ cho vòng tròn
            DrawCircleV({island.position.x + 3, island.position.y + 3}, 22, BLACK);
            
            // Vẽ vòng tròn đại diện đảo
            DrawCircleV(island.position, 20, island.color);
            DrawCircleLinesV(island.position, 20, RAYWHITE); // Viền trắng cho đảo

            // Hiển thị tên đảo (căn lề để chữ nằm giữa phía dưới đảo)
            int textWidth = MeasureText(island.name.c_str(), 16);
            DrawText(island.name.c_str(), 
                     (int)island.position.x - textWidth / 2, 
                     (int)island.position.y + 25, 
                     16, RAYWHITE);

            // Hiển thị ID của đảo ngay tâm vòng tròn
            DrawText(TextFormat("%d", island.id), 
                     (int)island.position.x - 5, 
                     (int)island.position.y - 8, 
                     18, WHITE);
        }

        // Hướng dẫn thao tác
        DrawRectangle(20, screenHeight - 40, 250, 30, Fade(SKYBLUE, 0.3f));
        DrawText("Nhan ESC de thoat", 30, screenHeight - 33, 15, RAYWHITE);

        EndDrawing();
    }

    // 3. Đóng cửa sổ và giải phóng bộ nhớ
    UnloadGameBackground();
    CloseWindow();

    return 0;
}