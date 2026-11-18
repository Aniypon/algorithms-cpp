#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    set<int> numbers;
    int n, s = 0;

    cin >> n;

    char operation;
    int val1, val2;

    for (int i = 0; i < n; ++i) {
        cin >> operation;

        if (operation == '+') {
            cin >> val1;
            numbers.insert((val1 + s) % 1000000001);
        } else if (operation == '-') {
            cin >> val1;
            numbers.erase((val1 + s) % 1000000001);
        } else if (operation == '?') {
            cin >> val1;
            cout << (numbers.count((val1 + s) % 1000000001) ? "Found" : "Not found") << "\n";
        } else {
            cin >> val1 >> val2;
            int f_left = (val1 + s) % 1000000001;
            int f_right = (val2 + s) % 1000000001;

            s = 0;

            for (auto it = numbers.lower_bound(f_left); it != numbers.end() && *it <= f_right; ++it) {
                s += *it;
            }

            cout << s << "\n";
        }
    }

    return 0;
}