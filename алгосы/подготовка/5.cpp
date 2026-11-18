#include <bits/stdc++.h>
using namespace std;

#define int long long

bool canCut(vector<int>& wires, int k, int len) {
    if (len == 0)
        return false;

    int count = 0;
    for (int wire : wires) {
        count += wire / len;
    }
    return count >= k;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> wires(n);
    for (int i = 0; i < n; i++) {
        cin >> wires[i];
    }


    int left = 1; 
    int right = *max_element(wires.begin(), wires.end()); 
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (canCut(wires, k, mid)) {
            // Если можно нарезать k отрезков длины mid,
            // сохраняем этот результат и пробуем больше
            result = mid;
            left = mid + 1;
        } else {
            // Иначе пробуем меньшую длину
            right = mid - 1;
        }
    }

    cout << result << endl;

    return 0;
}