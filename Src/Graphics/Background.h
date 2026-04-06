#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../global.h"

// Biến static để quản lý tài nguyên
static Texture2D islandTextures[10];
static Texture2D bgTexture, menuBg, instructionBg, buttonFrame, sidePanelBg, inventoryBg; 

// 1. Hàm vẽ nút bấm dùng ảnh nền
bool DrawMenuButton(Rectangle rect, const char* text) {
    Vector2 mousePos = GetMousePosition();
    bool isHover = CheckCollisionPointRec(mousePos, rect);
    
    Color tint = isHover ? WHITE : LIGHTGRAY; 

    DrawTexturePro(buttonFrame, 
        (Rectangle){ 0, 0, (float)buttonFrame.width, (float)buttonFrame.height },
        rect, (Vector2){ 0, 0 }, 0.0f, tint);

    DrawText(text, rect.x + (rect.width - MeasureText(text, 20)) / 2, rect.y + (rect.height / 2 - 10), 20, GOLD);

    return (isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

// 2. Khởi tạo tài nguyên
void InitGameMap() {
    menuBg = LoadTexture("Src/sources/photo/start_menu_bg.png"); 
    bgTexture = LoadTexture("Src/sources/photo/background.png");
    buttonFrame = LoadTexture("Src/sources/photo/button.png");
    instructionBg = LoadTexture("Src/sources/photo/background_tutorial.png"); 
    sidePanelBg = LoadTexture("Src/sources/photo/side_panel.png");
    inventoryBg = LoadTexture("Src/sources/photo/bag.png");

    for (int i = 0; i < 10; i++) {
        islandTextures[i] = LoadTexture(mapIslands[i].imagePath);
        if (islandTextures[i].id == 0) {
            TraceLog(LOG_WARNING, "Khong the tai anh dao: %s", mapIslands[i].imagePath);
        }
    }
}

// 3. Vẽ Menu chính
void DrawStartMenu() {
    DrawTexturePro(menuBg, (Rectangle){ 0, 0, (float)menuBg.width, (float)menuBg.height },
                   (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    
    if (DrawMenuButton({ (float)GetScreenWidth()/2 - 125, 350, 250, 60 }, "1. BAT DAU")) currentScreen = PLAYING;
    if (DrawMenuButton({ (float)GetScreenWidth()/2 - 125, 430, 250, 60 }, "2. HUONG DAN")) currentScreen = INSTRUCTIONS;
}

// 4. Vẽ Hướng dẫn
void DrawInstructions() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.6f));
    
    Rectangle destRect = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };
    DrawTexturePro(instructionBg, (Rectangle){ 0, 0, (float)instructionBg.width, (float)instructionBg.height },
                   destRect, (Vector2){ 0, 0 }, 0.0f, WHITE);

    const char* title = "HUONG DAN TRO CHOI";
    DrawText(title, destRect.x + (destRect.width - MeasureText(title, 35)) / 2, destRect.y + 60, 35, GOLD);

    const char* lines[] = {
        "- Nhan 'BAT DAU' de khoi hanh chuyen du hanh.",
        "- Click vao cac hon dao de thiet lap lo trinh.",
        "- Thuat toan Tarjan se tim cac vung lien thong manh.",
        "- Nhan 'QUAY LAI' trong game de tro ve Menu."
    };
    
    for (int i = 0; i < 4; i++) {
        DrawText(lines[i], destRect.x + 100, destRect.y + 160 + (i * 50), 22, WHITE);
    }
    
    if (DrawMenuButton({ (float)GetScreenWidth()/2 - 100, destRect.y + destRect.height - 100, 200, 55 }, "DA HIEU")) {
        currentScreen = MENU;
    }
}

