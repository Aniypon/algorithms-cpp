#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + (arr[i] == 0 ? 1 : 0);
    }

    int k;
    cin >> k;

    for (int i = 0; i < k; i++) {
        int l, r;
        cin >> l >> r;

        int zeros_count = prefix[r] - prefix[l - 1];
        
        cout << zeros_count;
        if (i < k - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
