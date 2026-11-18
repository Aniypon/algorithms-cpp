#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>(n, 0));
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u-1][v-1] = 1;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adj[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}