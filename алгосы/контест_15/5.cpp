#include <bits/stdc++.h>
using namespace std;

#define int long long

int timer;
vector<int> disc, low, parent;
vector<bool> isAP;
vector<vector<int>> g;

void dfs(int u) {
    disc[u] = low[u] = ++timer;
    int children = 0;
    for (int v : g[u]) {
        if (disc[v] == 0) {
            parent[v] = u;
            children++;
            dfs(v);
            low[u] = min(low[u], low[v]);
            if (parent[u] == -1 && children > 1)
                isAP[u] = true;
            if (parent[u] != -1 && low[v] >= disc[u])
                isAP[u] = true;
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    int total = N + M;
    g.resize(total + 1);
    for (int i = 1; i <= M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        int nodeP = N + i;

        g[a].push_back(nodeP);
        g[nodeP].push_back(a);
        g[b].push_back(nodeP);
        g[nodeP].push_back(b);
        g[c].push_back(nodeP);
        g[nodeP].push_back(c);
    }

    disc.assign(total + 1, 0);
    low.assign(total + 1, 0);
    parent.assign(total + 1, -1);
    isAP.assign(total + 1, false);
    timer = 0;

    for (int i = 1; i <= total; i++) {
        if (disc[i] == 0)
            dfs(i);
    }

    vector<int> ans;
    for (int i = 1; i <= M; i++) {
        int nodeP = N + i;
        if (isAP[nodeP])
            ans.push_back(i);
    }

    cout << ans.size() << "\n";
    for (int num : ans)
        cout << num << "\n";

    return 0;
}