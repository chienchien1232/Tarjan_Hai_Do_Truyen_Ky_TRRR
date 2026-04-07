#ifndef GLOBAL_H
#define GLOBAL_H

#include "raylib.h"
#include <vector>
#include <string>
#include <set>

inline Texture2D shipTexture;
// Các trạng thái màn hình chính
enum GameState { MENU, CHOOSE_ALGORITHM, CHOOSE_ISLAND, PLAYING, RESULT, INSTRUCTIONS };
inline GameState currentScreen = MENU;

// Các trạng thái trong game
enum AlgorithmType { NONE, DFS_TYPE };
inline AlgorithmType selectedAlgorithm = NONE;
inline int selectedStartIsland = -1;
inline int currentVisitingIsland = -1;
inline int currentTraversalIndex = -1;

enum GraphToolMode { TOOL_PICK_START, TOOL_ADD_VERTEX, TOOL_DELETE_VERTEX, TOOL_ADD_EDGE, TOOL_DELETE_EDGE };
inline GraphToolMode currentGraphTool = TOOL_PICK_START;
inline int firstEdgeVertex = -1;
inline bool stepByStepMode = false;
inline bool manualAdvanceRequested = false;

// Hệ thống rewards
struct Reward {
    int articulation_points = 0;  // Phần thưởng từ cut vertex
    int bridges = 0;               // Phần thưởng từ bridge
};

inline Reward playerRewards;
inline Reward rewardTargets = { 3, 2 };  // Mục tiêu: 3 articulation points, 2 bridges
inline std::vector<int> traversalPath;   // Đường đi DFS
inline std::set<int> visitedIslands;     // Những đảo đã viếng thăm
inline std::set<int> articulationPointsList;  // Danh sách cut vertex
inline std::set<std::pair<int, int>> bridgesList;  // Danh sách bridge

inline const int defaultGraph[10][10] = {
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, {1, 0, 1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 0, 0, 1, 0, 0, 0}, {1, 1, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0, 1, 0}, {0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 0, 1, 0}
};

inline int graph[10][10] = {
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, {1, 0, 1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 0, 0, 1, 0, 0, 0}, {1, 1, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0, 1, 0}, {0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 0, 1, 0}
};

inline bool vertexActive[10] = { true, true, true, true, true, true, true, true, true, true };

inline void ResetGraphToDefault() {
    for (int i = 0; i < 10; i++) {
        vertexActive[i] = true;
        for (int j = 0; j < 10; j++) {
            graph[i][j] = defaultGraph[i][j];
        }
    }
    selectedStartIsland = -1;
    currentGraphTool = TOOL_PICK_START;
    firstEdgeVertex = -1;
    manualAdvanceRequested = false;
    stepByStepMode = false;
}

inline void EnsureEdgeSymmetry() {
    for (int i = 0; i < 10; i++) {
        graph[i][i] = 0;
        for (int j = i + 1; j < 10; j++) {
            int value = (graph[i][j] != 0 || graph[j][i] != 0) ? 1 : 0;
            graph[i][j] = value;
            graph[j][i] = value;
        }
    }
}

struct Island {
    int id;
    std::string name;
    Vector2 position;
    const char* imagePath; 
};
const std::vector<Island> mapIslands = {
    {0, "Cu Lao Xanh", {500, 480}, "Src/sources/photo/island10.png"}, 
    {1, "Cat Ba",      {320, 300}, "Src/sources/photo/island11.png"},
    {2, "Ly Son",      {720, 320}, "Src/sources/photo/island12.png"},
    {3, "Hon Nghe",    {500, 720}, "Src/sources/photo/island3.png"},
    {4, "Co To",       {180, 120}, "Src/sources/photo/island4.png"},
    {5, "Bach Long Vi",{120, 380}, "Src/sources/photo/island5.png"},
    {6, "Hoang Sa",    {900, 200}, "Src/sources/photo/island6.png"},
    {7, "Phu Quoc",    {750, 580}, "Src/sources/photo/island7.png"}, 
    // ĐÃ CHỈNH: Con Dao dich ra giua hon (x tu 80 tang len 250)
    {8, "Con Dao",     {550, 80},  "Src/sources/photo/island 8.png"}, 
    {9, "Nam Du",      {80,  650}, "Src/sources/photo/island9.png"}
};

#endif