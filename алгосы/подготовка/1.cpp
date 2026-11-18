#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    unordered_map<int, int> mp;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        mp[temp]++;
    }

    for (auto it : mp) {
        if (it.second == 1 or it.second == 2) {
            cout << it.first << " " << it.second << endl;
            break;
        }
    }
}
