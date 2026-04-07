#ifndef ISLAND_CONTROLLER_H
#define ISLAND_CONTROLLER_H
#include "raylib.h"
#include "global.h"



// Trạng thái đảo
enum IslandState {
    NORMAL,
    HOVERED,
    DELETING,
    DELETED
};

struct IslandRuntime {
    IslandState state = NORMAL;
    float alpha = 1.0f; // dùng cho fade animation
};

inline IslandRuntime islandState[10];

// ===== Lấy đảo đang hover =====
inline int GetIslandAtMouse(Vector2 mouse) {
    for (int i = 0; i < 10; i++) {
        if (islandState[i].state == DELETED) continue;

        float dx = mouse.x - mapIslands[i].position.x;
        float dy = mouse.y - mapIslands[i].position.y;

        if (dx*dx + dy*dy <= 30*30)
            return i;
    }
    return -1;
}

// ===== Xóa đảo (có animation) =====
inline void StartDeleteIsland(int u) {
    if (u < 0 || u >= 10) return;
    if (islandState[u].state == DELETED) return;

    islandState[u].state = DELETING;
}

// ===== Update logic =====
inline void UpdateIslands() {
    Vector2 mouse = GetMousePosition();

    // reset hover
    for (int i = 0; i < 10; i++) {
        if (islandState[i].state == NORMAL)
            islandState[i].state = NORMAL;
    }

    int hover = GetIslandAtMouse(mouse);
    if (hover != -1 && islandState[hover].state == NORMAL) {
        islandState[hover].state = HOVERED;
    }

    // click để chọn
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (hover != -1) {
            StartDeleteIsland(hover);
        }
    }

    // animation fade-out
    for (int i = 0; i < 10; i++) {
        if (islandState[i].state == DELETING) {
            islandState[i].alpha -= 0.05f;

            if (islandState[i].alpha <= 0.0f) {
                islandState[i].state = DELETED;

                // xóa cạnh
                for (int j = 0; j < 10; j++) {
                    graph[i][j] = 0;
                    graph[j][i] = 0;
                }
            }
        }
    }
}

// ===== Check active =====
inline bool IsIslandVisible(int i) {
    return islandState[i].state != DELETED;
}

// ===== HÀM VẼ THUYỀN (THAY THẾ HÌNH TRÒN) =====
inline void DrawMovingShip(Vector2 currentPos) {
   

    // Vẽ thuyền thay thế:
    float scale = 0.3f; // Bạn có thể điều chỉnh độ to nhỏ của thuyền ở đây
    Rectangle source = { 0, 0, (float)shipTexture.width, (float)shipTexture.height };
    Rectangle dest = { currentPos.x, currentPos.y, shipTexture.width * scale, shipTexture.height * scale };
    Vector2 origin = { (shipTexture.width * scale) / 2, (shipTexture.height * scale) / 2 };

    DrawTexturePro(shipTexture, source, dest, origin, 0.0f, WHITE);
}

#endif