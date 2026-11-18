#include <bits/stdc++.h>
using namespace std;

#define int long long

struct SegmentTree {
    vector<int> min_val, max_val, lazy;
    int size;

    SegmentTree(int n) {
        size = 1;
        while (size < n)
            size *= 2;
        min_val.resize(2 * size);
        max_val.resize(2 * size);
        lazy.resize(2 * size, 0);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) {
                min_val[x] = max_val[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        min_val[x] = min(min_val[2 * x + 1], min_val[2 * x + 2]);
        max_val[x] = max(max_val[2 * x + 1], max_val[2 * x + 2]);
    }

    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void push(int x) {
        if (lazy[x] != 0) {
            min_val[2 * x + 1] += lazy[x];
            max_val[2 * x + 1] += lazy[x];
            min_val[2 * x + 2] += lazy[x];
            max_val[2 * x + 2] += lazy[x];

            lazy[2 * x + 1] += lazy[x];
            lazy[2 * x + 2] += lazy[x];
            lazy[x] = 0;
        }
    }

    void update(int l, int r, int v, int x, int lx, int rx) {
        if (lx >= r || rx <= l)
            return;
        if (lx >= l && rx <= r) {
            min_val[x] += v;
            max_val[x] += v;
            lazy[x] += v;
            return;
        }
        push(x);
        int m = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, m);
        update(l, r, v, 2 * x + 2, m, rx);
        min_val[x] = min(min_val[2 * x + 1], min_val[2 * x + 2]);
        max_val[x] = max(max_val[2 * x + 1], max_val[2 * x + 2]);
    }

    void update(int l, int r, int v) {
        update(l, r, v, 0, 0, size);
    }

    bool hasValue(int l, int r, int v, int x, int lx, int rx) {
        if (lx >= r || rx <= l)
            return false;
        if (min_val[x] > v || max_val[x] < v)
            return false;
        if (rx - lx == 1) {
            return min_val[x] == v;
        }
        push(x);
        int m = (lx + rx) / 2;
        return hasValue(l, r, v, 2 * x + 1, lx, m) || hasValue(l, r, v, 2 * x + 2, m, rx);
    }

    bool hasValue(int l, int r, int v) {
        return hasValue(l, r, v, 0, 0, size);
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    SegmentTree st(n);
    st.build(heights);

    for (int i = 0; i < m; i++) {
        char type;
        cin >> type;

        if (type == '+') {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            st.update(l, r, x);
        } else if (type == '?') {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            if (st.hasValue(l, r, x)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}