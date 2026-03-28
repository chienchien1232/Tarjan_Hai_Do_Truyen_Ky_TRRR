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
const std::vector<Island> mapIslands = {
    {0, "Phu Quoc", {250, 700}, DARKBROWN},
    {1, "Con Dao", {550, 750}, DARKBROWN},
    {2, "Ly Son", {1200, 450}, DARKBROWN},
    {3, "Cat Ba", {1000, 150}, DARKBROWN},
    {4, "Co To", {1400, 100}, DARKBROWN},
    {5, "Nam Du", {400, 800}, DARKBROWN},
    {6, "Phu Quy", {850, 650}, DARKBROWN},
    {7, "Cu Lao Cham", {1100, 350}, DARKBROWN},
    {8, "Hoang Sa", {1450, 400}, DARKBROWN}
};
// Danh sách các đường đi mẫu (để nhóm Thuật toán bắt đầu chạy Tarjan)
const std::vector<Edge> mapEdges = {
    {0, 5}, {5, 1}, {1, 6}, {6, 8}, {8, 2}, {2, 7}, {7, 3}, {3, 4}
};

#endif