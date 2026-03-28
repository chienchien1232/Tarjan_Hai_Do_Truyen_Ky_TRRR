#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../global.h"

// Biến tĩnh để lưu trữ hình ảnh nền (Texture)
static Texture2D backgroundTexture;

// 1. Hàm Tải hình ảnh từ thư mục Assets
void LoadGameBackground() {
    backgroundTexture = LoadTexture("Assets/biendao.png"); 
    
    // Kiểm tra nếu không tìm thấy ảnh
    if (backgroundTexture.id == 0) {
        TraceLog(LOG_ERROR, "KHONG TIM THAY FILE: Assets/biendao.png");
    }
}

// 2. Hàm Vẽ hình ảnh nền ra màn hình
void DrawGameBackground() {
    if (backgroundTexture.id != 0) {
        // Vẽ ảnh co giãn theo kích thước màn hình hiện tại
        DrawTexturePro(
            backgroundTexture, 
            { 0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height }, // Vùng ảnh gốc
            { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },               // Vùng vẽ (toàn màn hình)
            { 0, 0 }, 
            0.0f, 
            WHITE
        );
    } else {
        ClearBackground(DARKGRAY); 
    }
}

// 3. Hàm Giải phóng bộ nhớ ảnh (Quan trọng để tránh tốn RAM)
void UnloadGameBackground() {
    UnloadTexture(backgroundTexture);
}

#endif