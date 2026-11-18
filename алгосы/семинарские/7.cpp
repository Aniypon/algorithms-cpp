#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

struct Edge {
    int to, w;
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> type(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> type[i];
    }
    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // соединение можно прокладывать в обоих направлениях
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    // Мультиисходовая Дейкстра от городов с дата-центром Laim.UR (type==1)
    vector<int> dist(n + 1, INF);
    vector<int> source(n + 1, -1);  // откуда начат путь (город с Laim.UR)

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 1; i <= n; i++) {
        if (type[i] == 1) {
            dist[i] = 0;
            source[i] = i;
            pq.push({0, i});
        }
    }

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u])
            continue;
        for (auto &e : graph[u]) {
            int v = e.to;
            int nd = d + e.w;
            if (nd < dist[v]) {
                dist[v] = nd;
                source[v] = source[u];
                pq.push({nd, v});
            }
        }
    }

    int bestCost = INF, bestL = -1, bestX = -1;
    for (int i = 1; i <= n; i++) {
        if (type[i] == 2 && dist[i] < bestCost) {
            bestCost = dist[i];
            bestL = source[i];  // город с Laim.UR
            bestX = i;          // город с Xenda
        }
    }

    if (bestCost == INF)
        cout << -1 << "\n";
    else
        cout << bestL << " " << bestX << " " << bestCost << "\n";

    return 0;
}