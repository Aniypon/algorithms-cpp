#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;

struct Edge {
    int to, cap, flow, rev;
    Edge(int t, int c, int f, int r) : to(t), cap(c), flow(f), rev(r) {
    }
};

int32_t main() {
    int n, m, a, h;
    cin >> n >> m >> a >> h;

    vector<vector<Edge>> graph(n + 1);

    auto add_edge = [&](int from, int to) {
        graph[from].push_back(Edge(to, 1, 0, graph[to].size()));
        graph[to].push_back(Edge(from, 0, 0, graph[from].size() - 1));
    };

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        add_edge(x, y);
    }

    int max_flow = 0;
    while (max_flow < 2) {
        vector<int> parent(n + 1, -1);
        vector<int> edge_idx(n + 1, -1);
        queue<int> q;
        q.push(a);
        parent[a] = 0;

        while (!q.empty() && parent[h] == -1) {
            int v = q.front();
            q.pop();

            for (int i = 0; i < graph[v].size(); ++i) {
                Edge& e = graph[v][i];
                if (parent[e.to] == -1 && e.flow < e.cap) {
                    parent[e.to] = v;
                    edge_idx[e.to] = i;
                    q.push(e.to);
                }
            }
        }

        if (parent[h] == -1)
            break;

        int v = h;
        while (v != a) {
            int u = parent[v];
            int idx = edge_idx[v];
            graph[u][idx].flow += 1;
            graph[v][graph[u][idx].rev].flow -= 1;
            v = u;
        }

        max_flow++;
    }

    if (max_flow < 2) {
        cout << "NO" << endl;
        return 0;
    }

    vector<vector<int>> paths(2);

    for (int path_idx = 0; path_idx < 2; ++path_idx) {
        int v = a;
        paths[path_idx].push_back(v);

        while (v != h) {
            for (auto& e : graph[v]) {
                if (e.flow == 1 && e.cap == 1) {
                    e.flow = 0;
                    v = e.to;
                    paths[path_idx].push_back(v);
                    break;
                }
            }
        }
    }

    cout << "YES" << endl;

    for (int i = 0; i < paths[0].size(); ++i) {
        cout << paths[0][i] << (i < paths[0].size() - 1 ? " " : "");
    }
    cout << endl;

    for (int i = 0; i < paths[1].size(); ++i) {
        cout << paths[1][i] << (i < paths[1].size() - 1 ? " " : "");
    }
    cout << endl;

    return 0;
}