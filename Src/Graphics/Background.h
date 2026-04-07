#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../global.h"
#include "../Algorithms/Tarjan.h"
#include <cmath>
#include <cstring>
#include <queue>
#include <cstdio>
#include <initializer_list>
#include <utility>
#include <thread>
#include <chrono>

extern "C" __declspec(dllimport) int __stdcall Beep(unsigned int frequency, unsigned int duration);

static Texture2D bgTexture;
static Texture2D islandTextures[10];
static Texture2D specialtyTextures[10];
static Texture2D menuBg;
static Texture2D tutorialBgTexture;
static Texture2D panelTexture;
static Texture2D buttonTexture;
static Texture2D bagTexture;
static Texture2D keyTexture;
static Texture2D completeKeyTexture;
static Texture2D chestTexture;
static Sound uiClickSfx = { 0 };
static Sound rewardSpecialtySfx = { 0 };
static Sound rewardKeySfx = { 0 };
static Sound rewardComboSfx = { 0 };
static Music bgmMusic = { 0 };
static bool uiClickSfxLoaded = false;
static bool rewardSpecialtySfxLoaded = false;
static bool rewardKeySfxLoaded = false;
static bool rewardComboSfxLoaded = false;
static bool bgmMusicLoaded = false;
static bool audioReady = false;
static float pulseTimer = 0.0f;
static bool collectedSpecialties[10] = { false };
static bool hasStartRewardPopup = false;
static bool isTraveling = false;
static bool runFinished = false;
static float waitBeforeNextMove = 0.0f;
static float travelProgress = 0.0f;
static float rewardPopupTimer = 0.0f;
static float finishDelayTimer = 0.0f;
static int travelingFrom = -1;
static int travelingTo = -1;
static Vector2 travelerPosition = { 0.0f, 0.0f };
static std::string rewardPopupText = "";
static std::string rewardPopupDetailText = "";
static std::set<std::pair<int, int>> rewardedBridges;
static std::set<std::pair<int, int>> traversedEdges;
static std::vector<int> movementRoute;
static std::vector<int> traversalParentTree;
static float arrivalEffectTimer = 0.0f;
static int arrivalEffectIsland = -1;
static bool arrivalHasArticulation = false;
static bool arrivalHasBridge = false;
static int speedMode = 1; // 0: x0.5, 1: x1.0, 2: x1.5
static float travelDurationSeconds = 1.85f;
static float newKeyBadgeTimer = 0.0f;
static float newSpecialtyBadgeTimer = 0.0f;
static bool keyFlyActive = false;
static float keyFlyProgress = 0.0f;
static Vector2 keyFlyFrom = { 0.0f, 0.0f };
static Vector2 keyFlyTo = { 0.0f, 0.0f };
static bool specialtyFlyActive = false;
static float specialtyFlyProgress = 0.0f;
static Vector2 specialtyFlyFrom = { 0.0f, 0.0f };
static Vector2 specialtyFlyTo = { 0.0f, 0.0f };
static std::string graphEditorMessage = "Chon cong cu roi bam vao dao de sua do thi";
static float graphEditorMessageTimer = 0.0f;
static const Color UI_BLUE = { 36, 112, 142, 235 };
static const Color UI_BLUE_HOVER = { 57, 153, 189, 245 };
static const Color UI_TEAL = { 27, 136, 120, 235 };
static const Color UI_TEAL_HOVER = { 43, 171, 151, 245 };
static const Color UI_GOLD = { 200, 148, 63, 235 };
static const Color UI_GOLD_HOVER = { 230, 178, 88, 245 };
static const Color UI_SLATE = { 73, 88, 110, 235 };
static const Color UI_SLATE_HOVER = { 100, 121, 147, 245 };

void PlayAsyncBeeps(std::initializer_list<std::pair<unsigned int, unsigned int>> pattern);
void BuildActiveGraph(int outGraph[10][10]);
void PlayUiClickSound();
void InitGameAudio();
void UpdateGameAudio();
void CloseGameAudio();

void SetGraphEditorMessage(const std::string& message, float seconds = 1.9f) {
    graphEditorMessage = message;
    graphEditorMessageTimer = seconds;
}

int GetIslandIndexAtPosition(Vector2 mousePos) {
    for (int i = 9; i >= 0; i--) {
        float radius = vertexActive[i] ? 58.0f : 28.0f;
        if (CheckCollisionPointCircle(mousePos, mapIslands[i].position, radius)) {
            return i;
        }
    }
    return -1;
}

Vector2 GetKeySlotPosition(int index) {
    int maxKeyIcons = 6;
    int clamped = (index < 0) ? 0 : (index >= maxKeyIcons ? maxKeyIcons - 1 : index);
    float kx = 1028 + (clamped % 3) * 78.0f;
    float ky = 464 + (clamped / 3) * 42.0f;
    return { kx + 21.0f, ky + 17.0f };
}

Vector2 GetSpecialtySlotPosition(int index) {
    int clamped = (index < 0) ? 0 : index;
    int col = clamped % 2;
    int row = clamped / 2;
    float x = 1025 + col * 120.0f;
    float y = 540 + row * 70.0f;
    return { x + 21.0f, y + 21.0f };
}

bool DrawImageButton(Rectangle rect, const char* text, Color textColor, Color tintNormal, Color tintHover) {
    Vector2 mousePos = GetMousePosition();
    bool isHover = CheckCollisionPointRec(mousePos, rect);
    bool clicked = isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (buttonTexture.id > 0) {
        DrawTexturePro(buttonTexture,
            (Rectangle){ 0, 0, (float)buttonTexture.width, (float)buttonTexture.height },
            rect,
            (Vector2){ 0, 0 },
            0.0f,
            isHover ? tintHover : tintNormal);
    } else {
        DrawRectangleRounded(rect, 0.2f, 8, isHover ? tintHover : tintNormal);
    }

    DrawRectangleLinesEx(rect, 2, ColorAlpha(GOLD, 0.75f));
    DrawText(text, (int)(rect.x + (rect.width - MeasureText(text, 20)) / 2), (int)(rect.y + rect.height / 2 - 10), 20, textColor);
    if (clicked) {
        PlayUiClickSound();
    }
    return clicked;
}

bool DrawSmallUiButton(Rectangle rect, const char* text, Color baseColor, Color hoverColor) {
    Vector2 mousePos = GetMousePosition();
    bool isHover = CheckCollisionPointRec(mousePos, rect);
    bool clicked = isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (buttonTexture.id > 0) {
        DrawTexturePro(buttonTexture,
            (Rectangle){ 0, 0, (float)buttonTexture.width, (float)buttonTexture.height },
            rect,
            (Vector2){ 0, 0 },
            0.0f,
            isHover ? hoverColor : baseColor);
    } else {
        DrawRectangleRounded(rect, 0.18f, 8, isHover ? hoverColor : baseColor);
    }

    DrawRectangleLinesEx(rect, 1, ColorAlpha(GOLD, 0.7f));
    DrawText(text, (int)(rect.x + (rect.width - MeasureText(text, 14)) / 2), (int)(rect.y + rect.height / 2 - 7), 14, WHITE);
    if (clicked) {
        PlayUiClickSound();
    }
    return clicked;
}

void DrawRightPanel(float x, float y, float width, float height) {
    Rectangle panelRect = { x, y, width, height };
    if (panelTexture.id > 0) {
        DrawTexturePro(panelTexture,
            (Rectangle){ 0, 0, (float)panelTexture.width, (float)panelTexture.height },
            panelRect,
            (Vector2){ 0, 0 },
            0.0f,
            ColorAlpha(WHITE, 0.95f));
    } else {
        DrawRectangleRounded(panelRect, 0.05f, 10, ColorAlpha(DARKBLUE, 0.9f));
    }
}

