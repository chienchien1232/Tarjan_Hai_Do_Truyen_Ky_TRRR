#ifndef GLOBAL_H
#define GLOBAL_H

#include "raylib.h"
#include <vector>
#include <string>

// Cấu trúc dữ liệu cho một hòn đảo
struct Island {
    int id;                 // ID của đảo (0, 1, 2...)
    std::string name;       // Tên đảo
    Vector2 position;       // Tọa độ x, y để vẽ trên màn hình
    Color color;            // Màu sắc hiển thị
};

// Cấu trúc để định nghĩa một đường đi giữa 2 đảo (Cạnh của đồ thị)
struct Edge {
    int u, v;               // Nối từ đảo u sang đảo v
};

// Danh sách 9 hòn đảo cố định cho dự án "Tarjan Hải Đồ"
/* toạ độ cũ 1200 x 850
const std::vector<Island> mapIslands = {
    {0, "Phu Quoc", {200, 600}, DARKBROWN},
    {1, "Con Dao", {400, 700}, DARKBROWN},
    {2, "Ly Son", {900, 400}, DARKBROWN},
    {3, "Cat Ba", {800, 150}, DARKBROWN},
    {4, "Co To", {1000, 100}, DARKBROWN},
    {5, "Nam Du", {300, 750}, DARKBROWN},
    {6, "Phu Quy", {600, 650}, DARKBROWN},
    {7, "Cu Lao Cham", {850, 350}, DARKBROWN},
    {8, "Binh Ba", {700, 550}, DARKBROWN}
};
*/
// test toạ độ mới 1920 x 1080
const std::vector<Island> mapIslands = {
    {0, "Phu Quoc", {300, 850}, DARKBROWN},
    {1, "Con Dao", {700, 900}, DARKBROWN},
    {2, "Ly Son", {1400, 500}, DARKBROWN},
    {3, "Cat Ba", {1200, 200}, DARKBROWN},
    {4, "Co To", {1600, 150}, DARKBROWN},
    {5, "Nam Du", {500, 950}, DARKBROWN},
    {6, "Phu Quy", {1000, 800}, DARKBROWN},
    {7, "Cu Lao Cham", {1350, 400}, DARKBROWN},
    {8, "Hoang Sa", {1700, 450}, DARKBROWN}
};
// Danh sách các đường đi mẫu (để nhóm Thuật toán bắt đầu chạy Tarjan)
const std::vector<Edge> mapEdges = {
    {0, 5}, {5, 1}, {1, 6}, {6, 8}, {8, 2}, {2, 7}, {7, 3}, {3, 4}
};

#endif