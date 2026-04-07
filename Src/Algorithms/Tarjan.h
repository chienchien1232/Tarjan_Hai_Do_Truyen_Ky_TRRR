#ifndef TARJAN_H
#define TARJAN_H

#include <vector>
#include <set>
#include <algorithm>

// Tìm Articulation Point (Cut Vertex) bằng Tarjan
class TarjanAlgorithm {
private:
    std::vector<std::vector<int>> adj;
    std::vector<bool> visited;
    std::vector<int> disc, low, parent;
    std::set<int> articulationPoints;
    std::set<std::pair<int, int>> bridges;
    int timer;
    int n;

    void dfs(int u) {
        visited[u] = true;
        disc[u] = low[u] = timer++;
        int children = 0;

        for (int v : adj[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                dfs(v);
                low[u] = std::min(low[u], low[v]);

                // u là articulation point nếu:
                // 1. u là root có >= 2 children
                // 2. u không là root, low[v] >= disc[u]
                if ((parent[u] == -1 && children > 1) || 
                    (parent[u] != -1 && low[v] >= disc[u])) {
                    articulationPoints.insert(u);
                }

                // Kiểm tra bridge
                if (low[v] > disc[u]) {
                    bridges.insert({std::min(u, v), std::max(u, v)});
                }
            } else if (v != parent[u]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }
    }

public:
    TarjanAlgorithm(int n, const int graph[10][10]) : n(n), timer(0) {
        adj.resize(n);
        visited.assign(n, false);
        disc.assign(n, -1);
        low.assign(n, -1);
        parent.assign(n, -1);

        // Xây dựng adjacency list từ graph
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (graph[i][j] == 1) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
    }

    void findArticulationPoints() {
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i);
            }
        }
    }

    bool isArticulationPoint(int node) const {
        return articulationPoints.count(node) > 0;
    }

    bool isBridge(int u, int v) const {
        if (u > v) std::swap(u, v);
        return bridges.count({u, v}) > 0;
    }

    std::set<int> getArticulationPoints() const {
        return articulationPoints;
    }

    std::set<std::pair<int, int>> getBridges() const {
        return bridges;
    }
};

// DFS Traversal từ start node
class DFSTraversal {
private:
    std::vector<std::vector<int>> adj;
    std::vector<bool> visited;
    std::vector<int> traversalOrder;
    std::vector<int> parent;

    void dfs(int u) {
        visited[u] = true;
        traversalOrder.push_back(u);

        for (int v : adj[u]) {
            if (!visited[v]) {
                parent[v] = u;
                dfs(v);
            }
        }
    }

public:
    DFSTraversal(int n, const int graph[10][10], int startNode) {
        adj.resize(n);
        visited.assign(n, false);
        parent.assign(n, -1);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (graph[i][j] == 1) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        dfs(startNode);
    }

    std::vector<int> getTraversalOrder() const {
        return traversalOrder;
    }

    std::vector<int> getParentTree() const {
        return parent;
    }

    int getNextNode(int currentIndex) const {
        if (currentIndex + 1 < traversalOrder.size()) {
            return traversalOrder[currentIndex + 1];
        }
        return -1;
    }
};

#endif
