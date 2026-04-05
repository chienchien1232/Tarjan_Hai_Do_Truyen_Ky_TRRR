#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../global.h"

static Texture2D bgTexture;
static Texture2D islandTextures[10];
static Texture2D menuBg;

// 1. Hàm vẽ nút bấm (Giữ nguyên của bạn)
bool DrawMenuButton(Rectangle rect, const char* text, Color baseColor, Color hoverColor) {
    Vector2 mousePos = GetMousePosition();
    bool isHover = CheckCollisionPointRec(mousePos, rect);
    DrawRectangleRec(rect, isHover ? hoverColor : baseColor);
    DrawRectangleLinesEx(rect, 2, RAYWHITE);
    DrawText(text, rect.x + (rect.width - MeasureText(text, 20))/2, rect.y + 15, 20, WHITE);
    return (isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

// 2. Hàm khởi tạo tài nguyên
void InitGameMap() {
    menuBg = LoadTexture("Src/sources/photo/start_menu_bg.png"); 
    bgTexture = LoadTexture("Src/sources/photo/Gemini_Generated_Image_krqxy9krqxy9krqx.png");
    for (int i = 0; i < 10; i++) {
        islandTextures[i] = LoadTexture(mapIslands[i].imagePath);
    }
}

// 3. Hàm vẽ Menu chính (Chỉ giữ lại 1 hàm)
void DrawStartMenu() {
    DrawTexturePro(menuBg, (Rectangle){ 0, 0, (float)menuBg.width, (float)menuBg.height },
                   (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);

    DrawText("TARJAN HAI DO TRUYEN KY", GetScreenWidth()/2 - MeasureText("TARJAN HAI DO TRUYEN KY", 35)/2, 150, 35, GOLD);

    if (DrawMenuButton({ (float)GetScreenWidth()/2 - 125, 350, 250, 50 }, "1. BAT DAU", BLUE, DARKBLUE)) {
        currentScreen = PLAYING;
    }

    if (DrawMenuButton({ (float)GetScreenWidth()/2 - 125, 430, 250, 50 }, "2. HUONG DAN", DARKGREEN, LIME)) {
        currentScreen = INSTRUCTIONS;
    }
}

// 4. Hàm vẽ Hướng dẫn
void DrawInstructions() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.9f));
    DrawText("HUONG DAN TRO CHOI", GetScreenWidth()/2 - MeasureText("HUONG DAN TRO CHOI", 30)/2, 100, 30, GOLD);
    
    int startY = 200;
    DrawText("- Click vao cac hon dao de chon diem bat dau.", 150, startY, 20, RAYWHITE);
    DrawText("- Thuat toan Tarjan tim cac thanh phan lien thong manh.", 150, startY + 40, 20, RAYWHITE);
    DrawText("- Su dung Menu ben phai de dieu khien thuat toan.", 150, startY + 80, 20, RAYWHITE);

    if (DrawMenuButton({ (float)GetScreenWidth()/2 - 100, 600, 200, 50 }, "DA HIEU", RED, MAROON)) {
        currentScreen = MENU;
    }
}

// 5. Hàm vẽ Bản đồ Game (Bổ sung phần thiếu của bạn)
void DrawGameMap() {
    // Vẽ nền Map
    DrawTexturePro(bgTexture, (Rectangle){ 0, 0, (float)bgTexture.width, (float)bgTexture.height },
                   (Rectangle){ 0, 0, 1000, (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);

    // Vẽ Panel bên phải
    DrawRectangle(1000, 0, 280, GetScreenHeight(), ColorAlpha(DARKGRAY, 0.98f));
    DrawText("MENU CHUC NANG", 1025, 30, 22, GOLD);
    
    if (DrawMenuButton({ 1020, 820, 240, 45 }, "QUAY LAI", GRAY, DARKGRAY)) {
        currentScreen = MENU;
    }

    // Vẽ đường nối (Graph)
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (graph[i][j] == 1) DrawLineEx(mapIslands[i].position, mapIslands[j].position, 3.0f, Fade(SKYBLUE, 0.5f));
        }
    }

    // Vẽ Đảo (Phần code của Chiến)
    float imgSize = 110.0f; 
    for (int i = 0; i < 10; i++) {
        Vector2 pos = mapIslands[i].position;
        if (islandTextures[i].id > 0) {
            DrawTexturePro(islandTextures[i],
                (Rectangle){ 0, 0, (float)islandTextures[i].width, (float)islandTextures[i].height },
                (Rectangle){ pos.x - imgSize/2, pos.y - imgSize/2, imgSize, imgSize },
                (Vector2){ 0, 0 }, 0.0f, WHITE);
        } else {
            DrawCircleV(pos, 25, GOLD);
        }
        DrawText(mapIslands[i].name.c_str(), pos.x - MeasureText(mapIslands[i].name.c_str(), 16)/2, pos.y + 65, 16, RAYWHITE);
    }
}

// 6. Giải phóng bộ nhớ
void CloseGameMap() {
    UnloadTexture(bgTexture);
    UnloadTexture(menuBg);
    for (int i = 0; i < 10; i++) UnloadTexture(islandTextures[i]);
}

#endif