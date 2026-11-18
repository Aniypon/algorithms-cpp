#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, s, m;
    cin >> n >> s >> m;
    vector<vector<int>> rev(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        rev[b].push_back(a);
    }
    
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int nxt : rev[cur]) {
            if (dist[nxt] == -1) {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    return 0;
}