static const char* specialtyImagePaths[10] = {
    "Src/sources/dacsan/Gemini_Generated_Image_ac36acac36acac36.png",
    "Src/sources/dacsan/Gemini_Generated_Image_bm8v63bm8v63bm8v.png",
    "Src/sources/dacsan/Gemini_Generated_Image_bsxhdjbsxhdjbsxh.png",
    "Src/sources/dacsan/Gemini_Generated_Image_lknz2mlknz2mlknz.png",
    "Src/sources/dacsan/Gemini_Generated_Image_ll3835ll3835ll38.png",
    "Src/sources/dacsan/Gemini_Generated_Image_t2mr12t2mr12t2mr.png",
    "Src/sources/dacsan/Gemini_Generated_Image_xy7vdxy7vdxy7vdx.png",
    "Src/sources/dacsan/Gemini_Generated_Image_y6cfhly6cfhly6cf.png",
    "Src/sources/dacsan/ascii_specialty_1.jpg",
    "Src/sources/dacsan/ascii_specialty_2.jpg"
};

static const char* specialtyNames[10] = {
    "Tom hum", "Muc kho", "Toi Ly Son", "Nuoc mam",
    "Muc mot nang", "Tom tit", "Rong bien", "Banh in",
    "Cha muc", "Oc vu nang"
};

void ResetRunState() {
    selectedStartIsland = -1;
    currentVisitingIsland = -1;
    currentTraversalIndex = -1;
    playerRewards = { 0, 0 };
    rewardTargets = { 0, 0 };
    traversalPath.clear();
    visitedIslands.clear();
    articulationPointsList.clear();
    bridgesList.clear();
    rewardedBridges.clear();
    traversedEdges.clear();
    movementRoute.clear();
    traversalParentTree.clear();
    std::memset(collectedSpecialties, 0, sizeof(collectedSpecialties));
    hasStartRewardPopup = false;
    isTraveling = false;
    runFinished = false;
    waitBeforeNextMove = 0.0f;
    travelProgress = 0.0f;
    rewardPopupTimer = 0.0f;
    finishDelayTimer = 0.0f;
    travelingFrom = -1;
    travelingTo = -1;
    arrivalEffectTimer = 0.0f;
    arrivalEffectIsland = -1;
    arrivalHasArticulation = false;
    arrivalHasBridge = false;
    newKeyBadgeTimer = 0.0f;
    newSpecialtyBadgeTimer = 0.0f;
    keyFlyActive = false;
    keyFlyProgress = 0.0f;
    keyFlyFrom = { 0.0f, 0.0f };
    keyFlyTo = { 0.0f, 0.0f };
    specialtyFlyActive = false;
    specialtyFlyProgress = 0.0f;
    specialtyFlyFrom = { 0.0f, 0.0f };
    specialtyFlyTo = { 0.0f, 0.0f };
    speedMode = 1;
    travelDurationSeconds = 1.85f;
    rewardPopupText.clear();
    rewardPopupDetailText.clear();
}

