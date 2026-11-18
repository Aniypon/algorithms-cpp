#include <bits/stdc++.h>
using namespace std;

#define int long long

bool dfs(int v, vector<vector<int>>& graph, vector<bool>& used, vector<int>& matching) {
    if (used[v])
        return false;
    used[v] = true;

    for (int to : graph[v]) {
        if (matching[to] == -1 || dfs(matching[to], graph, used, matching)) {
            matching[to] = v;
            return true;
        }
    }
    return false;
}

int32_t main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);

    for (int i = 1; i <= n; i++) {
        int v;
        while (cin >> v && v != 0) {
            graph[i].push_back(v);
        }
    }
    vector<int> matching(m + 1, -1);

    int matchingSize = 0;
    for (int v = 1; v <= n; v++) {
        vector<bool> used(n + 1, false);
        if (dfs(v, graph, used, matching)) {
            matchingSize++;
        }
    }

    cout << matchingSize << endl;
    for (int j = 1; j <= m; j++) {
        if (matching[j] != -1) {
            cout << matching[j] << " " << j << endl;
        }
    }

    return 0;
}