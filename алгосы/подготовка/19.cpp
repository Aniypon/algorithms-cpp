#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 505;
vector<vector<int>> graph(MAXN);
vector<bool> visited(MAXN, false);
vector<int> parent(MAXN, -1);
int cycle_start, cycle_end;

bool dfs(int v, int par) {
    visited[v] = true;

    for (int to : graph[v]) {
        if (to == par)
            continue;

        if (visited[to]) {
            // Нашли цикл
            cycle_start = to;
            cycle_end = v;
            return true;
        }

        parent[to] = v;

        if (dfs(to, v)) {
            return true;
        }
    }

    return false;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Заполняем список смежности из матрицы смежности
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            if (x == 1 && i < j) {  // Добавляем ребро только один раз
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    // Ищем цикл
    cycle_start = -1;

    for (int i = 1; i <= n; i++) {
        if (!visited[i] && dfs(i, -1)) {
            break;
        }
    }

    if (cycle_start == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;

        // Восстанавливаем цикл
        vector<int> cycle;е
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle.push_back(v);
        }

        cout << cycle.size() << endl;
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}