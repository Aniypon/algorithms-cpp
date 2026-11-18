#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Edge {
    int u, v, L, idx;
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].L;
        edges[i].idx = i + 1;
    }

    int P5, Q5, P6, Q6;
    cin >> P5 >> Q5 >> P6 >> Q6;

    // Определяем кабель с меньшей ценой как "дешёвый" (cheap) и второй как "дорогой" (expensive)
    int cheapType, expensiveType;
    int cheapPrice, expensivePrice, cheapQ, expensiveQ;
    if (P5 <= P6) {
        cheapType = 5;
        expensiveType = 6;
        cheapPrice = P5;
        expensivePrice = P6;
        cheapQ = Q5;
        expensiveQ = Q6;
    } else {
        cheapType = 6;
        expensiveType = 5;
        cheapPrice = P6;
        expensivePrice = P5;
        cheapQ = Q6;
        expensiveQ = Q5;
    }

    cout << "Impossible";

    return 0;
}