// 5. Vẽ Bản đồ 
void DrawGameMap() {
    // Bước 1: Vẽ nền bản đồ chính (Bên trái)
    DrawTexturePro(bgTexture, (Rectangle){ 0, 0, (float)bgTexture.width, (float)bgTexture.height },
                   (Rectangle){ 0, 0, 1000, (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);

    // --- PHẦN BỊ THIẾU CỦA BẠN ĐÃ ĐƯỢC THÊM LẠI Ở ĐÂY ---
    // Bước 2: Vẽ đường nối giữa các đảo
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (graph[i][j]) DrawLineEx(mapIslands[i].position, mapIslands[j].position, 2.5f, Fade(SKYBLUE, 0.4f));
        }
    }

    // Bước 3: Vẽ các hòn đảo
    for (int i = 0; i < 10; i++) {
        Vector2 p = mapIslands[i].position;
        if (islandTextures[i].id > 0) {
            DrawTexturePro(islandTextures[i], (Rectangle){0,0,(float)islandTextures[i].width, (float)islandTextures[i].height},
                           (Rectangle){p.x - 55, p.y - 55, 110, 110}, (Vector2){0,0}, 0, WHITE);
        } else {
            DrawCircleV(p, 30, GOLD);
        }
        DrawText(mapIslands[i].name.c_str(), p.x - MeasureText(mapIslands[i].name.c_str(), 16)/2, p.y + 60, 16, RAYWHITE);
    }
    // ----------------------------------------------------

    // Bước 4: Vẽ Panel điều khiển (Bên phải)
    DrawTexturePro(sidePanelBg, 
        (Rectangle){ 0, 0, (float)sidePanelBg.width, (float)sidePanelBg.height },
        (Rectangle){ 1000, 0, 280, (float)GetScreenHeight() }, 
        (Vector2){ 0, 0 }, 0.0f, WHITE);

    float panelX = 1020; 
    float screenH = (float)GetScreenHeight();
    float btnH = 45;
    float spacing = 10;
    
    float resetY = screenH - 130; 
    float ketThucY = resetY - (btnH + spacing);
    float batDauY = ketThucY - (btnH + spacing);
    float bfsY = batDauY - (btnH + spacing);
    float dfsY = bfsY - (btnH + spacing);
    float choiY = dfsY - (btnH + spacing);

    // 1. Nhóm nút chức năng
    if (DrawMenuButton({ panelX, choiY, 240, btnH }, "CHOI")) { /* Logic */ }
    if (DrawMenuButton({ panelX, dfsY, 240, btnH }, "DFS")) { /* Logic */ }
    if (DrawMenuButton({ panelX, bfsY, 240, btnH }, "BFS")) { /* Logic */ }
    if (DrawMenuButton({ panelX, batDauY, 250, btnH }, "CHON DIEM BAT DAU")) { /* Logic */ }
    if (DrawMenuButton({ panelX, ketThucY, 250, btnH }, "LOAI BO HON DAO")) { /* Logic */ }
    if (DrawMenuButton({ panelX, resetY, 240, btnH }, "RESET")) { /* Logic */ }

    // 2. Vẽ Túi đồ
    float bagSize = 290;
    Rectangle inventoryRect = { panelX - 17, choiY - bagSize - 10, bagSize, bagSize }; 
    DrawTexturePro(inventoryBg, (Rectangle){ 0, 0, (float)inventoryBg.width, (float)inventoryBg.height }, inventoryRect, (Vector2){ 0, 0 }, 0.0f, WHITE);

    // 3. Nút QUAY LAI
    if (DrawMenuButton({ panelX, screenH - 70, 240, btnH }, "QUAY LAI")) {
        currentScreen = MENU;
    }
}

void CloseGameMap() {
    UnloadTexture(sidePanelBg);
    UnloadTexture(bgTexture); 
    UnloadTexture(menuBg);
    UnloadTexture(instructionBg); 
    UnloadTexture(buttonFrame);
    UnloadTexture(inventoryBg);
    for (int i = 0; i < 10; i++) UnloadTexture(islandTextures[i]);
}

#endif