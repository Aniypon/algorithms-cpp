#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> grid[i][j];

    vector<vector<int>> dist(N, vector<int>(M, LLONG_MAX));

    // Очередь для BFS
    queue<pair<int, int>> q;

    // Инициализируем BFS со всех клеток, в которых записана 1
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 1) {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    // Направления для перемещения (вверх, вниз, влево, вправо)
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    // BFS
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                if (dist[nx][ny] > dist[x][y] + 1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    // Вывод результата
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
