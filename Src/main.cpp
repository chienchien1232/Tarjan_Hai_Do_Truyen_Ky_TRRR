#include "raylib.h"
#include "Global.h" // Nhớ include file này để lấy dữ liệu 9 đảo

int main() {
    InitWindow(1200, 800, "Tarjan Hai Do Truyen Ky - Version 1.0");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Logic xử lý có thể viết thêm ở đây
        
        BeginDrawing();
            ClearBackground(SKYBLUE); // Màu nước biển

            // Dùng vòng lặp vẽ tất cả các đảo từ Global.h
            for (const auto& island : mapIslands) {
                // Vẽ bóng đổ cho đảo
                DrawCircle(island.position.x + 3, island.position.y + 3, 30, Fade(BLACK, 0.3f));
                // Vẽ đảo chính
                DrawCircleV(island.position, 30, island.color);
                // Vẽ tên đảo
                DrawText(island.name.c_str(), island.position.x - 40, island.position.y + 35, 15, WHITE);
            }

            DrawText("Dung chuot de kham pha cac hon dao!", 20, 20, 20, DARKBLUE);
            
            // Vẽ con thuyền tại vị trí chuột
            DrawTriangle({GetMousePosition().x, GetMousePosition().y - 10}, 
                         {GetMousePosition().x - 10, GetMousePosition().y + 10}, 
                         {GetMousePosition().x + 10, GetMousePosition().y + 10}, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}