#include <bits/stdc++.h>
using namespace std;

#define int long long

int N, M, S, E;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> disc, low;
vector<bool> containsE;
int timer = 0;
vector<bool> mustRepeat;  // флаг для вершин, которые обязательно встречаются дважды

void dfs(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = ++timer;
    // Если u является E, то имеем признак, что E обнаружена в данной ветке
    containsE[u] = (u == E);
    int childCount = 0;

    for (int v : adj[u]) {
        if (v == parent)
            continue;
        if (!visited[v]) {
            childCount++;
            dfs(v, u);
            containsE[u] = containsE[u] || containsE[v];
            low[u] = min(low[u], low[v]);
            // Если u не является S и E обнаружена в поддереве v, то проверяем условие артикуляционности
            if (u != S && containsE[v] && low[v] >= disc[u])
                mustRepeat[u] = true;
            // Для S, если найдётся более одного ребенка, ведущего к E, то S является точкой разрыва,
            // но согласно условию S не выводим.
        } else {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    adj.resize(N + 1);
    visited.assign(N + 1, false);
    disc.assign(N + 1, 0);
    low.assign(N + 1, 0);
    containsE.assign(N + 1, false);
    mustRepeat.assign(N + 1, false);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        // так как граф неориентированный
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> S >> E;

    dfs(S, -1);

    vector<int> answer;
    for (int i = 1; i <= N; i++) {
        // S и E не включаем
        if (i == S || i == E)
            continue;
        if (mustRepeat[i])
            answer.push_back(i);
    }
    sort(answer.begin(), answer.end());
    cout << answer.size() << "\n";
    for (int v : answer)
        cout << v << "\n";

    return 0;
}