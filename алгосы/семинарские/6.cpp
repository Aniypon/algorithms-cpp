#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Edge {
    int u, v, w;
};

int find(int a, vector<int> &parent) {
    return parent[a] == a ? a : parent[a] = find(parent[a], parent);
}

void unionSets(int a, int b, vector<int> &parent) {
    a = find(a, parent);
    b = find(b, parent);
    if (a != b)
        parent[b] = a;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    vector<vector<int>> conn(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> conn[i][j];
        }
    }

    vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // Объединяем вершины, которые уже соединены в графе
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (conn[i][j] == 1) {
                unionSets(i, j, parent);
            }
        }
    }

    // Формируем список потенциальных ребер между различными компонентами
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (find(i, parent) != find(j, parent)) {
                edges.push_back({i, j, cost[i][j]});
            }
        }
    }

    // Сортируем ребра по стоимости
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) { return a.w < b.w; });

    int ans = 0;
    for (auto &e : edges) {
        if (find(e.u, parent) != find(e.v, parent)) {
            unionSets(e.u, e.v, parent);
            ans += e.w;
        }
    }

    cout << ans;
    return 0;
}