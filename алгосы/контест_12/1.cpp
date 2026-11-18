#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;

int32_t main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> capacity(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; ++i) {
        int u, v, cap;
        cin >> u >> v >> cap;
        capacity[u][v] += cap;
    }

    int max_flow = 0;
    vector<vector<int>> flow(n + 1, vector<int>(n + 1, 0));

    while (true) {
        vector<int> parent(n + 1, -1);
        queue<int> q;
        q.push(1);
        parent[1] = 0;

        while (!q.empty() && parent[n] == -1) {
            int u = q.front();
            q.pop();

            for (int v = 1; v <= n; ++v) {
                if (parent[v] == -1 && capacity[u][v] > flow[u][v]) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        if (parent[n] == -1)
            break;

        int path_flow = INF;
        for (int v = n; v != 1; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, capacity[u][v] - flow[u][v]);
        }

        for (int v = n; v != 1; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += path_flow;
            flow[v][u] -= path_flow;
        }

        max_flow += path_flow;
    }

    cout << max_flow << endl;

    return 0;
}