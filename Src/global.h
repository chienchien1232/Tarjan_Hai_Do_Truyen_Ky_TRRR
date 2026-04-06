#ifndef GLOBAL_H
#define GLOBAL_H

#include "raylib.h"
#include <vector>
#include <string>

// Quản lý trạng thái màn hình
enum GameState { MENU, PLAYING, INSTRUCTIONS };
inline GameState currentScreen = MENU;

struct Island {
    int id;
    std::string name;
    Vector2 position;
    const char* imagePath; 
};

// Mảng đảo cố định
inline Island mapIslands[10] = {
    {0, "Cu Lao Xanh", {500, 480}, "Src/sources/photo/island10.png"}, 
    {1, "Cat Ba",      {320, 300}, "Src/sources/photo/island11.png"},
    {2, "Ly Son",      {720, 320}, "Src/sources/photo/island12.png"},
    {3, "Hon Nghe",    {500, 720}, "Src/sources/photo/island3.png"},
    {4, "Co To",       {180, 120}, "Src/sources/photo/island4.png"},
    {5, "Bach Long Vi",{120, 380}, "Src/sources/photo/island5.png"},
    {6, "Hoang Sa",    {900, 200}, "Src/sources/photo/island6.png"},
    {7, "Phu Quoc",    {750, 580}, "Src/sources/photo/island7.png"}, 
    {8, "Con Dao",     {550, 80},  "Src/sources/photo/island 8.png"}, 
    {9, "Nam Du",      {80,  650}, "Src/sources/photo/island9.png"}
};

// Ma trận kề của đồ thị
inline int graph[10][10] = {
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0, 0}
};

#endif