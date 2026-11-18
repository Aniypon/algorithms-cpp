#include <bits/stdc++.h>
using namespace std;

#define int long long

bool dfs(int v, vector<vector<int>>& graph, vector<bool>& used, vector<int>& matching) {
    if (used[v])
        return false;
    used[v] = true;

    for (int cube : graph[v]) {
        if (matching[cube] == -1 || dfs(matching[cube], graph, used, matching)) {
            matching[cube] = v;
            return true;
        }
    }
    return false;
}

int32_t main() {
    int n;
    cin >> n;

    string name;
    cin >> name;

    int m = name.size();

    vector<string> cubes(n);
    for (int i = 0; i < n; i++) {
        cin >> cubes[i];
    }

    vector<vector<int>> graph(m);

    for (int pos = 0; pos < m; pos++) {
        char letter = name[pos];
        for (int cubeIdx = 0; cubeIdx < n; cubeIdx++) {
            bool hasLetter = false;
            for (char c : cubes[cubeIdx]) {
                if (c == letter) {
                    hasLetter = true;
                    break;
                }
            }
            if (hasLetter) {
                graph[pos].push_back(cubeIdx);
            }
        }
    }

    vector<int> matching(n, -1);
    int matchingSize = 0;

    for (int pos = 0; pos < m; pos++) {
        vector<bool> used(m, false);
        if (dfs(pos, graph, used, matching)) {
            matchingSize++;
        }
    }

    if (matchingSize == m) {
        cout << "YES" << endl;

        vector<int> result(m);
        for (int cube = 0; cube < n; cube++) {
            if (matching[cube] != -1) {
                result[matching[cube]] = cube + 1;
            }
        }

        for (int i = 0; i < m; i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}