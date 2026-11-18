#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    int k;
    cin >> k;
    while (k--) {
        int s, t;
        cin >> s >> t;
        vector<int> dist(n + 1, INF);
        dist[s] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, s});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u])
                continue;
            if (u == t)
                break;
            for (auto &edge : graph[u]) {
                int v = edge.first, w = edge.second;
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        cout << (dist[t] == INF ? -1 : dist[t]) << "\n";
    }
    return 0;
}