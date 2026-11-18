#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Trip {
    int from, dep, to, arr;
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int start, finish;
    cin >> start >> finish;
    int r;
    cin >> r;

    vector<Trip> trips(r);
    for (int i = 0; i < r; i++) {
        cin >> trips[i].from >> trips[i].dep >> trips[i].to >> trips[i].arr;
    }

    // Инициализация времени прибытия: INF означает недостижимость
    const int INF = 1e18;
    vector<int> best(n + 1, INF);
    best[start] = 0;

    // Так как автобусные рейсы можно использовать в любую последующую минуту,
    // необходимо несколько раз пройтись по всем рейсам для релаксации.
    // Количество итераций ограничено количеством деревень.
    for (int iter = 0; iter < n - 1; iter++) {
        bool updated = false;
        for (auto &trip : trips) {
            if (best[trip.from] <= trip.dep && best[trip.to] > trip.arr) {
                best[trip.to] = trip.arr;
                updated = true;
            }
        }
        if (!updated)
            break;
    }

    if (best[finish] == INF)
        cout << -1;
    else
        cout << best[finish];

    return 0;
}
