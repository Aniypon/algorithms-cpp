#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Edge {
    int u, v, w, idx;
};

struct DSU {
    vector<int> parent, rank;
    DSU(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }
    int find(int a) {
        return parent[a] == a ? a : parent[a] = find(parent[a]);
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b)
            return false;
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
        return true;
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].idx = i;
    }

    // Сортируем рёбра по стоимости
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) { return a.w < b.w; });

    // Нахождение MST алгоритмом Крускала
    DSU dsu(N);
    int mstCost = 0;
    vector<int> mstEdges;  // индексы ребер, которые вошли в MST (индекс в массиве edges)
    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mstCost += e.w;
            mstEdges.push_back(e.idx);
        }
    }

    // Если MST не найден (граф не связный)
    if (mstEdges.size() != N - 1) {
        cout << "Impossible";
        return 0;
    }

    int secondCost = LLONG_MAX;

    // Для каждого ребра MST попробуем построить второй MST, исключив его
    for (auto skipIdx : mstEdges) {
        DSU dsu2(N);
        int cost = 0;
        int cnt = 0;
        for (auto &e : edges) {
            // Исключаем ребро, выбранное для исключения
            if (e.idx == skipIdx)
                continue;
            if (dsu2.unite(e.u, e.v)) {
                cost += e.w;
                cnt++;
                if (cnt == N - 1)
                    break;
            }
        }
        if (cnt == N - 1) {
            secondCost = min(secondCost, cost);
        }
    }

    cout << mstCost << " " << secondCost;

    return 0;
}