void PlayAsyncBeeps(std::initializer_list<std::pair<unsigned int, unsigned int>> pattern) {
    std::thread([pattern]() {
        for (const auto& tone : pattern) {
            Beep(tone.first, tone.second);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }).detach();
}

void PlayRewardSound(bool gotSpecialty, bool gotKey) {
    if (gotSpecialty && gotKey) {
        if (audioReady && rewardComboSfxLoaded) {
            PlaySound(rewardComboSfx);
        } else {
            PlayAsyncBeeps({ {659, 110}, {784, 110}, {988, 130} });
        }
    } else if (gotSpecialty) {
        if (audioReady && rewardSpecialtySfxLoaded) {
            PlaySound(rewardSpecialtySfx);
        } else {
            PlayAsyncBeeps({ {880, 130}, {988, 110} });
        }
    } else if (gotKey) {
        if (audioReady && rewardKeySfxLoaded) {
            PlaySound(rewardKeySfx);
        } else {
            PlayAsyncBeeps({ {523, 140} });
        }
    }
}

void InitGameAudio() {
    if (!IsAudioDeviceReady()) {
        InitAudioDevice();
    }
    audioReady = IsAudioDeviceReady();
    if (!audioReady) {
        return;
    }

    if (FileExists("Src/sources/audio/ui_click.wav")) {
        uiClickSfx = LoadSound("Src/sources/audio/ui_click.wav");
        uiClickSfxLoaded = (uiClickSfx.frameCount > 0);
    }
    if (FileExists("Src/sources/audio/reward_specialty.wav")) {
        rewardSpecialtySfx = LoadSound("Src/sources/audio/reward_specialty.wav");
        rewardSpecialtySfxLoaded = (rewardSpecialtySfx.frameCount > 0);
    }
    if (FileExists("Src/sources/audio/reward_key.wav")) {
        rewardKeySfx = LoadSound("Src/sources/audio/reward_key.wav");
        rewardKeySfxLoaded = (rewardKeySfx.frameCount > 0);
    }
    if (FileExists("Src/sources/audio/reward_combo.wav")) {
        rewardComboSfx = LoadSound("Src/sources/audio/reward_combo.wav");
        rewardComboSfxLoaded = (rewardComboSfx.frameCount > 0);
    }
    if (FileExists("Src/sources/audio/bgm_theme.mp3")) {
        bgmMusic = LoadMusicStream("Src/sources/audio/bgm_theme.mp3");
        bgmMusicLoaded = (bgmMusic.ctxData != nullptr);
        if (bgmMusicLoaded) {
            SetMusicVolume(bgmMusic, 0.38f);
            PlayMusicStream(bgmMusic);
        }
    }
}

void UpdateGameAudio() {
    if (audioReady && bgmMusicLoaded) {
        UpdateMusicStream(bgmMusic);
    }
}

std::vector<int> FindShortestPathNodes(int startNode, int endNode) {
    if (startNode == endNode) {
        return { startNode };
    }

    std::vector<int> parent(10, -1);
    std::vector<bool> seen(10, false);
    std::queue<int> q;
    q.push(startNode);
    seen[startNode] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == endNode) {
            break;
        }

        for (int v = 0; v < 10; v++) {
            if (vertexActive[v] && graph[u][v] == 1 && !seen[v]) {
                seen[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (!seen[endNode]) {
        return { startNode };
    }

    std::vector<int> path;
    for (int cur = endNode; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
        if (cur == startNode) {
            break;
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> FindPathInTreeNodes(int startNode, int endNode) {
    if (startNode == endNode) {
        return { startNode };
    }

    std::vector<std::vector<int>> treeAdj(10);
    for (int node = 0; node < 10; node++) {
        int parentNode = (node < (int)traversalParentTree.size()) ? traversalParentTree[node] : -1;
        if (parentNode != -1) {
            treeAdj[node].push_back(parentNode);
            treeAdj[parentNode].push_back(node);
        }
    }

    std::vector<int> parent(10, -1);
    std::vector<bool> seen(10, false);
    std::queue<int> q;
    q.push(startNode);
    seen[startNode] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == endNode) {
            break;
        }
        for (int v : treeAdj[u]) {
            if (!seen[v]) {
                seen[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (!seen[endNode]) {
        return FindShortestPathNodes(startNode, endNode);
    }

    std::vector<int> path;
    for (int cur = endNode; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
        if (cur == startNode) {
            break;
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void BuildMovementRouteFromTraversal() {
    movementRoute.clear();
    if (traversalPath.empty()) {
        return;
    }

    movementRoute.push_back(traversalPath[0]);
    for (int i = 1; i < (int)traversalPath.size(); i++) {
        int fromNode = movementRoute.back();
        int toNode = traversalPath[i];
        std::vector<int> segment = FindPathInTreeNodes(fromNode, toNode);
        for (int j = 1; j < (int)segment.size(); j++) {
            movementRoute.push_back(segment[j]);
        }
    }
}

void HandleArrivalReward(int fromNode, int toNode) {
    bool gotSpecialty = false;
    bool gotKey = false;
    std::pair<int, int> traveledEdge = { std::min(fromNode, toNode), std::max(fromNode, toNode) };
    traversedEdges.insert(traveledEdge);

    if (articulationPointsList.count(toNode) > 0 && !collectedSpecialties[toNode]) {
        collectedSpecialties[toNode] = true;
        playerRewards.articulation_points++;
        gotSpecialty = true;
    }

    int a = std::min(fromNode, toNode);
    int b = std::max(fromNode, toNode);
    std::pair<int, int> bridgeEdge = { a, b };
    if (bridgesList.count(bridgeEdge) > 0 && rewardedBridges.count(bridgeEdge) == 0) {
        rewardedBridges.insert(bridgeEdge);
        playerRewards.bridges++;
        gotKey = true;
    }

    arrivalEffectIsland = toNode;
    arrivalHasArticulation = gotSpecialty;
    arrivalHasBridge = gotKey;
    if (gotSpecialty || gotKey) {
        arrivalEffectTimer = 1.6f;
    }
    if (gotSpecialty) {
        newSpecialtyBadgeTimer = 1.8f;
        specialtyFlyActive = true;
        specialtyFlyProgress = 0.0f;
        specialtyFlyFrom = mapIslands[toNode].position;
        specialtyFlyTo = GetSpecialtySlotPosition(playerRewards.articulation_points - 1);
    }
    if (gotKey) {
        newKeyBadgeTimer = 1.8f;
        keyFlyActive = true;
        keyFlyProgress = 0.0f;
        keyFlyFrom = mapIslands[toNode].position;
        keyFlyTo = GetKeySlotPosition(playerRewards.bridges - 1);
    }

    PlayRewardSound(gotSpecialty, gotKey);

    const std::string fromName = mapIslands[fromNode].name;
    const std::string toName = mapIslands[toNode].name;
    const std::string edgeInfo = std::string("Canh: ") + fromName + " <-> " + toName;

    if (gotSpecialty && gotKey) {
        rewardPopupText = std::string("Nhan thuong tai dao ") + toName + ": +1 dac san +1 chia khoa";
        rewardPopupDetailText = std::string("Lo trinh: ") + fromName + " -> " + toName + " | " + edgeInfo;
        rewardPopupTimer = 2.6f;
    } else if (gotSpecialty) {
        rewardPopupText = std::string("Nhan dac san tai dao ") + toName + ": " + specialtyNames[toNode];
        rewardPopupDetailText = std::string("Lo trinh: ") + fromName + " -> " + toName + " | " + edgeInfo;
        rewardPopupTimer = 2.6f;
    } else if (gotKey) {
        rewardPopupText = std::string("Nhan chia khoa tai canh ") + fromName + " - " + toName;
        rewardPopupDetailText = std::string("Lo trinh: ") + fromName + " -> " + toName + " | " + edgeInfo;
        rewardPopupTimer = 2.4f;
    }
}

void PrepareRunFromIsland(int startIsland, bool manualStepMode) {
    ResetRunState();
    selectedStartIsland = startIsland;
    stepByStepMode = manualStepMode;
    manualAdvanceRequested = false;

    int activeGraph[10][10] = { 0 };
    BuildActiveGraph(activeGraph);

    DFSTraversal dfs(10, activeGraph, startIsland);
    traversalPath = dfs.getTraversalOrder();
    traversalParentTree = dfs.getParentTree();

    TarjanAlgorithm tarjan(10, activeGraph);
    tarjan.findArticulationPoints();
    articulationPointsList = tarjan.getArticulationPoints();
    bridgesList = tarjan.getBridges();

    BuildMovementRouteFromTraversal();

    if (movementRoute.empty()) {
        currentScreen = RESULT;
        return;
    }

    currentTraversalIndex = 0;
    currentVisitingIsland = movementRoute[0];
    travelerPosition = mapIslands[currentVisitingIsland].position;
    visitedIslands.insert(currentVisitingIsland);

    std::set<int> articulationOnRoute;
    std::set<std::pair<int, int>> bridgeOnRoute;
    for (int node : movementRoute) {
        if (articulationPointsList.count(node) > 0) {
            articulationOnRoute.insert(node);
        }
    }
    for (int i = 0; i + 1 < (int)movementRoute.size(); i++) {
        int a = std::min(movementRoute[i], movementRoute[i + 1]);
        int b = std::max(movementRoute[i], movementRoute[i + 1]);
        std::pair<int, int> edge = { a, b };
        if (bridgesList.count(edge) > 0) {
            bridgeOnRoute.insert(edge);
        }
    }
    rewardTargets = { (int)articulationOnRoute.size(), (int)bridgeOnRoute.size() };

    if (articulationPointsList.count(currentVisitingIsland) > 0) {
        collectedSpecialties[currentVisitingIsland] = true;
        playerRewards.articulation_points++;
        rewardPopupText = std::string("Thuong khoi hanh tai dao ") + mapIslands[currentVisitingIsland].name + ": " + specialtyNames[currentVisitingIsland];
        rewardPopupDetailText = std::string("Lo trinh: START -> ") + mapIslands[currentVisitingIsland].name + " | Canh: chua di chuyen";
        rewardPopupTimer = 2.6f;
        hasStartRewardPopup = true;
    }

    currentScreen = PLAYING;
}

void UpdateAutoTraversal() {
    if (currentScreen != PLAYING || movementRoute.empty()) {
        return;
    }

    float dt = GetFrameTime();
    pulseTimer += dt;

    if (rewardPopupTimer > 0.0f) {
        rewardPopupTimer -= dt;
        if (rewardPopupTimer < 0.0f) rewardPopupTimer = 0.0f;
    }
    if (arrivalEffectTimer > 0.0f) {
        arrivalEffectTimer -= dt;
        if (arrivalEffectTimer < 0.0f) arrivalEffectTimer = 0.0f;
    }
    if (newKeyBadgeTimer > 0.0f) {
        newKeyBadgeTimer -= dt;
        if (newKeyBadgeTimer < 0.0f) newKeyBadgeTimer = 0.0f;
    }
    if (newSpecialtyBadgeTimer > 0.0f) {
        newSpecialtyBadgeTimer -= dt;
        if (newSpecialtyBadgeTimer < 0.0f) newSpecialtyBadgeTimer = 0.0f;
    }
    if (keyFlyActive) {
        keyFlyProgress += dt / 0.75f;
        if (keyFlyProgress >= 1.0f) {
            keyFlyProgress = 1.0f;
            keyFlyActive = false;
        }
    }
    if (specialtyFlyActive) {
        specialtyFlyProgress += dt / 0.85f;
        if (specialtyFlyProgress >= 1.0f) {
            specialtyFlyProgress = 1.0f;
            specialtyFlyActive = false;
        }
    }

    if (runFinished) {
        finishDelayTimer += dt;
        if (finishDelayTimer >= 1.2f) {
            currentScreen = RESULT;
        }
        return;
    }

    if (!isTraveling) {
        if (stepByStepMode && !manualAdvanceRequested) {
            return;
        }
        waitBeforeNextMove += dt;
        if (waitBeforeNextMove < (hasStartRewardPopup ? 0.9f : 0.55f)) {
            return;
        }
        hasStartRewardPopup = false;
        if (stepByStepMode) {
            manualAdvanceRequested = false;
        }

        if (currentTraversalIndex + 1 >= (int)movementRoute.size()) {
            runFinished = true;
            finishDelayTimer = 0.0f;
            rewardPopupText = "Da ket thuc hanh trinh. Dang kiem tra kho bau...";
            rewardPopupDetailText.clear();
            rewardPopupTimer = 1.2f;
            return;
        }

        travelingFrom = movementRoute[currentTraversalIndex];
        travelingTo = movementRoute[currentTraversalIndex + 1];
        isTraveling = true;
        travelProgress = 0.0f;
        waitBeforeNextMove = 0.0f;
    }

    if (isTraveling) {
        travelProgress += dt / travelDurationSeconds;
        if (travelProgress > 1.0f) {
            travelProgress = 1.0f;
        }
        float smoothT = travelProgress * travelProgress * (3.0f - 2.0f * travelProgress);
        Vector2 fromPos = mapIslands[travelingFrom].position;
        Vector2 toPos = mapIslands[travelingTo].position;
        travelerPosition = {
            fromPos.x + (toPos.x - fromPos.x) * smoothT,
            fromPos.y + (toPos.y - fromPos.y) * smoothT
        };

        if (travelProgress >= 1.0f) {
            isTraveling = false;
            currentTraversalIndex++;
            currentVisitingIsland = travelingTo;
            visitedIslands.insert(currentVisitingIsland);
            HandleArrivalReward(travelingFrom, travelingTo);
            if (stepByStepMode) {
                manualAdvanceRequested = false;
            }
        }
    }
}

// Hàm vẽ nút bấm
bool DrawMenuButton(Rectangle rect, const char* text, Color baseColor, Color hoverColor) {
    Vector2 mousePos = GetMousePosition();
    bool isHover = CheckCollisionPointRec(mousePos, rect);
    bool clicked = isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    DrawRectangleRec(rect, isHover ? hoverColor : baseColor);
    DrawRectangleLinesEx(rect, 2, RAYWHITE);
    DrawText(text, rect.x + (rect.width - MeasureText(text, 20))/2, rect.y + 15, 20, WHITE);
    if (clicked) {
        PlayUiClickSound();
    }
    return clicked;
}

void PlayUiClickSound() {
    if (audioReady && uiClickSfxLoaded) {
        PlaySound(uiClickSfx);
    } else {
        PlayAsyncBeeps({ { 830, 35 } });
    }
}

void SetEdgeValue(int a, int b, int value) {
    if (a < 0 || a >= 10 || b < 0 || b >= 10 || a == b) return;
    graph[a][b] = value;
    graph[b][a] = value;
}

void ToggleVertexActive(int vertexIndex, bool active) {
    if (vertexIndex < 0 || vertexIndex >= 10) return;
    vertexActive[vertexIndex] = active;
    if (!active) {
        if (selectedStartIsland == vertexIndex) {
            selectedStartIsland = -1;
        }
        if (firstEdgeVertex == vertexIndex) {
            firstEdgeVertex = -1;
        }
        for (int i = 0; i < 10; i++) {
            graph[vertexIndex][i] = 0;
            graph[i][vertexIndex] = 0;
        }
    } else {
        for (int i = 0; i < 10; i++) {
            if (defaultGraph[vertexIndex][i] == 1 && vertexActive[i]) {
                graph[vertexIndex][i] = 1;
                graph[i][vertexIndex] = 1;
            }
        }
    }
}

void BuildActiveGraph(int outGraph[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            outGraph[i][j] = (vertexActive[i] && vertexActive[j]) ? graph[i][j] : 0;
        }
    }
}

void ResetInteractiveGraphState() {
    ResetGraphToDefault();
    selectedStartIsland = -1;
    currentGraphTool = TOOL_PICK_START;
    firstEdgeVertex = -1;
    manualAdvanceRequested = false;
    stepByStepMode = false;
    SetGraphEditorMessage("Da reset do thi ve mac dinh", 2.0f);
}

void HandleGraphEditorClick(int islandIndex) {
    if (islandIndex < 0 || islandIndex >= 10) return;

    if (currentGraphTool == TOOL_PICK_START) {
        if (vertexActive[islandIndex]) {
            selectedStartIsland = islandIndex;
            SetGraphEditorMessage(std::string("Da chon start: ") + mapIslands[islandIndex].name);
        } else {
            SetGraphEditorMessage("Dinh da bi xoa, khong the chon start");
        }
        return;
    }

    if (currentGraphTool == TOOL_ADD_VERTEX) {
        if (vertexActive[islandIndex]) {
            SetGraphEditorMessage(std::string("Dinh ") + mapIslands[islandIndex].name + " da ton tai");
            return;
        }
        ToggleVertexActive(islandIndex, true);
        SetGraphEditorMessage(std::string("Da them lai dinh: ") + mapIslands[islandIndex].name);
        return;
    }

    if (currentGraphTool == TOOL_DELETE_VERTEX) {
        if (!vertexActive[islandIndex]) {
            SetGraphEditorMessage(std::string("Dinh ") + mapIslands[islandIndex].name + " da bi xoa truoc do");
            return;
        }
        ToggleVertexActive(islandIndex, false);
        SetGraphEditorMessage(std::string("Da xoa dinh: ") + mapIslands[islandIndex].name);
        return;
    }

    if (currentGraphTool == TOOL_ADD_EDGE || currentGraphTool == TOOL_DELETE_EDGE) {
        if (!vertexActive[islandIndex]) {
            SetGraphEditorMessage("Khong the sua canh voi dinh da bi xoa");
            return;
        }
        if (firstEdgeVertex < 0) {
            firstEdgeVertex = islandIndex;
            SetGraphEditorMessage(std::string("Da chon diem 1: ") + mapIslands[islandIndex].name);
        } else if (firstEdgeVertex == islandIndex) {
            firstEdgeVertex = -1;
            SetGraphEditorMessage("Da huy chon diem 1");
        } else {
            bool oldValue = (graph[firstEdgeVertex][islandIndex] == 1);
            bool addMode = (currentGraphTool == TOOL_ADD_EDGE);
            if (addMode && oldValue) {
                SetGraphEditorMessage("Canh nay da ton tai");
            } else if (!addMode && !oldValue) {
                SetGraphEditorMessage("Canh nay khong ton tai");
            } else {
                SetEdgeValue(firstEdgeVertex, islandIndex, addMode ? 1 : 0);
                SetGraphEditorMessage(addMode ? "Da them canh moi" : "Da xoa canh");
            }
            firstEdgeVertex = -1;
        }
    }
}

void StartSelectedRun(bool manualStepMode) {
    if (selectedStartIsland < 0 || !vertexActive[selectedStartIsland]) {
        return;
    }
    PrepareRunFromIsland(selectedStartIsland, manualStepMode);
}

// Khởi tạo tài nguyên
void InitGameMap() {
    InitGameAudio();

    menuBg = LoadTexture("Src/sources/photo/start_menu_bg.png"); 
    bgTexture = LoadTexture("Src/sources/photo/background.png");
    tutorialBgTexture = LoadTexture("Src/sources/photo/background_tutorial.png");
    panelTexture = LoadTexture("Src/sources/photo/side_panel.png");
    buttonTexture = LoadTexture("Src/sources/photo/button.png");
    bagTexture = LoadTexture("Src/sources/photo/bag.png");
    keyTexture = LoadTexture("Src/sources/photo/key.png");
    completeKeyTexture = LoadTexture("Src/sources/photo/complete_key.png");
    chestTexture = LoadTexture("Src/sources/photo/ruong.png");
    for (int i = 0; i < 10; i++) {
        islandTextures[i] = LoadTexture(mapIslands[i].imagePath);
        specialtyTextures[i] = LoadTexture(specialtyImagePaths[i]);
    }
}

// Menu chính
void DrawStartMenu() {
    DrawTexturePro(menuBg, (Rectangle){ 0, 0, (float)menuBg.width, (float)menuBg.height },
                   (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);

    if (DrawImageButton({ (float)GetScreenWidth()/2 - 150, 350, 300, 58 }, "1. BAT DAU", WHITE, UI_BLUE, UI_BLUE_HOVER)) {
        currentScreen = CHOOSE_ALGORITHM;
    }

    if (DrawImageButton({ (float)GetScreenWidth()/2 - 150, 424, 300, 58 }, "2. HUONG DAN", WHITE, UI_TEAL, UI_TEAL_HOVER)) {
        currentScreen = INSTRUCTIONS;
    }
}

// Chọn thuật toán
void DrawChooseAlgorithmScreen() {
    if (tutorialBgTexture.id > 0) {
        DrawTexturePro(tutorialBgTexture, (Rectangle){ 0, 0, (float)tutorialBgTexture.width, (float)tutorialBgTexture.height },
                       (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    } else {
        DrawTexturePro(bgTexture, (Rectangle){ 0, 0, (float)bgTexture.width, (float)bgTexture.height },
                       (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, ColorAlpha(WHITE, 0.8f));
    }
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.28f));
    DrawText("CHON THUAT TOAN", GetScreenWidth()/2 - MeasureText("CHON THUAT TOAN", 40)/2, 150, 40, GOLD);

    if (DrawImageButton({ (float)GetScreenWidth()/2 - 150, 300, 300, 80 }, "DFS", WHITE, UI_BLUE, UI_BLUE_HOVER)) {
        selectedAlgorithm = DFS_TYPE;
        currentScreen = CHOOSE_ISLAND;
    }

    if (DrawImageButton({ (float)GetScreenWidth()/2 - 110, 700, 220, 50 }, "QUAY LAI", WHITE, UI_SLATE, UI_SLATE_HOVER)) {
        currentScreen = MENU;
    }
}

// Chọn đảo bắt đầu
void DrawChooseIslandScreen() {
    float dt = GetFrameTime();
    if (graphEditorMessageTimer > 0.0f) {
        graphEditorMessageTimer -= dt;
        if (graphEditorMessageTimer < 0.0f) graphEditorMessageTimer = 0.0f;
    }

    DrawTexturePro(bgTexture, (Rectangle){ 0, 0, (float)bgTexture.width, (float)bgTexture.height },
                   (Rectangle){ 0, 0, 1000, (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);

    DrawRightPanel(1000, 0, 280, (float)GetScreenHeight());
    DrawText("CHON DAO", 1025, 30, 22, GOLD);
    
    const char* algoName = "DFS";
    DrawText(algoName, 1060, 70, 18, SKYBLUE);

    const char* toolName = "Chon start";
    switch (currentGraphTool) {
        case TOOL_ADD_VERTEX: toolName = "Them dinh"; break;
        case TOOL_DELETE_VERTEX: toolName = "Xoa dinh"; break;
        case TOOL_ADD_EDGE: toolName = "Them canh"; break;
        case TOOL_DELETE_EDGE: toolName = "Xoa canh"; break;
        default: toolName = "Chon start"; break;
    }
    DrawText(TextFormat("Che do: %s", toolName), 1020, 100, 12, RAYWHITE);

    if (DrawSmallUiButton({ 1018, 126, 120, 34 }, "CHON START", UI_BLUE, UI_BLUE_HOVER)) {
        currentGraphTool = TOOL_PICK_START;
        firstEdgeVertex = -1;
    }
    if (DrawSmallUiButton({ 1140, 126, 116, 34 }, "RESET DO THI", UI_SLATE, UI_SLATE_HOVER)) {
        ResetInteractiveGraphState();
    }
    if (DrawSmallUiButton({ 1018, 168, 120, 34 }, "THEM DINH", UI_TEAL, UI_TEAL_HOVER)) {
        currentGraphTool = TOOL_ADD_VERTEX;
        firstEdgeVertex = -1;
    }
    if (DrawSmallUiButton({ 1140, 168, 116, 34 }, "XOA DINH", UI_TEAL, UI_TEAL_HOVER)) {
        currentGraphTool = TOOL_DELETE_VERTEX;
        firstEdgeVertex = -1;
    }
    if (DrawSmallUiButton({ 1018, 210, 120, 34 }, "THEM CANH", UI_GOLD, UI_GOLD_HOVER)) {
        currentGraphTool = TOOL_ADD_EDGE;
        firstEdgeVertex = -1;
    }
    if (DrawSmallUiButton({ 1140, 210, 116, 34 }, "XOA CANH", UI_GOLD, UI_GOLD_HOVER)) {
        currentGraphTool = TOOL_DELETE_EDGE;
        firstEdgeVertex = -1;
    }

    DrawText("Bam vao dao de chon hoac sua do thi", 1018, 252, 12, LIGHTGRAY);
    DrawText("Start / Step can mot dinh bat dau hop le", 1018, 268, 12, LIGHTGRAY);
    Color messageColor = (graphEditorMessageTimer > 0.0f) ? GOLD : LIGHTGRAY;
    DrawText(graphEditorMessage.c_str(), 1018, 284, 12, messageColor);

    bool readyToRun = (selectedStartIsland >= 0 && vertexActive[selectedStartIsland]);
    Color startBase = readyToRun ? UI_BLUE : ColorAlpha(UI_SLATE, 0.75f);
    Color startHover = readyToRun ? UI_BLUE_HOVER : ColorAlpha(UI_SLATE_HOVER, 0.85f);
    if (DrawSmallUiButton({ 1018, 316, 116, 38 }, "START", startBase, startHover) && readyToRun) {
        StartSelectedRun(false);
    }
    if (DrawSmallUiButton({ 1140, 316, 116, 38 }, "STEP BY STEP", startBase, startHover) && readyToRun) {
        StartSelectedRun(true);
    }

    if (selectedStartIsland >= 0) {
        DrawText(TextFormat("Start: %s", mapIslands[selectedStartIsland].name.c_str()), 1020, 360, 12, LIME);
    } else {
        DrawText("Start: chua chon", 1020, 360, 12, ORANGE);
    }

    if (DrawImageButton({ 1020, 820, 240, 45 }, "QUAY LAI", WHITE, UI_SLATE, UI_SLATE_HOVER)) {
        selectedAlgorithm = NONE;
        ResetRunState();
        currentScreen = CHOOSE_ALGORITHM;
    }

    // Vẽ đường nối
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (vertexActive[i] && vertexActive[j] && graph[i][j] == 1) {
                DrawLineEx(mapIslands[i].position, mapIslands[j].position, 3.0f, Fade(SKYBLUE, 0.5f));
            }
        }
    }

    Vector2 mousePos = GetMousePosition();
    int hoveredIsland = GetIslandIndexAtPosition(mousePos);
    if (hoveredIsland >= 0 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        HandleGraphEditorClick(hoveredIsland);
    }

    // Vẽ đảo
    float imgSize = 110.0f; 
    for (int i = 0; i < 10; i++) {
        Vector2 pos = mapIslands[i].position;
        bool isHover = (hoveredIsland == i);
        bool isActive = vertexActive[i];
        bool isSelectedStart = (selectedStartIsland == i);
        bool isEdgeAnchor = (firstEdgeVertex == i);

        if (isActive && islandTextures[i].id > 0) {
            DrawTexturePro(islandTextures[i],
                (Rectangle){ 0, 0, (float)islandTextures[i].width, (float)islandTextures[i].height },
                (Rectangle){ pos.x - imgSize/2, pos.y - imgSize/2, imgSize, imgSize },
                (Vector2){ 0, 0 }, 0.0f, isHover ? ColorAlpha(WHITE, 0.85f) : WHITE);
        } else {
            DrawCircleV(pos, isActive ? imgSize/2 : 24.0f, isActive ? GOLD : ColorAlpha(BLACK, 0.35f));
            if (!isActive) {
                DrawCircleLines((int)pos.x, (int)pos.y, 24.0f, ColorAlpha(GRAY, 0.8f));
                if (currentGraphTool == TOOL_ADD_VERTEX) {
                    DrawText("+", (int)pos.x - 6, (int)pos.y - 12, 24, LIGHTGRAY);
                }
            }
        }

        if (isSelectedStart && isActive) {
            DrawCircleLines((int)pos.x, (int)pos.y, imgSize/2 + 10, GOLD);
        }
        if (isEdgeAnchor && isActive) {
            DrawCircleLines((int)pos.x, (int)pos.y, imgSize/2 + 16, ORANGE);
        }

        Color labelColor = isActive ? RAYWHITE : ColorAlpha(LIGHTGRAY, 0.7f);
        DrawText(mapIslands[i].name.c_str(), pos.x - MeasureText(mapIslands[i].name.c_str(), 16)/2, pos.y + imgSize/2 + 15, 16, labelColor);
    }
}

// Màn hình chơi
void DrawGameplayScreen() {
    UpdateAutoTraversal();

    DrawTexturePro(bgTexture, (Rectangle){ 0, 0, (float)bgTexture.width, (float)bgTexture.height },
                   (Rectangle){ 0, 0, 1000, (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);

    // Panel bên phải
    DrawRightPanel(1000, 0, 280, (float)GetScreenHeight());
    DrawText("THONG TIN", 1020, 20, 20, GOLD);

    // Hiển thị thuật toán
    const char* algoName = "DFS";
    DrawText(TextFormat("Thuat toan: %s", algoName), 1020, 60, 13, SKYBLUE);
    DrawText(TextFormat("Da tham: %d/%d", (int)visitedIslands.size(), (int)traversalPath.size()), 1020, 84, 13, RAYWHITE);
    DrawText(stepByStepMode ? "Che do: Step by step" : "Che do: Tu dong mo phong", 1020, 106, 13, SKYBLUE);

    DrawText("--- TOC DO ---", 1020, 130, 14, GOLD);
    if (DrawImageButton({ 1020, 152, 74, 32 }, "x0.5", WHITE, speedMode == 0 ? UI_GOLD : UI_SLATE, speedMode == 0 ? UI_GOLD_HOVER : UI_SLATE_HOVER)) {
        speedMode = 0;
        travelDurationSeconds = 2.75f;
    }
    if (DrawImageButton({ 1103, 152, 74, 32 }, "x1", WHITE, speedMode == 1 ? UI_GOLD : UI_SLATE, speedMode == 1 ? UI_GOLD_HOVER : UI_SLATE_HOVER)) {
        speedMode = 1;
        travelDurationSeconds = 1.85f;
    }
    if (DrawImageButton({ 1186, 152, 74, 32 }, "x1.5", WHITE, speedMode == 2 ? UI_GOLD : UI_SLATE, speedMode == 2 ? UI_GOLD_HOVER : UI_SLATE_HOVER)) {
        speedMode = 2;
        travelDurationSeconds = 1.25f;
    }

    // Hiển thị rewards
    DrawText("--- PHAN THUONG ---", 1020, 192, 14, GOLD);
    if (bagTexture.id > 0) {
        DrawTexturePro(bagTexture,
            (Rectangle){ 0, 0, (float)bagTexture.width, (float)bagTexture.height },
            (Rectangle){ 1178, 188, 48, 48 },
            (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
    Texture2D usedKey = (playerRewards.bridges >= rewardTargets.bridges && completeKeyTexture.id > 0) ? completeKeyTexture : keyTexture;
    if (usedKey.id > 0) {
        DrawTexturePro(usedKey,
            (Rectangle){ 0, 0, (float)usedKey.width, (float)usedKey.height },
            (Rectangle){ 1179, 236, 46, 34 },
            (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
    DrawText(TextFormat("Dac san: %d/%d", playerRewards.articulation_points, rewardTargets.articulation_points), 1020, 217, 13, LIME);
    DrawText(TextFormat("Chia khoa: %d/%d", playerRewards.bridges, rewardTargets.bridges), 1020, 242, 13, LIME);

    bool chestReady = (playerRewards.articulation_points >= rewardTargets.articulation_points &&
                       playerRewards.bridges >= rewardTargets.bridges);
    if (chestTexture.id > 0) {
        DrawTexturePro(chestTexture,
            (Rectangle){ 0, 0, (float)chestTexture.width, (float)chestTexture.height },
            (Rectangle){ 1198, 270, 62, 62 },
            (Vector2){ 0, 0 }, 0.0f,
            chestReady ? WHITE : ColorAlpha(GRAY, 0.70f));
    }
    if (chestReady) {
        float cPulse = 0.45f + 0.55f * std::sin(pulseTimer * 8.0f);
        DrawCircleLines(1229, 301, 36.0f + 5.0f * cPulse, ColorAlpha(GOLD, 0.95f));
        DrawCircleLines(1229, 301, 28.0f + 6.0f * cPulse, ColorAlpha(ORANGE, 0.90f));
        DrawText("MO DUOC", 1176, 336, 12, GOLD);
    }

    if (newSpecialtyBadgeTimer > 0.0f) {
        float pulse = 0.70f + 0.30f * std::sin((1.8f - newSpecialtyBadgeTimer) * 16.0f);
        DrawRectangleRounded((Rectangle){ 1168, 210, 74, 24 }, 0.45f, 6, ColorAlpha(UI_GOLD, pulse));
        DrawText("NEW", 1192, 214, 14, WHITE);
    }

    DrawText("--- TIMELINE DFS ---", 1020, 270, 14, GOLD);
    int nextTarget = -1;
    for (int i = 0; i < (int)traversalPath.size(); i++) {
        if (visitedIslands.count(traversalPath[i]) == 0) {
            nextTarget = traversalPath[i];
            break;
        }
    }
    for (int i = 0; i < (int)traversalPath.size(); i++) {
        int node = traversalPath[i];
        int row = i;
        if (row > 9) {
            break;
        }
        int y = 295 + row * 14;
        Color c = LIGHTGRAY;
        if (visitedIslands.count(node) > 0) c = LIME;
        if (node == nextTarget) c = YELLOW;
        DrawText(TextFormat("%d) %s", i + 1, mapIslands[node].name.c_str()), 1024, y, 11, c);
    }

    DrawText("--- CHIA KHOA DA NHAN ---", 1020, 440, 14, GOLD);
    int shownKeys = playerRewards.bridges;
    int maxKeyIcons = 6;
    Texture2D bagKeyTex = (completeKeyTexture.id > 0) ? completeKeyTexture : keyTexture;
    for (int k = 0; k < shownKeys && k < maxKeyIcons; k++) {
        float kx = 1028 + (k % 3) * 78.0f;
        float ky = 464 + (k / 3) * 42.0f;
        DrawRectangleRounded((Rectangle){ kx, ky, 70, 36 }, 0.2f, 6, ColorAlpha(BLACK, 0.32f));

        if (newKeyBadgeTimer > 0.0f && k == shownKeys - 1) {
            float p = 0.55f + 0.45f * std::sin((1.8f - newKeyBadgeTimer) * 18.0f);
            DrawRectangleRounded((Rectangle){ kx - 2, ky - 2, 74, 40 }, 0.25f, 6, ColorAlpha(SKYBLUE, p));
        }

        if (bagKeyTex.id > 0) {
            DrawTexturePro(bagKeyTex,
                (Rectangle){ 0, 0, (float)bagKeyTex.width, (float)bagKeyTex.height },
                (Rectangle){ kx + 8, ky + 4, 26, 26 },
                (Vector2){ 0, 0 }, 0.0f, WHITE);
        }
        DrawText(TextFormat("x%d", k + 1), (int)kx + 40, (int)ky + 10, 14, GOLD);
    }
    if (newKeyBadgeTimer > 0.0f) {
        DrawRectangleRounded((Rectangle){ 1166, 470, 76, 24 }, 0.45f, 6, ColorAlpha(UI_BLUE_HOVER, 0.90f));
        DrawText("NEW", 1190, 474, 14, WHITE);
    }
    if (shownKeys == 0) {
        DrawText("Chua nhan key", 1030, 470, 12, LIGHTGRAY);
    } else if (shownKeys > maxKeyIcons) {
        DrawText(TextFormat("+%d key", shownKeys - maxKeyIcons), 1180, 504, 12, GOLD);
    }

    DrawText("--- DAC SAN DA NHAN ---", 1020, 515, 14, GOLD);
    int shown = 0;
    for (int i = 0; i < 10; i++) {
        if (!collectedSpecialties[i]) continue;
        int row = shown / 2;
        int col = shown % 2;
        float x = 1025 + col * 120.0f;
        float y = 540 + row * 70.0f;
        DrawRectangleRounded((Rectangle){ x, y, 108, 64 }, 0.12f, 6, ColorAlpha(BLACK, 0.35f));
        if (specialtyTextures[i].id > 0) {
            DrawTexturePro(specialtyTextures[i],
                (Rectangle){ 0, 0, (float)specialtyTextures[i].width, (float)specialtyTextures[i].height },
                (Rectangle){ x + 6, y + 6, 30, 30 },
                (Vector2){ 0, 0 }, 0.0f, WHITE);
        } else {
            DrawCircle((int)x + 22, (int)y + 20, 14, ORANGE);
        }
        DrawText(mapIslands[i].name.c_str(), (int)x + 40, (int)y + 8, 9, RAYWHITE);
        DrawText(specialtyNames[i], (int)x + 40, (int)y + 22, 9, GOLD);
        shown++;
    }
    if (shown == 0) {
        DrawText("Chua co dac san", 1030, 540, 12, LIGHTGRAY);
    }

    if (stepByStepMode) {
        DrawText("Nhan NEXT STEP de di tiep", 1020, 760, 12, GOLD);
        if (DrawSmallUiButton({ 1020, 780, 240, 36 }, "NEXT STEP", UI_BLUE, UI_BLUE_HOVER)) {
            manualAdvanceRequested = true;
        }
    } else {
        DrawText("Che do tu dong dang chay", 1020, 760, 12, LIGHTGRAY);
    }

    // Nút chức năng
    if (DrawImageButton({ 1020, 832, 116, 45 }, "RESET", WHITE, UI_GOLD, UI_GOLD_HOVER)) {
        if (selectedStartIsland >= 0 && vertexActive[selectedStartIsland]) {
            StartSelectedRun(stepByStepMode);
            return;
        }
    }
    if (DrawImageButton({ 1144, 832, 116, 45 }, "QUAY LAI", WHITE, UI_SLATE, UI_SLATE_HOVER)) {
        selectedAlgorithm = NONE;
        ResetRunState();
        currentScreen = CHOOSE_ALGORITHM;
    }

    // Vẽ đường nối
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (graph[i][j] == 1) {
                Color lineColor = Fade(SKYBLUE, 0.55f);
                std::pair<int, int> edge = { std::min(i, j), std::max(i, j) };
                bool isBridge = (bridgesList.count(edge) > 0);
                bool isTraversed = (traversedEdges.count(edge) > 0);

                if (isTraversed && isBridge) {
                    lineColor = ColorAlpha(RED, 0.95f);
                } else if (isTraversed) {
                    lineColor = ColorAlpha(YELLOW, 0.92f);
                }
                DrawLineEx(mapIslands[i].position, mapIslands[j].position, 3.0f, lineColor);
            }
        }
    }

    // Vẽ đảo
    float imgSize = 110.0f;
    for (int i = 0; i < 10; i++) {
        Vector2 pos = mapIslands[i].position;
        bool isVisited = visitedIslands.count(i) > 0;

        Color tintColor = WHITE;
        if (isVisited) tintColor = ColorAlpha(YELLOW, 0.95f);
        if (i == currentVisitingIsland) tintColor = ColorAlpha(LIME, 0.95f);

        if (islandTextures[i].id > 0) {
            DrawTexturePro(islandTextures[i],
                (Rectangle){ 0, 0, (float)islandTextures[i].width, (float)islandTextures[i].height },
                (Rectangle){ pos.x - imgSize/2, pos.y - imgSize/2, imgSize, imgSize },
                (Vector2){ 0, 0 }, 0.0f, tintColor);
        } else {
            DrawCircleV(pos, imgSize/2, tintColor);
        }

        if (collectedSpecialties[i]) {
            DrawCircleLinesV(pos, imgSize/2 + 13, ORANGE);
        }

        if (i == currentVisitingIsland) {
            float ringRadius = imgSize/2 + 20 + std::sin(pulseTimer * 8.0f) * 5.0f;
            DrawCircleLines((int)pos.x, (int)pos.y, ringRadius, GOLD);
        }

        DrawText(mapIslands[i].name.c_str(), pos.x - MeasureText(mapIslands[i].name.c_str(), 16)/2, pos.y + imgSize/2 + 15, 16, RAYWHITE);
    }

    // Vẽ nhân vật di chuyển
    
    if (isTraveling || !traversalPath.empty()) {
        /* DrawCircleV(travelerPosition, 12, GOLD); */ // Vòng tròn cũ - Đã đóng ghi chú
        
        // --- PHẦN THÊM MỚI: VẼ THUYỀN ---
        float scale = 0.35f; // Bạn có thể điều chỉnh 0.3f -> 0.5f tùy kích thước ảnh thuyen1.png
        Rectangle source = { 0, 0, (float)shipTexture.width, (float)shipTexture.height };
        Rectangle dest = { travelerPosition.x, travelerPosition.y, shipTexture.width * scale, shipTexture.height * scale };
        Vector2 origin = { (shipTexture.width * scale) / 2, (shipTexture.height * scale) / 2 };
        
        DrawTexturePro(shipTexture, source, dest, origin, 0.0f, WHITE);
        // --------------------------------

        // Giữ nguyên các hiệu ứng vòng sáng và ký hiệu liên quan bên dưới
        DrawCircleLines((int)travelerPosition.x, (int)travelerPosition.y, 16, ORANGE);
        DrawText("*", (int)travelerPosition.x - 5, (int)travelerPosition.y - 8, 20, MAROON);
    }

    if (arrivalEffectTimer > 0.0f && arrivalEffectIsland >= 0) {
        Vector2 fxPos = mapIslands[arrivalEffectIsland].position;
        float t = 1.0f - (arrivalEffectTimer / 1.6f);

        if (arrivalHasArticulation) {
            float radius = 82.0f + t * 72.0f;
            DrawCircleLines((int)fxPos.x, (int)fxPos.y, radius, ColorAlpha(ORANGE, 0.98f - t * 0.72f));
            DrawCircleLines((int)fxPos.x, (int)fxPos.y, radius - 15.0f, ColorAlpha(GOLD, 0.95f - t * 0.78f));
            DrawCircleLines((int)fxPos.x, (int)fxPos.y, radius - 30.0f, ColorAlpha(YELLOW, 0.9f - t * 0.82f));
            DrawText("+ DAC SAN", (int)fxPos.x - 66, (int)fxPos.y - 115, 28, GOLD);
        }

        if (arrivalHasBridge) {
            float radius = 72.0f + t * 92.0f;
            DrawCircleLines((int)fxPos.x, (int)fxPos.y, radius, ColorAlpha(RED, 0.98f - t * 0.72f));
            DrawCircleLines((int)fxPos.x, (int)fxPos.y, radius - 18.0f, ColorAlpha(ORANGE, 0.9f - t * 0.8f));
            if (travelingFrom >= 0) {
                Vector2 prevPos = mapIslands[travelingFrom].position;
                DrawLineEx(prevPos, fxPos, 10.0f, ColorAlpha(RED, 0.95f - t * 0.78f));
            }
            DrawText("+ CHIA KHOA", (int)fxPos.x - 74, (int)fxPos.y - 78, 26, RED);
        }
    }

    if (keyFlyActive && keyTexture.id > 0) {
        float t = keyFlyProgress;
        float ease = t * t * (3.0f - 2.0f * t);
        Vector2 cur = {
            keyFlyFrom.x + (keyFlyTo.x - keyFlyFrom.x) * ease,
            keyFlyFrom.y + (keyFlyTo.y - keyFlyFrom.y) * ease - 35.0f * std::sin(ease * 3.14159f)
        };
        float size = 30.0f - 8.0f * ease;
        DrawTexturePro(keyTexture,
            (Rectangle){ 0, 0, (float)keyTexture.width, (float)keyTexture.height },
            (Rectangle){ cur.x - size / 2.0f, cur.y - size / 2.0f, size, size },
            (Vector2){ 0, 0 },
            0.0f,
            ColorAlpha(WHITE, 1.0f - 0.05f * ease));
        DrawCircleLines((int)cur.x, (int)cur.y, 18.0f - 8.0f * ease, ColorAlpha(SKYBLUE, 0.9f - 0.5f * ease));
    }

    if (specialtyFlyActive) {
        int flyIndex = playerRewards.articulation_points - 1;
        Vector2 targetSlot = GetSpecialtySlotPosition(flyIndex);
        float t = specialtyFlyProgress;
        float ease = t * t * (3.0f - 2.0f * t);
        Vector2 cur = {
            specialtyFlyFrom.x + (targetSlot.x - specialtyFlyFrom.x) * ease,
            specialtyFlyFrom.y + (targetSlot.y - specialtyFlyFrom.y) * ease - 45.0f * std::sin(ease * 3.14159f)
        };
        float size = 34.0f - 10.0f * ease;
        DrawTexturePro(specialtyTextures[flyIndex],
            (Rectangle){ 0, 0, (float)specialtyTextures[flyIndex].width, (float)specialtyTextures[flyIndex].height },
            (Rectangle){ cur.x - size / 2.0f, cur.y - size / 2.0f, size, size },
            (Vector2){ 0, 0 },
            0.0f,
            ColorAlpha(WHITE, 1.0f - 0.05f * ease));
        DrawCircleLines((int)cur.x, (int)cur.y, 20.0f - 8.0f * ease, ColorAlpha(GOLD, 0.95f - 0.55f * ease));
    }

    // Vẽ popup nhận thưởng
    if (rewardPopupTimer > 0.0f && !rewardPopupText.empty()) {
        int alpha = (int)(220.0f * (rewardPopupTimer > 0.4f ? 1.0f : (rewardPopupTimer / 0.4f)));
        DrawRectangleRounded((Rectangle){ 150, 18, 840, 96 }, 0.25f, 8, ColorAlpha(BLACK, alpha / 255.0f));
        DrawRectangleLinesEx((Rectangle){ 150, 18, 840, 96 }, 3, ColorAlpha(GOLD, alpha / 255.0f));
        DrawText(rewardPopupText.c_str(), 174, 38, 28, ColorAlpha(GOLD, alpha / 255.0f));
        if (!rewardPopupDetailText.empty()) {
            DrawText(rewardPopupDetailText.c_str(), 174, 74, 18, ColorAlpha(RAYWHITE, alpha / 255.0f));
        }
    }
}

// Kết quả
void DrawResultScreen() {
    if (tutorialBgTexture.id > 0) {
        DrawTexturePro(tutorialBgTexture, (Rectangle){ 0, 0, (float)tutorialBgTexture.width, (float)tutorialBgTexture.height },
                       (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    } else {
        DrawTexturePro(bgTexture, (Rectangle){ 0, 0, (float)bgTexture.width, (float)bgTexture.height },
                       (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.40f));

    bool isWin = (playerRewards.articulation_points >= rewardTargets.articulation_points &&
                  playerRewards.bridges >= rewardTargets.bridges);

    if (isWin) {
        DrawText("THANG! - KHO BAU DA MO", GetScreenWidth()/2 - MeasureText("THANG! - KHO BAU DA MO", 40)/2, 150, 40, GOLD);
        DrawRectangle(GetScreenWidth()/2 - 200, 250, 400, 300, ColorAlpha(DARKGREEN, 0.7f));
    } else {
        DrawText("THUA! - KHO BAU CHUA MO", GetScreenWidth()/2 - MeasureText("THUA! - KHO BAU CHUA MO", 40)/2, 150, 40, RED);
        DrawRectangle(GetScreenWidth()/2 - 200, 250, 400, 300, ColorAlpha(MAROON, 0.7f));
    }

    if (chestTexture.id > 0) {
        DrawTexturePro(chestTexture,
            (Rectangle){ 0, 0, (float)chestTexture.width, (float)chestTexture.height },
            (Rectangle){ (float)GetScreenWidth()/2 - 90, 255, 180, 120 },
            (Vector2){ 0, 0 },
            0.0f,
            isWin ? WHITE : ColorAlpha(GRAY, 0.75f));
    }

    int y = 290;
    DrawText(TextFormat("Dac san: %d/%d", playerRewards.articulation_points, rewardTargets.articulation_points), GetScreenWidth()/2 - 150, y, 20, SKYBLUE);
    DrawText(TextFormat("Chia khoa: %d/%d", playerRewards.bridges, rewardTargets.bridges), GetScreenWidth()/2 - 150, y + 40, 20, SKYBLUE);
    DrawText(TextFormat("Tong tham: %d dao", (int)visitedIslands.size()), GetScreenWidth()/2 - 150, y + 80, 20, RAYWHITE);
    const char* algoName = "DFS";
    DrawText(TextFormat("Thuat toan: %s", algoName), GetScreenWidth()/2 - 150, y + 120, 20, RAYWHITE);

    if (DrawMenuButton({ (float)GetScreenWidth()/2 - 100, 650, 200, 50 }, "MENU CHINH", BLUE, DARKBLUE)) {
        selectedAlgorithm = NONE;
        ResetRunState();
        currentScreen = MENU;
    }
}

// Hướng dẫn
void DrawInstructions() {
    if (tutorialBgTexture.id > 0) {
        DrawTexturePro(tutorialBgTexture, (Rectangle){ 0, 0, (float)tutorialBgTexture.width, (float)tutorialBgTexture.height },
                       (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    } else {
        DrawTexturePro(bgTexture, (Rectangle){ 0, 0, (float)bgTexture.width, (float)bgTexture.height },
                       (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.45f));
    DrawText("HUONG DAN TRO CHOI", GetScreenWidth()/2 - MeasureText("HUONG DAN TRO CHOI", 30)/2, 100, 30, GOLD);
    
    int startY = 200;
    DrawText("- Chon DFS de chay thuat toan", 150, startY, 18, RAYWHITE);
    DrawText("- Chon mot hon dao de bat dau tham", 150, startY + 35, 18, RAYWHITE);
    DrawText("- Game tu dong chay qua tung dao theo DFS", 150, startY + 70, 18, RAYWHITE);
    DrawText("- Den dao la dinh cat: nhan dac san cua dao do", 150, startY + 105, 18, RAYWHITE);
    DrawText("- Di qua canh cau: nhan 1 chia khoa kho bau", 150, startY + 140, 18, RAYWHITE);
    DrawText("- Thu du dac san + chia khoa theo muc tieu de WIN", 150, startY + 175, 18, GOLD);

    if (DrawMenuButton({ (float)GetScreenWidth()/2 - 100, 600, 200, 50 }, "DA HIEU", RED, MAROON)) {
        currentScreen = MENU;
    }
}

// Giải phóng bộ nhớ
void CloseGameMap() {
    UnloadTexture(bgTexture);
    UnloadTexture(menuBg);
    UnloadTexture(tutorialBgTexture);
    UnloadTexture(panelTexture);
    UnloadTexture(buttonTexture);
    UnloadTexture(bagTexture);
    UnloadTexture(keyTexture);
    UnloadTexture(completeKeyTexture);
    UnloadTexture(chestTexture);
    for (int i = 0; i < 10; i++) {
        UnloadTexture(islandTextures[i]);
        UnloadTexture(specialtyTextures[i]);
    }

    CloseGameAudio();
}

void CloseGameAudio() {
    if (!audioReady) {
        return;
    }

    if (bgmMusicLoaded) {
        StopMusicStream(bgmMusic);
        UnloadMusicStream(bgmMusic);
        bgmMusicLoaded = false;
    }
    if (uiClickSfxLoaded) {
        UnloadSound(uiClickSfx);
        uiClickSfxLoaded = false;
    }
    if (rewardSpecialtySfxLoaded) {
        UnloadSound(rewardSpecialtySfx);
        rewardSpecialtySfxLoaded = false;
    }
    if (rewardKeySfxLoaded) {
        UnloadSound(rewardKeySfx);
        rewardKeySfxLoaded = false;
    }
    if (rewardComboSfxLoaded) {
        UnloadSound(rewardComboSfx);
        rewardComboSfxLoaded = false;
    }

    CloseAudioDevice();
    audioReady = false;
}

#endif